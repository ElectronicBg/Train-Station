#include "DiscountCard.h"

DiscountCard::DiscountCard(int code, const MyString& owner) : code(code), owner(owner)
{
}

int DiscountCard::getCode() const
{
	return code;
}

const MyString& DiscountCard::getOwner() const
{
	return owner;
}
