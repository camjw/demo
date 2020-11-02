#include "model_importer.h"
#include "assimp_helper_functions.h"

#include <ecs/components/name_component.h>
#include <utility>
#include <utils/uuid.h>

void ModelImporter::load_fbx(const std::string& filename, SceneNode* scene_node, ModelImportOptions import_options)
{
    const aiScene* assimp_scene = assimp_importer.ReadFile(filename.c_str(),
        aiProcess_Triangulate
            | aiProcess_GenNormals
            | aiProcess_GenUVCoords
            | aiProcess_EmbedTextures);

    if (assimp_scene == nullptr)
    {
        printf("Failed to load file from %s\n", filename.c_str());
        return;
    }

    std::vector<MeshID> mesh_ids = build_meshes(assimp_scene);
    std::unordered_map<MeshID, MaterialID> mesh_to_material_map = build_materials(assimp_scene, mesh_ids);

    std::unordered_set<MeshID> used_meshes;
    attach_assimp_node_to_scene(assimp_scene->mRootNode, scene_node, mesh_ids, mesh_to_material_map);

    if (import_options.import_camera)
    {
        update_scene_camera(assimp_scene, scene_node);
    }

    build_lights(assimp_scene, scene_node);
}

void ModelImporter::update_scene_camera(const aiScene* assimp_scene, SceneNode* scene_node)
{
    const Scene& scene = scene_node->get_scene();

    Entity scene_camera_entity = scene.get_camera();

    if (assimp_scene->mNumCameras == 0)
    {
        printf("Couldn't find camera in import");
        return;
    }

    const aiCamera* first_camera = assimp_scene->mCameras[0];

    CameraComponent& scene_camera = world->get_component<CameraComponent>(scene_camera_entity);
    const aiVector3D camera_up = first_camera->mUp;
    const aiVector3D camera_forward = first_camera->mLookAt;

    scene_camera.up = AssimpHelperFunctions::to_float3(camera_up);
    scene_camera.forward = AssimpHelperFunctions::to_float3(camera_forward);
    scene_camera.right = float3::cross(scene_camera.forward, scene_camera.up);

    Transform& scene_camera_transform = world->get_component<Transform>(scene_camera_entity);
    const aiVector3D camera_position = first_camera->mPosition;
    scene_camera_transform.position = AssimpHelperFunctions::to_float3(camera_position);
}

void ModelImporter::attach_assimp_node_to_scene(const aiNode* assimp_node, SceneNode* scene_node, const std::vector<MeshID>& mesh_ids,
    const std::unordered_map<MeshID, MaterialID>& mesh_to_material_map) const
{
    if (assimp_node->mNumMeshes > 0)
    {
        populate_node(assimp_node, scene_node, mesh_ids, mesh_to_material_map);
    }

    for (unsigned int i = 0; i < assimp_node->mNumChildren; i++)
    {
        SceneNode* child_node = scene_node->add_child(world->create_empty_entity());
        attach_assimp_node_to_scene(assimp_node->mChildren[i], child_node, mesh_ids, mesh_to_material_map);
    }

    aiMatrix4x4 assimp_transform = assimp_node->mTransformation;
    Transform node_transform = AssimpHelperFunctions::to_transform(assimp_transform);

    world->get_or_add_component<Transform>(scene_node->get_entity(), node_transform);
}

void ModelImporter::populate_node(const aiNode* assimp_node, SceneNode* scene_node,
    const std::vector<MeshID>& mesh_ids, const std::unordered_map<MeshID, MaterialID>& mesh_to_materials_map) const
{
    int num_meshes = assimp_node->mNumMeshes;
    for (int i = 0; i < num_meshes; i++)
    {
        MeshID mesh_id = mesh_ids[assimp_node->mMeshes[i]];
        MaterialID material_id = mesh_to_materials_map.find(mesh_id)->second;

        scene_node->add_child(world->create_entity()
                                  ->with(MeshComponent(mesh_id))
                                  ->with(Transform::identity())
                                  ->with(MaterialComponent(material_id, OPAQUE))
                                  ->build());
    }

    world->add_component(scene_node->get_entity(), NameComponent {
                                                       .name = assimp_node->mName.C_Str(),
                                                   });
}

