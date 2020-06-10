#ifndef DEMO_SET_SHADER_CAMERA_H
#define DEMO_SET_SHADER_CAMERA_H

#include <demo/constants/shader_constants.h>
#include <demo/maths/float3.h>
#include <demo/rendering/shader.h>
#include <demo/templates/action.h>

class SetShaderCamera : public Action<Shader>
{
public:
    SetShaderCamera(float3 position, float3 forward, glm::mat4 view)
        : position(position), forward(forward), view(view) {};
    void run(std::shared_ptr<Shader> shader);

private:
    float3 position;
    float3 forward;
    glm::mat4 view;
};

#endif // DEMO_SET_SHADER_CAMERA_H
