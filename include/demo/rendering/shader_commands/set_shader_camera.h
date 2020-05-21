#ifndef DEMO_SET_SHADER_CAMERA_H
#define DEMO_SET_SHADER_CAMERA_H

#include <demo/templates/action.h>
#include <demo/rendering/shader.h>
#include <demo/constants/shader_constants.h>

class SetShaderCamera : public Action<Shader>
{
public:
    SetShaderCamera(glm::vec3 position, glm::vec3 forward, glm::mat4 view)
        : position(position), forward(forward), view(view) {};
    void run(std::shared_ptr<Shader> shader);

private:
    glm::vec3 position;
    glm::vec3 forward;
    glm::mat4 view;
};


#endif // DEMO_SET_SHADER_CAMERA_H
