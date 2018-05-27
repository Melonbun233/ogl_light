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

using namespace glm;
using namespace std;

class PointLight() : public Light {
public:
	vec3 range;		//this light's range. large value results in large covering area

	//default constructor
	PointLight() = default;
	//direction is 0 because point light doesn't have a direction
	PointLight(vec3 pos, vec3 amb, vec3 diff, vec3 spec, vec3 range);

	//send all vectors to a specific shader with light's name
	void sendShader(Shader shader, const char *name) const override;

private:
	vec3 constant;	//constant coefficient of attenuation	
	vec3 linear;	//linear coefficient of attenuation
	vec3 quadra;	//quadra coefficient of attenuation
	//set all coefficients from range
	void setAttenuation();
}

#endif