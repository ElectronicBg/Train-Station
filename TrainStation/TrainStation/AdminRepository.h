#pragma once
#include "Admin.h"
#include "MyVector.hpp"

class AdminRepository
{
	MyVector<Admin> admins;
	const Admin* loggedInAdmin = nullptr;

public:
	void load();

	bool isValidLogin(const MyString& username, const MyString& password) const;

	bool isLoggedIn() const;

	bool login(const MyString& username, const MyString& password);

	void logout();

	const Admin* getLoggedAdmin() const;

	const MyVector<Admin>& getAllAdmins() const;
};

