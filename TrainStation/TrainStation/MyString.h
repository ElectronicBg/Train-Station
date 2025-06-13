#pragma once
#include <ostream>
#include <iostream>

class MyString
{
	char* string;
	size_t size;
	size_t capacity;

	void freeDynamicMemory();
	void copyDynamicMemory(const MyString& other);
	void resize(size_t newCapacity);

public:
	MyString();
	MyString(const MyString& other);
	MyString(const char* string);
	MyString& operator=(const MyString& other);
	~MyString();

	//Capacity
	bool empty()const;
	size_t getSize()const;
	int getCapacity()const;
	void shrinkToFit();
	void reserve(size_t newCapacity);

	//Modifiers
	void pushBack(char element);
	void popBack();
	void clear();
	void insert(size_t index, char element);
	void erase(size_t index);
	void swap(MyString& other);
	void append(const MyString& other);
	const char* getString()const;

	char& operator[](unsigned index);
	const char& operator[](unsigned index) const;

	MyString& operator+=(const MyString& other);

	friend MyString operator+(const MyString& lhs, const MyString& rhs);

	friend std::istream& operator>>(std::istream& is, MyString& str);
};
std::ostream& operator<<(std::ostream& os, const MyString& str);

bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);
bool operator<(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);
