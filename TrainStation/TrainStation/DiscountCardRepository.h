#pragma once
#include "MyVector.hpp"
#include "DiscountCard.h"

class DiscountCardRepository
{
	MyVector<std::shared_ptr<DiscountCard>> cards;
public:
	DiscountCardRepository() = default;
	~DiscountCardRepository() = default;

	void addCard(const std::shared_ptr<DiscountCard>& card);
	bool validateCard(int code) const;
	std::shared_ptr<DiscountCard> getCard(int code) const;

	void save(const MyString& filename) const;
	void load(const MyString& filename);
};

