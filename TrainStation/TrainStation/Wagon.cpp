#include "Wagon.h"

Wagon::Wagon(int id, WagonType type, double basePrice, int seatCount) : id(id), type(type), basePrice(basePrice), seatCount(seatCount)
{
	seats.reserve(seatCount);
	for (int i = 0; i < seatCount; ++i) seats.pushBack(true);
}

int Wagon::getId() const
{
	return id;
}

WagonType Wagon::getType() const
{
	return type;
}

double Wagon::getBasePrice() const
{
	return basePrice;
}

int Wagon::getSeatCount() const
{
	return seatCount;
}

bool Wagon::isSeatFree(int idx) const
{
	return idx >= 0 && idx < seatCount && seats[idx];
}

void Wagon::occupySeat(int idx)
{
	if (isSeatFree(idx)) {
		seats[idx] = false;
	}
}
