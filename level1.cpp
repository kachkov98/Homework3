#include <iostream>
#include "matrix.h"

int main ()
{
	LinearAlgebra::Matrix a =
	{{ 1,  2,  3,  4,  5},
	 { 6,  7,  8,  9, 10},
	 {11, 12, 13, 14, 15},
	 {16, 17, 18, 19, 20}};
	LinearAlgebra::Matrix b =
	{{1, 2, 3},
	 {4, 5, 6}};
	std::cout << "Matrix A:" << std::endl << a;
	std::cout << "Matrix B:" << std::endl << b;
	std::cout << "Kroneker product of A and B:" << std::endl << LinearAlgebra::KroneckerProduct(a, b);
	return 0;
}
