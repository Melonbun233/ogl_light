#version 330 core

struct Material{
	sampler2D ambient;
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct DirLight {
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadra;
};

struct SpotLight {
	vec3 direction;
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float inner_cutoff;	
	float outer_cutoff;
};

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
out vec4 FragColor;

uniform int NUM_DIR_LIGHTS
uniform int NUM_POINT_LIGHTS
uniform int NUM_SPOT_LIGHTS

uniform DirLight dirLights[NUM_DIR_LIGHTS]; 
uniform PointLight pointLights[NUM_POINT_LIGHTS];
uniform SpotLight spotLights[NUM_SPOT_LIGHTS];

uniform Material material;
uniform vec3 viewPos;

//functions to calculate ambient, diffuse and specular
vec3 calcAmbient(vec3 light_amb);
vec3 calcDiffuse(vec3 light_diff, vec3 normal, vec3 lightDir);
vec3 calcSpecular(vec3 light_spec, vec3 normal, vec3 lightDir, vec3 viewDir);

//functions to calculate different light type
vec3 processDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 processPointLight(PointLight light, vec3 normal, vec3 viewDir);
vec3 processSpotLight(SpotLight light, vec3 normal, vec3 viewDir);

void main()
{
	//light properties
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 result = processDirLight(dirLight, norm, viewDir);
	result += processPointLight(pointLight, norm, viewDir);
	result += processSpotLight(spotLight, norm, viewDir);

	FragColor = vec4(result, 1.0);

}

vec3 processDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	vec3 ambient = calcAmbient(light.ambient);
	vec3 diffuse = calcDiffuse(light.diffuse, normal, lightDir);
	vec3 specular = calcSpecular(light.specular, normal, lightDir, viewDir);
	return (ambient + diffuse + specular);
}

vec3 processPointLight(PointLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - FragPos);
	vec3 ambient = calcAmbient(light.ambient);
	vec3 diffuse = calcDiffuse(light.diffuse, normal, lightDir);
	vec3 specular = calcSpecular(light.specular, normal, lightDir, viewDir);

	//calculate attenuation
	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear*distance + light.quadra*(distance*distance));

	return (ambient + diffuse + specular) * attenuation;
}

vec3 processSpotLight(SpotLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - FragPos);
	//calculate theta, angle between light direction and frag direction
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.inner_cutoff - light.outer_cutoff;
	float intensity = clamp((theta - light.outer_cutoff) / epsilon, 0.0, 1.0);
	vec3 ambient, diffuse, specular;
	//do light calculation
	ambient = calcAmbient(light.ambient);
	diffuse = calcDiffuse(light.diffuse, normal, lightDir);
	specular = calcSpecular(light.specular, normal, lightDir, viewDir);

	return ambient + intensity * (diffuse + specular);
}

vec3 calcAmbient(vec3 light_amb)
{
	return light_amb * vec3(texture(material.ambient, TexCoords));
}

vec3 calcDiffuse(vec3 light_diff, vec3 normal, vec3 lightDir)
{
	float diff = max(dot(normal, lightDir), 0.0);
	return light_diff * diff * vec3(texture(material.diffuse, TexCoords));
}

vec3 calcSpecular(vec3 light_spec, vec3 normal, vec3 lightDir, vec3 viewDir)
{
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	return light_spec * spec * vec3(texture(material.specular, TexCoords));
}






