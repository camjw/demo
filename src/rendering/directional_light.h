#ifndef DEMO_DIRECTIONAL_LIGHT_HPP
#define DEMO_DIRECTIONAL_LIGHT_HPP

#include "shader.h"
#include <ecs/world.h>
#include <maths/float3.h>
#include <maths/float4.h>

struct DirectionalLight 
{
    float3 direction;
    float3 ambient;
    float3 diffuse;
    float3 specular;

    inline void bind(std::shared_ptr<Shader> shader, int index)
    {
        shader->bind();
        shader->set_float3("directionalLights[" + std::to_string(index) + "].direction", direction);
        shader->set_float3("directionalLights[" + std::to_string(index) + "].ambient", ambient);
        shader->set_float3("directionalLights[" + std::to_string(index) + "].diffuse", diffuse);
        shader->set_float3("directionalLights[" + std::to_string(index) + "].specular", specular);
    }
};

REGISTER_COMPONENT(DirectionalLight, DirectionalLight)

#endif
