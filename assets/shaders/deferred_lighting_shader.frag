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
    vec3 colour;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define MAX_NUM_DIRECTIONAL_LIGHTS 4
#define MAX_NUM_POINT_LIGHTS 32

uniform DirectionalLight directionalLights[MAX_NUM_DIRECTIONAL_LIGHTS];
uniform PointLight pointLights[MAX_NUM_POINT_LIGHTS];

uniform int NUM_ACTIVE_DIRECTIONAL_LIGHTS;
uniform int NUM_ACTIVE_POINT_LIGHTS;

uniform vec3 CAMERA_POSITION;
uniform vec3 CAMERA_FORWARD;

// function prototypes
vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir, float specular, vec3 albedo);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, float specular, vec3 albedo);

void main()
{
    // retrieve data from G-buffer
    vec3 FragPos = texture(gPosition, TexCoords).xyz;
    vec3 Normal = texture(gNormal, TexCoords).xyz;
    vec3 Albedo = texture(gAlbedoSpec, TexCoords).rgb;
    float Specular = texture(gAlbedoSpec, TexCoords).a;

//    if (Specular < 1.0)
//    {
//        discard;
//    }

    // then calculate lighting as usual
    vec3 viewDir = normalize(CAMERA_FORWARD - FragPos);
    vec3 result = Albedo * 0.1; // hard-coded ambient component

    // phase 1: directional lighting
    for (int i = 0; i < NUM_ACTIVE_DIRECTIONAL_LIGHTS; i++)
    {
        result += CalcDirectionalLight(directionalLights[i], Normal, viewDir, Specular, Albedo);
    }

    // phase 2: point lights
    for(int i = 0; i < NUM_ACTIVE_POINT_LIGHTS; i++)
    {
        result += CalcPointLight(pointLights[i], Normal, FragPos, viewDir, Specular, Albedo);
    }

    FragColor = vec4(result.xyz, 1.0f);
}

// calculates the color when using a directional light.
vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir, float spec, vec3 albedo)
{
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);

    // combine results
    vec3 diffuse = light.diffuse * diff * albedo;
    vec3 specular = light.specular * spec;
    return (diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, float spec, vec3 albedo)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);

    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // combine results
    vec3 diffuse = light.diffuse * diff * albedo;
    vec3 specular = light.specular * spec;

    return light.colour * (diffuse + specular);
}
