#include <memory>
#include <iostream>
#include <vector>
#include "Array.h"


#define log(x) std::cout << x << "\n";

int main() {

	int shape = 5;

	Vector<int> x(shape);
	{
	Vector<int> y(shape);
	y[0] = 1;
	y[1] = 2;
	y[2] = 3;
	y[3] = 4;
	y[4] = 5;
	//y[10] = 1;
	x = y;
	}


	log("Array content")
	for (unsigned int i = 0; i < x.size(); i++) {
		log(x[i]);
	}

	std::getchar();
}
