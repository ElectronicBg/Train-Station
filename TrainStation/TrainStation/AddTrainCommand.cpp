#include "AddTrainCommand.h"

void AddTrainCommand::execute(const MyVector<MyString>& args, TrainSystemApp& app) const
{
	if (!app.getAdminRepo().isLoggedIn()) {
		std::cout << "Admin privileges required.\n";
		return;
	}

	if (args.getSize() != 7) {
		std::cout << "Usage: add-train <from> <to> <distance> <speed> <date(dd/mm/yyyy)> <time(hh:mm)>\n";
		return;
	}

	const MyString& from = args[1];
	const MyString& to = args[2];
	double distance = args[3].parseToDouble();
	double speed = args[4].parseToDouble();
	const MyString& dateStr = args[5];
	const MyString& timeStr = args[6];

	try {
		auto& fromStation = app.getStationRepo().findStationByName(from);
		auto& toStation = app.getStationRepo().findStationByName(to);

		int day = std::atoi(dateStr.getString());
		int month = std::atoi(dateStr.getString() + 3);
		int year = std::atoi(dateStr.getString() + 6);
		int hour = std::atoi(timeStr.getString());
		int minute = std::atoi(timeStr.getString() + 3);

		std::tm tm = {};
		tm.tm_mday = day;
		tm.tm_mon = month - 1;
		tm.tm_year = year - 1900;
		tm.tm_hour = hour;
		tm.tm_min = minute;
		tm.tm_sec = 0;

		std::time_t departureTimestamp = std::mktime(&tm);
		if (departureTimestamp == -1) {
			std::cout << "Failed to convert date/time.\n";
			return;
		}
		auto departureTime = std::chrono::system_clock::from_time_t(departureTimestamp);

		int trainId = app.getStationRepo().getNewTrainId();

		auto train = fromStation->addTrain(trainId, to, departureTime, distance, speed);

		toStation->addArrivingTrain(train);

		std::cout << "Train " << trainId << " successfully added from " << from.getString() << " to " << to.getString() << ".\n";
	}
	catch (const std::exception& ex) {
		std::cout << "Error: " << ex.what() << "\n";
	}
}

