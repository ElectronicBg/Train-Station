#include "StationRepository.h"

const std::shared_ptr<Station>& StationRepository::findStationByName(const MyString& name) const
{
	for (int i = 0; i < stations.getSize(); ++i) {
		if (stations[i]->getName() == name) return stations[i];
	}
	throw std::runtime_error("Station not found");
}

std::shared_ptr<Station>& StationRepository::findStationByName(const MyString& name)
{
	for (int i = 0; i < stations.getSize(); ++i) {
		if (stations[i]->getName() == name) return stations[i];
	}
	throw std::runtime_error("Station not found");
}

void StationRepository::addStation(const std::shared_ptr<Station>& station)
{
	for (int i = 0; i < stations.getSize(); ++i) {
		if (stations[i]->getName() == station->getName()) {
			throw std::runtime_error("Station already exists");
		}
	}
	stations.pushBack(station);
}

int StationRepository::getStationsCount() const
{
	return stations.getSize();
}

int StationRepository::getNewStationId() const
{
	return getStationsCount() + 1;
}

const MyVector<std::shared_ptr<Station>>& StationRepository::getAllStations() const
{
	return stations;
}

const std::shared_ptr<Train>& StationRepository::findTrainById(int id) const
{
	for (int i = 0; i < trains.getSize(); ++i) {
		if (trains[i]->getId() == id) {
			return trains[i];
		}
	}
	throw std::runtime_error("Train not found: " + id);
}

std::shared_ptr<Train>& StationRepository::findTrainById(int id)
{
	for (int i = 0; i < trains.getSize(); ++i) {
		if (trains[i]->getId() == id) {
			return trains[i];
		}
	}
	throw std::runtime_error("Train not found: " + id);
}

void StationRepository::addTrain(const std::shared_ptr<Train>& train)
{
	for (int i = 0; i < trains.getSize(); ++i) {
		if (trains[i]->getId() == train->getId()) {
			throw std::runtime_error("Train already exists: " + train->getId());
		}
	}
	trains.pushBack(train);

	MyString depName = train->getDepartureStation();
	std::shared_ptr<Station> depStation = findStationByName(depName);

	if (depStation) {
		depStation->addDepartingTrain(train);
	}
}

int StationRepository::getTrainsCount() const
{
	return trains.getSize();
}

int StationRepository::getNewTrainId() const
{
	return getTrainsCount() + 1;
}

const MyVector<std::shared_ptr<Train>>& StationRepository::getAllTrains() const
{
	return trains;
}

const std::shared_ptr<Wagon>& StationRepository::findWagonById(int id) const
{
	for (int i = 0; i < wagons.getSize(); ++i) {
		if (wagons[i]->getId() == id) {
			return wagons[i];
		}
	}
	throw std::runtime_error("Wagon not found: " + id);
}

std::shared_ptr<Wagon>& StationRepository::findWagonById(int id)
{
	for (int i = 0; i < wagons.getSize(); ++i) {
		if (wagons[i]->getId() == id) {
			return wagons[i];
		}
	}
	throw std::runtime_error("Wagon not found: " + id);
}

void StationRepository::addWagon(const std::shared_ptr<Wagon>& wagon)
{
	for (int i = 0; i < wagons.getSize(); ++i) {
		if (wagons[i]->getId() == wagon->getId()) {
			throw std::runtime_error("Wagon already exists: " + wagon->getId());
		}
	}
	wagons.pushBack(wagon);
}

int StationRepository::getWagonsCount() const
{
	return wagons.getSize();
}

int StationRepository::getNewWagonId() const
{
	return wagons.getSize() + 1;
}

const MyVector<std::shared_ptr<Wagon>>& StationRepository::getAllWagons() const
{
	return wagons;
}
