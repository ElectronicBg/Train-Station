#include "AdminRepository.h"

void AdminRepository::load(const MyString& filename)
{

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

const MyVector<Admin>& AdminRepository::getAllAdmins() const 
{
	return admins;
}