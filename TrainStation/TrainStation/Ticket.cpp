#include "Ticket.h"
#include <fstream>
#include <ctime>
#include <iomanip>

Ticket::Ticket(int trainId, int wagonId, int seatId, double finalPrice, double discountAmount): trainId(trainId), wagonId(wagonId), seatId(seatId),finalPrice(finalPrice), discountAmount(discountAmount)
{
	purchaseTime = std::chrono::system_clock::now();
}

void Ticket::saveToFile(const MyString& fileName) const
{
	std::ofstream ofs(fileName.getString(), std::ios::out);
	if (!ofs) {
		std::cerr << "Failed to write ticket to file.\n";
		return;
	}

	time_t t = std::chrono::system_clock::to_time_t(purchaseTime);
	ofs << "|=== TICKET ===|\n";
	ofs << "Train ID: " << trainId << '\n';
	ofs << "Wagon ID: " << wagonId << '\n';
	ofs << "Seat ID: " << seatId << '\n';
	//ofs << "Purchase Time: " << std::put_time(std::localtime(&t), "%d/%m/%Y %H:%M:%S") << '\n';
	ofs << "Final Price: " << finalPrice << " BGN\n";
	ofs << "Discount Applied: " << discountAmount << " BGN\n";
	ofs << "|==============|\n";
}
