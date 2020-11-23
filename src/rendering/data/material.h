#ifndef DEMO_MATERIAL_H
#define DEMO_MATERIAL_H

#include "shader.h"
#include "texture.h"
#include <maths/colour.h>
#include <maths/float3.h>
#include <resources/resource_handle.h>

enum RenderMode
{
    OPAQUE,
    TRANSPARENT,
};

inline RenderMode render_mode_from_string(const std::string& render_mode)
{
    std::string render_mode_lower = render_mode;
    std::transform(render_mode_lower.begin(), render_mode_lower.end(), render_mode_lower.begin(), ::tolower);
    if (render_mode_lower == "transparent")
    {
        return RenderMode::TRANSPARENT;
    }

    return RenderMode::OPAQUE;
}

struct Material
{
    // only should be used if neither of the textures are set
    colour ambient_colour;
    colour diffuse_colour;
    colour specular_colour;

    ResourceHandle diffuse_texture = ResourceHandle::invalid_handle<Texture>();
    ResourceHandle specular_texture = ResourceHandle::invalid_handle<Texture>();

    TextureProperties diffuse_texture_properties = DEFAULT_TEXTURE_PROPERTIES;
    TextureProperties specular_texture_properties = DEFAULT_TEXTURE_PROPERTIES;

    ResourceHandle shader = ResourceHandle::invalid_handle<Shader>();

    float shininess;

    bool is_using_texture = true;

    RenderMode render_mode = RenderMode::OPAQUE;

    void bind(Shader* shader);
};

#endif // DEMO_MATERIAL_H
