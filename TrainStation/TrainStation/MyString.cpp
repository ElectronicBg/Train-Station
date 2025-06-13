#include "MyString.h"
#pragma warning (disable : 4996)


namespace CONSTANTS {
	const size_t EMPTY = 0;
	const size_t DEF_MULTIPLIER = 2;
	const char TERMINATING_ZERO = '\0';
}

void MyString::freeDynamicMemory()
{
	delete[] string;
	string = nullptr;
	size = 0;
	capacity = 0;
}

void MyString::copyDynamicMemory(const MyString& other)
{
	capacity = other.capacity;

	string = new char[capacity];
	strcpy(string, other.string);

	size = other.size;
}

void MyString::resize(size_t newCapacity)
{
	char* newData = new char[newCapacity + 1];
	strcpy(newData, string);

	delete[] string;

	string = newData;
	capacity = newCapacity;
}

MyString::MyString()
{
	size = 0;
	capacity = 4;
	string = new char[capacity + 1];
	string[0] = '\0';
}

MyString::MyString(const MyString& other)
{
	copyDynamicMemory(other);
}

MyString::MyString(const char* string)
{
	size = strlen(string);
	capacity = size * 2;

	this->string = new char[capacity + 1];
	strcpy(this->string, string);
	this->string[size] = '\0';
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other) {
		freeDynamicMemory();
		copyDynamicMemory(other);
	}
	return*this;
}

MyString::~MyString()
{
	freeDynamicMemory();
}
bool MyString::empty() const
{
	if (size > CONSTANTS::EMPTY) {
		return false;
	}
	return true;
}

int MyString::getCapacity() const
{
	return this->capacity;
}

void MyString::shrinkToFit()
{
	resize(size);
}

void MyString::reserve(size_t newCapacity)
{
	resize(newCapacity);
}


// Modifiers
void MyString::pushBack(char element)
{
	if (size == capacity) {
		resize(capacity * CONSTANTS::DEF_MULTIPLIER);
	}

	string[size++] = element;
	string[size] = CONSTANTS::TERMINATING_ZERO;
}

void MyString::popBack()
{
	if (empty()) {
		throw std::out_of_range("Cannot pop from an empty stringing");
	}

	size--;
}

void MyString::clear()
{
	//freeDynamicMemory();
	//size = 0;
	//capacity = 4;

	//string = new char[capacity];
	//string[0] = CONSTANTS::TERMINATING_ZERO;

	size = 0;
	if (string) {
		string[0] = '\0';
	}
}

void MyString::insert(size_t index, char c)
{
	if (index > size) {
		throw std::out_of_range("Index out of range");
	}

	if (size == capacity)
		resize(capacity * CONSTANTS::DEF_MULTIPLIER);

	for (size_t i = size; i > index; i--) {
		string[i] = string[i - 1];
	}

	string[index] = c;
	size++;
}

void MyString::erase(size_t index)
{
	if (index >= size) {
		throw std::out_of_range("Index out of range in erase");
	}

	for (size_t i = index; i < size - 1; i++) {
		string[i] = string[i + 1];
	}

	size--;
	string[size] = CONSTANTS::TERMINATING_ZERO;
}

void MyString::swap(MyString& other)
{
	MyString temp(string);

	freeDynamicMemory();
	copyDynamicMemory(other);

	other.freeDynamicMemory();
	other.copyDynamicMemory(temp);
}

void MyString::append(const MyString& other)
{
	size_t newSize = this->size + other.size;

	if (newSize > this->capacity) {
		resize(newSize * CONSTANTS::DEF_MULTIPLIER);
	}


	for (size_t i = 0; i < other.size; i++) {
		this->string[this->size + i] = other.string[i];
	}

	this->size = newSize;
	this->string[newSize] = CONSTANTS::TERMINATING_ZERO;
}

const char* MyString::getString() const
{
	return string;
}

size_t MyString::getSize() const
{
	return size;
}

char& MyString::operator[](unsigned index)
{
	return string[index];
}

const char& MyString::operator[](unsigned index) const
{
	return string[index];
}

MyString& MyString::operator+=(const MyString& other)
{
	size_t expectedCapacity = size + other.size + 1;

	if (expectedCapacity > capacity)
		resize(expectedCapacity * 2);

	strncat(string, other.string, other.size);

	size += other.size;

	return *this;
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
	MyString res(lhs);
	res += rhs;

	return res;
}

std::istream& operator>>(std::istream& is, MyString& str)
{
	str.freeDynamicMemory();

	size_t size;
	is >> size;
	is.ignore();

	str.capacity = size * 2;
	str.string = new char[str.capacity];

	is.getline(str.string, size);

	str.size = size;

	return is;
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	os << str.getSize() << " " << str.getString() << std::endl;
	return os;
}

bool operator==(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.getString(), rhs.getString()) == 0;
}

bool operator!=(const MyString& lhs, const MyString& rhs)
{
	return !(lhs == rhs);
}

bool operator>(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.getString(), rhs.getString()) > 0;
}

bool operator>=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.getString(), rhs.getString()) >= 0;
}

bool operator<(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.getString(), rhs.getString()) < 0;
}

bool operator<=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.getString(), rhs.getString()) <= 0;
}