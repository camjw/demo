#version 330 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

in vec2 TexCoord;

uniform vec3 lightColour;

uniform Material material;

void main()
{
    FragColor = vec4(lightColour, 1.0); // set all 4 vector values to 1.0
}
