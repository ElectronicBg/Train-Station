#pragma once
#include "Wagon.h"

class SleeperWagon : public Wagon
{
	double pricePer100Km;
	
public:
    SleeperWagon(int id, double basePrice, double pricePer100Km);

	double calculatePrice(int seatIndex, double extraParam) const override;

	double getPricePer100Km() const;

	void saveWagonsToFile(std::ofstream& ofs) const override;
	void loadWagonsFromFile(std::ifstream& ifs)override;
};

