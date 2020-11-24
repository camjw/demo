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
    if (is_present("square"))
    {
        return get("square");
    }

    Mesh mesh = Mesh::square();

    insert("square", std::move(mesh));

    return get("square");
}

Mesh* MeshFactory::get_or_create_cube()
{
    if (is_present("cube"))
    {
        return get("cube");
    }

    Mesh mesh = Mesh::cube();

    insert("cube", std::move(mesh));

    return get("cube");
}

Mesh* MeshFactory::get_or_create_skybox()
{
    if (is_present("skybox"))
    {
        return get("skybox");
    }

    Mesh mesh = Mesh::skybox();

    insert("skybox", std::move(mesh));

    return get("skybox");
}