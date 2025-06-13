#pragma once
#include "Wagon.h"

class SecondClassWagon : public Wagon 
{
	double baggagePricePerKg;

public:
    SecondClassWagon(int id, double basePrice, double baggagePricePerKg);

    double calculatePrice(int seatIndex, double extraParam) const override;
};

