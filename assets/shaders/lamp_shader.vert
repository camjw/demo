#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform float TOTAL_TIME;
uniform float DELTA_TIME;

uniform mat4 MODEL;
uniform mat3 NORMAL_MODEL;
uniform mat4 VIEW;
uniform mat4 PROJECTION;

uniform vec3 CAMERA_POSITION;
uniform vec3 CAMERA_FORWARD;


void main()
{
	TexCoords = vec2(aTexCoord.x, aTexCoord.y);
    Normal = NORMAL_MODEL * aNormal;

    FragPos = vec3(MODEL * vec4(aPos, 1.0));
    gl_Position = PROJECTION * VIEW * vec4(FragPos, 1.0);
}
