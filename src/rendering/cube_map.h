#ifndef DEMO_CUBE_MAP_HPP
#define DEMO_CUBE_MAP_HPP

#include <glad/glad.h>
#include <stb_image.h>

#include <cstdint>
#include <ecs/world.h>
#include <string>
#include <vector>

using CubeMapID = uint32_t;
const CubeMapID INVALID_CUBE_MAP = UINT32_MAX;

struct CubeMapComponent
{
    CubeMapID id = INVALID_CUBE_MAP;

    explicit CubeMapComponent() = default;
    explicit CubeMapComponent(CubeMapID id) : id(id) {};
};

REGISTER_COMPONENT(CubeMap, CubeMapComponent)

class CubeMap
{
public:
    CubeMap(const std::vector<std::string>& faces);
    inline GLuint id() const
    {
        return id_;
    }

    CubeMap(const CubeMap&) = delete;
    CubeMap& operator=(const CubeMap&) = delete;

    CubeMap(CubeMap&& other)
        : id_(other.id_)
    {
        other.id_ = 0;
    }

    CubeMap& operator=(CubeMap&& other)
    {
        if (this != &other)
        {
            release();
            std::swap(id_, other.id_);
        }

        return *this;
    }

    void bind() const;

    void release()
    {
        glDeleteTextures(1, &id_);
        id_ = 0;
    }
private:
    GLuint id_ = 0;
    void build(const std::vector<std::string>& faces);

    GLuint get_image_format(int num_channels) const;
};

#endif
