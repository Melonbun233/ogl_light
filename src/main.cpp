#define STB_IMAGE_IMPLEMENTATION
#define PI 3.14159265
#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

#include "../include/camera.h"
#include "../include/shader.h"
#include "../include/config.h"
#include "../include/data.h"
#include "../include/utils.h"
#include "../include/light.h"
#include "../include/dirLight.h"
#include "../include/pointLight.h"
#include "../include/spotLight.h"

using namespace std;
using namespace glm;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;
const string window_name = "This is Light";
const string vshader_path = "../resources/shader/vshader.vs";
const string fshader_path = "../resources/shader/fshader.fs";
const string light_fshader_path = "../resources/shader/light.fs";
const string lamp_fshader_path = "../resources/shader/lamp.fs";

float delta_time = 0.0;
float current_frame = 0.0;
float last_frame = 0.0;
extern float cube_vertices[];
extern vec3 cube_pos[];

//setting up camera
Camera camera = Camera(vec3(0, 0, 6));
float MOUSE_X, MOUSE_Y;
GLboolean MOUSE_FIRST = true;
GLboolean MOUSE_VERTICAL_INVERSE = true;
GLboolean MOUSE_HORIZONTAL_INVERSE = false;

int main(){
	GLFWwindow *window = init(SCR_WIDTH, SCR_HEIGHT, window_name);
	if(window == NULL)
		return -1;
	
	if(MOUSE_VERTICAL_INVERSE)
		camera.setMouseVerticalInverse(true);
	if(MOUSE_HORIZONTAL_INVERSE)
		camera.setMouseHorizontalInverse(true);

	Shader lampShader(vshader_path, lamp_fshader_path);
	Shader lightShader(vshader_path, light_fshader_path);

	//-----------------------load Vertices and Data--------------------------//
	//create VAO
	unsigned int cubeVAO, VBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);
	//setting vao
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, 
		GL_STATIC_DRAW);
	//vertex position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//vertex texture corrdinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 
		(void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//vertex normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
		(void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//light VAO
	unsigned int lampVAO;
	glGenVertexArrays(1, &lampVAO);
	glBindVertexArray(lampVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//--------------------------configure light------------------------------//
	//direction/position, ambient, diffuse, specular, direction
	lightShader.use();
	const int dirLightsNum = 1;
	const int pointLightsNum = 2;
	const int spotLightsNum = 2;
	DirLight dirLights[] = {
		DirLight(vec3(1.0, 1.0, 1.0), vec3(-0.2, -1.0, -0.3), vec3(0.05f), vec3(0.2f), vec3(0.8f))
	};

	PointLight pointLights[] = {
		PointLight(vec3(3.0, 2.0, -1.0), 50.0f),
		PointLight(vec3(0.0, 0.0, -15.0), 50.0f)
	};

	SpotLight spotLights[] = {
		SpotLight(vec3(-1.0, -2.0, -2.0), vec3(1.0, 2.0, 2.0), 20.0, 22.0),
		SpotLight(vec3(-3.0, -2.0, -1.0), vec3(3.0, 2.0, -1.0), 20.0, 23.0)
	};
	spotLights[0].color = vec3(0.0, 1.0, 0.0);
	
	//--------------------------material and texture----------------------------//
	unsigned int diffuse_map, specular_map, emission_map;
	glGenTextures(1, &diffuse_map);
	glGenTextures(1, &specular_map);
	glGenTextures(1, &emission_map);
	const string diffuse_path = "../resources/textures/container.png";
	const string specular_path = "../resources/textures/container_specular.png";
	const string emission_path = "../resources/textures/matrix.jpg";
	loadTexture(diffuse_path, diffuse_map);
	loadTexture(specular_path, specular_map);
	loadTexture(emission_path, emission_map);

	lightShader.use();
	lightShader.setInt("material.ambient", 0);  //TEXTURE0
	lightShader.setInt("material.diffuse", 1);	//TEXTURE1
	lightShader.setInt("material.specular", 2);	//TEXTURE2
	lightShader.setInt("material.emission", 3); //TEXTURE3
	lightShader.setFloat("material.shininess", 64.0);
	//-----------------------resndering loop---------------------------------//
	while (!glfwWindowShouldClose(window)){
		processInput(window);
		//update frame timer
		current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		last_frame = current_frame;
		//clear last frame
		glClearColor(0.25, 0.25, 0.25, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//update model, view, projection
		//drawing main object
		lightShader.use();
		mat4 view, proj;
		view = camera.getView();
		proj = perspective(radians(camera.getFOV()), float(SCR_WIDTH/SCR_HEIGHT), 
			0.1f, 100.0f);

		//light
		//sendDirLights(dirLights, dirLightsNum, lightShader);
		//sendPointLights(pointLights, pointLightsNum, lightShader);
		sendSpotLights(spotLights, spotLightsNum, lightShader);

		lightShader.setMat4("view", view);
		lightShader.setMat4("proj", proj);
		lightShader.setVec3("viewPos", camera.Position);

		//for this one, we use diffuse map as ambient map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuse_map);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, diffuse_map);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, specular_map);
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, emission_map);

		//draw objects
		glBindVertexArray(cubeVAO);
		for (int i = 0; i < 10; i ++)
		{
			mat4 model;
			model = translate(model, cube_pos[i]);
			float angle = 20.0f * i;
			model = rotate(model, radians(angle), vec3(1.0f, 0.3f, 0.5f));
			lightShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//drawing lamp
		lampShader.use();
		//drawing point lights
		for (int i = 0; i < pointLightsNum; i ++)
		{
			mat4 lampModel;
			lampModel = translate(lampModel, pointLights[i].position);
			lampModel = scale(lampModel, vec3(0.2f));
			lampShader.setMat4("model", lampModel);
			lampShader.setMat4("view", view);
			lampShader.setMat4("proj", proj);
			lampShader.setVec3("lightColor", pointLights[i].color);
			glBindVertexArray(lampVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//drawingg spot lights
		for (int i = 0; i < spotLightsNum; i ++)
		{
			mat4 lampModel;
			lampModel = translate(lampModel, spotLights[i].position);
			lampModel = scale(lampModel, vec3(0.2f));
			lampShader.setMat4("model", lampModel);
			lampShader.setMat4("view", view);
			lampShader.setMat4("proj", proj);
			lampShader.setVec3("lightColor", spotLights[i].color);
			glBindVertexArray(lampVAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lampVAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}