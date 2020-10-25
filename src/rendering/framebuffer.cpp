#include "framebuffer.h"

Framebuffer::Framebuffer(int width, int height)
{
    glGenFramebuffers(1, &id_);

    render_texture = std::make_unique<Texture>(width, height);
    position_texture = std::make_unique<Texture>(width, height, GL_RGBA16F, GL_RGBA);
    normal_texture = std::make_unique<Texture>(width, height, GL_RGBA16F, GL_RGBA);
    albedo_texture = std::make_unique<Texture>(width, height);
    renderbuffer = std::make_unique<Renderbuffer>(width, height);

    bind();
    render_texture->bind(0);
    DEFAULT_TEXTURE_PROPERTIES.apply();
    attach(render_texture.get(), 0);

    position_texture->bind(1);
    DEFAULT_TEXTURE_PROPERTIES.apply();
    attach(position_texture.get(), 1);

    normal_texture->bind(2);
    DEFAULT_TEXTURE_PROPERTIES.apply();
    attach(normal_texture.get(), 2);

    albedo_texture->bind(3);
    DEFAULT_TEXTURE_PROPERTIES.apply();
    attach(albedo_texture.get(), 3);

    renderbuffer->bind();
    attach(renderbuffer.get());
    if (!is_complete())
    {
        printf("Frame buffer is not complete!\n");
    }

    unbind();
}

void Framebuffer::bind_render_texture(int bind_index) const
{
    render_texture->bind(bind_index);
}