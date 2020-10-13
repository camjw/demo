#version 330 core
out vec4 FragColor;

struct Material {
    vec3 ambient_colour;
    vec3 diffuse_colour;
    vec3 specular_colour;

    sampler2D diffuse_texture;
    sampler2D specular_texture;
    float shininess;
};

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
#define MAX_NUM_POINT_LIGHTS 10

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 CAMERA_POSITION;
uniform vec3 CAMERA_FORWARD;

uniform DirectionalLight directionalLights[MAX_NUM_DIRECTIONAL_LIGHTS];
uniform PointLight pointLights[MAX_NUM_POINT_LIGHTS];
uniform Material material;

uniform int NUM_ACTIVE_DIRECTIONAL_LIGHTS;
uniform int NUM_ACTIVE_POINT_LIGHTS;

// function prototypes
vec4 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{    
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(CAMERA_POSITION - FragPos);

    vec4 result = vec4(0);
    // phase 1: directional lighting
    for (int i = 0; i < NUM_ACTIVE_DIRECTIONAL_LIGHTS; i++)
    {
        result += CalcDirectionalLight(directionalLights[i], norm, viewDir);
    }
    // phase 2: point lights
    for(int i = 0; i < NUM_ACTIVE_POINT_LIGHTS; i++)
    {
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    }

    //FragColor = result;
    FragColor = texture(material.diffuse_texture, TexCoords);
}

// calculates the color when using a directional light.
vec4 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // combine results
    vec4 diffuse = vec4(light.diffuse, 1.0f) * diff * texture(material.diffuse_texture, TexCoords);
    vec4 specular = vec4(light.specular, 1.0f) * spec * texture(material.specular_texture, TexCoords);
    return (diffuse + specular);
}

// calculates the color when using a point light.
vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    // combine results
    vec4 diffuse = vec4(light.diffuse, 1.0f) * diff * texture(material.diffuse_texture, TexCoords);
    vec4 specular = vec4(light.specular, 1.0f) * spec * texture(material.specular_texture, TexCoords);

    return vec4(light.colour, 1.0f) * (diffuse + specular);
}
