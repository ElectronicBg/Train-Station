#include "FirstClassWagon.h"

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
