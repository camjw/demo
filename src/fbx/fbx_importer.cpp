#include "fbx_importer.h"

#include <ecs/components/name_component.h>
#include <utility>

void FBXImporter::load_fbx(const std::string& filename, SceneNode* scene_node, FBXImportOptions import_options)
{
    const aiScene* assimp_scene = assimp_importer.ReadFile(filename.c_str(), aiProcess_Triangulate);

    if (assimp_scene == nullptr)
    {
        printf("Failed to load fbx from %s\n", filename.c_str());
        return;
    }

    std::vector<MeshID> mesh_ids = build_meshes(assimp_scene);
    printf("Imported %lu meshes from fbx\n", mesh_ids.size());
    std::vector<TextureID> texture_ids = build_textures(assimp_scene);

    std::unordered_set<MeshID> used_meshes;
    attach_assimp_node_to_scene(assimp_scene->mRootNode, scene_node, mesh_ids, texture_ids, used_meshes);

    printf("Used %lu meshes from fbx\n", used_meshes.size());

    if (import_options.import_camera)
    {
        update_scene_camera(assimp_scene, scene_node);
    }
}

void FBXImporter::update_scene_camera(const aiScene* assimp_scene, SceneNode* scene_node)
{
    const Scene* scene = scene_node->get_scene();
    assert(scene != nullptr && "Scene node is not attached to scene");

    Entity scene_camera_entity = scene->get_camera();

    if (assimp_scene->mNumCameras == 0)
    {
        printf("Couldn't find camera in fbx");
        return;
    }

    const aiCamera* first_camera = assimp_scene->mCameras[0];

    CameraComponent& scene_camera = world->get_component<CameraComponent>(scene_camera_entity);
    const aiVector3D camera_up = first_camera->mUp;
    const aiVector3D camera_forward = first_camera->mLookAt;

    scene_camera.up = float3(camera_up.x, camera_up.y, camera_up.z);
    scene_camera.forward = float3(camera_forward.x, camera_forward.y, camera_forward.z);
    scene_camera.right = float3::cross(scene_camera.forward, scene_camera.up);

    Transform& scene_camera_transform = world->get_component<Transform>(scene_camera_entity);
    const aiVector3D camera_position = first_camera->mPosition;
    scene_camera_transform.position = float3(camera_position.x, camera_position.y, camera_position.z);
}

void FBXImporter::attach_assimp_node_to_scene(const aiNode* assimp_node, SceneNode* scene_node, std::vector<MeshID>& mesh_ids,
    std::vector<TextureID>& texture_ids, std::unordered_set<MeshID>& used_meshes)
{
    printf("Assimp node: %s\n", assimp_node->mName.C_Str());
    if (assimp_node->mNumMeshes > 0)
    {
        populate_node(assimp_node, scene_node, mesh_ids, used_meshes);
    }

    for (unsigned int i = 0; i < assimp_node->mNumChildren; i++)
    {
        SceneNode* child_node = scene_node->add_child(world->create_empty_entity());
        attach_assimp_node_to_scene(assimp_node->mChildren[i], child_node, mesh_ids, texture_ids, used_meshes);
    }

    aiVector3D position;
    aiQuaternion rotation;
    aiVector3D scale;

    aiMatrix4x4 assimp_transform = assimp_node->mTransformation;
    assimp_transform.Decompose(scale, rotation, position);

    Transform node_transform = Transform {
        .position = float3(position.x, position.y, position.z),
        .rotation = quaternion(rotation.w, rotation.x, rotation.y, rotation.z),
        .scale = float3(scale.x, scale.y, scale.z)
    };

    if (world->has_component<Transform>(scene_node->get_entity()))
    {
        world->get_component<Transform>(scene_node->get_entity()) = node_transform;
    }
    else
    {
        world->add_component<Transform>(scene_node->get_entity(), node_transform);
    }
}

void FBXImporter::populate_node(const aiNode* assimp_node, SceneNode* scene_node, std::vector<MeshID> mesh_ids, std::unordered_set<MeshID>& used_meshes)
{
    int num_meshes = assimp_node->mNumMeshes;
    for (int i = 0; i < num_meshes; i++)
    {
        scene_node->add_child(world->create_entity()
                                  .with(MeshComponent(mesh_ids[assimp_node->mMeshes[i]]))
                                  .with(Transform::identity())
                                  .with(ShaderComponent(shader_repository->get_shader_id("lighting")))
                                  .with(PEWTER_MATERIAL)
                                  .build());

        used_meshes.insert(mesh_ids[assimp_node->mMeshes[i]]);
    }

    world->add_component(scene_node->get_entity(), NameComponent {
                                                       .name = assimp_node->mName.C_Str(),
                                                   });
}


// TODO: implement texture importing
std::vector<TextureID> FBXImporter::build_textures(const aiScene* assimp_scene)
{
    unsigned int num_textures = assimp_scene->mNumTextures;

    std::vector<TextureID> texture_ids(num_textures);

    for (unsigned int i = 0; i < num_textures; i++)
    {
    }

    return texture_ids;
}

std::vector<MeshID> FBXImporter::build_meshes(const aiScene* assimp_scene)
{
    unsigned int num_meshes = assimp_scene->mNumMeshes;

    std::vector<MeshID> mesh_ids(num_meshes);

    for (unsigned int i = 0; i < num_meshes; i++)
    {
        const aiMesh* mesh = assimp_scene->mMeshes[i];
        unsigned int numVertices = mesh->mNumVertices;

        std::vector<float3> vertices(numVertices);
        std::vector<float3> normals(numVertices);
        std::vector<float2> uvs(numVertices, float2::zero());

        for (int j = 0; j < numVertices; j++)
        {
            const aiVector3D vertex = mesh->mVertices[j];
            const aiVector3D normal = mesh->mNormals[j];

            vertices[j] = 0.01f * float3(vertex.x, vertex.y, vertex.z);
            normals[j] = float3(normal.x, normal.y, normal.z);
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