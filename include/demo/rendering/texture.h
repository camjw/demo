#ifndef DEMO_TEXTURE_HPP
#define DEMO_TEXTURE_HPP

#include <glad/glad.h>
#include <stb_image.h>

#include <cstdint>
#include <string>

using TextureID = uint8_t;

struct TextureComponent
{
    TextureID id;
};

class Texture
{
public:
    Texture();
    explicit Texture(const std::string& filename);
    GLuint ID = 0;

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    Texture(Texture&& other) noexcept
        : ID(other.ID)
    {
        other.ID = 0;
    }

    Texture& operator=(Texture&& other) noexcept
    {
        if (this != &other)
        {
            release();
            std::swap(ID, other.ID);
        }

        return *this;
    }

    void build(const std::string& filename);
    void bind(int texture_index) const;
    void destroy() {};

private:
    void release()
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
};

#endif
