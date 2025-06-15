#include "RouteCard.h"

RouteCard::RouteCard(int code, const MyString& owner, const MyString& route) : DiscountCard(code, owner), route(route)
{
}

const MyString RouteCard::getRoute() const
{
	return route;
}

double RouteCard::getDiscount(double age, const MyString& destination, double dist) const
{
	return (destination == route) ? 1.0 : 0.0;
}
