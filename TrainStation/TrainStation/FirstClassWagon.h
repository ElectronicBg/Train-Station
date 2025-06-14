#pragma once
#include "Wagon.h"

class FirstClassWagon : public Wagon
{
	double comfortFactor;

public:
	FirstClassWagon(int id, double basePrice, double comfortFactor);

	double calculatePrice(int seatIndex, double extraParam) const override;

	double getComfortFactor() const;

	void saveWagonsToFile(std::ofstream& ofs) const override;
	void loadWagonsFromFile(std::ifstream& ifs)override;
};

