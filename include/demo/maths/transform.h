#ifndef DEMO_TRANSFORM_H
#define DEMO_TRANSFORM_H

#include <demo/maths/float3.h>
#include <demo/maths/quaternion.h>
#include <glm/glm.hpp>

struct TransformComponent
{
    float3 position;
    quaternion rotation;
    float3 scale;

    glm::mat4 get_model_matrix()
    {
        return glm::mat4(1.0f);
    }
};

#endif // DEMO_TRANSFORM_H
