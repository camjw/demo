#ifndef DEMO_POINT_LIGHT_H
#define DEMO_POINT_LIGHT_H

#include "rendering/data/shader.h"
#include <ecs/world.h>
#include <maths/colour.h>
#include <maths/float3.h>

struct PointLight
{
    colour main_colour;

    float constant;
    float linear;
    float quadratic;

    colour ambient;
    colour diffuse;
    colour specular;

    inline void bind(Shader* shader, int index, float3 position)
    {
        shader->set_float3("pointLights[" + std::to_string(index) + "].position", position);
        shader->set_float3("pointLights[" + std::to_string(index) + "].colour", main_colour.to_float3());
        shader->set_float("pointLights[" + std::to_string(index) + "].constant", constant);
        shader->set_float("pointLights[" + std::to_string(index) + "].linear", linear);
        shader->set_float("pointLights[" + std::to_string(index) + "].quadratic", quadratic);
        shader->set_float3("pointLights[" + std::to_string(index) + "].ambient", ambient.to_float3());
        shader->set_float3("pointLights[" + std::to_string(index) + "].diffuse", diffuse.to_float3());
        shader->set_float3("pointLights[" + std::to_string(index) + "].specular", specular.to_float3());
    }
};

REGISTER_COMPONENT(PointLight, PointLight)

#endif //DEMO_POINT_LIGHT_H