std::unordered_map<MeshID, MaterialID> ModelImporter::build_materials(const aiScene* assimp_scene, const std::vector<MeshID>& mesh_ids)
{
    unsigned int num_textures = assimp_scene->mNumTextures;
    std::unordered_map<std::string, TextureID> texture_ids;
    std::vector<TextureID> texture_ids_list;

    for (unsigned int i = 0; i < num_textures; i++)
    {
        aiTexture* assimp_texture = assimp_scene->mTextures[i];
        TextureID texture_id = texture_repository->create_texture(uuid::new_uuid(), assimp_texture);
        texture_ids.insert(std::pair<std::string, TextureID>(assimp_texture->mFilename.C_Str(), texture_id));
        texture_ids_list.push_back(texture_id);
    }

    unsigned int num_materials = assimp_scene->mNumMaterials;
    std::vector<MaterialID> material_ids(num_materials);

    ShaderID lighting_shader_id = shader_repository->get_shader_id("deferred_rendering");
    ShaderID simple_lighting_shader_id = shader_repository->get_shader_id("simple_lighting");

    for (unsigned int i = 0; i < assimp_scene->mNumMaterials; i++)
    {
        aiMaterial* assimp_material = assimp_scene->mMaterials[i];
        aiString material_name = assimp_material->GetName();

        Material material;
        if (assimp_material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
        {
            aiString texture_path;
            // This can fail but I think since we've already checked the texture count and we're getting the first one we don't need to double check
            assimp_material->GetTexture(aiTextureType_DIFFUSE, 0, &texture_path);
            TextureID diffuse_texture_id;
            if (texture_ids.find(texture_path.C_Str()) != texture_ids.end())
            {
                diffuse_texture_id = texture_ids.find(texture_path.C_Str())->second;
            }
            else
            {
                int texture_index = atoi(&texture_path.C_Str()[1]);
                if (texture_index < texture_ids_list.size())
                {
                    diffuse_texture_id = texture_ids_list[texture_index];
                }
                else
                {
                    diffuse_texture_id = texture_repository->create_texture(texture_path.C_Str(), texture_path.C_Str());
                }
            }

            TextureID specular_texture_id = INVALID_TEXTURE;
            if (assimp_material->GetTextureCount(aiTextureType_SPECULAR) > 0)
            {
                assimp_material->GetTexture(aiTextureType_SPECULAR, 0, &texture_path);
                if (texture_ids.find(texture_path.C_Str()) != texture_ids.end())
                {
                    specular_texture_id = texture_ids.find(texture_path.C_Str())->second;
                }
                else
                {
                    int texture_index = atoi(&texture_path.C_Str()[1]);
                    if (texture_index < texture_ids_list.size())
                    {
                        specular_texture_id = texture_ids_list[texture_index];
                    }
                    else
                    {
                        specular_texture_id = texture_repository->create_texture(texture_path.C_Str(), texture_path.C_Str());
                    }
                }
            }

            material = Material(lighting_shader_id, diffuse_texture_id, specular_texture_id, 1.0f);
        }
        else
        {
            material = Material(simple_lighting_shader_id);
        }

        aiColor4D assimp_ambient;
        if (assimp_material->Get(AI_MATKEY_COLOR_AMBIENT, assimp_ambient) == AI_SUCCESS)
        {
            material.ambient_colour = AssimpHelperFunctions::to_float3(assimp_ambient);
        }

        aiColor4D assimp_diffuse;
        if (assimp_material->Get(AI_MATKEY_COLOR_DIFFUSE, assimp_diffuse) == AI_SUCCESS)
        {
            material.diffuse_colour = AssimpHelperFunctions::to_float3(assimp_diffuse);
        }

        aiColor4D assimp_specular;
        if (assimp_material->Get(AI_MATKEY_COLOR_SPECULAR, assimp_specular) == AI_SUCCESS)
        {
            material.specular_colour = AssimpHelperFunctions::to_float3(assimp_specular);
        }

        ai_real assimp_shininess;
        if (assimp_material->Get(AI_MATKEY_MAPPING_SHININESS(0), assimp_shininess) == AI_SUCCESS)
        {
            material.shininess = assimp_shininess;
        }

        MaterialID new_material_id = material_repository->insert_material(material, material_name.C_Str());
        material_ids[i] = new_material_id;
    }

    std::unordered_map<MeshID, MaterialID> mesh_to_material_map;
    for (unsigned int i = 0; i < assimp_scene->mNumMeshes; i++)
    {
        mesh_to_material_map.insert(std::pair<MeshID, MaterialID>(mesh_ids[i], material_ids[assimp_scene->mMeshes[i]->mMaterialIndex]));
    }

    return mesh_to_material_map;
}

std::vector<MeshID> ModelImporter::build_meshes(const aiScene* assimp_scene)
{
    unsigned int num_meshes = assimp_scene->mNumMeshes;
    std::vector<MeshID> mesh_ids(num_meshes);

    for (unsigned int i = 0; i < num_meshes; i++)
    {
        const aiMesh* mesh = assimp_scene->mMeshes[i];
        unsigned int numVertices = mesh->mNumVertices;

        std::vector<float3> vertices(numVertices, float3::zero());
        std::vector<float3> normals(numVertices, float3::zero());
        std::vector<float2> uvs(numVertices, float2::zero());

        for (int j = 0; j < numVertices; j++)
        {
            vertices[j] = 0.01f * AssimpHelperFunctions::to_float3(mesh->mVertices[j]);
            normals[j] = AssimpHelperFunctions::to_float3(mesh->mNormals[j]);
        }

        if (mesh->HasTextureCoords(0))
        {
            for (int j = 0; j < numVertices; j++)
            {
                aiVector3D uv = mesh->mTextureCoords[0][j];
                uvs[j] = float2(uv.x, uv.y);
            }
        }

        unsigned int numFaces = mesh->mNumFaces;
        // Passed the triangulate flag so all faces should be tris
        std::vector<uint32_t> indices(3 * mesh->mNumFaces);

        for (unsigned int j = 0; j < numFaces; j++)
        {
            const aiFace face = mesh->mFaces[j];
            indices[3 * j] = face.mIndices[0];
            indices[3 * j + 1] = face.mIndices[1];
            indices[3 * j + 2] = face.mIndices[2];
        }

        mesh_ids[i] = mesh_repository->create_mesh(vertices, normals, uvs, indices);
        glCheckError();
    }

    return mesh_ids;
}

void ModelImporter::build_lights(const aiScene* assimp_scene, SceneNode* scene_node)
{
    SceneNode* lights_parent = scene_node->add_child(world->create_entity()
                                                         ->with(NameComponent { .name = "Lights" })
                                                         ->build());

    for (int i = 0; i < assimp_scene->mNumLights; i++)
    {
        aiLight* light = assimp_scene->mLights[i];

        aiNode* assimp_node = assimp_scene->mRootNode->FindNode(light->mName);
        Transform light_transform = assimp_node == nullptr ? Transform::identity() : AssimpHelperFunctions::to_transform(assimp_node->mTransformation);

        Entity light_entity = world->create_entity()
                                  ->with(light_transform)
                                  ->build();
        switch (light->mType)
        {
        case aiLightSource_POINT:
            add_point_light(light, light_entity);
            break;
        case aiLightSource_DIRECTIONAL:
            add_directional_light(light, light_entity);
            break;
        case aiLightSource_SPOT:
            add_spot_light(light, light_entity);
            break;
        case aiLightSource_UNDEFINED:
        case aiLightSource_AMBIENT:
        case aiLightSource_AREA:
        case _aiLightSource_Force32Bit:
            printf("Unhandled light type\n");
            break;
        }

        lights_parent->add_child(light_entity);
    }
}

void ModelImporter::add_directional_light(const aiLight* light, const Entity entity) const
{
    printf("Add directional light\n");
    DirectionalLight directional_light = DirectionalLight {
        .direction = AssimpHelperFunctions::to_float3(light->mDirection),
        .ambient = AssimpHelperFunctions::to_float3(light->mColorAmbient),
        .diffuse = AssimpHelperFunctions::to_float3(light->mColorDiffuse),
        .specular = AssimpHelperFunctions::to_float3(light->mColorSpecular),
    };

    world->add_component(entity, directional_light);
}

void ModelImporter::add_point_light(const aiLight* light, const Entity entity) const
{
    printf("Add point light\n");
    PointLight point_light = PointLight {
        .constant = light->mAttenuationConstant,
        .linear = light->mAttenuationLinear,
        .quadratic = light->mAttenuationQuadratic,
        .ambient = AssimpHelperFunctions::to_float3(light->mColorAmbient),
        .diffuse = AssimpHelperFunctions::to_float3(light->mColorDiffuse),
        .specular = AssimpHelperFunctions::to_float3(light->mColorSpecular),
    };

    world->add_component(entity, point_light);
}

void ModelImporter::add_spot_light(const aiLight* pLight, const Entity entity) const
{
    printf("Add spot light\n");
}
