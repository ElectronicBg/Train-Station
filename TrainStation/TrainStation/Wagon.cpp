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

bool Wagon::hasOccupiedSeats() const
{
	for (size_t i = 0; i < seats.getSize(); ++i) {
		if (!seats[i]) {
			return true;
		}
	}
	return false; 
}

void Wagon::occupySeat(int idx)
{
	if (isSeatFree(idx)) {
		seats[idx] = false;
	}
}

void Wagon::setId(int newId)
{
	id = newId;
}

void Wagon::setBasePrice(double price)
{
	basePrice = price;
}

void Wagon::setSeatCount(int count)
{
	seatCount = count;
}

void Wagon::clearSeats()
{
	seats.clear();
}

void Wagon::pushSeat(bool isFree)
{
	seats.pushBack(isFree);
}


