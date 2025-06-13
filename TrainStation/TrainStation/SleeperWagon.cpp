#include "SleeperWagon.h"

SleeperWagon::SleeperWagon(int id, double basePrice, double pricePer100Km) : Wagon(id, WagonType::Sleeper, basePrice, 5), pricePer100Km(pricePer100Km)
{
}

double SleeperWagon::calculatePrice(int seatIndex, double extraParam) const
{
    return getBasePrice() + (pricePer100Km / 100.0) * extraParam;
}
