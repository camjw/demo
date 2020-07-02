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
        shader->bind();
        shader->set_float3("material.ambient", ambient);
        shader->set_float3("material.diffuse", diffuse);
        shader->set_float3("material.specular", specular);
        shader->set_float("material.shininess", shininess);
    }
};

const Material PEWTER_MATERIAL = Material {
    .ambient = float3(0.105882, 0.058824, 0.113725),
    .diffuse = float3(0.427451, 0.470588, 0.541176),
    .specular = float3(0.333333, 0.333333, 0.521569),
    .shininess = 9.84615,
};

const Material RUBY_MATERIAL = Material {
    .ambient = float3(0.1745, 0.01175, 0.01175),
    .diffuse = float3(0.61424, 0.04136, 0.04136),
    .specular = float3(0.727811, 0.626959, 0.626959),
    .shininess = 76.8,
};

const Material EMERALD_MATERIAL = Material {
    .ambient = float3(0.0215, 0.1745, 0.0215),
    .diffuse = float3(0.07568, 0.61424, 0.07568),
    .specular = float3(0.633, 0.727811, 0.633),
    .shininess = 76.8,
};

const Material TURQUOISE_MATERIAL = Material
{
    .ambient = float3(0.1, 0.18725, 0.1745),
    .diffuse = float3(0.396, 0.74151, 0.69102),
    .specular = float3(0.297254, 0.30829, 0.306678),
    .shininess = 12.8,
};

#endif // DEMO_MATERIAL_H
