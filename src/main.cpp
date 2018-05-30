#define STB_IMAGE_IMPLEMENTATION
#define PI 3.14159265
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "config.h" //include all necessary header files

using namespace std;
using namespace glm;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;
const string window_name = "This is Light";

float delta_time = 0.0;
float current_frame = 0.0;
float last_frame = 0.0;

const extern float cube_vertices[];
const extern vec3 cube_pos[];

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

	//configure paths
	const string vshader_path = "../resources/shader/vshader.vs";
	const string fshader_path = "../resources/shader/fshader.fs";
	const string light_fshader_path = "../resources/shader/light.fs";
	const string lamp_fshader_path = "../resources/shader/lamp.fs";
	const string nano_suit_path = "../resources/models/nanosuit/nanosuit.obj";

	Shader nano_suit_shader(vshader_path, light_fshader_path);
	//--------------------------models---------------------------------------//
	Model nano_suit(nano_suit_path);

	//--------------------------configure light------------------------------//
	//direction/position, ambient, diffuse, specular, direction
	nano_suit_shader.use();
	const int dirLightsNum = 2;
	const int pointLightsNum = 2;
	const int spotLightsNum = 2;
	DirLight dirLights[] = {
		DirLight(vec3(1.0, 1.0, 1.0), vec3(-0.2, -1.0, -0.3), vec3(0.1), vec3(0.3), vec3(0.8)),
		DirLight(vec3(1.0, 0.0, 0.0), vec3(0.2, 1.0, 0.3), vec3(0.1), vec3(0.3), vec3(0.8))
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
		nano_suit_shader.use();
		mat4 model, view, proj;
		model = translate(model, vec3(0.0f, -1.75f, 0.0f));
		model = scale(model, vec3(0.2f, 0.2f, 0.2f));
		view = camera.getView();
		proj = perspective(radians(camera.getFOV()), float(SCR_WIDTH/SCR_HEIGHT), 
			0.1f, 100.0f);

		//light
		sendDirLights(dirLights, dirLightsNum, nano_suit_shader);
		sendPointLights(pointLights, pointLightsNum, nano_suit_shader);
		sendSpotLights(spotLights, spotLightsNum, nano_suit_shader);

		nano_suit_shader.setMat4("view", view);
		nano_suit_shader.setMat4("proj", proj);
		nano_suit_shader.setMat4("model", model);
		nano_suit_shader.setVec3("viewPos", camera.Position);

		//draw objects
		nano_suit.render(nano_suit_shader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}