#include <rendering/texture.h>

Texture::Texture()
    : internal_format(GL_RGBA)
    , image_format(GL_RGBA)
    , width(0)
    , height(0)
{
}

Texture::Texture(const std::string& filename)
    : Texture()
{
    int image_width, image_height, num_channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* image_data = stbi_load(filename.c_str(), &image_width, &image_height, &num_channels, 0);

    if (image_data == nullptr)
    {
        printf("Failed to load texture\n");
        return;
    }

    load_from_data(image_data, image_width, image_width, num_channels);
}

Texture::Texture(const aiTexture* assimp_texture)
    : Texture()
{
    unsigned char* image_data;
    int image_width, image_height, num_channels;

    if (assimp_texture->mHeight == 0)
    {
        image_data = stbi_load_from_memory(reinterpret_cast<unsigned char*>(assimp_texture->pcData), assimp_texture->mWidth, &image_width, &image_height, &num_channels, 0);
    }
    else
    {
        image_data = stbi_load_from_memory(reinterpret_cast<unsigned char*>(assimp_texture->pcData), assimp_texture->mWidth * assimp_texture->mHeight, &image_width, &image_height, &num_channels, 0);
    }

    if (image_data == nullptr)
    {
        printf("Failed to load texture\n");
        return;
    }

    load_from_data(image_data, image_width, image_width, num_channels);
}

void Texture::load_from_data(unsigned char* image_data, const int image_width, const int image_height, const int num_channels)
{
    glGenTextures(1, &ID);

    width = image_width;
    height = image_height;
    if (num_channels == 3)
    {
        image_format = GL_RGB;
        internal_format = GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
    }
    else if (num_channels == 4)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    }

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(image_data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind(int texture_index) const
{
    printf("Binding texture with id: %i\n", ID);
    glActiveTexture(GL_TEXTURE0 + texture_index);
    glBindTexture(GL_TEXTURE_2D, ID);
}
