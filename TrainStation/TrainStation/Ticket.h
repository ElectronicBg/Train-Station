#pragma once
#include "MyString.h"
#include <chrono>

class Ticket
{
	int trainId;
	int wagonId;
	int seatId;
	double finalPrice;
	double discountAmount;
	std::chrono::system_clock::time_point purchaseTime;

public:
	Ticket(int trainId, int wagonId, int seatId, double finalPrice, double discountAmount);

	void saveToFile(const MyString& fileName) const;
};
