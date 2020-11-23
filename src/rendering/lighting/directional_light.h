#ifndef DEMO_DIRECTIONAL_LIGHT_HPP
#define DEMO_DIRECTIONAL_LIGHT_HPP

#include "rendering/data/shader.h"
#include <ecs/world.h>
#include <maths/float3.h>
#include <maths/colour.h>
#include <maths/float4.h>

struct DirectionalLight 
{
    float3 direction;
    colour ambient;
    colour diffuse;
    colour specular;

    inline void bind(Shader* shader, int index)
    {
        shader->set_float3("directionalLights[" + std::to_string(index) + "].direction", direction);
        shader->set_float3("directionalLights[" + std::to_string(index) + "].ambient", ambient.to_float3());
        shader->set_float3("directionalLights[" + std::to_string(index) + "].diffuse", diffuse.to_float3());
        shader->set_float3("directionalLights[" + std::to_string(index) + "].specular", specular.to_float3());
    }
};

REGISTER_COMPONENT(DirectionalLight, DirectionalLight)

#endif
