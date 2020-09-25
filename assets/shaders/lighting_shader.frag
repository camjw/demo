#version 330 core
out vec4 FragColor;

//struct Material {
//    sampler2D diffuse;
//    sampler2D specular;
//    float shininess;
//};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
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
vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{    
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(CAMERA_POSITION - FragPos);

    vec3 result = vec3(0);
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

    FragColor = vec4(result, 1.0);
}

// calculates the color when using a directional light.
vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // combine results
    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * diff * material.diffuse;
    vec3 specular = light.specular * spec * material.specular;
    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
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
    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * diff * material.diffuse;
    vec3 specular = light.specular * spec * material.specular;

    return light.colour * (ambient + diffuse + specular);
}
