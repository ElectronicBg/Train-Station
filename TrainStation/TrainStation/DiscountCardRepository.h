#pragma once
#include "MyVector.hpp"
#include "DiscountCard.h"

class DiscountCardRepository
{
	MyVector<std::shared_ptr<DiscountCard>> issuedCards;
public:
	DiscountCardRepository() = default;
	~DiscountCardRepository() = default;

	void addCard(const std::shared_ptr<DiscountCard>& card);
	bool isCodeValid(int code) const;
	std::shared_ptr<DiscountCard> loadCardFromFile(const MyString& filename) const;

	void saveToFile(const MyString& fileName) const;
	void loadFromFile(const MyString& fileName);
	   
};

