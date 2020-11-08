#ifndef DEMO_MATHS_FLOAT_4_HPP
#define DEMO_MATHS_FLOAT_4_HPP

#include <cstdio>
#include <cmath>
#include <maths/float2.h>
#include <maths/float3.h>

struct float4
{

public:
    float4(): x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    float4(float x, float y, float z, float w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {
    }

    explicit float4(float t)
        : x(t)
        , y(t)
        , z(t)
        , w(t)
    {
    }

    float length() const
    {
        return sqrt(length_squared());
    }

    float length_squared() const
    {
        return x * x + y * y + z * z + w * w;
    }

    float dot(float4 other) const
    {
        return x * other.x + y * other.y + z * other.z + x * other.w;
    }

    static float4 zero()
    {
        return {0.0f, 0.0f, 0.0f, 0.0f};
    }

    static float4 one()
    {
        return {1.0f, 1.0f, 1.0f, 1.0f};
    }

    float4 operator+(float4 const& other) const
    {
        return {x + other.x, y + other.y, z + other.z, w + other.w};
    }

    float4 operator-(float4 const& other) const
    {
        return {x - other.x, y - other.y, z - other.z, w - other.w};
    }

    float4 operator*(float4 const& other) const
    {
        return {x * other.x, y * other.y, z * other.z, w * other.w};
    }

    float4 operator*(const float scale) const
    {
        return {x * scale, y * scale, z * scale, w * scale};
    }

    float4 operator/(float4 const& other) const
    {
        return {x / other.x, y / other.y, z / other.z, w / other.w};
    }

    float4 operator/(const float scale) const
    {
        return {x / scale, y / scale, z / scale, w / scale};
    }

    float4 operator-() const
    {
        return {-x, -y, -z, -w};
    }

    float4 operator+=(float4 const& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;

        return *this;
    }

    float4 operator-=(float4 const& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;

        return *this;
    }

    float4 operator*=(float4 const& other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        w *= other.w;

        return *this;
    }

    float4 operator*=(const float scale)
    {
        x *= scale;
        y *= scale;
        z *= scale;
        w *= scale;

        return *this;
    }

    float4 operator/=(float4 const& other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        w /= other.w;

        return *this;
    }

    float4 operator/=(const float scale)
    {
        x /= scale;
        y /= scale;
        z /= scale;
        w /= scale;

        return *this;
    }

    bool operator==(float4 const& other) const
    {
        return x == other.x && y == other.y && x == other.z && w == other.w;
    }

    bool operator!=(float4 const& other) const
    {
        return x != other.x || y != other.y || x != other.z || w != other.w;
    }

    void print() const
    {
        printf("(%f, %f, %f, %f)\n", x, y, z, w);
    }

    float4 normalise()
    {
        float l = length();
        this->x /= l;
        this->y /= l;
        this->z /= l;
        this->w /= l;

        return *this;
    }

    float const& operator[](int index) const
    {
        switch(index)
        {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        default:
            return w;
        }
    }

    operator float * () { return reinterpret_cast<float *>(this); }

    float x, y, z, w;
};

#endif
