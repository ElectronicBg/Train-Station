#pragma once
#include "MyVector.hpp"
#include "Station.h"

class StationRepository
{
	MyVector<std::shared_ptr<Station>> stations;

public:
	void load(const MyString& filename);
	void save(const MyString& filename) const;


	const std::shared_ptr<Station>& findStationByName(const MyString& name) const;
	std::shared_ptr<Station>& findStationByName(const MyString& name);
	void addStation(const std::shared_ptr<Station>& station);
	int  getStationsCount() const;
	int getTrainCount() const;
	int getNewTrainId() const;
	int  getNewStationId() const;
	const MyVector<std::shared_ptr<Station>>& getAllStations() const;
};

