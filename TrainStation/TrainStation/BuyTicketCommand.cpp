#include "BuyTicketCommand.h"
#include "Train.h"
#include "Station.h"
#include "Wagon.h"
#include "StationRepository.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

#pragma warning(disable : 4996)

void BuyTicketCommand::execute(const MyVector<MyString>& args, TrainSystemApp& app) const {
    if (args.getSize() < 5 || args.getSize() > 6) {
        std::cout << "Usage: buy-ticket <trainID> <wagonID> <seatID> <ticketFile> [extraParam]\n";
        return;
    }

    int trainId = args[1].parseToInt();
    int wagonId = args[2].parseToInt();
    int seatId = args[3].parseToInt();
    const MyString& ticketFile = args[4];
    double extraParam = args.getSize() == 6 ? args[5].parseToDouble() : 0.0;

    std::shared_ptr<Train> train = nullptr;

    const auto& stations = app.getStationRepo().getAllStations();
    for (size_t i = 0; i < stations.getSize(); ++i) {
        const auto& trains = stations[i]->getDepartingTrains();
        for (size_t j = 0; j < trains.getSize(); ++j) {
            if (trains[j]->getId() == trainId) {
                train = trains[j];
                break;
            }
        }
        if (train) break;
    }

    if (!train) {
        std::cout << "Train with ID " << trainId << " not found.\n";
        return;
    }

    const auto& wagons = train->getWagons();
    std::shared_ptr<Wagon> wagon = nullptr;

    for (size_t i = 0; i < wagons.getSize(); ++i) {
        if (wagons[i]->getId() == wagonId) {
            wagon = wagons[i];
            break;
        }
    }

    if (!wagon) {
        std::cout << "Wagon with ID " << wagonId << " not found in train " << trainId << ".\n";
        return;
    }

    if (seatId < 0 || seatId >= wagon->getSeatCount()) {
        std::cout << "Invalid seat index.\n";
        return;
    }

    if (!wagon->isSeatFree(seatId)) {
        std::cout << "Seat is already occupied.\n";
        return;
    }

    double price = wagon->calculatePrice(seatId, extraParam);

    std::ofstream ofs(ticketFile.getString());
    if (!ofs.is_open()) {
        std::cout << "Failed to open ticket file: " << ticketFile.getString() << "\n";
        return;
    }

    std::time_t now = std::time(nullptr);
    char timeStr[30];
    std::strftime(timeStr, sizeof(timeStr), "%d/%m/%Y %H:%M:%S", std::localtime(&now));

    ofs << "|=== Ticket ===|\n";
    ofs << "|Train: " << trainId << "\n";
    ofs << "|Wagon: " << wagonId << "\n";
    ofs << "|Seat: " << seatId << "\n";
    ofs << "|Purchased at: " << timeStr << "\n";
    ofs << "|Discount: 0%\n";
    ofs << "|Price: " << std::fixed << std::setprecision(2) << price << "\n";
    ofs << "|===============|\n";

    ofs.close();

    wagon->occupySeat(seatId);
    std::cout << "Ticket bought successfully. Saved to: " << ticketFile.getString() << "\n";
}
