#ifndef DEMO_DIRECTIONAL_LIGHT_HPP
#define DEMO_DIRECTIONAL_LIGHT_HPP

#include "shader.h"
#include <maths/float3.h>
#include <maths/float4.h>

struct DirectionalLight 
{
    float3 direction;
    float3 ambient;
    float3 diffuse;
    float3 specular;

    void bind(std::shared_ptr<Shader> shader)
    {
        shader->bind();
        shader->set_float3("directionalLight.direction", direction);
        shader->set_float3("directionalLight.ambient", ambient);
        shader->set_float3("directionalLight.diffuse", diffuse);
        shader->set_float3("directionalLight.specular", specular);
    }
};

#endif
