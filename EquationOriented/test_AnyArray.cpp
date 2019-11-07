#include <memory>
#include <iostream>
#include <vector>
#include "Array.h"


#define log(x) std::cout << x << "\n";

int main() {

	int nrow = 3, ncol = 2;
	Matrix<int> x(nrow, ncol);

	int c = 1;
	for (int i=0; i<nrow; i++){
		for (int j=0; j<ncol; j++){
			x(i, j) = c++;
		}
	}

	for (int i=0; i<x.size(); i++){
		log(*(x.getData() + i));
	}

	std::getchar();
}
