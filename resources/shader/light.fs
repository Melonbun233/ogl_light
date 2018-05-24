#version 330 core

struct Material{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct Light {
	vec4 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadra;
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
	//check whether directional light
	bool directional = light.direction.w == 0.0;

	//calculate ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

	//calculate diffuse
	vec3 norm = normalize(Normal);
	//calculate light direction
	vec3 lightDir;
	if (directional) //directional light
		lightDir = normalize(-vec3(light.direction));
	else if (light.direction.w == 1.0) //positional light
		lightDir = normalize(vec3(light.direction) - FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

	//calculate specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

	//emission, not using
	vec3 emission = vec3(texture(material.emission, TexCoords + vec2(0.0, time)));
	float fade = sin(time * 3) * 0.5 + 0.5;

	//calculating light attenuation
	if (!directional) {
		float dis = length(vec3(light.direction) - FragPos);
		float att = 1.0 / (light.constant + light.linear * dis + light.quadra * (dis * dis));
		FragColor = vec4(att * (ambient + diffuse + specular), 1.0f);
	} else {
		FragColor = vec4(ambient + diffuse + specular, 1.0f);
	}

}