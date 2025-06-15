#include "LoginCommand.h"

void LoginCommand::execute(const MyVector<MyString>& args, TrainSystemApp& app) const
{
	if (args.getSize() != 3) {
		std::cout << "Usage: login <username> <password>\n";
		return;
	}

	if (app.getAdminRepo().isLoggedIn()) {
		std::cout << "An administrator is already logged in.\n";
		return;
	}

	const MyString& username = args[1];
	const MyString& password = args[2];

	try {
		bool success = app.getAdminRepo().login(username, password);
		if (!success) {
			std::cout << "Invalid credentials.\n";
			return;
		}

		std::cout << "Login successful as '" << username.getString() << "'\n";
	}
	catch (const std::exception& ex) {
		std::cout << "Failed to login: " << ex.what() << "\n";
	}
}
