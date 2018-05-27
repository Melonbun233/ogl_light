#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H
//this is a derived class inheriting from Light
//you should use this class instead of the original base class Light
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "shader.h"
#include "light.h"

#include <string>

using namespace glm;
using namespace std;

class SpotLight : public Ligght {
public:
	float cutoff; //the angle specifies light's radius. this value should between
				  // 0 - 180 (inclusive)
	//default constructor
	SpotLight() = default;
	//direction and position are both required for a spot light
	SpotLight(vec3 dir, vec3 pos, vec3 amb, vec3 diff, vec3 spec, float cut);

	//send all vectors to a specific shader with light's name
	void sendShader(Shader shader, const char *name) const override;
}