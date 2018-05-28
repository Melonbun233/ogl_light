#include "../include/utils.h"
using namespace std;
//this file contains all math and other utility functions

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
	for (int i = 0; i < light_num; i ++){
		lights[i].sendShader(shader, "pointLights[" + i + "]");
	}
}

void sendDirLights(DirLight lights[], int light_num, Shader &shader)
{
	for (int i = 0; i < light_num; i ++){
		lights[i].sendShader(shader, "dirLights[" + i + "]");
	}
}

void sendSpotLights(SpotLight lights[], int light_num, Shader &shader)
{
	for (int i = 0; i < light_num; i ++){
		lights[i].sendShader(shader, "SpotLights[" + i + "]");
	}
}