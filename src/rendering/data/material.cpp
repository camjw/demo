#include "material.h"

void Material::bind(Shader* shader)
{
    shader->set_float3("material.ambient_colour", ambient_colour.to_float3());
    shader->set_float3("material.diffuse_colour", diffuse_colour.to_float3());
    shader->set_float3("material.specular_colour", specular_colour.to_float3());
    shader->set_float("material.shininess", shininess);
}
