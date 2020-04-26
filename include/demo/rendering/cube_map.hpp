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

        CubeMap(const CubeMap&) = delete;
        CubeMap& operator=(const CubeMap&) = delete;

        CubeMap(CubeMap &&other) : ID(other.ID) 
        {
            other.ID = 0;
        }

        CubeMap &operator=(CubeMap &&other)
        {
            if(this != &other)
            {
                release();
                std::swap(ID, other.ID);
            }

            return *this;
        }

        void build(const std::vector<std::string> faces);
        void bind() const;

    private:
        void release()
        {
            glDeleteTextures(1, &ID);
            ID = 0;
        }
};

#endif
