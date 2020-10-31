#ifndef DEMO_SET_SHADER_PROJECTION_H
#define DEMO_SET_SHADER_PROJECTION_H

#include <constants/shader_constants.h>
#include <rendering/shader.h>
#include <templates/action.h>

class SetShaderProjection
{
public:
    SetShaderProjection(glm::mat4 projection)
        : projection(projection) {};

    inline void operator()(Shader* shader)
    {
        shader->bind();
        shader->set_mat4(DEMO_CONSTANTS_PROJECTION, projection);
    }

private:
    glm::mat4 projection;
};

#endif // DEMO_SET_SHADER_PROJECTION_H
