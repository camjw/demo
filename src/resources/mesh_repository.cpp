#include <resources/mesh_repository.h>

std::shared_ptr<Mesh> MeshRepository::get_mesh(MeshID mesh_id)
{
    assert(meshes.find(mesh_id) != meshes.end() && "No such mesh.");

    return meshes[mesh_id];
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

std::shared_ptr<Mesh> MeshRepository::get_or_create_square()
{
    if (square_mesh != nullptr)
    {
        return square_mesh;
    }

    std::shared_ptr<Mesh> mesh = Mesh::square();
    mesh->init();

    meshes.insert(std::make_pair(++current_mesh_id, mesh));

    square_mesh = mesh;
    square_mesh_id = current_mesh_id;
    return mesh;
}

std::shared_ptr<Mesh> MeshRepository::get_or_create_cube()
{
    if (cube_mesh != nullptr)
    {
        return cube_mesh;
    }

    std::shared_ptr<Mesh> mesh = Mesh::cube();
    mesh->init();

    meshes.insert(std::make_pair(++current_mesh_id, mesh));

    cube_mesh = mesh;
    cube_mesh_id = current_mesh_id;
    return mesh;
}

std::shared_ptr<Mesh> MeshRepository::get_or_create_skybox()
{
    if (skybox_mesh != nullptr)
    {
        return skybox_mesh;
    }

    std::shared_ptr<Mesh> mesh = Mesh::skybox();
    mesh->init();

    meshes.insert(std::make_pair(++current_mesh_id, mesh));

    skybox_mesh = mesh;
    skybox_mesh_id = current_mesh_id;
    return mesh;
}

MeshID MeshRepository::get_square_id()
{
    if (square_mesh_id != INVALID_MESH)
    {
        return square_mesh_id;
    }

    get_or_create_square();
    return square_mesh_id;
}

MeshID MeshRepository::get_cube_id()
{
    if (cube_mesh_id != INVALID_MESH)
    {
        return cube_mesh_id;
    }

    get_or_create_cube();
    return cube_mesh_id;
}

MeshID MeshRepository::get_skybox_id()
{
    if (skybox_mesh_id != INVALID_MESH)
    {
        return skybox_mesh_id;
    }

    get_or_create_skybox();
    return skybox_mesh_id;
}

void MeshRepository::delete_mesh(MeshID mesh_id)
{
    assert(meshes.find(mesh_id) != meshes.end() && "Removing non-existent mesh.");

    std::shared_ptr<Mesh> mesh_to_delete = meshes[mesh_id];
    mesh_to_delete->destroy();
    meshes.erase(mesh_id);
}

void MeshRepository::clear()
{
    for (auto mesh : meshes)
    {
        delete_mesh(mesh.first);
    }
}
