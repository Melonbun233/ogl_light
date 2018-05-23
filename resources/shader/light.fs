#version 330 core

struct Material{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
out vec4 FragColor;

uniform Light light; 
uniform Material material;
uniform vec3 viewPos;
uniform float time;

void main()
{
	//calculate ambient
	vec3 ambient = light.ambient * vec3(texture(material.specular, TexCoords));

	//calculate diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.specular, TexCoords));

	//calculate specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

	//emission
	vec3 emission = vec3(texture(material.emission, TexCoords + vec2(0.0, time)));
	float fade = sin(time * 3) * 0.5 + 0.5;

	//result of all three components of phong light
	vec3 result;
	if (vec3(texture(material.specular, TexCoords)) == vec3(0))
		result = ambient + diffuse + specular + emission * fade;
	else
		result = ambient + diffuse + specular;

	FragColor = vec4(result, 1.0f);
}