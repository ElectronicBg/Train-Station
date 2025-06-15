#include "MoveWagonCommand.h"
#include <iostream>

void MoveWagonCommand::execute(const MyVector<MyString>& args, TrainSystemApp& app) const {
    if (!app.getAdminRepo().isLoggedIn()) {
        std::cout << "Admin privileges required.\n";
        return;
    }

    if (args.getSize() != 4) {
        std::cout << "Usage: move-wagon <sourceTrainID> <wagonID> <destinationTrainID>\n";
        return;
    }

    int sourceTrainId = args[1].parseToInt();
    int wagonId = args[2].parseToInt();
    int destTrainId = args[3].parseToInt();

    std::shared_ptr<Train> sourceTrain = nullptr;
    std::shared_ptr<Train> destTrain = nullptr;

    const auto& stations = app.getStationRepo().getAllStations();

    for (size_t i = 0; i < stations.getSize(); ++i) {
        const auto& trains = stations[i]->getDepartingTrains();
        for (size_t j = 0; j < trains.getSize(); ++j) {
            if (trains[j]->getId() == sourceTrainId)
                sourceTrain = trains[j];
            if (trains[j]->getId() == destTrainId)
                destTrain = trains[j];
        }
    }

    if (!sourceTrain || !destTrain) {
        std::cout << "One or both trains not found.\n";
        return;
    }

    auto now = std::chrono::system_clock::now();
    if (sourceTrain->getDepartureTime() < now || destTrain->getDepartureTime() < now) {
        std::cout << "Cannot move wagons between departed trains.\n";
        return;
    }

    auto& sourceWagons = const_cast<MyVector<std::shared_ptr<Wagon>>&>(sourceTrain->getWagons());
    std::shared_ptr<Wagon> toMove = nullptr;

    for (size_t i = 0; i < sourceWagons.getSize(); ++i) {
        if (sourceWagons[i]->getId() == wagonId) {
            if (sourceWagons[i]->hasOccupiedSeats()) {
                std::cout << "Wagon " << wagonId << " has occupied seats. Cannot move.\n";
                return;
            }
            toMove = sourceWagons[i];
            removeWagonAtIndex(sourceWagons, i);
            break;
        }
    }

    if (!toMove) {
        std::cout << "Wagon " << wagonId << " not found in source train.\n";
        return;
    }

    destTrain->addWagon(toMove);
    std::cout << "Wagon " << wagonId << " moved from train " << sourceTrainId << " to " << destTrainId << ".\n";
}
