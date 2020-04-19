#ifndef DEMO_CUBE_MAP_HPP
#define DEMO_CUBE_MAP_HPP

#include <glad/glad.h>
#include <stb_image.h>

#include <cstdint>
#include <string>
#include <vector>

class CubeMap
{
public:
    CubeMap();
    GLuint ID = 0;

    //Delete the copy constructor/assignment.
    CubeMap(const CubeMap &) = delete;
    CubeMap &operator=(const CubeMap &) = delete;

    CubeMap(CubeMap &&other) : ID(other.ID)
    {
        other.ID = 0;
    }

    void build(const std::vector<std::string> faces);
    void bind() const;
};

#endif
