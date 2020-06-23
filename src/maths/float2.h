#ifndef DEMO_MATHS_FLOAT_2_HPP
#define DEMO_MATHS_FLOAT_2_HPP

#include <cmath>
#include <cstdio>

struct float2
{
public:
    float2()
        : x(0.0f)
        , y(0.0f)
    {
    }
    float2(float x, float y)
        : x(x)
        , y(y)
    {
    }

    float length() const
    {
        return sqrt(length_squared());
    }

    float length_squared() const
    {
        return x * x + y * y;
    }

    float dot(float2 other) const
    {
        return x * other.x + y * other.y;
    }

    static float2 zero()
    {
        return { 0.0f, 0.0f };
    }

    static float2 one()
    {
        return { 1.0f, 1.0f };
    }

    float2 operator+(float2 const& other) const
    {
        return { x + other.x, y + other.y };
    }

    float2 operator-(float2 const& other) const
    {
        return { x - other.x, y - other.y };
    }

    float2 operator*(float2 const& other) const
    {
        return { x * other.x, y * other.y };
    }

    float2 operator*(const float scale) const
    {
        return { x * scale, y * scale };
    }

    float2 operator/(float2 const& other) const
    {
        return { x / other.x, y / other.y };
    }

    float2 operator/(const float scale) const
    {
        return { x / scale, y / scale };
    }

    float2 operator-() const
    {
        return { -x, -y };
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

    bool operator==(float2 const& other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(float2 const& other) const
    {
        return x != other.x || y != other.y;
    }

    void print() const
    {
        printf("(%f, %f)\n", x, y);
    }

    float const& operator[](int index) const
    {
        if (index == 0)
        {
            return x;
        }

        return y;
    }

    float x, y;
};

#endif
