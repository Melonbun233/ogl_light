//this is a mesh class that containes an object's vertices, indices and textures
//this class also contains rendering functions
#include <vector>
#include <string>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "shader.h"
#include "../include/glm/glm.hpp"

enum TexType {
	ambient,
	diffuse,
	specular
	//emission; //not used
};

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

struct Texture {
	unsigned int ID;
	TexType type;
};


class Mesh {
public: 
	//mesh data
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	//default constructor
	Mesh() = default;

	//complete constructor
	Mesh(std::vector<Vertex> &vertex, std::vector<unsigned int> &index, std::vector<Texture> &tex):
		vertices(vertex), indices(index), textures(tex){
			setup();
		}

	//this function should be called every time you changed mesh's data
	void setup();
	//draw the mesh using provided shader
	void render(Shader &shader);
private:
	//rendering data
	unsigned int VAO, VBO, EBO;
};
