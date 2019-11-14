#ifndef ARRAY_H
#define ARRAY_H

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
	Vector(){}
	Vector(const unsigned int size);
	Vector(const Vector<T>& obj);
	~Vector();

	// Functions
	// Return the current size of vector (number of elements>
	inline unsigned int size() const { return this->_size; }
	// Get the pointer to the raw data
	inline T* getData() const { return this->data; }
	// Copy object (deep copy)
	void copy(const Vector <T>& obj);
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
	this->copy(obj);
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
inline void Vector<T>::copy(const Vector<T>& obj)
{
	this->_size = obj.size();
	delete[] data;
	data = new T[this->_size];
	//for (unsigned int i = 0; i < this->_size; i++) {
	//	data[i] = *(obj.getData() + i);
	//}
	memcpy(data, &obj, sizeof(obj.data));
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
	this->copy(obj);
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
	Matrix(){}
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
	// Return T element at index 'i', 'j'
	T& at(const unsigned int i, const unsigned int j);
	T& operator()(const unsigned int i, const unsigned int j);
	// Copy (deep) form obj
	void copy(const Matrix <T>& obj);
	void copy(const Vector <T>& obj);
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
	this->copy(obj);
}

template<class T>
Matrix<T>::Matrix(const Vector<T>& obj)
{
	this->copy(obj);
}

template<class T>
void Matrix<T>::copy(const Vector<T>& obj)
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
T& Matrix<T>::at(const unsigned int i, const unsigned int j)
{
	return data[i + _nrow*j];
}

template<class T>
T& Matrix<T>::operator()(const unsigned int i, const unsigned int j)
{
	return this->at(i, j);
}

template<class T>
inline void Matrix<T>::copy(const Matrix<T>& obj)
{
	_nrow = obj.numberOfRows();
	_ncol = obj.numberOfCols();
	_size = obj.size();
	delete[] data;
	data = new T[_size];
	for (unsigned int i = 0; i < _size; i++)
		data[i] = *(obj.getData()+i);
}

template<class T>
void Matrix<T>::operator=(const Matrix<T>& obj)
{
	this->copy(obj);
}

#pragma endregion Matrix

#endif // ARRAY_H
