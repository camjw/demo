#ifndef DEMO_SET_SHADER_PROJECTION_H
#define DEMO_SET_SHADER_PROJECTION_H

#include <constants/shader_constants.h>
#include <templates/action.h>
#include <rendering/shader.h>

class SetShaderProjection : public Action<Shader>
{
public:
    SetShaderProjection(glm::mat4 projection): projection(projection) {};
    void run(std::shared_ptr<Shader> shader);

private:
    glm::mat4 projection;
};

#endif // DEMO_SET_SHADER_PROJECTION_H
