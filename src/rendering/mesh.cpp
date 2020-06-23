#include <utils/opengl_helpers.h>
#include <rendering/mesh.h>

std::shared_ptr<Mesh> Mesh::square()
{
    std::vector<float3> square_positions = {
        float3(-0.5f, -0.5f, 0.0f),
        float3(-0.5f, 0.5f, 0.0f),
        float3(0.5f, 0.5f, 0.0f),
        float3(0.5f, -0.5f, 0.0f),
    };

    std::vector<float3> square_normals = {
        float3(0.0f, 0.0f, 1.0f),
        float3(0.0f, 0.0f, 1.0f),
        float3(0.0f, 0.0f, 1.0f),
        float3(0.0f, 0.0f, 1.0f)
    };

    std::vector<float2> square_uvs = {
        float2(0.0f, 0.0f),
        float2(1.0f, 0.0f),
        float2(1.0f, 1.0f),
        float2(0.0f, 1.0f)
    };

    std::vector<uint32_t> square_indices = {
        0, 1, 2, 0, 2, 3,
        0, 2, 1, 0, 3, 2
    };

    return std::make_shared<Mesh>(square_positions, square_normals, square_uvs, square_indices);
}

std::shared_ptr<Mesh> Mesh::cube()
{
    std::vector<float3> cube_positions = {
        float3(-0.5f, -0.5f, -0.5f),
        float3(-0.5f, 0.5f, -0.5f),
        float3(0.5f, 0.5f, -0.5f),
        float3(0.5f, -0.5f, -0.5f),

        float3(-0.5f, -0.5f, 0.5f),
        float3(0.5f, -0.5f, 0.5f),
        float3(0.5f, 0.5f, 0.5f),
        float3(-0.5f, 0.5f, 0.5f),

        float3(-0.5f, 0.5f, 0.5f),
        float3(-0.5f, 0.5f, -0.5f),
        float3(-0.5f, -0.5f, -0.5f),
        float3(-0.5f, -0.5f, 0.5f),

        float3(0.5f, 0.5f, 0.5f),
        float3(0.5f, -0.5f, 0.5f),
        float3(0.5f, -0.5f, -0.5f),
        float3(0.5f, 0.5f, -0.5f),

        float3(-0.5f, -0.5f, -0.5f),
        float3(0.5f, -0.5f, -0.5f),
        float3(0.5f, -0.5f, 0.5f),
        float3(-0.5f, -0.5f, 0.5f),

        float3(-0.5f, 0.5f, -0.5f),
        float3(-0.5f, 0.5f, 0.5f),
        float3(0.5f, 0.5f, 0.5f),
        float3(0.5f, 0.5f, -0.5f)
    };

    std::vector<float3> cube_normals = {
        float3(0.0f, 0.0f, -1.0f),
        float3(0.0f, 0.0f, -1.0f),
        float3(0.0f, 0.0f, -1.0f),
        float3(0.0f, 0.0f, -1.0f),

        float3(0.0f, 0.0f, 1.0f),
        float3(0.0f, 0.0f, 1.0f),
        float3(0.0f, 0.0f, 1.0f),
        float3(0.0f, 0.0f, 1.0f),

        float3(-1.0f, 0.0f, 0.0f),
        float3(-1.0f, 0.0f, 0.0f),
        float3(-1.0f, 0.0f, 0.0f),
        float3(-1.0f, 0.0f, 0.0f),

        float3(1.0f, 0.0f, 0.0f),
        float3(1.0f, 0.0f, 0.0f),
        float3(1.0f, 0.0f, 0.0f),
        float3(1.0f, 0.0f, 0.0f),

        float3(0.0f, -1.0f, 0.0f),
        float3(0.0f, -1.0f, 0.0f),
        float3(0.0f, -1.0f, 0.0f),
        float3(0.0f, -1.0f, 0.0f),

        float3(0.0f, 1.0f, 0.0f),
        float3(0.0f, 1.0f, 0.0f),
        float3(0.0f, 1.0f, 0.0f),
        float3(0.0f, 1.0f, 0.0f)
    };

    std::vector<float2> cube_uvs = {
        float2(0.0f, 0.0f),
        float2(1.0f, 0.0f),
        float2(1.0f, 1.0f),
        float2(0.0f, 1.0f),

        float2(0.0f, 0.0f),
        float2(1.0f, 0.0f),
        float2(1.0f, 1.0f),
        float2(0.0f, 1.0f),

        float2(0.0f, 0.0f),
        float2(1.0f, 0.0f),
        float2(1.0f, 1.0f),
        float2(0.0f, 1.0f),

        float2(0.0f, 0.0f),
        float2(1.0f, 0.0f),
        float2(1.0f, 1.0f),
        float2(0.0f, 1.0f),

        float2(0.0f, 0.0f),
        float2(1.0f, 0.0f),
        float2(1.0f, 1.0f),
        float2(0.0f, 1.0f),

        float2(0.0f, 0.0f),
        float2(1.0f, 0.0f),
        float2(1.0f, 1.0f),
        float2(0.0f, 1.0f)
    };

    std::vector<uint32_t> cube_indices;

    for (uint32_t i = 0; i < 6; i++)
    {
        cube_indices.push_back(4 * i);
        cube_indices.push_back(4 * i + 1);
        cube_indices.push_back(4 * i + 2);

        cube_indices.push_back(4 * i);
        cube_indices.push_back(4 * i + 2);
        cube_indices.push_back(4 * i + 3);
    };

    return std::make_shared<Mesh>(cube_positions, cube_normals, cube_uvs, cube_indices);
}

