#include <demo/rendering/shader_commands/set_shader_camera.h>

void SetShaderCamera::run(std::shared_ptr<Shader> shader)
{
    shader->setVec3(DEMO_CONSTANTS_CAMERA_POSITION, position);
    shader->setVec3(DEMO_CONSTANTS_CAMERA_FORWARD, forward);
    shader->setMat4(DEMO_CONSTANTS_VIEW, view);
}