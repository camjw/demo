#ifndef DEMO_RENDERING_MESH_HPP
#define DEMO_RENDERING_MESH_HPP

#include <string>
#include <vector>

#include <demo/maths/maths.hpp>

using MeshID = uint8_t;

struct MeshComponent
{
    MeshID id;
};

class Mesh
{
    public:
        Mesh() {};
        Mesh(
            std::vector<float3> positions, 
            std::vector<float3> normals, 
            std::vector<float2> uvs, 
            std::vector<uint32_t> indices
        ) : positions(positions), normals(normals), uvs(uvs), indices(indices) {};

        std::vector<float3> positions;
        std::vector<float3> normals;
        std::vector<float2> uvs;

        std::vector<uint32_t> indices;

        void destroy() {}

        unsigned int VAO;

    private:
        unsigned int VBO, EBO;
};

#endif
