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
				vec2[i] = extractFloat(line, lineIndex + 1, &lineIndex, i);
			this->textureCoords.push_back(vec2);
		} else if(line[0] == 'v' && line[1] == 'n') {
			for (int i = 0; i < 3; i++)
				vec3[i] = extractFloat(line, lineIndex + 1, &lineIndex, i);
			this->normals.push_back(vec3);
		} else if (line[0] == 'v') {
			for (int i = 0; i < 3; i++)
				vec3[i] = extractFloat(line, lineIndex + 1, &lineIndex, i);
			this->positions.push_back(vec3);
		} else if(line[0] == 'f') {
			parseFaces(line);
		}
	}
	std::cout << min[0] << " " << max[0] << std::endl;
	std::cout << min[1] << " " << max[1] << std::endl;
	std::cout << min[2] << " " << max[2] << std::endl;
}

void	ParserObj::parseFaces(std::string line) {
	unsigned int lineIndex;
	std::string	split[3];
	int temp;
	
	lineIndex = 1;
	while (line[lineIndex] == ' ')
		lineIndex++;
	for (int i = 0; i < 3; i++) {
		temp = line.find(' ', lineIndex);
		split[i] = line.substr(lineIndex, temp - lineIndex);
		lineIndex = temp + 1;
	}
	
	createFaces(split);
	while (lineIndex && line.find_first_of("0123456789", lineIndex) != std::string::npos) {
		split[1] = split[2];
		temp = line.find_first_of(" ", lineIndex);
		if (temp != std::string::npos) 
			split[2] = line.substr(lineIndex, temp - lineIndex);
		else
			split[2] = line.substr(lineIndex);
		lineIndex = temp + 1;
		createFaces(split);
	}
}

void	ParserObj::createFaces(std::string *split) {
	Vertex 		tempVertex;
	glm::vec2	tempVec2;
	glm::vec3	tempVec3;

	unsigned int	findex = 0;
	float				deltaX = this->max[0] - this->min[0];
	float				deltaY = this->max[1] - this->min[1];
	float				deltaZ = this->max[2] - this->min[2];

	for (int i = 0; i < 3; i++) {
		if (split[i].find("//") != std::string::npos) { //pos//norm
			tempVertex.Position = this->positions[std::stof(split[i].substr(0, (split[i].find("/")))) - 1];
			tempVec2[0] = (tempVertex.Position[0] - this->min[0]) / deltaX;
			tempVec2[1] = (tempVertex.Position[1] - this->min[1]) / deltaY;
			tempVertex.TextureCoords = tempVec2;
			tempVertex.Normal = this->normals[std::stof(split[i].substr(split[i].find("/") + 2, (split[i].find("/")))) - 1];
		} else if ((findex = split[i].find("/")) != 0
				&& split[i].find("/", findex + 1) != std::string::npos) { //pos/text/norm
			tempVertex.Position = this->positions[std::stof(split[i].substr(0, findex)) - 1];
			tempVertex.TextureCoords = this->textureCoords[std::stof(split[i].substr(findex + 1, (split[i].find("/", findex + 1)))) - 1];
			// findex = split[i].find("/", findex);
			// tempVertex.Normal = this->normals[std::stof(split[i].substr(findex + 1, (split[i].find("/", findex + 1)))) - 1];
		} else if (split[i].find("/") != std::string::npos) { // pos/text/
			tempVertex.Position = this->positions[std::stof(split[i].substr(0, findex)) - 1];
			tempVertex.TextureCoords = this->textureCoords[std::stof(split[i].substr(findex + 1, (split[i].find("/", findex + 1)))) - 1];
		} else {
			tempVertex.Position = this->positions[std::stof(split[i]) - 1];
			tempVec2[0] = (tempVertex.Position[0] - this->min[0]) / deltaX;
			tempVec2[1] = (tempVertex.Position[1] - this->min[1]) / deltaY;
			tempVertex.TextureCoords = tempVec2;
		}
		this->vertices.push_back(tempVertex);
	}
}

float	ParserObj::extractFloat(std::string line, unsigned int start, unsigned int *lineIndex, int i) {
	float temp;
	*lineIndex = line.find(' ', start);
	temp = std::stof(line.substr(start, *lineIndex - start));
	if (temp > this->max[i]) this->max[i] = temp;
	if (temp < this->min[i]) this->min[i] = temp;
	return (temp);
}
