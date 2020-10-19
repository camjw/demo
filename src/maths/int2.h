#ifndef DEMO_INT2_H
#define DEMO_INT2_H

#include <cmath>
#include <cstdio>

struct int2
{
public:
    int2()
        : x(0)
        , y(0)
    {
    }
    int2(int x, int y)
        : x(x)
        , y(y)
    {
    }

    float length() const
    {
        return sqrt(length_squared());
    }

    int length_squared() const
    {
        return x * x + y * y;
    }

    int dot(int2 other) const
    {
        return x * other.x + y * other.y;
    }

    static int2 zero()
    {
        return { 0, 0 };
    }

    static float2 one()
    {
        return { 1, 1 };
    }

    int2 operator+(int2 const& other) const
    {
        return { x + other.x, y + other.y };
    }

    int2 operator-(int2 const& other) const
    {
        return { x - other.x, y - other.y };
    }

    int2 operator*(int2 const& other) const
    {
        return { x * other.x, y * other.y };
    }

    int2 operator*(const int scale) const
    {
        return { x * scale, y * scale };
    }

    float2 operator/(int2 const& other) const
    {
        return { (float)x / other.x, (float)y / other.y };
    }

    float2 operator/(const int scale) const
    {
        return { (float)x / scale, (float)y / scale };
    }

    float2 operator/(const float scale) const
    {
        return { x / scale, y / scale };
    }

    int2 operator-() const
    {
        return { -x, -y };
    }

    int2 operator+=(int2 const& other)
    {
        x += other.x;
        y += other.y;

        return *this;
    }

    int2 operator-=(int2 const& other)
    {
        x -= other.x;
        y -= other.y;

        return *this;
    }

    int2 operator*=(int2 const& other)
    {
        x *= other.x;
        y *= other.y;

        return *this;
    }

    int2 operator*=(const int scale)
    {
        x *= scale;
        y *= scale;

        return *this;
    }

    bool operator==(int2 const& other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(int2 const& other) const
    {
        return x != other.x || y != other.y;
    }

    void print() const
    {
        printf("(%i, %i)\n", x, y);
    }

    int const& operator[](int index) const
    {
        if (index == 0)
        {
            return x;
        }

        return y;
    }

    int x, y;
};

#endif // DEMO_INT2_H
