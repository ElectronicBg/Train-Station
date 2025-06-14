#pragma once
#include "Wagon.h"

class SecondClassWagon : public Wagon 
{
	double baggagePricePerKg;

public:
    SecondClassWagon(int id, double basePrice, double baggagePricePerKg);

    double calculatePrice(int seatIndex, double extraParam) const override;

    double getBaggagePrice() const;

    void saveWagonsToFile(std::ofstream& ofs) const override;
    void loadWagonsFromFile(std::ifstream& ifs)override;
};

