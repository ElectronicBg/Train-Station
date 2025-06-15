#include "BuyTicketDiscountCommand.h"
#include "Train.h"
#include "Station.h"
#include "Wagon.h"
#include "DiscountCard.h"
#include "DiscountCardRepository.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

#pragma warning(disable : 4996)

void BuyTicketDiscountCommand::execute(const MyVector<MyString>& args, TrainSystemApp& app) const {
    if (args.getSize() < 6 || args.getSize() > 7) {
        std::cout << "Usage: buy-ticket-discount <trainID> <wagonID> <seatID> <ticketFile> <cardFile> [extraParam]\n";
        return;
    }

    int trainId = args[1].parseToInt();
    int wagonId = args[2].parseToInt();
    int seatId = args[3].parseToInt();
    const MyString& ticketFile = args[4];
    const MyString& cardFile = args[5];
    double extraParam = args.getSize() == 7 ? args[6].parseToDouble() : 0.0;

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

    std::shared_ptr<Wagon> wagon = nullptr;
    for (size_t i = 0; i < train->getWagons().getSize(); ++i) {
        if (train->getWagons()[i]->getId() == wagonId) {
            wagon = train->getWagons()[i];
            break;
        }
    }

    if (!wagon) {
        std::cout << "Wagon with ID " << wagonId << " not found.\n";
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

    std::shared_ptr<DiscountCard> card = app.getDiscountCardRepo().loadCardFromFile(cardFile);
    if (!card) {
        std::cout << "Failed to load discount card from file.\n";
        return;
    }

    if (!app.getDiscountCardRepo().isCodeValid(card->getCode())) {
        std::cout << "Card is not valid.\n";
        return;
    }

    double fullPrice = wagon->calculatePrice(seatId, extraParam);
    double discountPercent = card->getDiscount(20, train->getArrivalStation(), train->getDistance());
    double discountedPrice = fullPrice * (1.0 - discountPercent);

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
    ofs << "|Discount: " << (int)(discountPercent * 100) << "%\n";
    ofs << "|Final Price: " << std::fixed << std::setprecision(2) << discountedPrice << "\n";
    ofs << "|===============|\n";
    ofs.close();

    wagon->occupySeat(seatId);
    std::cout << "Discounted ticket bought. Saved to: " << ticketFile.getString() << "\n";
}
