#ifndef DEMO_SET_SHADER_CAMERA_H
#define DEMO_SET_SHADER_CAMERA_H

#include <constants/shader_constants.h>
#include <maths/float3.h>
#include <rendering/shader.h>
#include <templates/action.h>

class SetShaderCamera
{
public:
    SetShaderCamera(float3 position, float3 forward, glm::mat4 view)
        : position(position)
        , forward(forward)
        , view(view) {};

    inline void operator()(Shader* shader)
    {
        shader->bind();

        shader->set_float3(DEMO_CONSTANTS_CAMERA_POSITION, position);
        shader->set_float3(DEMO_CONSTANTS_CAMERA_FORWARD, forward);
        shader->set_mat4(DEMO_CONSTANTS_VIEW, view);
    }

private:
    float3 position;
    float3 forward;
    glm::mat4 view;
};

#endif // DEMO_SET_SHADER_CAMERA_H
