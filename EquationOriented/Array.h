#pragma once

#include <memory>
#include <vector>

#pragma region
// ============= ArrayAny =================
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
// ============= End Of ArrayAny =================
#pragma endregion ArrayAny end

// ============= Vector =================

// Class to represent a vector
template<class T>
class Vector {

private:
	// Variables
	// Raw data
	T* data ;
	// Size
	unsigned int _size ;

public:
	// Constructors and destructors
	Vector(const unsigned int size);
	Vector(const Vector<T>& obj);
	~Vector();

	// Functions
	// Return the current size of vector (number of elements>
	inline unsigned int size() const { return this->_size; }
	// Get the pointer to the raw data
	inline T* getData() const { return this->data; }
	// Return T element at index 'i'
	T& operator[](const unsigned int i);
	T& at(const unsigned int i);
	// Operator "=" overload
	void operator=(const Vector<T>& obj);


};

template<class T>
 Vector<T>::Vector(const unsigned int size)
	: _size(size)
{
	data = new T[this->_size];
}

template<class T>
Vector<T>::Vector(const Vector<T> & obj)
{
	this->_size = obj.size();
	data = new T[this->_size];
	for (unsigned int i = 0; i < this->_size; i++) {
		data[i] = *(obj.getData() + i);
	}
}

template<class T>
Vector<T>::~Vector()
{
	if (this->_size > 1)
		delete[] data;
	else
		delete data;
	data = nullptr;
}

// Return T element at index 'i'
template<class T>
T& Vector<T>::operator[](const unsigned int i)
{
	return this->at(i);
}

template<class T>
T & Vector<T>::at(const unsigned int i)
{
	#ifdef _DEBUG
	if (i < 0 || i >= this->_size)
		throw "OUT OF BOUNDS!";
	#endif
	return this->data[i];
}

template<class T>
void Vector<T>::operator=(const Vector<T>& obj)
{
	this->_size = obj.size();
	data = new T[this->_size];
	for (unsigned int i = 0; i < this->_size; i++) {
		data[i] = *(obj.getData() + i);
	}
}
