#include "PrintScheduleDestinationCommand.h"
#pragma warning(disable : 4996)
#include "Station.h"
#include "Train.h"
#include <iostream>
#include <chrono>
#include <iomanip>

std::string formatTimeDest(const std::chrono::system_clock::time_point& tp) {
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%d/%m/%Y %H:%M", std::localtime(&t));
    return buf;
}

void PrintScheduleDestinationCommand::execute(const MyVector<MyString>& args, TrainSystemApp& app) const {
    if (args.getSize() != 3) {
        std::cout << "Usage: print-schedule-destination <station> <destination>\n";
        return;
    }

    const MyString& stationName = args[1];
    const MyString& destinationName = args[2];

    try {
        const auto& station = app.getStationRepo().findStationByName(stationName);
        const auto& trains = station->getDepartingTrains();

        bool found = false;
        std::cout << "Trains from " << stationName << " to " << destinationName << ":\n";

        for (size_t i = 0; i < trains.getSize(); ++i) {
            const auto& train = trains[i];

            if (train->getArrivalStation() == destinationName) {
                found = true;
                std::cout << "- Train " << train->getId()
                    << " departing at " << formatTimeDest(train->getDepartureTime())
                    << " [Platform " << train->getDeparturePlatform() << "]\n";
            }
        }

        if (!found) {
            std::cout << "No trains found from " << stationName << " to " << destinationName << ".\n";
        }

    }
    catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << "\n";
    }
}
