#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;

// Globals
uniform float TOTAL_TIME;
uniform float DELTA_TIME;

uniform mat4 VIEW;
uniform mat4 PROJECTION;

uniform vec3 CAMERA_POSITION;
uniform vec3 CAMERA_FORWARD;

// Mesh specific
uniform mat4 model;

void main()
{
	gl_Position = PROJECTION * VIEW * model * vec4(aPos, 1.0);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
