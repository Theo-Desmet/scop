#include "scop/ParserObj.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

ParserObj::ParserObj(std::string objFileName) {
	std::ifstream	file;
	std::string		line;
	glm::vec3		vec3;
	glm::vec2		vec2;
	unsigned int	lineIndex;
	int posi, texti, normi = 0;

	file.open(objFileName);

	while(std::getline(file, line)) {
		lineIndex = 1; 
		if (line[0] == 'v' && line[1] == 't') {
			lineIndex++;
			for (int i = 0; i < 2; i++)
				vec2[i] = extractFloat(line, lineIndex + 1, &lineIndex);
			this->textureCoords.push_back(vec2);
		} else if(line[0] == 'v' && line[1] == 'n') {
			lineIndex++;
			for (int i = 0; i < 3; i++)
				vec3[i] = extractFloat(line, lineIndex + 1, &lineIndex);
			this->normals.push_back(vec3);
		} else if (line[0] == 'v') {
			for (int i = 0; i < 3; i++)
				vec3[i] = extractFloat(line, lineIndex + 1, &lineIndex);
			this->positions.push_back(vec3);
		} else if(line[0] == 'f') {
			lineIndex++;
			parseFaces(line, lineIndex);
		}
	}
}

void	ParserObj::parseFaces(std::string line, unsigned int lineIndex) {
	std::string	split[4];
	int i = 0;
	unsigned int temp;
	Vertex tempVertex;

	for (; i < 3; i++) {
		temp = line.find(' ', lineIndex);
		split[i] = line.substr(lineIndex, temp - lineIndex);
		lineIndex = temp + 1;
	}
	if (lineIndex) {
		temp = line.find(' ', lineIndex);
		split[i++] = line.substr(lineIndex, temp - lineIndex);
	}
	unsigned int findex = 0;
	glm::vec3 fpos;
	glm::vec3 ftext;
	glm::vec3 fnorm;
	for (int j = 0; j < 3; j++) {
		if (split[j].find("//") != std::string::npos) { //pos//norm
			tempVertex.Position = this->positions[std::stoi(split[j].substr(0, split[j].find('/'))) - 1];
			tempVertex.Normal = this->normals[std::stoi(split[j].substr(split[j].rfind('/') + 1)) -1];
		} else if ((findex = split[j].find("/")) != 0
				&& split[j].find("/", findex + 1) != std::string::npos) { //pos/text/norm
			tempVertex.Position = this->positions[std::stoi(split[j].substr(0, split[j].find('/'))) - 1];
			tempVertex.TextureCoords = this->textureCoords[std::stoi(split[j].substr(findex + 1, split[j].find('/'))) - 1];
			tempVertex.Normal = this->normals[std::stoi(split[j].substr(split[j].rfind('/') + 1)) - 1];
		} else if (split[j].find("/") != std::string::npos) { // pos/text
			tempVertex.Position = this->positions[std::stoi(split[j].substr(0, split[j].find('/'))) - 1];
			tempVertex.TextureCoords = this->textureCoords[std::stoi(split[j].substr(findex + 1, split[j].find('/'))) - 1];
		} else { // pos
			tempVertex.Position = this->positions[std::stoi(split[j].substr(0, split[j].find('/'))) - 1];
		}
		this->vertices.push_back(tempVertex);
	}
}

float	ParserObj::extractFloat(std::string line, unsigned int start, unsigned int *lineIndex) {
	float temp;
	*lineIndex = line.find(' ', start);
	temp = std::stof(line.substr(start, *lineIndex - start));
	return (temp);
}
