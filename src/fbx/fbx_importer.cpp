#include "fbx_importer.h"

#include <utility>

void FBXImporter::load_fbx(const std::string& filename, SceneNode* scene_node)
{
    const aiScene* assimp_scene = assimp_importer.ReadFile(filename.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);

    assert(assimp_scene != nullptr && "Assimp failed to import fbx from file");

    std::vector<MeshID> mesh_ids = build_meshes(assimp_scene);
    std::vector<TextureID> texture_ids = build_textures(assimp_scene);

    attach_assimp_node_to_scene(assimp_scene->mRootNode, scene_node, mesh_ids, texture_ids);
}

void FBXImporter::attach_assimp_node_to_scene(const aiNode* assimp_node, SceneNode* scene_node, std::vector<MeshID>& mesh_ids, std::vector<TextureID>& texture_ids)
{
    world->add_component(scene_node->get_entity(), MeshComponent(mesh_ids[assimp_node->mMeshes[0]]));

    for (unsigned int i = 0; i < assimp_node->mNumChildren; i++)
    {
        SceneNode* child_node = scene_node->add_child(world->create_empty_entity());
        attach_assimp_node_to_scene(assimp_node->mChildren[i], child_node, mesh_ids, texture_ids);
    }
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
                aiVector3D uv = mesh->mTextureCoords[0][i];
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
    }

    return mesh_ids;
}