#include "Train.h"

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
