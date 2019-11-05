#include <memory>
#include <iostream>
#include <vector>
#include "Array.h"


#define log(x) std::cout << x << "\n";

int main() {

	std::vector<unsigned int> shape(1);

	shape[0] = 10;

	ArrayAny<int> x(shape);

	for (int i = 0; i < shape[0]; i++)
		x[i] = i;

	log("Array content")
	for (int i = 0; i < shape[0]; i++)
		log(x[i]);

	std::getchar();
}
