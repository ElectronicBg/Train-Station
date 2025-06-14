#include "FirstClassWagon.h"
#include <fstream>

FirstClassWagon::FirstClassWagon(int id, double basePrice, double comfortFactor) : Wagon(id, WagonType::FirstClass, basePrice, 10), comfortFactor(comfortFactor)
{
}

double FirstClassWagon::calculatePrice(int seatIndex, double extraParam) const
{
	double price = getBasePrice() * comfortFactor;

	if (extraParam > 0.5) {
		price += 10.0;
	}
	return price;
}

double FirstClassWagon::getComfortFactor() const
{
	return comfortFactor;
}

void FirstClassWagon::saveWagonsToFile(std::ofstream& ofs) const
{
	int typeInt = static_cast<int>(WagonType::FirstClass);
	ofs.write(reinterpret_cast<const char*>(&typeInt), sizeof(typeInt));

	int id = getId();
	double basePrice = getBasePrice();
	int seatCount = getSeatCount();

	ofs.write(reinterpret_cast<const char*>(&id), sizeof(id));
	ofs.write(reinterpret_cast<const char*>(&basePrice), sizeof(basePrice));
	ofs.write(reinterpret_cast<const char*>(&seatCount), sizeof(seatCount));
	ofs.write(reinterpret_cast<const char*>(&comfortFactor), sizeof(comfortFactor));

	for (int i = 0; i < seatCount; ++i) {
		bool taken = !isSeatFree(i);
		ofs.write(reinterpret_cast<const char*>(&taken), sizeof(taken));
	}
}

void FirstClassWagon::loadWagonsFromFile(std::ifstream& ifs)
{
	int id, seatCount;
	double basePrice;

	ifs.read(reinterpret_cast<char*>(&id), sizeof(id));
	ifs.read(reinterpret_cast<char*>(&basePrice), sizeof(basePrice));
	ifs.read(reinterpret_cast<char*>(&seatCount), sizeof(seatCount));
	ifs.read(reinterpret_cast<char*>(&comfortFactor), sizeof(comfortFactor));

	setId(id);
	setBasePrice(basePrice);
	setSeatCount(seatCount);

	clearSeats();
	for (int i = 0; i < seatCount; ++i) {
		bool taken;
		ifs.read(reinterpret_cast<char*>(&taken), sizeof(taken));
		pushSeat(!taken);


		for (int i = 0; i < seatCount; ++i) {
			bool taken;
			ifs.read(reinterpret_cast<char*>(&taken), sizeof(taken));
			if (taken) occupySeat(i);
		}
	}
}