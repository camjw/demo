#ifndef DEMO_RENDERING_MESH_HPP
#define DEMO_RENDERING_MESH_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <utility>
#include <vector>

#include <ecs/ecs.h>
#include <maths/maths.h>

using MeshID = uint32_t;
const MeshID INVALID_MESH = UINT32_MAX;

struct MeshComponent
{
    MeshID id;
    explicit MeshComponent() = default;
    explicit MeshComponent(MeshID id) : id(id) {};
};

MARK_AS_COMPONENT(MeshComponent)

class Mesh
{
public:
    Mesh() = default;
    static std::shared_ptr<Mesh> square();
    static std::shared_ptr<Mesh> cube();
    static std::shared_ptr<Mesh> skybox();
    Mesh(
        std::vector<float3> positions,
        std::vector<float3> normals,
        std::vector<float2> uvs,
        std::vector<uint32_t> indices)
        : positions(std::move(positions))
        , normals(std::move(normals))
        , uvs(std::move(uvs))
        , indices(std::move(indices)) {};

    std::vector<float3> positions;
    std::vector<float3> normals;
    std::vector<float2> uvs;

    std::vector<uint32_t> indices;

    void init();
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
};

#endif
