#ifndef DEMO_TEXTURE_HPP
#define DEMO_TEXTURE_HPP

#include <glad/glad.h>
#include <stb_image.h>

#include <assimp/texture.h>
#include <cstdint>
#include <ecs/ecs.h>
#include <string>

using TextureID = uint32_t;
const TextureID INVALID_TEXTURE = UINT32_MAX;

struct TextureComponent
{
    TextureID id;
    int binding_index;
    explicit TextureComponent() = default;
    TextureComponent(TextureID id, int binding_index)
        : id(id)
        , binding_index(binding_index) {};
};

MARK_AS_COMPONENT(TextureComponent)

struct Texture
{
    Texture();
    explicit Texture(const std::string& filename);
    explicit Texture(const aiTexture* assimp_texture);

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

    void bind(int texture_index) const;
    void destroy() {};
    void release()
    {
        glDeleteTextures(1, &ID);
        ID = 0;
    }

    inline GLuint get_id()
    {
        return ID;
    }

private:
    GLuint ID = 0;
    GLuint internal_format;
    GLuint image_format;
    GLuint width;
    GLuint height;
    void load_from_data(unsigned char* image_data, const int image_width, const int image_height, const int num_channels);
};

struct TextureProperties
{
    GLuint wrap_s;
    GLuint wrap_t;
    GLuint filter_min;
    GLuint filter_max;

    void apply()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_min);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_max);
    }
};

const TextureProperties DEFAULT_TEXTURE_PROPERTIES = TextureProperties {
    .wrap_s = GL_REPEAT,
    .wrap_t = GL_REPEAT,
    .filter_min = GL_LINEAR,
    .filter_max = GL_LINEAR,
};

#endif
