#ifndef DEMO_RENDER_QUEUE_H
#define DEMO_RENDER_QUEUE_H

#include "material.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include <glm/mat4x4.hpp>

struct RenderCommand
{
    MeshID mesh_id;

    ShaderID shader_id;

    TextureID diffuse_texture_id = 0;
    TextureID specular_texture_id = 0;

    MaterialID material_id;

    glm::mat4 transform;
};

class RenderQueue
{
public:
    inline void push_back(const RenderCommand render_command)
    {
        commands.push_back(render_command);
    }

    inline void clear()
    {
        commands.clear();
    }

    std::vector<RenderCommand> commands;
};

#endif //DEMO_RENDER_QUEUE_H
