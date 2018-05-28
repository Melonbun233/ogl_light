#include "../include/dirLight.h"

using namespace glm;
using namespace std;

DirLight::DirLight(vec3 dir, vec3 amb, vec3 diff, vec3 spec)
{
	direction = dir;
	position = vec3(0); //directional light doesn't have a direction
	ambient = amb;
	diffuse = diff;
	specular = spec;
}

void DirLight::sendShader(Shader &shader, const string &name) const
{

	string dir(name);
	string amb(name);
	string diff(name);
	string spec(name);

	shader.setVec3(dir.append(".direction"), direction);
	shader.setVec3(amb.append(".ambient"), ambient);
	shader.setVec3(diff.append(".diffuse"), diffuse);
	shader.setVec3(spec.append(".specular"), specular);
}