#include "PrintScheduleTimeCommand.h"
#include "Station.h"
#include "Train.h"
#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>

#pragma warning(disable : 4996)

std::chrono::system_clock::time_point parseDateTime(const MyString& dateStr, const MyString& timeStr) {
    std::tm tm{};
    sscanf(dateStr.getString(), "%d/%d/%d", &tm.tm_mday, &tm.tm_mon, &tm.tm_year);
    sscanf(timeStr.getString(), "%d:%d", &tm.tm_hour, &tm.tm_min);
    tm.tm_mon -= 1;
    tm.tm_year -= 1900;
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

std::string formatTimeReadable(const std::chrono::system_clock::time_point& tp) {
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%d/%m/%Y %H:%M", std::localtime(&t));
    return buf;
}

void PrintScheduleTimeCommand::execute(const MyVector<MyString>& args, TrainSystemApp& app) const {
    if (args.getSize() != 4) {
        std::cout << "Usage: print-schedule-time <station> <date> <time>\n";
        return;
    }

    const MyString& stationName = args[1];
    const MyString& dateStr = args[2];
    const MyString& timeStr = args[3];

    try {
        const auto& station = app.getStationRepo().findStationByName(stationName);
        const auto& trains = station->getDepartingTrains();
        auto targetTime = parseDateTime(dateStr, timeStr);

        bool found = false;
        std::cout << "Trains from " << stationName << " after " << dateStr << " " << timeStr << ":\n";

        for (size_t i = 0; i < trains.getSize(); ++i) {
            const auto& train = trains[i];
            if (train->getDepartureTime() > targetTime) {
                found = true;
                std::cout << "- Train " << train->getId()
                    << " to " << train->getArrivalStation()
                    << " at " << formatTimeReadable(train->getDepartureTime())
                    << " [Platform " << train->getDeparturePlatform() << "]\n";
            }
        }

        if (!found) {
            std::cout << "No trains found after the given time.\n";
        }

    }
    catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << "\n";
    }
}
