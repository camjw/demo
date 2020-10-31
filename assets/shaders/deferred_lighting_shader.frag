#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct GBufferData {
    vec3 frag_pos;
    vec3 normal;
    vec3 albedo;
    float specular;
};

#define MAX_NUM_DIRECTIONAL_LIGHTS 4
#define MAX_NUM_POINT_LIGHTS 32
#define MAX_NUM_SPOT_LIGHTS 32

uniform DirectionalLight directionalLights[MAX_NUM_DIRECTIONAL_LIGHTS];
uniform PointLight pointLights[MAX_NUM_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_NUM_SPOT_LIGHTS];

uniform int NUM_ACTIVE_DIRECTIONAL_LIGHTS;
uniform int NUM_ACTIVE_POINT_LIGHTS;
uniform int NUM_ACTIVE_SPOT_LIGHTS;

uniform vec3 CAMERA_POSITION;
uniform vec3 CAMERA_FORWARD;

vec3 calculate_directional_light_result(GBufferData data, DirectionalLight light, vec3 view_direction);
vec3 calculate_point_light_result(GBufferData data, PointLight light, vec3 view_direction);
vec3 calculate_spot_light_result(GBufferData data, SpotLight light, vec3 view_direction);

void main()
{
    vec3 frag_position = texture(gPosition, TexCoords).xyz;

    GBufferData g_buffer_data = GBufferData(
        frag_position,
        texture(gNormal, TexCoords).xyz,
        texture(gAlbedoSpec, TexCoords).rgb,
        texture(gAlbedoSpec, TexCoords).a
    );

    vec3 view_direction = normalize(CAMERA_POSITION - frag_position);
    vec3 result = g_buffer_data.albedo * 0.01;

    // phase 1: directional lighting
    for (int i = 0; i < NUM_ACTIVE_DIRECTIONAL_LIGHTS; i++)
    {
        result += calculate_directional_light_result(g_buffer_data, directionalLights[i], view_direction);
    }

    // phase 2: point lights
    for (int i = 0; i < NUM_ACTIVE_POINT_LIGHTS; i++)
    {
        result += calculate_point_light_result(g_buffer_data, pointLights[i], view_direction);
    }

    // phase 3: spot lights
    for (int i = 0; i < NUM_ACTIVE_SPOT_LIGHTS; i++)
    {
        result += calculate_spot_light_result(g_buffer_data, spotLights[i], view_direction);
    }

    FragColor = vec4(result.xyz, 1.0f);
}

// calculates the color when using a directional light.
vec3 calculate_directional_light_result(GBufferData data, DirectionalLight light, vec3 view_direction)
{
    // diffuse
    vec3 light_direction = normalize(-light.direction);
    float diff = max(dot(data.normal, light_direction), 0.0);
    vec3 diffuse = light.diffuse * diff * data.albedo;

    // specular
    vec3 reflect_direction = reflect(-light_direction, data.normal);
    float spec = pow(max(dot(view_direction, reflect_direction), 0.0), 16.0);
    vec3 specular = light.specular * spec * data.specular;
    return diffuse + specular;
}

vec3 calculate_point_light_result(GBufferData data, PointLight light, vec3 view_direction)
{
    // diffuse
    vec3 light_direction = normalize(light.position - data.frag_pos);
    vec3 diffuse = max(dot(data.normal, light_direction), 0.0) * data.albedo * light.diffuse;
    // specular
    vec3 halfway_direction = normalize(light_direction + view_direction);
    float spec = pow(max(dot(data.normal, halfway_direction), 0.0), 16.0);
    vec3 specular = light.specular * spec * data.specular;
    // attenuation
    float distance = length(light.position - data.frag_pos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
    diffuse *= attenuation;
    specular *= attenuation;

    return diffuse + specular;
}

vec3 calculate_spot_light_result(GBufferData data, PointLight light, vec3 view_direction)
{
    return vec3(0);
}
