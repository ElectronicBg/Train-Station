#pragma once
#include <iostream>
#include <chrono>
#include "MyString.h"
#include "Wagon.h"

class Train
{
	int id;
	MyString departureStation;
	MyString arrivalStation;
	std::chrono::system_clock::time_point departureTime;
	std::chrono::system_clock::time_point arrivalTime;
	int departurePlatform;
	int arrivalPlatform;
	double distance;
	double speed;
	MyVector<std::shared_ptr<Wagon>> wagons;

public:
	Train(int id, const  MyString& departureStation, const  MyString& arrivalStation, const std::chrono::system_clock::time_point& departureTime, const std::chrono::system_clock::time_point& arrivalTime, double distance, double speed);

	int getId() const;
	const  MyString& getDepartureStation() const;
	const  MyString& getArrivalStation() const;
	const std::chrono::system_clock::time_point& getDepartureTime() const;
	const std::chrono::system_clock::time_point& getArrivalTime() const;
	int getDeparturePlatform() const;
	int getArrivalPlatform() const;
	double getDistance() const;
	double getSpeed() const;

	void setDeparturePlatform(int platform);
	void setArrivalPlatform(int platform);

	void addWagon(const std::shared_ptr<Wagon>& wagon);

	const MyVector<std::shared_ptr<Wagon>>& getWagons() const;
};

