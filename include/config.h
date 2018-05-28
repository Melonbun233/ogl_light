#ifndef CONFIG_H
#define CONFIG_H
//this file contains all config functions used in this project, including the extern
//variables that are used in main function.
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "glm/glm.hpp"
#include "camera.h"

using namespace std;

extern float delta_time, MOUSE_X, MOUSE_Y;
extern Camera camera;
extern GLboolean MOUSE_FIRST;

//process user input in the render loop
//PRE:
// window: user's window
void processInput(GLFWwindow *window);

//this function is automatically called every time the window is resized
//PRE:
//	window: user's window
//	width: new window's width
//  height: new window's height
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

//this function is automatically called every time the window is resized
// extern GLboolean MOUSE_FIRST;
// extern float MOUSE_X, MOUSE_Y; //mouse's position
void mouse_callback(GLFWwindow *window, double x, double y);

//this function is automatically called every time the mouse is scrolled
void scroll_callback(GLFWwindow *window, double x, double y);

#endif 