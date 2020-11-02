#version 330 core
layout (location = 0) out vec4 gPosition;
layout (location = 1) out vec4 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

struct Material {
    sampler2D diffuse_texture;
    sampler2D specular_texture;
    float shininess;
    bool has_alpha_cutoff;
};

uniform Material material;

void main()
{
    vec4 diffuse_colour = texture(material.diffuse_texture, TexCoords);
    if (diffuse_colour.a < 1.0f && material.has_alpha_cutoff)
    {
        discard;
    }

    gAlbedoSpec.rgb = diffuse_colour.rgb;
    gAlbedoSpec.a = texture(material.specular_texture, TexCoords).r;
    gPosition = vec4(FragPos, 1.0f);
    gNormal = vec4(normalize(Normal), 1.0f);
}