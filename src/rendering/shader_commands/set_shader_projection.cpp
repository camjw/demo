#include <demo/rendering/shader_commands/set_shader_projection.h>

void SetShaderProjection::run(std::shared_ptr<Shader> shader)
{
    shader->bind();
    shader->setMat4(DEMO_CONSTANTS_PROJECTION, projection);
}