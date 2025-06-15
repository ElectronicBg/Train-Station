#include "PrintWagonCommand.h"
#include "Train.h"
#include "Station.h"
#include "Wagon.h"
#include "StationRepository.h"
#include <iostream>

void PrintWagonCommand::execute(const MyVector<MyString>& args, TrainSystemApp& app) const {
    if (args.getSize() != 3) {
        std::cout << "Usage: print-wagon <trainID> <wagonID>\n";
        return;
    }

    int trainId = args[1].parseToInt();
    int wagonId = args[2].parseToInt();

    const auto& stations = app.getStationRepo().getAllStations();
    std::shared_ptr<Train> foundTrain = nullptr;

    for (size_t i = 0; i < stations.getSize(); ++i) {
        const auto& deps = stations[i]->getDepartingTrains();
        for (size_t j = 0; j < deps.getSize(); ++j) {
            if (deps[j]->getId() == trainId) {
                foundTrain = deps[j];
                break;
            }
        }
        if (foundTrain) break;
    }

    if (!foundTrain) {
        std::cout << "Train with ID " << trainId << " not found.\n";
        return;
    }

    const auto& wagons = foundTrain->getWagons();
    for (size_t i = 0; i < wagons.getSize(); ++i) {
        if (wagons[i]->getId() == wagonId) {
            auto w = wagons[i];
            std::cout << "Wagon ID: " << w->getId() << "\n";
            std::cout << "Type: ";
            switch (w->getType()) {
            case WagonType::FirstClass: std::cout << "FirstClass"; break;
            case WagonType::SecondClass: std::cout << "SecondClass"; break;
            case WagonType::Sleeper: std::cout << "Sleeper"; break;
            }
            std::cout << "\nBase Price: " << w->getBasePrice() << "\n";
            std::cout << "Seats: " << w->getSeatCount() << "\n";
            std::cout << "Occupied: ";
            for (int s = 0; s < w->getSeatCount(); ++s) {
                std::cout << (w->isSeatFree(s) ? "[ ]" : "[X]");
            }
            std::cout << "\n";
            return;
        }
    }

    std::cout << "Wagon with ID " << wagonId << " not found in train " << trainId << ".\n";
}
