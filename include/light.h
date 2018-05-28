//This is parent light class for directional, positional, and spot lihgt class
//you should NOT use this class.
//you should use directional/positional/spot light instead of this one
#ifndef LIGHT_H
#define LIGHT_H

#include "glad/glad.h"
#include "glm/glm.hpp"
#include <string>

//include all other derived class
#include "dirLight.h"
#include "pointLihgt.h"
#include "spotLight.h"

#include "shader.h"


class Light
{
public:
	glm::vec3 direction;	//direction of the light. from light source to the fragment
	glm::vec3 position; 	//position of the light

	glm::vec3 ambient;	//ambient color and stength of it
	glm::vec3 diffuse;	//diffuse color and stength of it
	glm::vec3 specular;	//specular color and stength of it

	//default constructor
	Light() = default;
	Light(glm::vec3 dir, glm::vec3 pos, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec) 
		: direction(dir), position(pos), ambient(amb), diffuse(diff), specular(spec){}

	//this function send light's spec into the shader
	//Pre: 
	//	shader: shader needs to be configured
	//	name: light's name in the shader, the light should be the same type as 
	//	the light class here
	virtual void sendShader(Shader shader, const std::string &name) const {
		string str1(name);
		string str2(name);
		string str3(name);
		string str4(name);
		string str5(name);

		str1.append(".direction");
		shader.setVec3(str1, direction);
		str2.append(".position");
		shader.setVec3(str2, position);
		str3.append(".ambient");
		shader.setVec3(str3, ambient);
		str4.append(".diffuse");
		shader.setVec3(str4, diffuse);
		str5.append(".specular");
		shader.setVec3(str5, specular);
	}

}

#endif