#include "mesh_factory.h"
#include <utils/uuid.h>

ResourceHandle MeshFactory::create_mesh(
    std::vector<float3> positions,
    std::vector<float3> normals,
    std::vector<float2> uvs,
    std::vector<uint32_t> indices)
{
    Mesh new_mesh = Mesh(positions, normals, uvs, indices);

    return insert(uuid::new_uuid(), std::move(new_mesh));
}

Mesh* MeshFactory::get_or_create_square()
{
    Mesh* square_mesh = get("cube");
    if (square_mesh != nullptr)
    {
        return square_mesh;
    }

    Mesh mesh = Mesh::square();

    insert("sqyare", std::move(mesh));

    return get("square");
}

Mesh* MeshFactory::get_or_create_cube()
{
    Mesh* cube_mesh = get("cube");
    if (cube_mesh != nullptr)
    {
        return cube_mesh;
    }

    Mesh mesh = Mesh::cube();

    insert("cube", std::move(mesh));

    return get("cube");
}

Mesh* MeshFactory::get_or_create_skybox()
{
    Mesh* skybox_mesh = get("skybox");
    if (skybox_mesh != nullptr)
    {
        return skybox_mesh;
    }

    Mesh mesh = Mesh::skybox();

    insert("skybox", std::move(mesh));

    return get("skybox");
}