#include "framebuffer.h"
#include <utils/opengl_helpers.h>

Framebuffer::Framebuffer(int width, int height)
{
    glGenFramebuffers(1, &id_);
    bind();

    position_texture = std::make_unique<Texture>(width, height, GL_RGBA16F, GL_RGBA);
    normal_texture = std::make_unique<Texture>(width, height, GL_RGBA16F, GL_RGBA);
    colour_texture = std::make_unique<Texture>(width, height);
    renderbuffer = std::make_unique<Renderbuffer>(width, height);

    position_texture->bind(0);
    DEFAULT_TEXTURE_PROPERTIES.apply();
    attach(position_texture.get(), 0);

    normal_texture->bind(1);
    DEFAULT_TEXTURE_PROPERTIES.apply();
    attach(normal_texture.get(), 1);

    colour_texture->bind(2);
    DEFAULT_TEXTURE_PROPERTIES.apply();
    attach(colour_texture.get(), 2);

    unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    glDrawBuffers(3, attachments);

    renderbuffer->bind();
    attach(renderbuffer.get());
    if (!is_complete())
    {
        printf("Frame buffer is not complete!\n");
    }

    unbind();
    glCheckError();
}

void Framebuffer::bind_textures() const
{
    position_texture->bind(0);
    normal_texture->bind(1);
    colour_texture->bind(2);
}

void Framebuffer::bind_texture(int texture_index) const
{
    normal_texture->bind(texture_index);
}