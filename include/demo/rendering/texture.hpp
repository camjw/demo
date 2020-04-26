#ifndef DEMO_TEXTURE_HPP
#define DEMO_TEXTURE_HPP

#include <glad/glad.h>
#include <stb_image.h>

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

class Texture
{
public:
    Texture();
    GLuint ID = 0;

    Texture(const Texture &) = delete;
    Texture &operator=(const Texture &) = delete;

    Texture(Texture &&other) : ID(other.ID)
    {
        other.ID = 0; //Use the "null" texture for the old object.
    }

    Texture &operator=(Texture &&other)
    {
        //ALWAYS check for self-assignment.
        if(this != &other)
        {
            Release();
            //obj_ is now 0.
            std::swap(ID, other.ID);
        }
    }

    void build(const std::string& filename);
    void bind() const;
    inline TextureType get_type()
    {
        return type;
    }

private:
    void Release()
    {
        glDeleteTextures(1, &ID);
        ID = 0;
    }
    GLuint width, height;
    GLuint Internal_Format;
    GLuint Image_Format;
    GLuint Wrap_S;
    GLuint Wrap_T;
    GLuint Filter_Min;
    GLuint Filter_Max;

    TextureType type = TextureType::NONE;
};

#endif
