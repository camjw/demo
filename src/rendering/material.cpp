#include "material.h"

void Material::bind(Shader* shader)
{
    shader->set_float3("material.ambient_colour", ambient_colour);
    shader->set_float3("material.diffuse_colour", diffuse_colour);
    shader->set_float3("material.specular_colour", specular_colour);
    shader->set_float("material.shininess", shininess);
}
