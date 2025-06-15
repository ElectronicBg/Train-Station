#include "DiscountCardUtils.h"
#include <fstream>

void saveCardToTextFile(const DiscountCard& card, const MyString& filename)
{
	std::ofstream ofs(filename.getString());
	if (!ofs.is_open()) {
		throw std::runtime_error("Failed to open card file for writing.");
	}

	const MyString& owner = card.getOwner();
	int code = card.getCode();

	if (const AgeCard* ageCard = dynamic_cast<const AgeCard*>(&card)) {
		double age = ageCard->getAge();

		ofs << "|===Age card===|\n";
		ofs << "|" << owner << "   |\n";
		ofs << "|" << int(age) << " years old  |\n";
		ofs << "|" << code << "        |\n";
		ofs << "|==============|\n";
	}
	else if (const RouteCard* routeCard = dynamic_cast<const RouteCard*>(&card)) {
		MyString route = routeCard->getRoute();

		ofs << "|===Route card===|\n";
		ofs << "|" << owner << "     |\n";
		ofs << "|" << route << "  |\n";
		ofs << "|" << code << "          |\n";
		ofs << "|===============|\n";
	}
	else if (const DistanceCard* distCard = dynamic_cast<const DistanceCard*>(&card)) {
		int dist = int(distCard->getMaxDistance());

		ofs << "|==Distance card==|\n";
		ofs << "|" << owner << "      |\n";
		ofs << "|" << dist << " km           |\n";
		ofs << "|" << code << "          |\n";
		ofs << "|=================|\n";
	}
	else {
		throw std::runtime_error("Unknown card type.");
	}
}
