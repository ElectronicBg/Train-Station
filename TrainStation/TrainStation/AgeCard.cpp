#include "AgeCard.h"

AgeCard::AgeCard(int code, const MyString& owner, double ageYears) : DiscountCard(code, owner), age(ageYears)
{
}

double AgeCard::getAge() const
{
    return age;
}

double AgeCard::getDiscount(double ageYears, const MyString& dest, double dist) const
{
    if (age <= 10) return 1.0;
    else if (age <= 18) return 0.5;
    else return 0.2;
}
