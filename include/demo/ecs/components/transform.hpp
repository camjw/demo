#ifndef DEMO_ECS_COMPONENTS_TRANSFORM_HPP
#define DEMO_ECS_COMPONENTS_TRANSFORM_HPP

#include <demo/maths/maths.hpp>

struct Transform
{
    float3 position;
    quaternion rotation;
    float3 scale;
};

#endif
