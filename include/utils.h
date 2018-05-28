#ifndef UTILS_H
#define UTILS_H
//this file contains all math and utility functions
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "stb_image.h"
#include "shader.h"


//distance constant linear quadratic
extern int att_table_size;
extern float att_table[];

//load texture and configure it as GL_REPEAT and GL_LINEAR for magnification and 
//minization
//PRE:
//	path: path of the texture file, should be a image file
//	texture: texture int created by OpenGL function
void loadTexture(const std::string &path, int texture);

#endif