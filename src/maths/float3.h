#ifndef DEMO_MATHS_FLOAT_3_HPP
#define DEMO_MATHS_FLOAT_3_HPP

#include <cstdio>
#include <cmath>
#include <maths/float2.h>

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

    explicit float3(float t)
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

    float length() const
    {
        return sqrt(length_squared());
    }

    float length_squared() const
    {
        return x * x + y * y + z * z;
    }

    float dot(float3 other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    static float3 zero()
    {
        return {0.0f, 0.0f, 0.0f};
    }

    static float3 one()
    {
        return {1.0f, 1.0f, 1.0f};
    }

    static float3 up()
    {
        return {0.0f, 1.0f, 0.0f};
    }

    static float3 down()
    {
        return {0.0f, -1.0f, 0.0f};
    }

    static float3 left()
    {
        return {-1.0f, 0.0f, 0.0f};
    }

    static float3 right()
    {
        return {1.0f, 0.0f, 0.0f};
    }

    static float3 forward()
    {
        return {0.0f, 0.0f, 1.0f};
    }

    static float3 backward()
    {
        return {0.0f, 0.0f, -1.0f};
    }

    float3 operator+(float3 const& other) const
    {
        return {x + other.x, y + other.y, z + other.z};
    }

    float3 operator-(float3 const& other) const
    {
        return {x - other.x, y - other.y, z - other.z};
    }

    float3 operator*(float3 const& other) const
    {
        return {x * other.x, y * other.y, z * other.z};
    }

    float3 operator*(const float scale) const
    {
        return {x * scale, y * scale, z * scale};
    }

    float3 operator/(float3 const& other) const
    {
        return {x / other.x, y / other.y, z / other.z};
    }

    float3 operator/(const float scale) const
    {
        return {x / scale, y / scale, z / scale};
    }

    float3 operator-() const
    {
        return {-x, -y, -z};
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

    bool operator==(float3 const& other) const
    {
        return x == other.x && y == other.y && x == other.z;
    }

    bool operator!=(float3 const& other) const
    {
        return x != other.x || y != other.y || x != other.z;
    }

    void print() const
    {
        printf("(%f, %f, %f)\n", x, y, z);
    }

    float3 normalise()
    {
        float l = length();
        this->x /= l;
        this->y /= l;
        this->z /= l;

        return *this;
    }

    static float3 cross(float3 l, float3 r)
    {
        float3 output;
        output.x = l.y * r.z - l.z * r.y;
        output.y = r.x * l.z - r.z * l.x;
        output.z = l.x * r.y - l.y * r.x;

        return output;
    }

    float const& operator[](int index) const
    {
        switch(index)
        {
        case 0:
            return x;
        case 1:
            return y;
        default:
            return z;
        }
    }

    float x, y, z;
};

#endif
