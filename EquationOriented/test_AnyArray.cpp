#include <iostream>
#include "Array.h"

#define log(x) std::cout << x << "\n";

extern "C" {
	void smul_(double* mat, int* nrow, int* ncol, double *vec, double* res);
}

//int main() {
//
//	int nrow = 3, ncol = 2;
//
//	std::cout << "Nrow: "; std::cin >> nrow;
//	std::cout << "Ncol: "; std::cin >> ncol;
//
//	Matrix<double> x(nrow, ncol);
//	Vector<double> y(ncol);
//	Vector<double> res(nrow);
//
//
//	int c = 1;
//	for (int i=0; i<nrow; i++){
//		for (int j=0; j<ncol; j++){
//			std::cout << "Mat(" << i << "," << j << "): ";
//			std::cin >> x(i, j);
//		}
//	}
//
//	for (int i = 0; i < y.size(); i++) {
//		std::cout << "Vec(" << i << "): ";
//		std::cin >> y(i);
//	}
//
//	log("Doing math in FORTRAN...");
//
//	smul_(x.getData(), &nrow, &ncol, y.getData(), res.getData());
//	log("Result vec");
//	for (int j=0; j<res.size(); j++){
//		log(res(j));
//	}
//
//	std::getchar();
//}
