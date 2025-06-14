#include "SleeperWagon.h"
#include <fstream>

SleeperWagon::SleeperWagon(int id, double basePrice, double pricePer100Km) : Wagon(id, WagonType::Sleeper, basePrice, 5), pricePer100Km(pricePer100Km)
{
}

double SleeperWagon::calculatePrice(int seatIndex, double extraParam) const
{
    return getBasePrice() + (pricePer100Km / 100.0) * extraParam;
}

double SleeperWagon::getPricePer100Km() const
{
    return pricePer100Km;
}

void SleeperWagon::saveWagonsToFile(std::ofstream& ofs) const
{
	int typeInt = static_cast<int>(WagonType::Sleeper);
	ofs.write(reinterpret_cast<const char*>(&typeInt), sizeof(typeInt));

	int id = getId();
	double basePrice = getBasePrice();
	int seatCount = getSeatCount();

	ofs.write(reinterpret_cast<const char*>(&id), sizeof(id));
	ofs.write(reinterpret_cast<const char*>(&basePrice), sizeof(basePrice));
	ofs.write(reinterpret_cast<const char*>(&seatCount), sizeof(seatCount));
	ofs.write(reinterpret_cast<const char*>(&pricePer100Km), sizeof(pricePer100Km));

	for (int i = 0; i < seatCount; ++i) {
		bool taken = !isSeatFree(i);
		ofs.write(reinterpret_cast<const char*>(&taken), sizeof(taken));
	}
}

void SleeperWagon::loadWagonsFromFile(std::ifstream& ifs)
{
	int id, seatCount;
	double basePrice;

	ifs.read(reinterpret_cast<char*>(&id), sizeof(id));
	ifs.read(reinterpret_cast<char*>(&basePrice), sizeof(basePrice));
	ifs.read(reinterpret_cast<char*>(&seatCount), sizeof(seatCount));
	ifs.read(reinterpret_cast<char*>(&pricePer100Km), sizeof(pricePer100Km));

	setId(id);
	setBasePrice(basePrice);
	setSeatCount(seatCount);

	clearSeats();
	for (int i = 0; i < seatCount; ++i) {
		bool taken;
		ifs.read(reinterpret_cast<char*>(&taken), sizeof(taken));
		pushSeat(!taken);
	}
}
