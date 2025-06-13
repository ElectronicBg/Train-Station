#pragma once
#include "MyVector.hpp"
#include "Station.h"

class StationRepository
{
	//Когато добавяме  train wagon не се добавят пойнтъри като shared
	//load save функция към train wagon station
	MyVector<std::shared_ptr<Station>> stations;
	MyVector<std::shared_ptr<Train>> trains;
	MyVector<std::shared_ptr<Wagon>> wagons;

public:
	void load(const MyString& filename);
	void save(const MyString& filename) const;


	const std::shared_ptr<Station>& findStationByName(const MyString& name) const;
	std::shared_ptr<Station>& findStationByName(const MyString& name);
	void addStation(const std::shared_ptr<Station>& station);
	int  getStationsCount() const;
	int  getNewStationId() const;
	const MyVector<std::shared_ptr<Station>>& getAllStations() const;


	const std::shared_ptr<Train>& findTrainById(int id) const;
	std::shared_ptr<Train>& findTrainById(int id);
	void addTrain(const std::shared_ptr<Train>& train);
	int  getTrainsCount() const;
	int  getNewTrainId() const;
	const MyVector<std::shared_ptr<Train>>& getAllTrains() const;


	const std::shared_ptr<Wagon>& findWagonById(int id) const;
	std::shared_ptr<Wagon>& findWagonById(int id);
	void addWagon(const std::shared_ptr<Wagon>& wagon);
	int  getWagonsCount() const;
	int  getNewWagonId() const;
	const MyVector<std::shared_ptr<Wagon>>& getAllWagons() const;
};

