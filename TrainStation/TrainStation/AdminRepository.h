#pragma once
#include "Admin.h"
#include "MyVector.hpp"

class AdminRepository
{
	MyVector<Admin> admins;

public:
	void load(const MyString& filename);

	bool isValidLogin(const MyString& username, const MyString& password) const;

	const MyVector<Admin>& getAllAdmins() const;
};

