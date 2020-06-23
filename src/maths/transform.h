#ifndef DEMO_TRANSFORM_H
#define DEMO_TRANSFORM_H

#include <glm/glm.hpp>
#include <maths/float3.h>
#include <maths/quaternion.h>

struct Transform
{
    float3 position;
    quaternion rotation;
    float3 scale;

    glm::mat4 get_model_matrix()
    {
        return glm::mat4(1.0f);
    }

    static Transform identity()
    {
        return Transform {
            .position = float3::zero(),
            .rotation = quaternion::identity(),
            .scale = float3::one(),
        };
    }
};

#endif // DEMO_TRANSFORM_H
