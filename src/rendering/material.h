#ifndef DEMO_MATERIAL_H
#define DEMO_MATERIAL_H

#include "shader.h"
#include <maths/float3.h>

struct Material
{
    float3 ambient;
    float3 diffuse;
    float3 specular;
    float shininess;

    void bind(std::shared_ptr<Shader> shader)
    {
        shader->set_float3("material.ambient", ambient);
        shader->set_float3("material.diffuse", diffuse);
        shader->set_float3("material.specular", specular);
        shader->set_float("material.shininess", shininess);
    }
};

const Material DEFAULT_MATERIAL = Material {
    .ambient = float3(0.105882, 0.058824, 0.113725),
    .diffuse = float3(0.427451, 0.470588, 0.541176),
    .specular = float3(0.333333, 0.333333, 0.521569),
    .shininess = 9.84615,
};

#endif // DEMO_MATERIAL_H
