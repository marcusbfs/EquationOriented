#ifndef ARRAY_H
#define ARRAY_H

//#pragma region
//// ============= ArrayAny =================
//// Represents an multidimensinal array.
//// The raw data is stored in a column-major format (like Fortran)
//template<class T>
//class ArrayAny {
//public:
//	// Data is stored in a column-major format (like Fortran)
//	//std::shared_ptr<T[]> data;
//	T *data;
//	// Total number of elements in array
//	unsigned int _length = 0;
//	// Shape of the array
//	std::vector<unsigned int> _shape;
//
//	// Constructor
//	ArrayAny(std::vector<unsigned int> shape);
//
//	// Destructor
//	~ArrayAny();
//
//	// Return if current array is an scalar
//	bool isScalar() const;
//
//	// Return the length of the array (total number of elements)
//	unsigned long length() const;
//
//	// Return a integer vector containing the shape of the data
//	std::vector<unsigned int > shape() const;
//
//	// Return value at index i
//	T& at(unsigned int i);
//
//	// Operator [] overload to "at" function
//	T& operator[](unsigned int i);
//
//};
//
//// Constructor: Receives the shape as argument
//template<class T>
//ArrayAny<T>::ArrayAny(std::vector<unsigned int> shape) :
//	_shape(shape) {
//	// Sets length
//	_length = 1;
//	for (unsigned int i = 0; i < _shape.size(); i++)
//		_length *= _shape[i];
//	// Allocates memory
//
//	data = new T[_length];
//}
//
//// Destructor
//template<class T>
//ArrayAny<T>::~ArrayAny() {
//	delete[] data;
//	data = NULL;
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
//T& ArrayAny<T>::at(unsigned int i) {
//	return data[i];
//}
//
//// Operator [] overload to "at" function
//template<class T>
//T& ArrayAny<T>::operator[](unsigned int i) {
//	return this->at(i);
//}
//// ============= End Of ArrayAny =================
//#pragma endregion ArrayAny
//

#pragma region
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
	Vector();
	Vector(const unsigned int size);
	Vector(const Vector<T>& obj);
	~Vector();

	// Functions
	// Return the current size of vector (number of elements>
	inline unsigned int size() const { return this->_size; }
	// Get the pointer to the raw data
	inline T* getData() const { return this->data; }
	// Return T element at index 'i'
	T& at(const unsigned int i);
	T& operator()(const unsigned int i);
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
T& Vector<T>::operator()(const unsigned int i)
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
// ============= Vector =================
#pragma endregion Vector

#pragma region
// Class to represent a Matrix
template<class T>
class Matrix {

private:
	// Variables
	// Raw data
	T* data ;
	// Size = total number of elements
	unsigned int _size ;
	// Number of rows
	unsigned int _nrow ;
	// Number of columns
	unsigned int _ncol ;

public:
	// Constructors and destructors
	Matrix();
	Matrix(const unsigned int nrow, const unsigned int ncol);
	Matrix(const Matrix<T>& obj);
	Matrix(const Vector<T>& obj);
	~Matrix();

	// Functions
	// Return the current size of vector (number of elements>
	inline unsigned int size() const { return this->_size; }
	// Return the current number of rows
	inline unsigned int numberOfRows() const { return this->_nrow; }
	// Return the current number of columns
	inline unsigned int numberOfCols() const { return this->_ncol; }
	// Get the pointer to the raw data
	inline T* getData() const { return this->data; }
	// Return T element at index 'i', j
	T& at(const unsigned int i, const unsigned int j);
	T& operator()(const unsigned int i, const unsigned int j);
	// Operator "=" overload
	void operator=(const Matrix<T>& obj);
};

template<class T>
Matrix<T>::Matrix(const unsigned int nrow, const unsigned int ncol)
: _nrow(nrow), _ncol(ncol)
{
	_size = _nrow * _ncol;
	data = new T[_size];

}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& obj)
{
	_nrow = obj.numberOfRows();
	_ncol = obj.numberOfCols();
	_size = obj.size();
	data = new T[_size];
	for (unsigned int i = 0; i < _size; i++)
		data[i] = *(obj.getData()+i);
}

template<class T>
Matrix<T>::Matrix(const Vector<T>& obj)
{
	_nrow = obj.size();
	_ncol = 1;
	_size = _nrow;
	data = new T[_size];
	for (unsigned int i = 0; i < _size; i++)
		data[i] = *(obj.getData()+i);
}

template<class T>
Matrix<T>::~Matrix()
{
	if (_size > 0)
		delete[] data;
	else
		delete data;
	data = nullptr;
}

template<class T>
T & Matrix<T>::at(const unsigned int i, const unsigned int j)
{
	return data[i + _nrow*j];
}

template<class T>
T& Matrix<T>::operator()(const unsigned int i, const unsigned int j)
{
	return this->at(i, j);
}

template<class T>
void Matrix<T>::operator=(const Matrix<T>& obj)
{
	_nrow = obj.numberOfRows();
	_ncol = obj.numberOfCols();
	_size = obj.size();
	data = new T[_size];
	for (unsigned int i = 0; i < _size; i++)
		data[i] = *(obj.getData()+i);
}

#pragma endregion Matrix

#endif // ARRAY_H
