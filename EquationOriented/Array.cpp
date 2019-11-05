//#include "Array.h"
//#pragma once
//#include <memory>
//#include <vector>
//
//// Constructor: Receives the shape as argumente
//template<class T>
//ArrayAny<T>::ArrayAny(std::vector<unsigned int> shape) :
//	_shape(shape) {
//	// Sets length
//	_length = 1;
//	for (unsigned int i = 0; i < _shape.size(); i++)
//		_length *= _shape[i];
//	// Allocates memory
//
//	//data = std::make_shared<T[_length]>;
//	data = new T[_length];
//}
//
//// Return if current array is an scalar
//template<class T>
//bool ArrayAny<T>::isScalar() const {
//	return _length == 1;
//}
//
//// Return the length of the array (total number of elements)
//template<class T>
//unsigned long ArrayAny<T>::length() const {
//	return _length;
//}
//
//// Return a integer vector containing the shape of the data
//template<class T>
//std::vector<unsigned int > ArrayAny<T>::shape() const {
//	return _shape;
//}
//
//// Return value at index i
//template<class T>
//T ArrayAny<T>::at(unsigned int i) {
//	return data[i];
//}
