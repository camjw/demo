#ifndef DEMO_MATHS_MATHS_HPP
#define DEMO_MATHS_MATHS_HPP

#include <demo/maths/float2.hpp>
#include <demo/maths/float3.hpp>

#include <demo/maths/quaternion.hpp>

class maths
{
public:
    static float3 multiply(quaternion q, float3 v)
    {
        quaternion c = q.inverse() * quaternion(0, v.x, v.y, v.z) * q;
        return float3(c.x, c.y, c.z);
    }
};

#endif
