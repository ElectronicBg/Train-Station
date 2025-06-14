#pragma once
#include "DiscountCard.h"

class RouteCard : public DiscountCard
{
	MyString route;

public:
    RouteCard(int code, const MyString& owner, const MyString& route);

    double getDiscount(double age, const MyString& destination, double dist) const override;
};

