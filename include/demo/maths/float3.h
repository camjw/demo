#ifndef DEMO_MATHS_FLOAT_3_HPP
#define DEMO_MATHS_FLOAT_3_HPP

#include <demo/maths/float2.h>
#include <math.h>
#include <cstdio>

struct float3
{

public:
    float3(): x(0.0f), y(0.0f), z(0.0f) {}
    float3(float x, float y, float z)
        : x(x)
        , y(y)
        , z(z)
    {
    }
    float3(float t)
        : x(t)
        , y(t)
        , z(t)
    {
    }
    float3(float2 v, float z)
        : x(v.x)
        , y(v.y)
        , z(z)
    {
    }
    float3(float x, float2 v)
        : x(x)
        , y(v.x)
        , z(v.y)
    {
    }

    float length()
    {
        return sqrt(length_squared());
    }

    float length_squared()
    {
        return x * x + y * y + z * z;
    }

    float dot(float3 other)
    {
        return x * other.x + y * other.y + z * other.z;
    }

    static float3 zero()
    {
        return float3(0.0f, 0.0f, 0.0f);
    }

    static float3 one()
    {
        return float3(1.0f, 1.0f, 1.0f);
    }

    float3 operator+(float3 const& other)
    {
        return float3(x + other.x, y + other.y, z + other.z);
    }

    float3 operator-(float3 const& other)
    {
        return float3(x - other.x, y - other.y, z - other.z);
    }

    float3 operator*(float3 const& other)
    {
        return float3(x * other.x, y * other.y, z * other.z);
    }

    float3 operator*(const float scale)
    {
        return float3(x * scale, y * scale, z * scale);
    }

    float3 operator/(float3 const& other)
    {
        return float3(x / other.x, y / other.y, z / other.z);
    }

    float3 operator/(const float scale)
    {
        return float3(x / scale, y / scale, z / scale);
    }

    float3 operator-()
    {
        return float3(-x, -y, -z);
    }

    float3 operator+=(float3 const& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;

        return *this;
    }

    float3 operator-=(float3 const& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;

        return *this;
    }

    float3 operator*=(float3 const& other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        
        return *this;
    }

    float3 operator*=(const float scale)
    {
        x *= scale;
        y *= scale;
        z *= scale;

        return *this;
    }

    float3 operator/=(float3 const& other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;

        return *this;
    }

    float3 operator/=(const float scale)
    {
        x /= scale;
        y /= scale;
        z /= scale;

        return *this;
    }

    bool operator==(float3 const& other)
    {
        return x == other.x && y == other.y && x == other.z;
    }

    bool operator!=(float3 const& other)
    {
        return x != other.x || y != other.y || x != other.z;
    }

    void print()
    {
        printf("(%f, %f, %f)\n", x, y, z);
    }

    float x, y, z;
};

#endif
