#ifndef DEMO_RENDERBUFFER_H
#define DEMO_RENDERBUFFER_H

#include <algorithm>
#include <glad/glad.h>

class Renderbuffer
{
public:
    Renderbuffer(int width, int height)
    {
        glGenRenderbuffers(1, &id_);
        glBindRenderbuffer(GL_RENDERBUFFER, id_);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    Renderbuffer(const Renderbuffer&) = delete;
    Renderbuffer& operator=(const Renderbuffer&) = delete;

    Renderbuffer(Renderbuffer&& other) noexcept
    : id_(other.id_)
    {
        other.id_ = 0;
    }

    Renderbuffer& operator=(Renderbuffer&& other) noexcept
    {
        if (this != &other)
        {
            release();
            std::swap(id_, other.id_);
        }

        return *this;
    }

    inline void bind()
    {
        glBindRenderbuffer(GL_RENDERBUFFER, id_);
    }

    inline GLuint id() const
    {
        return id_;
    }

    inline void release()
    {
        glDeleteFramebuffers(1, &id_);
    }

private:
    GLuint id_;
};

#endif //DEMO_RENDERBUFFER_H
