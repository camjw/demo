#ifndef DEMO_RENDER_BUFFER_H
#define DEMO_RENDER_BUFFER_H

class RenderBuffer
{
public:
    RenderBuffer(int width, int height)
    {
        glGenRenderbuffers(1, &id_);
        glBindRenderbuffer(GL_RENDERBUFFER, id_);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    RenderBuffer(const RenderBuffer&) = delete;
    RenderBuffer& operator=(const RenderBuffer&) = delete;

    RenderBuffer(RenderBuffer&& other) noexcept
    : id_(other.id_)
    {
        other.id_ = 0;
    }

    RenderBuffer& operator=(RenderBuffer&& other) noexcept
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

#endif //DEMO_RENDER_BUFFER_H
