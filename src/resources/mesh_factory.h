#ifndef DEMO_MESH_FACTORY_H
#define DEMO_MESH_FACTORY_H

#include <rendering/data/mesh.h>
#include "resources/resource_factory.h"

class MeshFactory : public ResourceFactory<Mesh>
{
public:
    explicit MeshFactory()
        : ResourceFactory("assets/meshes")
    {
        get_or_create_square();
        get_or_create_cube();
        get_or_create_skybox();
    }

    Mesh* get_or_create_square();
    Mesh* get_or_create_cube();
    Mesh* get_or_create_skybox();

protected:
    inline virtual std::shared_ptr<Mesh> build(const std::string& name) override
    {
        assert("Can't load meshes from files at the moment");
        return nullptr;
    }

    ResourceHandle create_mesh(
        std::vector<float3> positions,
        std::vector<float3> normals,
        std::vector<float2> uvs,
        std::vector<uint32_t> indices);
};

#endif // DEMO_MESH_FACTORY_H
