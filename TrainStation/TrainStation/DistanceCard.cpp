#include "DistanceCard.h"

DistanceCard::DistanceCard(int code, const MyString& owner, double maxDistance) : DiscountCard(code, owner), maxDistance(maxDistance)
{
}

double DistanceCard::getDiscount(double age, const MyString& dest, double travelDistance) const
{
	if (travelDistance <= maxDistance) return 0.5;
	else return 0.3;
}
