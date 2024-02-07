#ifndef OBJ_HPP
#define OBJ_HPP

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "scop/Shader.hpp"

struct Vertex {
	glm::vec3	Position;
	glm::vec2	TextureCoords;
	glm::vec3	Normal;
};

struct Texture {
	unsigned int id;
	std::string type;
};

class Obj {
	public:
        std::vector<Vertex>       vertices;
        Texture      textures;

		Obj(std::string	objFileName);
		Obj(std::vector<Vertex> vertices, Texture textures);
        
		void Draw(Shader &shader);

	private:
	    unsigned int	VAO, VBO, EBO;
        void			setupObj();
};

#endif