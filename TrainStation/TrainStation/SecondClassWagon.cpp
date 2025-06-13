#include "SecondClassWagon.h"

SecondClassWagon::SecondClassWagon(int id, double basePrice, double baggagePricePerKg) : Wagon(id, WagonType::SecondClass, basePrice, 20),baggagePricePerKg(baggagePricePerKg)
{
}

double SecondClassWagon::calculatePrice(int seatIndex, double extraParam) const 
{
    return getBasePrice() + baggagePricePerKg * extraParam;
}
