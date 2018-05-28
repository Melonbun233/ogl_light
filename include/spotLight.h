#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H
//this is a derived class inheriting from Light
//you should use this class instead of the original base class Light
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "shader.h"
#include "light.h"

#include <string>


class SpotLight : public Light {
public:
	float inner_cutoff; //the angle specifies light's radius. this value should between
				  // 0 - 180 (inclusive)
	float outer_cutoff;	
	//default constructor
	SpotLight() = default;
	//direction and position are both required for a spot light
	SpotLight(glm::vec3 dir, glm::vec3 pos, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, 
		float innner, float outer);

	//send all vectors to a specific shader with light's name
	void sendShader(Shader &shader, const std::string &name) const override;
};

#endif