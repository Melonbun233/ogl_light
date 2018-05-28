#ifndef UTILS_H
#define UTILS_H
//this file contains all math and utility functions
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "stb_image.h"
#include "shader.h"
#include "light.h"
#include "pointLight.h"
#include "dirLight.h"
#include "spotLight.h"


//distance constant linear quadratic
extern int att_table_size;
extern float att_table[];

//load texture and configure it as GL_REPEAT and GL_LINEAR for magnification and 
//minization
//PRE:
//	path: path of the texture file, should be a image file
//	texture: texture int created by OpenGL function
void loadTexture(const std::string &path, int texture);

//send an array of point lights to a specific shader
void sendPointLights(PointLight lights[], int light_num, Shader &shader);
//send an array of directional lights to a specific shader
void sendDirLights(DirLight lights[], int light_num, Shader &shader);
//send an array of spot lights to a specific shader
void sendSpotLights(SpotLight lights[], int light_num, Shader &shader)

#endif