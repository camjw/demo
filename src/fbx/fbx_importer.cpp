#include "fbx_importer.h"

#include <utility>

void FBXImporter::load_fbx(const std::string& filename, SceneNode* scene_node, FBXImportOptions import_options)
{
    const aiScene* assimp_scene = assimp_importer.ReadFile(filename.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if (assimp_scene == nullptr)
    {
        printf("Failed to load fbx from %s\n", filename.c_str());
        return;
    }

    std::vector<MeshID> mesh_ids = build_meshes(assimp_scene);
    std::vector<TextureID> texture_ids = build_textures(assimp_scene);

    attach_assimp_node_to_scene(assimp_scene->mRootNode, scene_node, mesh_ids, texture_ids);

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

void FBXImporter::attach_assimp_node_to_scene(const aiNode* assimp_node, SceneNode* scene_node, std::vector<MeshID>& mesh_ids, std::vector<TextureID>& texture_ids)
{
    if (assimp_node->mNumMeshes > 0)
    {
        populate_node(assimp_node, scene_node, mesh_ids);
    }

    for (unsigned int i = 0; i < assimp_node->mNumChildren; i++)

    //    unsigned int minNumChildren = 2 < assimp_node->mNumChildren ? 2 : assimp_node->mNumChildren;
    //    for (unsigned int i = 0; i < minNumChildren; i++)
    {
        SceneNode* child_node = scene_node->add_child(world->create_empty_entity());
        attach_assimp_node_to_scene(assimp_node->mChildren[i], child_node, mesh_ids, texture_ids);
    }
}

void FBXImporter::populate_node(const aiNode* assimp_node, SceneNode* scene_node, std::vector<MeshID> mesh_ids)
{
    Entity node_entity = world->create_entity()
                             .with(MeshComponent(mesh_ids[assimp_node->mMeshes[0]]))
                             .with(Transform::identity())
                             .with(ShaderComponent(shader_repository->get_shader_id("simple")))
                             //                             .with_parent()
                             .build();

    scene_node->set_entity(node_entity);
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

            vertices[j] = float3(vertex.x, vertex.y, vertex.z);
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