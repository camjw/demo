#ifndef DEMO_MATHS_FLOAT_2_HPP
#define DEMO_MATHS_FLOAT_2_HPP

#include <math.h>
#include <cstdio>

struct float2
{
public:
    float2(): x(0.0f), y(0.0f) {}
    float2(float x, float y)
        : x(x)
        , y(y)
    {
    }

    float length()
    {
        return sqrt(length_squared());
    }

    float length_squared()
    {
        return x * x + y * y;
    }

    float dot(float2 other)
    {
        return x * other.x + y * other.y;
    }

    static float2 zero()
    {
        return float2(0.0f, 0.0f);
    }

    static float2 one()
    {
        return float2(1.0f, 1.0f);
    }

    float2 operator+(float2 const& other)
    {
        return float2(x + other.x, y + other.y);
    }

    float2 operator-(float2 const& other)
    {
        return float2(x - other.x, y - other.y);
    }

    float2 operator*(float2 const& other)
    {
        return float2(x * other.x, y * other.y);
    }

    float2 operator*(const float scale)
    {
        return float2(x * scale, y * scale);
    }

    float2 operator/(float2 const& other)
    {
        return float2(x / other.x, y / other.y);
    }

    float2 operator/(const float scale)
    {
        return float2(x / scale, y / scale);
    }

    float2 operator-()
    {
        return float2(-x, -y);
    }

    float2 operator+=(float2 const& other)
    {
        x += other.x;
        y += other.y;
        
        return *this;
    }

    float2 operator-=(float2 const& other)
    {
        x -= other.x;
        y -= other.y;
        
        return *this;
    }

    float2 operator*=(float2 const& other)
    {
        x *= other.x;
        y *= other.y;
        
        return *this;
    }

    float2 operator*=(const float scale)
    {
        x *= scale;
        y *= scale;
        
        return *this;
    }

    float2 operator/=(float2 const& other)
    {
        x /= other.x;
        y /= other.y;

        return *this;
    }

    float2 operator/=(const float scale)
    {
        x /= scale;
        y /= scale;
        
        return *this;
    }

    bool operator==(float2 const& other)
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(float2 const& other)
    {
        return x != other.x || y != other.y;
    }

    void print()
    {
        printf("(%f, %f)\n", x, y);
    }

    float x, y;
};

#endif
