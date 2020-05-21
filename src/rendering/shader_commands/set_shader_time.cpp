#include <demo/rendering/shader_commands/set_shader_time.h>

void SetShaderTime::run(std::shared_ptr<Shader> shader)
{
    shader->setFloat(DEMO_CONSTANTS_TOTAL_TIME, time.total_time);
    shader->setFloat(DEMO_CONSTANTS_DELTA_TIME, time.delta_time);
}