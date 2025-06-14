#pragma once
#include <fstream>
#include "MyString.h"

inline void writeString(std::ofstream& ofs, const MyString& s)
{
	size_t len = s.getSize();
	ofs.write(reinterpret_cast<const char*>(&len), sizeof(len));
	ofs.write(s.getString(), len);
}

inline bool readString(std::ifstream& ifs, MyString& s)
{
	size_t len;
	ifs.read(reinterpret_cast<char*>(&len), sizeof(len));

	if (!ifs) {
		return false;
	}

	s.clear();
	s.reserve(len);

	char* buf = new char[len];
	ifs.read(buf, len);

	if (!ifs) {
		delete[] buf; return false;
	}

	for (size_t i = 0; i < len; ++i) {
		s.pushBack(buf[i]);
	}

	delete[] buf;

	return true;
}