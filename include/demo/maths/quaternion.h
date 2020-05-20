#ifndef DEMO_MATHS_QUATERNION_HPP
#define DEMO_MATHS_QUATERNION_HPP

#include <math.h>
#include <cstdio>

#include <demo/maths/float3.h>

struct quaternion
{
public:
    quaternion()
        : w(1.0f)
        , x(0.0f)
        , y(0.0f)
        , z(0.0f) {};
    quaternion(float w, float x, float y, float z)
        : w(w)
        , x(x)
        , y(y)
        , z(z) {};

    quaternion normalise()
    {
        float l = length();

        w /= l;
        x /= l;
        y /= l;
        z /= l;

        return *this;
    }

    float length_squared()
    {
        return w * w - x * x - y * y - z * z;
    }

    float length()
    {
        return sqrt(length_squared());
    }

    quaternion operator*(quaternion const& other)
    {
        return quaternion(
            w * other.w - x * other.x - y * other.y - z * other.z,
            w * other.x + x * other.w + y * other.z - z * other.y,
            w * other.y - x * other.z + y * other.w + z * other.z,
            w * other.z + x * other.y - y * other.x + z * other.x);
    }

    quaternion operator*=(quaternion const& other)
    {
        w = w * other.w - x * other.x - y * other.y - z * other.z;
        x = w * other.x + x * other.w + y * other.z - z * other.y;
        y = w * other.y - x * other.z + y * other.w + z * other.z;
        z = w * other.z + x * other.y - y * other.x + z * other.x;

        return *this;
    }

    quaternion inverse()
    {
        return quaternion(w, -x, -y, -z);
    }

    void print() 
    {       
        printf("(%f, %f, %f, %f)\n", w, x, y, z);
    }

    float w, x, y, z;
};

#endif