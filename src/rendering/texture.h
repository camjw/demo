#ifndef DEMO_TEXTURE_HPP
#define DEMO_TEXTURE_HPP

#include <glad/glad.h>
#include <stb_image.h>

#include <assimp/texture.h>
#include <cstdint>
#include <string>

using TextureID = uint32_t;
const TextureID INVALID_TEXTURE = UINT32_MAX;

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
    explicit Texture(const aiTexture* assimp_texture);
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

    void bind(int texture_index) const;
    void destroy() {};

private:
    void release()
    {
        glDeleteTextures(1, &ID);
        ID = 0;
    }

    void load_from_data(unsigned char* image_data, const int image_width, const int image_height, const int num_channels);

    GLuint width, height;
    GLuint internal_format;
    GLuint image_format;
    GLuint wrap_s;
    GLuint wrap_t;
    GLuint filter_min;
    GLuint filter_max;
};

#endif
