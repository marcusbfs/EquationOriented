#pragma once

#include <memory>
#include <vector>

// Represents an multidimensinal array.
// The raw data is stored in a column-major format (like Fortran)
template<class T>
class ArrayAny {
public:
	// Data is stored in a column-major format (like Fortran)
	//std::shared_ptr<T[]> data;
	T *data;
	// Total number of elements in array
	unsigned int _length = 0;
	// Shape of the array
	std::vector<unsigned int> _shape;

	// Constructor
	ArrayAny(std::vector<unsigned int> shape);

	// Destructor
	~ArrayAny();

	// Return if current array is an scalar
	bool isScalar() const;

	// Return the length of the array (total number of elements)
	unsigned long length() const;

	// Return a integer vector containing the shape of the data
	std::vector<unsigned int > shape() const;

	// Return value at index i
	T& at(unsigned int i);

	// Operator [] overload to "at" function
	T& operator[](unsigned int i);

};

// Constructor: Receives the shape as argument
template<class T>
ArrayAny<T>::ArrayAny(std::vector<unsigned int> shape) :
	_shape(shape) {
	// Sets length
	_length = 1;
	for (unsigned int i = 0; i < _shape.size(); i++)
		_length *= _shape[i];
	// Allocates memory

	data = new T[_length];
}

// Destructor
template<class T>
ArrayAny<T>::~ArrayAny() {
	delete[] data;
	data = NULL;
}

// Return if current array is an scalar
template<class T>
bool ArrayAny<T>::isScalar() const {
	return _length == 1;
}

// Return the length of the array (total number of elements)
template<class T>
unsigned long ArrayAny<T>::length() const {
	return _length;
}

// Return a integer vector containing the shape of the data
template<class T>
std::vector<unsigned int > ArrayAny<T>::shape() const {
	return _shape;
}

// Return value at index i
template<class T>
T& ArrayAny<T>::at(unsigned int i) {
	return data[i];
}

// Operator [] overload to "at" function
template<class T>
T& ArrayAny<T>::operator[](unsigned int i) {
	return this->at(i);
}
