#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform vec3 lightColour;


void main()
{
    FragColor = vec4(lightColour, 1.0); // set all 4 vector values to 1.0
}
