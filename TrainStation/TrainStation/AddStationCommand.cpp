#include "AddStationCommand.h"

void AddStationCommand::execute(const MyVector<MyString>& args, TrainSystemApp& app) const
{
	if (!app.isAdminLoggedIn()) {
		std::cout << "Admin privileges required.\n";
		return;
	}

	if (args.getSize() != 2) {
		std::cout << "Usage: add-station <stationName>\n";
		return;
	}

	const MyString& name = args[1];

	try {
		auto station = std::make_shared<Station>(name, 5);
		app.getStationRepo().addStation(station);
		std::cout << "Station '" << name << "' added successfully.\n";
	}
	catch (const std::exception& ex) {
		std::cout << "Failed to add station: " << ex.what() << "\n";
	}
}
