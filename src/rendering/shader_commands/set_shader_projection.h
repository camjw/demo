#ifndef DEMO_SET_SHADER_PROJECTION_H
#define DEMO_SET_SHADER_PROJECTION_H

#include <constants/shader_constants.h>
#include <rendering/shader.h>
#include <templates/action.h>

class SetShaderProjection : public Action<Shader>
{
public:
    SetShaderProjection(glm::mat4 projection)
        : projection(projection) {};
    inline void run(std::shared_ptr<Shader> shader)
    {
        shader->bind();
        shader->set_mat4(DEMO_CONSTANTS_PROJECTION, projection);
    }

private:
    glm::mat4 projection;
};

#endif // DEMO_SET_SHADER_PROJECTION_H
