#include "scop/ParserObj.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

ParserObj::ParserObj(std::string fileName) {
	std::array<float, 3>	tempf;
	std::array<int, 3>	tempi;
	std::ifstream			file;
	std::string				line;

	file.open(fileName);
	while(std::getline(file, line)) {
		lineIndex = 1; 
		if (line[0] == 'v' && line[1] == 't') {
			for (int i = 0; i < 3; i++) {
				vt.push_back(extractFloat(line, lineIndex + 1));
			}
			nbVt++;
		} else if(line[0] == 'v' && line[1] == 'n') {
			for (int i = 0; i < 3; i++) {
				vn.push_back(extractFloat(line, lineIndex + 1));
			}
			nbVn++;
		} else if (line[0] == 'v') {
			for (int i = 0; i < 3; i++) {
				v.push_back(extractFloat(line, lineIndex + 1));
			}
			nbV++;
		} else if(line[0] == 'f') {
			for (int i = 0; i < 3; i++) {
				tempi[i] = extractInt(line, lineIndex + 1);
			}
			f.push_back(tempi);
			if (lineIndex + 1) {
				tempi[0] = tempi[1];
				tempi[1] = tempi[2];
				tempi[2] = extractInt(line, lineIndex + 1);
				f.push_back(tempi);
				nbF++;
			}
			nbF++;
		} 
	}
}

int ParserObj::extractInt(std::string line, int start) {
	int temp;
	lineIndex = line.find(' ', start);
	temp = std::stoi(line.substr(start, lineIndex - start));
	return (temp);
}


float ParserObj::extractFloat(std::string line, int start) {
	float temp;
	lineIndex = line.find(' ', start);
	temp = std::stof(line.substr(start, lineIndex - start));
	return (temp);
}