#include "CommandFactory.h"
#include "PrintStationsCommand.h"
#include "LoginCommand.h"
#include "AddStationCommand.h"


Command* CommandFactory::create(const MyString& commandType) {
	if (commandType == "print-stations") {
		return new PrintStationsCommand();
	}
	else if (commandType == "login") {
		return new LoginCommand();
	}
	else if (commandType == "add-station") {
		return new AddStationCommand();
	}

	return nullptr;
}
