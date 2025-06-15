#include "AddWagonCommand.h"
#include "FirstClassWagon.h"
#include "SecondClassWagon.h"
#include "SleeperWagon.h"
#include <iostream>

void AddWagonCommand::execute(const MyVector<MyString>& args, TrainSystemApp& app) const {
	if (!app.getAdminRepo().isLoggedIn()) {
		std::cout << "Admin privileges required.\n";
		return;
	}

	if (args.getSize() < 4) {
		std::cout << "Usage: add-wagon <trainID> <wagonType> <basePrice> [extra]\n";
		return;
	}

	int trainId = args[1].parseToInt();
	MyString type = args[2];
	double basePrice = args[3].parseToDouble();

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

	int newWagonId = (int)targetTrain->getWagons().getSize() + 1;
	std::shared_ptr<Wagon> wagon;

	if (type == "first-class") {
		if (args.getSize() < 5) {
			std::cout << "Usage for first class: add-wagon <trainID> first-class <basePrice> <comfortFactor>\n";
			return;
		}
		double comfort = args[4].parseToDouble();
		wagon = std::make_shared<FirstClassWagon>(newWagonId, basePrice, comfort);
	}
	else if (type == "second-class") {
		if (args.getSize() < 5) {
			std::cout << "Usage for second class: add-wagon <trainID> second-class <basePrice> <baggagePricePerKg>\n";
			return;
		}
		double baggage = args[4].parseToDouble();
		wagon = std::make_shared<SecondClassWagon>(newWagonId, basePrice, baggage);
	}
	else if (type == "sleeper") {
		if (args.getSize() < 5) {
			std::cout << "Usage for sleeper: add-wagon <trainID> sleeper <basePrice> <pricePer100Km>\n";
			return;
		}
		double per100Km = args[4].parseToDouble();
		wagon = std::make_shared<SleeperWagon>(newWagonId, basePrice, per100Km);
	}
	else {
		std::cout << "Invalid wagon type. Use: first, second, sleeper\n";
		return;
	}

	targetTrain->addWagon(wagon);

	MyString wagonTypeStr;
	switch (wagon->getType()) {
	case WagonType::FirstClass:
		wagonTypeStr = "First-class";
		break;
	case WagonType::SecondClass:
		wagonTypeStr = "Second-class";
		break;
	case WagonType::Sleeper:
		wagonTypeStr = "Sleeper";
		break;
	}

	std::cout << wagonTypeStr.getString() << " wagon with ID " << newWagonId
		<< " added to train " << trainId << ".\n";

}
