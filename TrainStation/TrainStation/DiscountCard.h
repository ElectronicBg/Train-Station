#pragma once
#include "MyString.h"

class DiscountCard
{
	int code;
	MyString owner;

public:
	DiscountCard(int code, const MyString& owner);

	virtual ~DiscountCard() = default;

	int getCode() const;
	const MyString& getOwner() const;

	virtual double getDiscount(double ageYears, const MyString& destination, double travelDistance) const = 0;

};

