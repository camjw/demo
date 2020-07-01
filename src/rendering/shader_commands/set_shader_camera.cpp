#include <utils/opengl_helpers.h>
#include <rendering/shader_commands/set_shader_camera.h>

void SetShaderCamera::run(std::shared_ptr<Shader> shader)
{
    shader->bind();

    shader->set_float3(DEMO_CONSTANTS_CAMERA_POSITION, position);
    shader->set_float3(DEMO_CONSTANTS_CAMERA_FORWARD, forward);
    shader->set_mat4(DEMO_CONSTANTS_VIEW, view);
}