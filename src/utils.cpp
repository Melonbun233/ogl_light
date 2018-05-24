#include "../include/utils.h"
//this file contains all math and other utility functions

int att_table_size = 12;
float att_table[] = {
	7.0, 	1.0, 	0.7, 	1.8,
	13.0, 	1.0, 	0.35, 	0.44,
	20.0, 	1.0, 	0.22, 	0.20,
	32.0, 	1.0, 	0.14, 	0.07,
	50.0, 	1.0, 	0.09, 	0.032,
	65.0, 	1.0, 	0.07, 	0.017,
	100.0, 	1.0, 	0.045, 	0.0075,
	160.0, 	1.0, 	0.027, 	0.0028,
	200.0, 	1.0, 	0.022, 	0.0019,
	325.0, 	1.0, 	0.014, 	0.0007,
	600.0, 	1.0, 	0.007, 	0.0002,
	3250.0, 1.0, 	0.0014, 0.000007
};

//load textures
void loadTexture(const char *path, int texture){
	int width, height, channels;
	glBindTexture(GL_TEXTURE_2D, texture);
	//set texture wrapping/filtering options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//loading picture 
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);
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

//get attenuation values
void setAttenuation(Light &light, float distance){
	for (int i = 0; i < att_table_size; i ++){
		if(distance <= att_table[i * 4]){
			light.constant = att_table[i * 4 + 1];
			light.linear = att_table[i * 4 + 2];
			light.quadra = att_table[i * 4 + 3];
			return;
		}
	}
	//range larger than the largest distance on the table
	light.constant = att_table[(att_table_size - 1) * 4 + 1];
	light.linear = att_table[(att_table_size - 1) * 4 + 2];
	light.quadra = att_table[(att_table_size - 1) * 4 + 3];
}