#ifndef OBJ_HPP
#define OBJ_HPP

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "scop/Shader.hpp"

struct Vertex {
	glm::vec3	Position;
	glm::vec3	Normal;
	glm::vec2	TextureCoords;
};

struct Texture {
	unsigned int id;
	std::string type;
};

class Obj {
	public:
        std::vector<Vertex>       vertices;
        // std::vector<unsigned int> id;
        Texture      textures;

		Obj(std::string	objFileName);
		Obj(std::vector<Vertex> vertices, Texture textures);
        
		void Draw(Shader &shader);

	private:
	    unsigned int VAO, VBO, EBO;
        void setupObj();
};

#endif