std::shared_ptr<Mesh> Mesh::skybox()
{
    std::vector<float3> skybox_positions = {
        float3(-1.0f, -1.0f, -1.0f),
        float3(-1.0f, 1.0f, -1.0f),
        float3(1.0f, 1.0f, -1.0f),
        float3(1.0f, -1.0f, -1.0f),

        float3(-1.0f, -1.0f, 1.0f),
        float3(1.0f, -1.0f, 1.0f),
        float3(1.0f, 1.0f, 1.0f),
        float3(-1.0f, 1.0f, 1.0f),

        float3(-1.0f, 1.0f, 1.0f),
        float3(-1.0f, 1.0f, -1.0f),
        float3(-1.0f, -1.0f, -1.0f),
        float3(-1.0f, -1.0f, 1.0f),

        float3(1.0f, 1.0f, 1.0f),
        float3(1.0f, -1.0f, 1.0f),
        float3(1.0f, -1.0f, -1.0f),
        float3(1.0f, 1.0f, -1.0f),

        float3(-1.0f, -1.0f, -1.0f),
        float3(1.0f, -1.0f, -1.0f),
        float3(1.0f, -1.0f, 1.0f),
        float3(-1.0f, -1.0f, 1.0f),

        float3(-1.0f, 1.0f, -1.0f),
        float3(-1.0f, 1.0f, 1.0f),
        float3(1.0f, 1.0f, 1.0f),
        float3(1.0f, 1.0f, -1.0f)
    };

    std::vector<float3> skybox_normals = {
        float3(0.0f, 0.0f, -1.0f),
        float3(0.0f, 0.0f, -1.0f),
        float3(0.0f, 0.0f, -1.0f),
        float3(0.0f, 0.0f, -1.0f),

        float3(0.0f, 0.0f, 1.0f),
        float3(0.0f, 0.0f, 1.0f),
        float3(0.0f, 0.0f, 1.0f),
        float3(0.0f, 0.0f, 1.0f),

        float3(-1.0f, 0.0f, 0.0f),
        float3(-1.0f, 0.0f, 0.0f),
        float3(-1.0f, 0.0f, 0.0f),
        float3(-1.0f, 0.0f, 0.0f),

        float3(1.0f, 0.0f, 0.0f),
        float3(1.0f, 0.0f, 0.0f),
        float3(1.0f, 0.0f, 0.0f),
        float3(1.0f, 0.0f, 0.0f),

        float3(0.0f, -1.0f, 0.0f),
        float3(0.0f, -1.0f, 0.0f),
        float3(0.0f, -1.0f, 0.0f),
        float3(0.0f, -1.0f, 0.0f),

        float3(0.0f, 1.0f, 0.0f),
        float3(0.0f, 1.0f, 0.0f),
        float3(0.0f, 1.0f, 0.0f),
        float3(0.0f, 1.0f, 0.0f)
    };

    std::vector<float2> skybox_uvs = {
        float2(0.0f, 0.0f),
        float2(1.0f, 0.0f),
        float2(1.0f, 1.0f),
        float2(0.0f, 1.0f),

        float2(0.0f, 0.0f),
        float2(1.0f, 0.0f),
        float2(1.0f, 1.0f),
        float2(0.0f, 1.0f),

        float2(0.0f, 0.0f),
        float2(1.0f, 0.0f),
        float2(1.0f, 1.0f),
        float2(0.0f, 1.0f),

        float2(0.0f, 0.0f),
        float2(1.0f, 0.0f),
        float2(1.0f, 1.0f),
        float2(0.0f, 1.0f),

        float2(0.0f, 0.0f),
        float2(1.0f, 0.0f),
        float2(1.0f, 1.0f),
        float2(0.0f, 1.0f),

        float2(0.0f, 0.0f),
        float2(1.0f, 0.0f),
        float2(1.0f, 1.0f),
        float2(0.0f, 1.0f)
    };

    std::vector<uint32_t> skybox_indices;

    for (uint32_t i = 0; i < 6; i++)
    {
        skybox_indices.push_back(4 * i);
        skybox_indices.push_back(4 * i + 2);
        skybox_indices.push_back(4 * i + 1);

        skybox_indices.push_back(4 * i);
        skybox_indices.push_back(4 * i + 3);
        skybox_indices.push_back(4 * i + 2);
    };

    return std::make_shared<Mesh>(skybox_positions, skybox_normals, skybox_uvs, skybox_indices);
}

void Mesh::init()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER,
        (positions.size() + normals.size()) * sizeof(float3) + uvs.size() * sizeof(float2),
        NULL,
        GL_STATIC_DRAW);

    glBufferSubData(
        GL_ARRAY_BUFFER,
        0,
        positions.size() * sizeof(float3),
        &positions[0]);

    glBufferSubData(
        GL_ARRAY_BUFFER,
        positions.size() * sizeof(float3),
        normals.size() * sizeof(float3),
        &normals[0]);

    glBufferSubData(
        GL_ARRAY_BUFFER,
        (positions.size() + normals.size()) * sizeof(float3),
        uvs.size() * sizeof(float2),
        &uvs[0]);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(float3),
        0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(float3),
        (void*)(positions.size() * sizeof(float3)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(float2),
        (void*)((positions.size() + normals.size()) * sizeof(float3)));

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);

    glCheckError();
}

void Mesh::bind()
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void Mesh::draw()
{
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::destroy()
{
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VAO);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &EBO);
}
