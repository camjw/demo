#ifndef DEMO_RENDERING_MESH_REPOSITORY_HPP
#define DEMO_RENDERING_MESH_REPOSITORY_HPP

#include <rendering/mesh.h>

#include <unordered_map>

class MeshRepository
{
public:
    std::shared_ptr<Mesh> get_mesh(MeshID mesh_id);

    // helper functions for common meshes
    std::shared_ptr<Mesh> get_or_create_square();
    std::shared_ptr<Mesh> get_or_create_cube();
    std::shared_ptr<Mesh> get_or_create_skybox();

    MeshID get_square_id();
    MeshID get_cube_id();
    MeshID get_skybox_id();

    void delete_mesh(MeshID mesh_id);
    void clear();

    MeshID create_mesh(
        std::vector<float3> positions,
        std::vector<float3> normals,
        std::vector<float2> uvs,
        std::vector<uint32_t> indices);

private:
    std::unordered_map<std::string, MeshID> filename_to_mesh_id;
    std::unordered_map<MeshID, std::shared_ptr<Mesh>> meshes;
    MeshID current_mesh_id = 0;

    std::shared_ptr<Mesh> square_mesh = nullptr;
    std::shared_ptr<Mesh> cube_mesh = nullptr;
    std::shared_ptr<Mesh> skybox_mesh = nullptr;

    MeshID square_mesh_id = INVALID_MESH;
    MeshID cube_mesh_id = INVALID_MESH;
    MeshID skybox_mesh_id = INVALID_MESH;
};

#endif