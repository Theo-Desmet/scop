#ifndef	MATH_HPP
#define MATH_HPP

#include <iostream>
#include <cmath>

template<class T>
struct vec2{
	T tab[2];
};

template<class T>
struct vec3{
	T tab[3];
};

template<class T>
class Maths {
	public:
		T matrix[16];

		Maths() {
			matrix[0] = 1.0f;
			matrix[1] = 0.0f;
			matrix[2] = 0.0f;
			matrix[3] = 0.0f;
			matrix[4] = 0.0f;
			matrix[5] = 1.0f;
			matrix[6] = 0.0f;
			matrix[7] = 0.0f;
			matrix[8] = 0.0f;
			matrix[9] = 0.0f;
			matrix[10] = 1.0f;
			matrix[11] = 0.0f;
			matrix[12] = 0.0f;
			matrix[13] = 0.0f;
			matrix[14] = 0.0f;
			matrix[15] = 1.0f;
		};
		
		void	printMatrix() {
			std::cout << "[" << matrix[0] << ", " << matrix[1] << ", " << matrix[2] << ", " << matrix[3] << "," << std::endl;
			std::cout << " " << matrix[4] << ", " << matrix[5] << ", " << matrix[6] << ", " << matrix[3] << "," << std::endl;
			std::cout << " " << matrix[8] << ", " << matrix[9] << ", " << matrix[10] << ", " << matrix[11] << "," << std::endl;
			std::cout << " " << matrix[12] << ", " << matrix[13] << ", " << matrix[14] << ", " << matrix[15] << "]" << std::endl;
		};

		void	add(T x, T y, T z) {
			matrix[0] += x;
			matrix[5] += y;
			matrix[10] += z;
		}
		
		void	sub(T x, T y, T z) {
			matrix[0] -= x;
			matrix[5] -= y;
			matrix[10] -= z;
		}
		
		void	scale(T x, T y, T z) {
			matrix[0] *= x;
			matrix[5] *= y;
			matrix[10] *= z;
		}

		void	translate(T x, T y, T z) {
			matrix[3] += x;
			matrix[7] += y;
			matrix[11] += z;
		}

		void	rotateX(float theta) {
			matrix[5] = std::cos(theta);
			matrix[6] = std::sin(theta) * -1;
			matrix[9] = std::sin(theta);
			matrix[10] = std::cos(theta);
		}

		void	rotateY(float theta) {
			matrix[0] = std::cos(theta);
			matrix[2] = std::sin(theta);
			matrix[8] = std::sin(theta) * -1;
			matrix[10] = std::cos(theta);
		}

		void	rotateZ(float theta) {
			matrix[0] = std::cos(theta);
			matrix[1] = std::sin(theta) * -1;
			matrix[4] = std::sin(theta);
			matrix[5] = std::cos(theta);
		}

	private:
		float PI = 3.14159265359;
};

#endif