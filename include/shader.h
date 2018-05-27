#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;
using namespace glm;

//define material and light struct
struct Light {
	vec4 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	//attenuation
	float constant;
	float linear;
	float quadra;
};

struct Material {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};

class Shader{

public: 
	//constructor that builds and reads the shader
	Shader(const char* vertexPath, const char* fragmentPath);

	//shader program ID
	int ID;

	//this function should be called before each rendering
	void use();

	//set a bool uniform in the shader
	void setBool(const char *name, bool value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	//set a integer uniform in the shader
	void setInt(const char *name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	//set a float uniform in the shader
	void setFloat(const char *name, float value) const {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	//set a mat4 unifrom in the shader
	void setMat4(const char *name, mat4 value) const {
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, value_ptr(value));
	}
	//set a vec3 uniform in the shader
	void setVec3(const char *name, vec3 value) const {
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, value_ptr(value));
	}
	//set a vec4 uniform in the shader
	void setVec4(const char *name, vec4 value) const {
		glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, value_ptr(value));
	}


private:
	// check whether shader is compiled succesfully
	void checkShaderSuccess(unsigned int shader, const char *type);
	// check whether shader program is succesfully linked
	void checkLinkSuccess(unsigned int ID);

};


#endif