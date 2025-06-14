#include "SecondClassWagon.h"
#include <fstream>

SecondClassWagon::SecondClassWagon(int id, double basePrice, double baggagePricePerKg) : Wagon(id, WagonType::SecondClass, basePrice, 20),baggagePricePerKg(baggagePricePerKg)
{
}

double SecondClassWagon::calculatePrice(int seatIndex, double extraParam) const 
{
    return getBasePrice() + baggagePricePerKg * extraParam;
}

double SecondClassWagon::getBaggagePrice() const
{
    return baggagePricePerKg;
}

void SecondClassWagon::saveWagonsToFile(std::ofstream& ofs) const
{
	int typeInt = static_cast<int>(WagonType::SecondClass);
	ofs.write(reinterpret_cast<const char*>(&typeInt), sizeof(typeInt));

	int id = getId();
	double basePrice = getBasePrice();
	int seatCount = getSeatCount();

	ofs.write(reinterpret_cast<const char*>(&id), sizeof(id));
	ofs.write(reinterpret_cast<const char*>(&basePrice), sizeof(basePrice));
	ofs.write(reinterpret_cast<const char*>(&seatCount), sizeof(seatCount));
	ofs.write(reinterpret_cast<const char*>(&baggagePricePerKg), sizeof(baggagePricePerKg));

	for (int i = 0; i < seatCount; ++i) {
		bool taken = !isSeatFree(i);
		ofs.write(reinterpret_cast<const char*>(&taken), sizeof(taken));
	}
}

void SecondClassWagon::loadWagonsFromFile(std::ifstream& ifs)
{
	int idRead, seatCountRead;
	double basePriceRead;

	ifs.read(reinterpret_cast<char*>(&idRead), sizeof(idRead));
	ifs.read(reinterpret_cast<char*>(&basePriceRead), sizeof(basePriceRead));
	ifs.read(reinterpret_cast<char*>(&seatCountRead), sizeof(seatCountRead));
	ifs.read(reinterpret_cast<char*>(&baggagePricePerKg), sizeof(baggagePricePerKg));

	setId(idRead);
	setBasePrice(basePriceRead);
	setSeatCount(seatCountRead);
	clearSeats();
	for (int i = 0; i < seatCountRead; ++i) {
		bool taken;
		ifs.read(reinterpret_cast<char*>(&taken), sizeof(taken));
		pushSeat(!taken);
	}
}
