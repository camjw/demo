#ifndef DEMO_RENDERING_MESH_HPP
#define DEMO_RENDERING_MESH_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
    static std::shared_ptr<Mesh> cube();
    Mesh(
        std::vector<float3> positions,
        std::vector<float3> normals,
        std::vector<float2> uvs,
        std::vector<uint32_t> indices)
        : positions(positions)
        , normals(normals)
        , uvs(uvs)
        , indices(indices) {};

    std::vector<float3> positions;
    std::vector<float3> normals;
    std::vector<float2> uvs;

    std::vector<uint32_t> indices;

    void init();
    void destroy();

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    Mesh(Mesh&& other)
        : VAO(other.VAO)
        , EBO(other.EBO)
        , VBO(other.VBO)
    {
        other.VAO = 0;
        other.VBO = 0;
        other.EBO = 0;
    }

    Mesh& operator=(Mesh&& other)
    {
        if (this != &other)
        {
            destroy();
            std::swap(VAO, other.VAO);
            std::swap(VBO, other.VBO);
            std::swap(EBO, other.EBO);
        }

        return *this;
    }

    unsigned int VAO, EBO, VBO;
};

#endif
