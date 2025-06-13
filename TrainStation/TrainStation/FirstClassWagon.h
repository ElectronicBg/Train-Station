#pragma once
#include "Wagon.h"

class FirstClassWagon : public Wagon 
{
	double comfortFactor;

public:
    FirstClassWagon(int id, double basePrice, double comfortFactor);

    double calculatePrice(int seatIndex, double extraParam) const override;
};

