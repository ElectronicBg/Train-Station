#pragma once
#include "DiscountCard.h"

class DistanceCard : public DiscountCard
{
	double maxDistance;

public:
    DistanceCard(int code, const MyString& owner, double maxDistance);

    double getMaxDistance()const;
    double getDiscount(double age, const MyString& dest, double travelDistance) const override;
};

