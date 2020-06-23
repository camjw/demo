#ifndef DEMO_RENDERING_MESH_REPOSITORY_HPP
#define DEMO_RENDERING_MESH_REPOSITORY_HPP

#include <demo/rendering/mesh.h>

#include <unordered_map>

class MeshRepository
{
public:
    std::shared_ptr<Mesh> get_mesh(MeshID mesh_id);
    MeshID get_or_create_mesh(const std::string& filename);

    // helper functions for common meshes
    MeshID create_square();
    MeshID create_cube();
    MeshID create_skybox();

    void delete_mesh(MeshID mesh_id);
    void clear();

private:
    std::unordered_map<std::string, MeshID> filename_to_mesh_id;
    std::unordered_map<MeshID, std::shared_ptr<Mesh>> meshes;
    MeshID current_mesh_id = 0;

    MeshID create_mesh(
        std::vector<float3> positions,
        std::vector<float3> normals,
        std::vector<float2> uvs,
        std::vector<uint32_t> indices);
};

#endif