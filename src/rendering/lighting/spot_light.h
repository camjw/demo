#ifndef DEMO_SPOT_LIGHT_HPP
#define DEMO_SPOT_LIGHT_HPP

#include "rendering/data/shader.h"
#include <ecs/world.h>
#include <maths/colour.h>
#include <maths/float3.h>
#include <maths/float4.h>

struct SpotLight
{
    float3 direction;

    float inner_cone_angle;
    float outer_cone_angle;

    colour ambient;
    colour diffuse;
    colour specular;

    inline void bind(Shader* shader, int index, float3 position)
    {
        shader->set_float3("spotLights[" + std::to_string(index) + "].position", position);
        shader->set_float3("spotLights[" + std::to_string(index) + "].direction", direction);
        shader->set_float("spotLights[" + std::to_string(index) + "].inner_cone_angle", inner_cone_angle);
        shader->set_float("spotLights[" + std::to_string(index) + "].outer_cone_angle", outer_cone_angle);
        shader->set_float3("spotLights[" + std::to_string(index) + "].ambient", ambient.to_float3());
        shader->set_float3("spotLights[" + std::to_string(index) + "].diffuse", diffuse.to_float3());
        shader->set_float3("spotLights[" + std::to_string(index) + "].specular", specular.to_float3());
    }
};

REGISTER_COMPONENT(SpotLight, SpotLight)

#endif
