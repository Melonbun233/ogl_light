#ifndef POINT_LIGHT_H;
#define POINT_LIGHT_H;
//this is a derived class of Light
//you should use this class instead of original base class
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "shader.h"
#include "light.h"

#include <string>

class PointLight() : public Light {
public:
	glm::vec3 range;	//this light's range. large value results in large covering area

	//default constructor
	PointLight() = default;
	//direction is 0 because point light doesn't have a direction
	PointLight(glm::vec3 pos, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, glm::vec3 range);

	//send all vectors to a specific shader with light's name
	void sendShader(Shader shader, const std::string &name) const override;

private:
	glm::vec3 constant;	//constant coefficient of attenuation	
	glm::vec3 linear;	//linear coefficient of attenuation
	glm::vec3 quadra;	//quadra coefficient of attenuation
	//set all coefficients from range
	void setAttenuation();
}

#endif