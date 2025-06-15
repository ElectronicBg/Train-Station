#include "CreateDiscountCardCommand.h"
#include "DiscountCard.h"
#include "AgeCard.h"
#include "RouteCard.h"
#include "DistanceCard.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iostream>

static int generateCode() {
    return 100000 + std::rand() % 900000;
}

void CreateDiscountCardCommand::execute(const MyVector<MyString>& args, TrainSystemApp& app) const {
    if (!app.getAdminRepo().isLoggedIn()) {
        std::cout << "Admin privileges required.\n";
        return;
    }

    if (args.getSize() < 5) {
        std::cout << "Usage: create-discount-card <cardType> <ownerName> <fileName> [extra]\n";
        return;
    }

    const MyString& type = args[1];
    const MyString& owner = args[2];
    const MyString& file = args[3];
    int code = generateCode();

    std::shared_ptr<DiscountCard> card = nullptr;

    if (type == "age") {
        if (args.getSize() != 5) {
            std::cout << "Usage for age: create-discount-card age <owner> <file> <ageYears>\n";
            return;
        }
        double age = args[4].parseToDouble();
        card = std::make_shared<AgeCard>(code, owner, age);
    }
    else if (type == "route") {
        if (args.getSize() != 5) {
            std::cout << "Usage for route: create-discount-card route <owner> <file> <destination>\n";
            return;
        }
        card = std::make_shared<RouteCard>(code, owner, args[4]);
    }
    else if (type == "distance") {
        if (args.getSize() != 5) {
            std::cout << "Usage for distance: create-discount-card distance <owner> <file> <kmLimit>\n";
            return;
        }
        double limit = args[4].parseToDouble();
        card = std::make_shared<DistanceCard>(code, owner, limit);
    }
    else {
        std::cout << "Unknown card type: " << type.getString() << "\n";
        return;
    }

    app.getDiscountCardRepo().addCard(card);

    std::ofstream ofs(file.getString());
    if (!ofs.is_open()) {
        std::cout << "Failed to create card file.\n";
        return;
    }

    if (type == "age") {
        ofs << "|===Age card===|\n";
        ofs << "|" << owner.getString() << "|\n";
        ofs << "|" << args[4].getString() << " years old|\n";
        ofs << "|" << code << "|\n";
        ofs << "|==============|\n";
    }
    else if (type == "route") {
        ofs << "|===Route card===|\n";
        ofs << "|" << owner.getString() << "|\n";
        ofs << "|" << args[4].getString() << "|\n";
        ofs << "|" << code << "|\n";
        ofs << "|===============|\n";
    }
    else if (type == "distance") {
        ofs << "|==Distance card==|\n";
        ofs << "|" << owner.getString() << "|\n";
        ofs << "|" << args[4].getString() << " km|\n";
        ofs << "|" << code << "|\n";
        ofs << "|=================|\n";
    }

    std::cout << "Discount card created with code " << code << " and saved to " << file.getString() << "\n";
}
