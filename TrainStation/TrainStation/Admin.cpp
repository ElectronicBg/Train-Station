#include "Admin.h"

Admin::Admin(const MyString& username, const MyString& password) : username(username), password(password)
{
}

const MyString& Admin::getUsername() const
{
	return username;
}

bool Admin::checkPassword(const MyString& pwd) const
{
	return password == pwd;
}
