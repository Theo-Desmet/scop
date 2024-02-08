#include "scop/Maths.hpp"

int main () {
	Maths<float> maths;

	maths.createIdentity();
	maths.printMatrix();
}