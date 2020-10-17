#ifndef DEMO_FRAME_BUFFER_H
#define DEMO_FRAME_BUFFER_H

#include "render_buffer.h"
#include <string>
#include <unordered_map>

class FrameBuffer
{
public:
    FrameBuffer()
    {
        glGenFramebuffers(1, &id_);
    }

    inline void bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, id_);
    }

    FrameBuffer(const FrameBuffer&) = delete;
    FrameBuffer& operator=(const FrameBuffer&) = delete;

    FrameBuffer(FrameBuffer&& other) noexcept
    : id_(other.id_)
    {
        other.id_ = 0;
    }

    FrameBuffer& operator=(FrameBuffer&& other) noexcept
    {
        if (this != &other)
        {
            release();
            std::swap(id_, other.id_);
        }

        return *this;
    }

    inline GLuint id() const
    {
        return id_;
    }

    inline void unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    inline void release()
    {
        glDeleteFramebuffers(1, &id_);
    }

    inline void attach(Texture* texture, int binding_index)
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + binding_index, GL_TEXTURE_2D, texture->id(), 0);
    }

    inline void attach(Texture* texture, int binding_index, int mipmap_level)
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + binding_index, GL_TEXTURE_2D, texture->id(), mipmap_level);
    }

    inline void attach(RenderBuffer* render_buffer)
    {
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, render_buffer->id());
    }

    inline bool is_complete() const
    {
        return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
    }

private:
    GLuint id_;
    std::unordered_map<std::string, Texture*> attached_textures;
};

#endif //DEMO_FRAME_BUFFER_H
