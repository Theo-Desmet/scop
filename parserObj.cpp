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
		while (line[lineIndex + 1] == ' ')
			lineIndex++;
		if (line[0] == 'v' && line[1] == 't') {
			for (int i = 0; i < 2; i++)
				vec2[i] = extractFloat(line, lineIndex + 1, &lineIndex);
			this->textureCoords.push_back(vec2);
		} else if(line[0] == 'v' && line[1] == 'n') {
			for (int i = 0; i < 3; i++)
				vec3[i] = extractFloat(line, lineIndex + 1, &lineIndex);
			this->normals.push_back(vec3);
		} else if (line[0] == 'v') {
			for (int i = 0; i < 3; i++)
				vec3[i] = extractFloat(line, lineIndex + 1, &lineIndex);
			this->positions.push_back(vec3);
		} else if(line[0] == 'f') {
			parseFaces(line);
		}
	}
}

void	ParserObj::parseFaces(std::string line) {
	unsigned int lineIndex;
	std::string	split[3];
	unsigned int temp;
	
	lineIndex = 1;
	while (line[lineIndex] == ' ')
		lineIndex++;
	for (int i = 0; i < 3; i++) {
		temp = line.find(' ', lineIndex);
		split[i] = line.substr(lineIndex, temp - lineIndex);
		lineIndex = temp + 1;
	}
	createFaces(split);
	if (lineIndex) {
		split[1] = split[2];
		temp = line.find(' ', lineIndex);
		split[2] = line.substr(lineIndex, temp - lineIndex);
		createFaces(split);
	}
	// while (line[lineIndex]) {
	// 	split[1] = split[2];
	// 	temp = line.find(' ', lineIndex);
	// 	split[2] = line.substr(lineIndex, temp - lineIndex);
	// 	lineIndex = temp + 1;
	// 	std::cout << line[lineIndex] << std::endl;
	// 	createFaces(split);
	// }
}

void	ParserObj::createFaces(std::string *split) {
	Vertex tempVertex;
	unsigned int findex = 0;

	for (int i = 0; i < 3; i++) {
		if (split[i].find("//") != std::string::npos) { //pos//norm
			tempVertex.Position = this->positions[std::stoi(split[i].substr(0, split[i].find('/'))) - 1];
			tempVertex.Normal = this->normals[std::stoi(split[i].substr(split[i].rfind('/') + 1)) -1];
		} else if ((findex = split[i].find("/")) != 0
				&& split[i].find("/", findex + 1) != std::string::npos) { //pos/text/norm
			tempVertex.Position = this->positions[std::stoi(split[i].substr(0, split[i].find('/'))) - 1];
			tempVertex.TextureCoords = this->textureCoords[std::stoi(split[i].substr(findex + 1, split[i].find('/'))) - 1];
			tempVertex.Normal = this->normals[std::stoi(split[i].substr(split[i].rfind('/') + 1)) - 1];
		} else if (split[i].find("/") != std::string::npos) { // pos/text/
			tempVertex.Position = this->positions[std::stoi(split[i].substr(0, split[i].find('/'))) - 1];
			tempVertex.TextureCoords = this->textureCoords[std::stoi(split[i].substr(findex + 1, split[i].find('/'))) - 1];
		} else { // pos//
			tempVertex.Position = this->positions[std::stoi(split[i].substr(0, split[i].find('/'))) - 1];
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
