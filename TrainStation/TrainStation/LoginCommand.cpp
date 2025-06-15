#include "LoginCommand.h"

void LoginCommand::execute(const MyVector<MyString>& args, TrainSystemApp& app) const
{/*
	if (args.getSize() != 3) {
		std::cout << "Usage: login <username> <password>\n";
		return;
	}

	if (app.isAdminLoggedIn()) {
		std::cout << "An administrator is already logged in.\n";
		return;
	}

	const MyString& username = args[1];
	const MyString& password = args[2];

	try {
		AdminRepository& adminRepo = app.getAdminRepo();

		if (!adminRepo.isValidLogin(username, password)) {
			std::cout << "Invalid credentials.\n";
			return;
		}

		const MyVector<Admin>& admins = adminRepo.getAllAdmins();
		for (size_t i = 0; i < admins.getSize(); ++i) {
			if (admins[i].getUsername() == username) {
				app.setCurrentAdmin(&admins[i]);
				break;
			}
		}

		std::cout << "Login successful as '" << username << "'\n";
	}
	catch (const std::exception& ex) {
		std::cout << "Failed to login: " << ex.what() << "\n";
	}*/
}
