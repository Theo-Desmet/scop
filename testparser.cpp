#include "scop/ParserObj.hpp"
#include <iostream>

int main(int argc, char **argv) {
	ParserObj test(argv[1]);
	int i = 0;
	while (i < test.vertices.size()) {
		std::cout << '[' << test.vertices[i].Position[0]<< ", " << test.vertices[i].Position[1] << ", " << test.vertices[i].Position[2] << ']' << std::endl;
		std::cout << '[' << test.vertices[i].TextureCoords[0] << ", " << test.vertices[i].TextureCoords[1] << ']' << std::endl;
		std::cout << '[' << test.vertices[i].Normal[0] << ", " << test.vertices[i].Normal[1] << ", " << test.vertices[i].Normal[2] << ']' << std::endl << std::endl;
		i++;
	}
	// i= 0;
	// while (i < test.positions.size()) {
	// 	std::cout << '[' << test.positions[i][0] << ", " << test.positions[i][1] << ", " << test.positions[i][2] << ']' << std::endl;
	// 	i++;
	// }
	// i = 0;
	// while (i < test.textureCoords.size()) {
	// 	std::cout << '[' << test.textureCoords[i][0] << ", " << test.textureCoords[i][1] << ']' << std::endl;
	// 	i++;
	// }
	// i = 0;
	// while (i < test.normals.size()) {
	// 	std::cout << '[' << test.normals[i][0] << ", " << test.normals[i][1] << ", " << test.normals[i][2] << ']' << std::endl;
	// 	i++;
	// }
	// i = 0;
	// std::cout << std::endl;
	// while (i < nbF) {
	// 	std::cout << '[' << f[i][0] << " ," << f[i][1] << " ," << f[i][2] << ']' << std::endl;
	// 	i++;
	// }
}