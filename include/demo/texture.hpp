#ifndef DEMO_TEXTURE_HPP
#define DEMO_TEXTURE_HPP

#include <cstdint>
#include <string>

enum TextureType
{
    NONE = 0,
    DIFFUSE = 1,
    SPECULAR = 2,
    NORMAL = 3,
    HEIGHT = 4,
};

std::string to_string(TextureType type)
{
    switch (type)
    {
        case (NONE):
        {
            return "texture_none";
        }
        case (DIFFUSE):
        {
            return "texture_diffuse";
        }
        case (SPECULAR):
        {
            return "texture_specular";
        }
        case (NORMAL):
        {
            return "texture_normal";
        }
        case (HEIGHT):
        {
            return "texture_height";
        }
    }

    return "";
}


struct Texture
{
    uint16_t id;
    std::string path;
    TextureType type;
};

#endif

