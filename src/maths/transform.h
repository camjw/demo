#ifndef DEMO_TRANSFORM_H
#define DEMO_TRANSFORM_H

#include <glm/glm.hpp>
#include <maths/float3.h>
#include <maths/quaternion.h>

struct Transform
{
    float3 position = float3::zero();
    quaternion rotation = quaternion::identity();
    float3 scale = float3::one();

    glm::mat4 get_model_matrix()
    {
        glm::vec3 glm_position = position.to_glm();
        glm::quat glm_rotation = rotation.to_glm();
        glm::vec3 glm_scale = scale.to_glm();

        glm::mat4 model_matrix = glm::mat4(1.0f);

        model_matrix = glm::scale(model_matrix, glm_scale);
        model_matrix = glm::toMat4(glm_rotation) * model_matrix;
        model_matrix = glm::translate(model_matrix, glm_position);
        return model_matrix;
    }

    static Transform identity()
    {
        return Transform();
    }
};

#endif // DEMO_TRANSFORM_H
