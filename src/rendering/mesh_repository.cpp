#include <demo/rendering/mesh_repository.h>

std::shared_ptr<Mesh> MeshRepository::get_mesh(MeshID mesh_id)
{
    assert(meshes.find(mesh_id) != meshes.end() && "No such mesh.");

    return meshes[mesh_id];
}

MeshID MeshRepository::create_mesh()
{
    std::shared_ptr<Mesh> new_mesh = std::make_shared<Mesh>();

    meshes.insert(std::make_pair(++current_mesh_id, new_mesh));
    return current_mesh_id;
}

MeshID MeshRepository::create_mesh(
    std::vector<float3> positions,
    std::vector<float3> normals,
    std::vector<float2> uvs,
    std::vector<uint32_t> indices)
{
    std::shared_ptr<Mesh> new_mesh = std::make_shared<Mesh>(positions, normals, uvs, indices);
    new_mesh->init();

    meshes.insert(std::make_pair(++current_mesh_id, new_mesh));
    return current_mesh_id;
}

MeshID MeshRepository::create_cube()
{
    std::shared_ptr<Mesh> cube_mesh = Mesh::cube();
    cube_mesh->init();

    meshes.insert(std::make_pair(++current_mesh_id, cube_mesh));
    return current_mesh_id;
}

MeshID MeshRepository::create_skybox()
{
    std::shared_ptr<Mesh> skybox_mesh = Mesh::skybox();
    skybox_mesh->init();

    meshes.insert(std::make_pair(++current_mesh_id, skybox_mesh));
    return current_mesh_id;
}

void MeshRepository::delete_mesh(MeshID mesh_id)
{
    assert(meshes.find(mesh_id) != meshes.end() && "Removing non-existent mesh.");

    std::shared_ptr<Mesh> meshToDelete = meshes[mesh_id];
    meshToDelete->destroy();
    meshes.erase(mesh_id);
}