#ifndef DEMO_FLOAT2_HPP
#define DEMO_FLOAT2_HPP

#include <cmath>

class float2
{
    public:
        inline float2(): x(0.0f), y(0.0f) {}
        inline float2(float _x, float _y): x(_x), y(_y) {}

        float x;
        float y;

        float2 operator + (float2 const &other)
        {
            return float2(x + other.x, y + other.y);
        }

        float2 operator - (float2 const &other)
        {
            return float2(x - other.x, y - other.y);
        }

        float2 operator * (float const l)
        {
            return float2(l * x, l * y);
        }

        float2 operator / (float const l)
        {
            return float2(x / l, y / l);
        }

        void operator += (float2 const &other)
        {
            x += other.x;
            y += other.y;
        }

        void operator *= (float const l)
        {
            x *= l;
            y *= l;
        }

        inline float magnitude_squared() 
        {
            return x * x + y * y;
        }
    
        inline float magnitude()
        {
            return sqrt(magnitude_squared());
        }
    
        inline float2 normalise()
        {
            float m = magnitude();
            return float2(x / m, y / m);
        }
};

#endif
