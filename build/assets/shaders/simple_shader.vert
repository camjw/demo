#version 330 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColour;

out vec3 vertColour;

void main()
{
    vertColour = inColour;
    gl_Position = vec4(inPosition, 1.0);
}
