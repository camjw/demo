#include "framebuffer.h"

Framebuffer::Framebuffer(int width, int height)
{
    glGenFramebuffers(1, &id_);

    render_texture = std::make_unique<Texture>(width, height);
    renderbuffer = std::make_unique<Renderbuffer>(width, height);

    bind();
    render_texture->bind(0);
    TextureProperties::Default().apply();
    attach(render_texture.get(), 0);
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