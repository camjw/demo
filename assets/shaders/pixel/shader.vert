#version 330 core
layout (location = 0) in vec2 inPosition;
layout (location = 1) in vec2 inTexCoord;

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
    TexCoords = inTexCoord;
    gl_Position = PROJECTION * VIEW * MODEL * vec4(inPosition, 0.0, 1.0);
}
