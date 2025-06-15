#pragma once
#include "DiscountCard.h"

class AgeCard : public DiscountCard
{
    double age;

public:
    AgeCard(int code, const MyString& owner, double ageYears);

    double getAge()const;
    double getDiscount(double ageYears, const MyString& dest, double dist) const override;
};

