#ifndef DEMO_SET_SHADER_CAMERA_H
#define DEMO_SET_SHADER_CAMERA_H

#include <constants/shader_constants.h>
#include <maths/float3.h>
#include <templates/action.h>
#include <rendering/shader.h>

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
