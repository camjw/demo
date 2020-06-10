#ifndef DEMO_MATHS_MATHS_HPP
#define DEMO_MATHS_MATHS_HPP

#include <demo/maths/float2.h>
#include <demo/maths/float3.h>

#include <demo/maths/quaternion.h>

class maths
{
public:
    static float3 multiply(quaternion q, float3 v)
    {
        quaternion c = q.inverse() * quaternion(0, v.x, v.y, v.z) * q;
        return float3(c.x, c.y, c.z);
    }

    static float mod(float value, float modulus)
    {
        return value - (modulus * int(value / modulus));
    }

    static float min(float first, float second)
    {
        if (first < second)
        {
            return first;
        }

        return second;
    }

    static float max(float first, float second)
    {
        if (first < second)
        {
            return second;
        }

        return first;
    }

    static float clamp(float value, float min, float max)
    {
        if (value < min)
        {
            return min;
        }

        if (value > max)
        {
            return max;
        }

        return value;
    }
};

#endif
