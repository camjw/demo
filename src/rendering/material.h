#ifndef DEMO_MATERIAL_H
#define DEMO_MATERIAL_H

#include "shader.h"
#include "texture.h"
#include <maths/float3.h>

using MaterialID = uint32_t;
const MaterialID INVALID_MATERIAL = UINT32_MAX;

enum RenderMode
{
    OPAQUE,
    TRANSPARENT,
};

struct MaterialComponent
{
    MaterialID material_id = INVALID_MATERIAL;
    RenderMode render_mode = OPAQUE;

    explicit MaterialComponent() = default;

    MaterialComponent(MaterialID material_id, RenderMode render_mode)
        : material_id(material_id)
        , render_mode(render_mode)
    {
    }
};

REGISTER_COMPONENT(Material, MaterialComponent)

struct Material
{
    // only should be used if neither of the textures are set
    float3 ambient_colour;
    float3 diffuse_colour;
    float3 specular_colour;

    TextureID diffuse_texture = INVALID_TEXTURE;
    TextureID specular_texture = INVALID_TEXTURE;
    TextureProperties diffuse_texture_properties = DEFAULT_TEXTURE_PROPERTIES;
    TextureProperties specular_texture_properties = DEFAULT_TEXTURE_PROPERTIES;

    ShaderID shader;

    float shininess;

    Material(ShaderID shader, TextureID diffuse_texture, TextureID specular_texture, float shininess)
        : diffuse_texture(diffuse_texture)
        , specular_texture(specular_texture)
        , shader(shader)
        , shininess(shininess)
    {
    }

    Material(ShaderID shader, float3 ambient_colour, float3 diffuse_colour, float3 specular_colour, float shininess)
        : ambient_colour(ambient_colour)
        , diffuse_colour(diffuse_colour)
        , specular_colour(specular_colour)
        , shader(shader)
        , shininess(shininess)
    {
    }

    Material(ShaderID shader)
        : shader(shader)
    {
    }

    void bind(Shader* shader);

    Material() { }
};

inline Material pewter_material(ShaderID shader)
{
    return Material(
        shader,
        float3(0.105882, 0.058824, 0.113725),
        float3(0.427451, 0.470588, 0.541176),
        float3(0.333333, 0.333333, 0.521569),
        9.84615);
}

inline Material ruby_material(ShaderID shader)
{
    return Material(
        shader,
        float3(0.1745, 0.01175, 0.01175),
        float3(0.61424, 0.04136, 0.04136),
        float3(0.727811, 0.626959, 0.626959),
        76.8);
}

inline Material emerald_material(ShaderID shader)
{
    return Material(
        shader,
        float3(0.0215, 0.1745, 0.0215),
        float3(0.07568, 0.61424, 0.07568),
        float3(0.633, 0.727811, 0.633),
        76.8);
}

inline Material turquoise_material(ShaderID shader)
{
    return Material(
        shader,
        float3(0.1, 0.18725, 0.1745),
        float3(0.396, 0.74151, 0.69102),
        float3(0.297254, 0.30829, 0.306678),
        12.8);
}

#endif // DEMO_MATERIAL_H
