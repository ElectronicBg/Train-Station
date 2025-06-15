#include "RemoveWagonCommand.h"
#include <iostream>

void RemoveWagonCommand::execute(const MyVector<MyString>& args, TrainSystemApp& app) const {
	if (!app.getAdminRepo().isLoggedIn()) {
		std::cout << "Admin privileges required.\n";
		return;
	}

	if (args.getSize() != 3) {
		std::cout << "Usage: remove-wagon <trainID> <wagonID>\n";
		return;
	}

	int trainId = args[1].parseToInt();
	int wagonId = args[2].parseToInt();

	std::shared_ptr<Train> targetTrain = nullptr;

	const auto& stations = app.getStationRepo().getAllStations();
	for (size_t i = 0; i < stations.getSize(); ++i) {
		const auto& trains = stations[i]->getDepartingTrains();
		for (size_t j = 0; j < trains.getSize(); ++j) {
			if (trains[j]->getId() == trainId) {
				targetTrain = trains[j];
				break;
			}
		}
		if (targetTrain) break;
	}

	if (!targetTrain) {
		std::cout << "Train with ID " << trainId << " not found.\n";
		return;
	}

	auto& wagons = const_cast<MyVector<std::shared_ptr<Wagon>>&>(targetTrain->getWagons());

	for (size_t i = 0; i < wagons.getSize(); ++i) {
		if (wagons[i]->getId() == wagonId) {
			if (wagons[i]->hasOccupiedSeats()) {
				std::cout << "Cannot remove wagon " << wagonId << " — it has occupied seats.\n";
				return;
			}

			removeWagonAtIndex(wagons, i);
			std::cout << "Wagon " << wagonId << " removed from train " << trainId << ".\n";
			return;
		}
	}

	std::cout << "Wagon " << wagonId << " not found in train " << trainId << ".\n";
}
