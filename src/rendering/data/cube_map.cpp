#include <rendering/data/cube_map.h>

CubeMap::CubeMap(const std::vector<std::string>& faces)
{
    build(faces);
};

void CubeMap::build(const std::vector<std::string>& faces)
{
    glGenTextures(1, &this->id_);
    glBindTexture(GL_TEXTURE_CUBE_MAP, id_);

    stbi_set_flip_vertically_on_load(false);

    int width, height, num_channels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &num_channels, 0);
        if (data)
        {
            GLuint image_format = get_image_format(num_channels);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, image_format, width, height, 0, image_format, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            printf("Cube Map texture failed to load at path: %s\n", faces[i].c_str());
            stbi_image_free(data);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

GLuint CubeMap::get_image_format(int num_channels) const
{
    switch (num_channels)
    {
    case 1:
        return GL_RED;
    case 2:
        return GL_RG;
    case 3:
        return GL_RGB;
    default:
        return GL_RGBA;
    }
}

void CubeMap::bind() const
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->id_);
}
