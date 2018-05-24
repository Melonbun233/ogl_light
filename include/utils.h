#ifndef UTILS_H
#define UTILS_H
//this file contains all math and utility functions
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "stb_image.h"
#include "shader.h"

using namespace std;

//distance constant linear quadratic
extern int att_table_size;
extern float att_table[];

//load texture and configure it as GL_REPEAT and GL_LINEAR for magnification and 
//minization
//PRE:
//	path: path of the texture file, should be a image file
//	texture: texture int created by OpenGL function
void loadTexture(const char *path, int texture);

//set light's attenuation variables
//there are three variables: constant, linear and quadratic
//F_att = 1.0 / (constant + linear * d + quadratic * d ^ 2)
//where d is distance from the fragment to the lisght source
//PRE:
//	light: light object
//	distance: largest distance from a object to the light source
void setAttenuation(Light &light, float distance);

#endif