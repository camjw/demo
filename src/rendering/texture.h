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
    int binding_index;
    explicit TextureComponent() = default;
    TextureComponent(TextureID id, int binding_index) : id(id), binding_index(binding_index) {};
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
        other.width = 0;
        other.height = 0;
        other.internal_format = 0;
        other.image_format = 0;
        other.wrap_s = 0;
        other.wrap_t = 0;
        other.filter_min = 0;
        other.filter_max = 0;
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
    GLuint internal_format;
    GLuint image_format;
    GLuint wrap_s;
    GLuint wrap_t;
    GLuint filter_min;
    GLuint filter_max;
};

#endif
