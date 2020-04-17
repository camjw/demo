#version 330 core

out vec4 fragColour;
in vec3 vertColour;

void main()
{
   fragColour = vec4(vertColour, 1.0);
}
