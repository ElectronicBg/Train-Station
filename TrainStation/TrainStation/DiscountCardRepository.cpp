#include "DiscountCardRepository.h"
#include <fstream>
#include "AgeCard.h"
#include "RouteCard.h"
#include "DistanceCard.h"
#include "StringHelper.h"

void DiscountCardRepository::addCard(const std::shared_ptr<DiscountCard>& card)
{
    issuedCards.pushBack(card);
}

bool DiscountCardRepository::isCodeValid(int code) const {
    for (size_t i = 0; i < issuedCards.getSize(); ++i) {
        if (issuedCards[i]->getCode() == code) return true;
    }
    return false;
}

std::shared_ptr<DiscountCard> DiscountCardRepository::loadCardFromFile(const MyString& filename) const
{
	std::ifstream ifs(filename.getString());
	if (!ifs.is_open()) {
		throw std::runtime_error("Failed to open discount card file.");
	}

    MyString line;

    auto readLine = [&]() -> MyString {
        MyString result;
        char c;
        while (ifs.get(c)) {
            if (c == '\n') break;
            result.pushBack(c);
        }
        return result.trim();
        };

    line = readLine();

    if (line == "|===Age card===|") {
        MyString owner = readLine();
        MyString ageLine = readLine();
        MyString codeLine = readLine();

        MyString ageStr;
        for (size_t i = 0; i < ageLine.getSize(); ++i) {
            if (ageLine[i] == ' ') break;
            ageStr.pushBack(ageLine[i]);
        }

        int age = ageStr.parseToInt();
        int code = codeLine.parseToInt();

        return std::make_shared<AgeCard>(code, owner, age);
    }
    else if (line == "|===Route card===|") {
        MyString owner = readLine();
        MyString route = readLine();
        MyString codeLine = readLine();

        int code = codeLine.parseToInt();

        return std::make_shared<RouteCard>(code, owner, route);
    }
    else if (line == "|==Distance card==|") {
        MyString owner = readLine();
        MyString distLine = readLine();
        MyString codeLine = readLine();

        MyString distStr;
        for (size_t i = 0; i < distLine.getSize(); ++i) {
            if (distLine[i] == ' ') break;
            distStr.pushBack(distLine[i]);
        }

        double maxDist = distStr.parseToDouble();
        int code = codeLine.parseToInt();

        return std::make_shared<DistanceCard>(code, owner, maxDist);
    }
    else {
        throw std::runtime_error("Unknown or unsupported discount card format.");
    }
}

void DiscountCardRepository::save(const MyString& fileName) const
{
    std::ofstream ofs(fileName.getString(), std::ios::binary);
    if (!ofs) throw std::runtime_error("Failed to open discount card file for saving.");

    size_t count = issuedCards.getSize();
    ofs.write(reinterpret_cast<const char*>(&count), sizeof(count));

    for (size_t i = 0; i < count; ++i) {
        const DiscountCard* card = issuedCards[i].get();

        int type = 0;
        if (dynamic_cast<const AgeCard*>(card)) type = 1;
        else if (dynamic_cast<const RouteCard*>(card)) type = 2;
        else if (dynamic_cast<const DistanceCard*>(card)) type = 3;

        ofs.write(reinterpret_cast<const char*>(&type), sizeof(type));
        int code = card->getCode();
        ofs.write(reinterpret_cast<const char*>(&code), sizeof(code));

        writeString(ofs, card->getOwner());

        if (type == 1) {
            double age = static_cast<const AgeCard*>(card)->getAge();
            ofs.write(reinterpret_cast<const char*>(&age), sizeof(age));
        }
        else if (type == 2) {
            writeString(ofs, static_cast<const RouteCard*>(card)->getRoute());
        }
        else if (type == 3) {
            double dist = static_cast<const DistanceCard*>(card)->getMaxDistance();
            ofs.write(reinterpret_cast<const char*>(&dist), sizeof(dist));
        }
    }
}

void DiscountCardRepository::load(const MyString& fileName)
{
    issuedCards.clear();

    std::ifstream ifs(fileName.getString(), std::ios::binary);
    if (!ifs.is_open()) {
        std::cerr << "Failed to open file for loading: " << fileName.getString() << " Creating a new file.\n";

        std::ofstream newFile(fileName.getString(), std::ios::binary);
        newFile.close();

        return;
    }

    size_t count = 0;
    ifs.read(reinterpret_cast<char*>(&count), sizeof(count));

    for (size_t i = 0; i < count; ++i) {
        int type = 0;
        ifs.read(reinterpret_cast<char*>(&type), sizeof(type));

        int code = 0;
        ifs.read(reinterpret_cast<char*>(&code), sizeof(code));

        MyString owner;
        if (!readString(ifs, owner)) throw std::runtime_error("Failed to read owner.");

        if (type == 1) {
            double age = 0;
            ifs.read(reinterpret_cast<char*>(&age), sizeof(age));
            issuedCards.pushBack(std::make_shared<AgeCard>(code, owner, age));
        }
        else if (type == 2) {
            MyString route;
            if (!readString(ifs, route)) throw std::runtime_error("Failed to read route.");
            issuedCards.pushBack(std::make_shared<RouteCard>(code, owner, route));
        }
        else if (type == 3) {
            double dist = 0;
            ifs.read(reinterpret_cast<char*>(&dist), sizeof(dist));
            issuedCards.pushBack(std::make_shared<DistanceCard>(code, owner, dist));
        }
    }
}
