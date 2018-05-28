#include "../include/utils.h"
using namespace std;
//this file contains all math and other utility functions

GLFWwindow* init(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT, const string name){
	//initiate glfw and window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, name.c_str(), NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//load glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to load glad" << endl;
		return NULL;
	}

	glEnable(GL_DEPTH_TEST);
	return window;
}

//load textures
void loadTexture(const string &path, int texture)
{
	int width, height, channels;
	glBindTexture(GL_TEXTURE_2D, texture);
	//set texture wrapping/filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//loading picture 
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);
	if (data) 
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, 
			GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		cout << path << " texture successfully loaded" << endl;
	}
	else 
	{
		cout << "Failed to load texture" << endl;
	}
	stbi_image_free(data);
}

void sendPointLights(PointLight lights[], int light_num, Shader &shader)
{
	shader.setInt("POINT_LIGHTS_NUM", light_num);
	for (int i = 0; i < light_num; i ++){
		lights[i].sendShader(shader, "pointLights[" + to_string(i) + "]");
	}
}

void sendDirLights(DirLight lights[], int light_num, Shader &shader)
{
	shader.setInt("DIR_LIGHTS_NUM", light_num);
	for (int i = 0; i < light_num; i ++){
		lights[i].sendShader(shader, "dirLights[" + to_string(i) + "]");
	}
}

void sendSpotLights(SpotLight lights[], int light_num, Shader &shader)
{
	shader.setInt("SPOT_LIGHTS_NUM", light_num);
	for (int i = 0; i < light_num; i ++){
		lights[i].sendShader(shader, "spotLights[" + to_string(i) + "]");
	}
}