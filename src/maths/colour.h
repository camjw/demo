#ifndef WINTER_COLOUR_H
#define WINTER_COLOUR_H

#include "float4.h"
struct colour
{
    colour()
        : r(255)
        , g(255)
        , b(255)
        , a(255)
    {
    }

    colour(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        : r(r)
        , g(g)
        , b(b)
        , a(a)
    {
    }

    colour(uint8_t r, uint8_t g, uint8_t b)
        : r(r)
        , g(g)
        , b(b)
        , a(255)
    {
    }

    uint8_t r, g, b, a;

    float4 to_float4() const
    {
        return float4((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, (float)a / 255.0f);
    }

    float3 to_float3() const
    {
        return float3((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f);
    }

    static colour black()
    {
        return colour(0, 0, 0);
    }

    static colour white()
    {
        return colour(255, 255, 255);
    }

    static colour red()
    {
        return colour(255, 0, 0);
    }

    static colour blue()
    {
        return colour(0, 255, 0);
    }

    static colour green()
    {
        return colour(0, 0, 255);
    }
};

#endif // WINTER_COLOUR_H
