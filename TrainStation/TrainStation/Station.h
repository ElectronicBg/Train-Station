#pragma once
#include "Train.h"
#include "MyString.h"
#include "MyVector.hpp"

class Train;

class Station
{
	MyString name;
	int platforms;
	MyVector<std::shared_ptr<Train>> departures;
	MyVector< std::weak_ptr<Train>> arrivals;

	int assignPlatform(const std::chrono::system_clock::time_point& time);

public:

	Station(const MyString& name, int platforms);

	const MyString& getName() const;
	int getPlatforms() const;

	void addDepartingTrain(const std::shared_ptr<Train>& train);
	void addArrivingTrain(const std::shared_ptr<Train>& train);

	std::shared_ptr<Train> addTrain(int id, const MyString& arrivalStationName, const std::chrono::system_clock::time_point& depTime, double distance, double speed);

	const MyVector<std::shared_ptr<Train>>& getDepartingTrains() const;
	const MyVector<std::weak_ptr<Train>>& getArrivingTrains() const;

	void save(std::ofstream& ofs) const;
	void load(std::ifstream& ifs);
};

