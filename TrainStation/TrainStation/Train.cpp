#include "Train.h"
#include <fstream>
#include "StringHelper.h"
#include "FirstClassWagon.h"
#include "SleeperWagon.h"
#include "SecondClassWagon.h"

Train::Train(int id, const  MyString& departureStation, const  MyString& arrivalStation, const std::chrono::system_clock::time_point& departureTime, const std::chrono::system_clock::time_point& arrivalTime, double distance, double speed) : id(id), departureStation(departureStation), arrivalStation(arrivalStation), departureTime(departureTime), arrivalTime(arrivalTime), departurePlatform(-1), arrivalPlatform(-1), distance(distance), speed(speed)
{
}

int Train::getId() const
{
	return id;
}

const  MyString& Train::getDepartureStation() const
{
	return departureStation;
}

const  MyString& Train::getArrivalStation() const
{
	return arrivalStation;
}

const std::chrono::system_clock::time_point& Train::getDepartureTime() const
{
	return departureTime;
}

const std::chrono::system_clock::time_point& Train::getArrivalTime() const
{
	return arrivalTime;
}

int Train::getDeparturePlatform() const
{
	return departurePlatform;
}

int Train::getArrivalPlatform() const
{
	return arrivalPlatform;
}

double Train::getDistance() const
{
	return distance;
}

double Train::getSpeed() const
{
	return speed;
}

void Train::setDeparturePlatform(int platform)
{
	departurePlatform = platform;
}

void Train::setArrivalPlatform(int platform)
{
	arrivalPlatform = platform;
}

void Train::addWagon(const std::shared_ptr<Wagon>& wagon)
{
	wagons.pushBack(wagon);
}

const MyVector<std::shared_ptr<Wagon>>& Train::getWagons() const
{
	return wagons;
}

void Train::saveToFile(std::ofstream& ofs) const
{
	ofs.write(reinterpret_cast<const char*>(&id), sizeof(id));

	writeString(ofs, departureStation);
	writeString(ofs, arrivalStation);

	std::time_t depTime = std::chrono::system_clock::to_time_t(departureTime);
	std::time_t arrTime = std::chrono::system_clock::to_time_t(arrivalTime);
	ofs.write(reinterpret_cast<const char*>(&depTime), sizeof(depTime));
	ofs.write(reinterpret_cast<const char*>(&arrTime), sizeof(arrTime));

	ofs.write(reinterpret_cast<const char*>(&departurePlatform), sizeof(departurePlatform));
	ofs.write(reinterpret_cast<const char*>(&arrivalPlatform), sizeof(arrivalPlatform));
	ofs.write(reinterpret_cast<const char*>(&distance), sizeof(distance));
	ofs.write(reinterpret_cast<const char*>(&speed), sizeof(speed));

	size_t wagonCount = wagons.getSize();
	ofs.write(reinterpret_cast<const char*>(&wagonCount), sizeof(wagonCount));

	for (size_t i = 0; i < wagonCount; ++i) {
		wagons[i]->saveWagonsToFile(ofs);
	}
}

void Train::loadFromFile(std::ifstream& ifs)
{
	ifs.read(reinterpret_cast<char*>(&id), sizeof(id));

	if (!readString(ifs, departureStation)) throw std::runtime_error("Failed to read departureStation");
	if (!readString(ifs, arrivalStation)) throw std::runtime_error("Failed to read arrivalStation");

	std::time_t depTimeRaw, arrTimeRaw;
	ifs.read(reinterpret_cast<char*>(&depTimeRaw), sizeof(depTimeRaw));
	ifs.read(reinterpret_cast<char*>(&arrTimeRaw), sizeof(arrTimeRaw));
	departureTime = std::chrono::system_clock::from_time_t(depTimeRaw);
	arrivalTime = std::chrono::system_clock::from_time_t(arrTimeRaw);

	ifs.read(reinterpret_cast<char*>(&departurePlatform), sizeof(departurePlatform));
	ifs.read(reinterpret_cast<char*>(&arrivalPlatform), sizeof(arrivalPlatform));
	ifs.read(reinterpret_cast<char*>(&distance), sizeof(distance));
	ifs.read(reinterpret_cast<char*>(&speed), sizeof(speed));

	size_t wagonCount;
	ifs.read(reinterpret_cast<char*>(&wagonCount), sizeof(wagonCount));

	for (size_t i = 0; i < wagonCount; ++i) {
		int typeInt;
		ifs.read(reinterpret_cast<char*>(&typeInt), sizeof(typeInt));
		WagonType type = static_cast<WagonType>(typeInt);

		std::shared_ptr<Wagon> w;
		switch (type) {
		case WagonType::FirstClass:
			w = std::make_shared<FirstClassWagon>(0, 0.0, 0.0); break;
		case WagonType::SecondClass:
			w = std::make_shared<SecondClassWagon>(0, 0.0, 0.0); break;
		case WagonType::Sleeper:
			w = std::make_shared<SleeperWagon>(0, 0.0, 0.0); break;
		default:
			throw std::runtime_error("Unknown wagon type while loading train");
		}

		w->loadWagonsFromFile(ifs);
		wagons.pushBack(w);
	}
}
