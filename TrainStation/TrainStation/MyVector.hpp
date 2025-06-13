#pragma once
#include <iostream>

template<typename T>
class MyVector {
private:
	T* vector;
	size_t size;
	size_t capacity;

	void free();
	void copyFrom(const MyVector& other);
	void resize(size_t newCapacity);

	unsigned int getNextPowerOfTwo(unsigned int n) const;
	unsigned int allocateCapacity(unsigned int n) const;

public:
	// Constructors / Destructor / Assignment
	MyVector();
	MyVector(const MyVector& other);
	explicit MyVector(size_t capacity);
	MyVector(size_t size, const T* vector);
	MyVector& operator=(const MyVector& other);
	~MyVector();

	// Element access
	T   at(size_t index) const;
	const T& operator[](size_t index) const;
	T& operator[](size_t index);
	T   front() const;
	T   back() const;
	T* data() const;

	// Capacity
	bool  empty() const;
	size_t getSize() const;
	size_t getCapacity() const;
	void  shrinkToFit();
	void  reserve(size_t newCapacity);

	// Modifiers
	void pushBack(const T& element);
	void popBack();
	void clear();
	void insert(size_t index, const T& element);
	void erase(size_t index);
	void swap(MyVector& other);
	bool contains(const T& el) const;

	// Comparison
	bool operator==(const MyVector& other) const;

	template <typename D>
	friend std::istream& operator>>(std::istream& is, MyVector<D>& vector);

	template <typename D>
	friend std::ostream& operator<<(std::ostream& os, const MyVector<D>& vector);
};

namespace CONSTANTS {
	const size_t EMPTY = 0;
	const size_t DEF_MULTIPLIER = 2;
}

template<typename T>
void MyVector<T>::free() {
	delete[] vector;
}

template<typename T>
void MyVector<T>::copyFrom(const MyVector& other) {
	size = other.size;
	capacity = other.capacity;
	vector = new T[capacity];

	for (size_t i = 0; i < size; ++i) {
		vector[i] = other.vector[i];
	}
}

template<typename T>
void MyVector<T>::resize(size_t newCapacity) {
	T* buffer = new T[size];
	for (size_t i = 0; i < size; ++i) {
		buffer[i] = vector[i];
	}

	delete[] vector;
	capacity = newCapacity;
	vector = new T[capacity + 1];

	for (size_t i = 0; i < size; ++i) {
		vector[i] = buffer[i];
	}
	delete[] buffer;
}

template <typename T>
inline unsigned int MyVector<T>::getNextPowerOfTwo(unsigned int n) const
{
	if (n == 0) return 1;

	while (n & (n - 1))
	{
		n &= (n - 1);
	}

	return n << 1;
}

template <typename T>
inline unsigned int MyVector<T>::allocateCapacity(unsigned int n) const
{
	return std::max(getNextPowerOfTwo(n + 1), 8u);
}

template<typename T>
MyVector<T>::MyVector()
	: vector(new T[4])
	, size(0)
	, capacity(4)
{}

template<typename T>
MyVector<T>::MyVector(const MyVector& other) {
	copyFrom(other);
}

template<typename T>
MyVector<T>::MyVector(size_t capacity)
	: vector(new T[capacity])
	, size(0)
	, capacity(capacity)
{}

template<typename T>
MyVector<T>::MyVector(size_t size, const T* arr)
	: vector(new T[size * CONSTANTS::DEF_MULTIPLIER])
	, size(size)
	, capacity(size* CONSTANTS::DEF_MULTIPLIER)
{
	for (size_t i = 0; i < size; ++i) {
		vector[i] = arr[i];
	}
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
MyVector<T>::~MyVector() {
	free();
}

template<typename T>
T MyVector<T>::at(size_t index) const {
	if (index >= size) {
		throw std::out_of_range("Index out of range");
	}
	return vector[index];
}

template<typename T>
const T& MyVector<T>::operator[](size_t index) const {
	return at(index);
}

template<typename T>
T& MyVector<T>::operator[](size_t index) {
	return vector[index];
}

template<typename T>
T MyVector<T>::front() const {
	if (empty()) {
		throw std::out_of_range("MyVector is empty");
	}
	return vector[0];
}

template<typename T>
T MyVector<T>::back() const {
	if (empty()) {
		throw std::out_of_range("MyVector is empty");
	}
	return vector[size - 1];
}

template<typename T>
T* MyVector<T>::data() const {
	return vector;
}

template<typename T>
bool MyVector<T>::empty() const {
	return size == CONSTANTS::EMPTY;
}

template<typename T>
size_t MyVector<T>::getSize() const {
	return size;
}

template<typename T>
size_t MyVector<T>::getCapacity() const {
	return capacity;
}

template<typename T>
void MyVector<T>::shrinkToFit() {
	resize(size);
}

template<typename T>
void MyVector<T>::reserve(size_t newCapacity) {
	if (newCapacity > capacity)
		resize(newCapacity);
}

template<typename T>
void MyVector<T>::pushBack(const T& element) {
	if (size == capacity) {
		resize(capacity * CONSTANTS::DEF_MULTIPLIER);
	}
	vector[size] = element;
	size++;
}

template<typename T>
void MyVector<T>::popBack() {
	if (empty()) {
		throw std::out_of_range("Cannot pop from an empty vector");
	}
	--size;
}

template<typename T>
void MyVector<T>::clear() {
	delete[] vector;
	vector = nullptr;
	size = 0;
	capacity = 0;
}

template<typename T>
void MyVector<T>::insert(size_t index, const T& element) {
	if (index > size) {
		throw std::out_of_range("Index out of range");
	}
	if (size == capacity) {
		resize(capacity * CONSTANTS::DEF_MULTIPLIER);
	}
	for (size_t i = size; i > index; --i) {
		vector[i] = vector[i - 1];
	}
	vector[index] = element;
	++size;
}

template<typename T>
void MyVector<T>::erase(size_t index) {
	if (index >= size) {
		throw std::out_of_range("Index out of range in erase");
	}
	for (size_t i = index; i < size - 1; ++i) {
		vector[i] = vector[i + 1];
	}
	--size;
}

template<typename T>
void MyVector<T>::swap(MyVector& other) {
	MyVector<T> tmp(*this);
	free();
	copyFrom(other);
	other.free();
	other.copyFrom(tmp);
}

template<typename T>
inline bool MyVector<T>::contains(const T& el) const
{
	for (size_t i = 0; i < size; ++i) {
		if (vector[i] == el)
			return true;
	}
	return false;
}

template<typename T>
bool MyVector<T>::operator==(const MyVector& other) const {
	if (size != other.size) return false;
	for (size_t i = 0; i < size; ++i) {
		if (vector[i] != other.vector[i]) return false;
	}
	return true;
}

template <typename D>
inline std::istream& operator>>(std::istream& is, MyVector<D>& vector)
{
	is >> vector.size;
	vector.resize(vector.allocateCapacity(vector.getSize()));

	for (size_t i = 0; i < vector.getSize(); i++)
	{
		is >> vector.vector[i];
	}

	return is;
}

template <typename D>
inline std::ostream& operator<<(std::ostream& os, const MyVector<D>& vector)
{
	for (size_t i = 0; i < vector.getSize(); i++)
	{
		os << vector.vector[i] << " ";
	}

	os << std::endl;
	return os;
}