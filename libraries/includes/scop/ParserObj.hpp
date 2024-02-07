#ifndef PARSER_OBJ_HPP
#define PARSER_OBJ_HPP

#include <vector>
#include <array>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "scop/Obj.hpp"
#include "scop/ParserObj.hpp"

class ParserObj{
	private:
		float min[3] = {10000000000};
		float max[3] = {-10000000000};
		
		float	extractFloat(std::string line, unsigned int start, unsigned int *lineIndex, int i);
		void	parseFaces(std::string line);
		void	createFaces(std::string *split);

	public:
		ParserObj(std::string fileName);
		std::vector<Vertex> vertices;
		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> textureCoords;
};
#endif