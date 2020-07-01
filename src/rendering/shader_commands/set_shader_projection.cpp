#include <rendering/shader_commands/set_shader_projection.h>

void SetShaderProjection::run(std::shared_ptr<Shader> shader)
{
    shader->bind();
    shader->set_mat4(DEMO_CONSTANTS_PROJECTION, projection);
}