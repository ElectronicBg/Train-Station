#include "AdminRepository.h"

void AdminRepository::load()
{
	admins.pushBack(Admin("admin", "123"));
	admins.pushBack(Admin("ivan_admin", "123"));
}

bool AdminRepository::isValidLogin(const MyString& username, const MyString& password) const
{
	for (size_t i = 0; i < admins.getSize(); ++i) {
		if (admins[i].getUsername() == username && admins[i].checkPassword(password)) {
			return true;
		}
	}
	return false;
}

bool AdminRepository::login(const MyString& username, const MyString& password)
{
	if (isLoggedIn()) return false;

	for (size_t i = 0; i < admins.getSize(); ++i) {
		if (admins[i].getUsername() == username && admins[i].checkPassword(password)) {
			loggedInAdmin = &admins[i];
			return true;
		}
	}
	return false;
}

void AdminRepository::logout()
{
	loggedInAdmin = nullptr;
}

bool AdminRepository::isLoggedIn() const
{
	return loggedInAdmin != nullptr;
}

const Admin* AdminRepository::getLoggedAdmin() const
{
	return loggedInAdmin;
}

const MyVector<Admin>& AdminRepository::getAllAdmins() const
{
	return admins;
}