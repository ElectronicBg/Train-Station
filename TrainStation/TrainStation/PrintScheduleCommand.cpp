#include "PrintScheduleCommand.h"
#pragma warning(disable : 4996)
#include "Station.h"
#include "Train.h"
#include <iostream>
#include <chrono>

std::string formatTime(const std::chrono::system_clock::time_point& tp) {
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%d/%m/%Y %H:%M", std::localtime(&t));
    return buf;
}

void PrintScheduleCommand::execute(const MyVector<MyString>& args, TrainSystemApp& app) const {
    if (args.getSize() != 2) {
        std::cout << "Usage: print-schedule <station>\n";
        return;
    }

    const MyString& stationName = args[1];

    try {
        const auto& station = app.getStationRepo().findStationByName(stationName);

        std::cout << "Schedule for station: " << station->getName().getString() << "\n\n";

        auto now = std::chrono::system_clock::now();

        std::cout << "Departures:\n";
        const auto& departures = station->getDepartingTrains();
        for (size_t i = 0; i < departures.getSize(); ++i) {
            const auto& train = departures[i];
            std::cout << "- Train " << train->getId()
                << " to " << train->getArrivalStation().getString()
                << " at " << formatTime(train->getDepartureTime())
                << " [Platform " << train->getDeparturePlatform() << "]";

            if (train->getDepartureTime() < now)
                std::cout << " (Departed)";
            std::cout << "\n";
        }

        std::cout << "\nArrivals:\n";
        const auto& arrivals = station->getArrivingTrains();
        for (size_t i = 0; i < arrivals.getSize(); ++i) {
            if (auto trainPtr = arrivals[i].lock()) {
                std::cout << "- Train " << trainPtr->getId()
                    << " from " << trainPtr->getDepartureStation().getString()
                    << " at " << formatTime(trainPtr->getArrivalTime())
                    << " [Platform " << trainPtr->getArrivalPlatform() << "]";

                if (trainPtr->getArrivalTime() < now)
                    std::cout << " (Arrived)";
                std::cout << "\n";
            }
        }
    }
    catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << "\n";
    }
}
