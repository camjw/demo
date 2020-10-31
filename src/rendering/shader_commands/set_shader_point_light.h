#ifndef DEMO_SET_SHADER_POINT_LIGHT_H
#define DEMO_SET_SHADER_POINT_LIGHT_H

class SetShaderPointLight
{
public:
    SetShaderPointLight(PointLight point_light, int light_index)
        : point_light(point_light)
        , light_index(light_index) {};

    inline void operator()(Shader* shader)
    {
        shader->bind();
        shader->set_float3("pointLight[" + std::to_string(light_index) + "].ambient", point_light.ambient);
        shader->set_float3("pointLight[" + std::to_string(light_index) + "].diffuse", point_light.diffuse);
        shader->set_float3("pointLight[" + std::to_string(light_index) + "].specular", point_light.specular);
        shader->set_float3("pointLight[" + std::to_string(light_index) + "].colour", point_light.colour);
        shader->set_float("pointLight[" + std::to_string(light_index) + "].constant", point_light.constant);
        shader->set_float("pointLight[" + std::to_string(light_index) + "].linear", point_light.linear);
        shader->set_float("pointLight[" + std::to_string(light_index) + "].quadratic", point_light.quadratic);
    }

private:
    PointLight point_light;
    int light_index;
};
#endif // DEMO_SET_SHADER_POINT_LIGHT_H
