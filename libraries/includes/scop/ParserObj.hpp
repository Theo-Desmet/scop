#ifndef PARSER_OBJ_HPP
#define PARSER_OBJ_HPP

#include <vector>
#include <array>
#include <string>

class ParserObj{
	private:
	int extractInt(std::string line, int start);
	float extractFloat(std::string line, int start);
	int	lineIndex;

	public:
		ParserObj(std::string fileName);

		// std::vector<std::array<float, 3>> v;
		std::vector<float> v;
		std::vector<float> vt;
		std::vector<float> vn;
		std::vector<std::array<int, 3>> f;
		int	nbV = 0;
		int	nbVt = 0;
		int	nbVn = 0;
		int	nbF = 0;
};
#endif