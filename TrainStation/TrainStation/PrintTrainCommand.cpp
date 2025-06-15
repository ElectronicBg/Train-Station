#include "PrintTrainCommand.h"
#include "Train.h"
#include "StationRepository.h"
#include "Station.h"
#include "Wagon.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>

#pragma warning(disable : 4996)

std::string formatDateTime(const std::chrono::system_clock::time_point& tp) {
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%d/%m/%Y %H:%M", std::localtime(&t));
    return buf;
}

void PrintTrainCommand::execute(const MyVector<MyString>& args, TrainSystemApp& app) const {
	if (args.getSize() != 2) {
		std::cout << "Usage: print-train <trainID>\n";
		return;
	}

	int trainId = args[1].parseToInt();
	const auto& stations = app.getStationRepo().getAllStations();
	std::shared_ptr<Train> found = nullptr;

	for (size_t i = 0; i < stations.getSize(); ++i) {
		const auto& deps = stations[i]->getDepartingTrains();
		for (size_t j = 0; j < deps.getSize(); ++j) {
			if (deps[j]->getId() == trainId) {
				found = deps[j];
				break;
			}
		}
		if (found) break;
	}

	if (!found) {
		std::cout << "Train with ID " << trainId << " not found.\n";
		return;
	}

	std::cout << "===Train ID: " << found->getId() << "===\n";
	std::cout << "Starting Station: " << found->getDepartureStation().getString() << "\n";
	std::cout << "Destination: " << found->getArrivalStation().getString() << "\n";
	std::cout << "Distance: " << found->getDistance() << " km\n";
	std::cout << "Speed: " << found->getSpeed() << " km/h\n";
	std::cout << "Departure Time: " << formatDateTime(found->getDepartureTime()) << "\n";
	std::cout << "Arrival Time: " << formatDateTime(found->getArrivalTime()) << "\n";
	std::cout << "Departure Platform: " << found->getDeparturePlatform() << "\n";

	std::cout << "Wagons:\n";
	const auto& wagons = found->getWagons();

	if (wagons.empty()) {
		std::cout << "  (none)\n";
	}
	else {
		for (size_t i = 0; i < wagons.getSize(); ++i) {
			auto w = wagons[i];
			std::cout << "  - Wagon ID: " << w->getId() << ", Type: ";

			switch (w->getType()) {
			case WagonType::FirstClass: std::cout << "FirstClass"; break;
			case WagonType::SecondClass: std::cout << "SecondClass"; break;
			case WagonType::Sleeper: std::cout << "Sleeper"; break;
			}

			std::cout << ", Seats: " << w->getSeatCount() << "\n";
		}
	}
}
