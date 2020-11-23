#ifndef DEMO_RENDERING_MESH_HPP
#define DEMO_RENDERING_MESH_HPP

#include <utils/opengl_include.h>

#include <string>
#include <utility>
#include <vector>

#include <ecs/ecs.h>
#include <ecs/world.h>
#include <maths/maths.h>

class Mesh
{
public:
    Mesh() = default;
    static Mesh square();
    static Mesh cube();
    static Mesh skybox();
    Mesh(
        std::vector<float3> positions,
        std::vector<float3> normals,
        std::vector<float2> uvs,
        std::vector<uint32_t> indices)
        : positions(std::move(positions))
        , normals(std::move(normals))
        , uvs(std::move(uvs))
        , indices(std::move(indices))
    {
        init();
    };

    std::vector<float3> positions;
    std::vector<float3> normals;
    std::vector<float2> uvs;

    std::vector<uint32_t> indices;

    void bind() const;
    void draw() const;
    void bind_and_draw() const;
    void destroy();

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    Mesh(Mesh&& other) noexcept
        : VAO(other.VAO)
        , EBO(other.EBO)
        , VBO(other.VBO)
    {
        other.VAO = 0;
        other.VBO = 0;
        other.EBO = 0;
    }

    Mesh& operator=(Mesh&& other) noexcept
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

    unsigned int VAO = 0;
    unsigned int EBO = 0;
    unsigned int VBO = 0;

private:
    void init();
};

#endif
