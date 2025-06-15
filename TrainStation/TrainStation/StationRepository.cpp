#include "StationRepository.h"
#include <fstream>

void StationRepository::load(const MyString& filename)
{
	std::ifstream ifs(filename.getString(), std::ios::binary);
	if (!ifs.is_open()) {
		std::cerr << "Failed to open file for loading: " << filename.getString() << " Creating a new file.\n";

		std::ofstream newFile(filename.getString(), std::ios::binary);
		newFile.close();

		return;
	}

	stations.clear();

	size_t stationCount = 0;
	ifs.read(reinterpret_cast<char*>(&stationCount), sizeof(stationCount));

	for (size_t i = 0; i < stationCount; ++i) {
		auto station = std::make_shared<Station>("", 0);
		station->load(ifs);
		stations.pushBack(station);
	}

	for (size_t i = 0; i < stations.getSize(); ++i) {
		const auto& deps = stations[i]->getDepartingTrains();
		for (size_t j = 0; j < deps.getSize(); ++j) {
			const MyString& dest = deps[j]->getArrivalStation();
			try {
				auto& destStation = findStationByName(dest);
				destStation->addArrivingTrain(deps[j]);
			}
			catch (const std::exception& ex) {
				std::cerr << "Warning: Failed to link arrival station '" << dest << "': " << ex.what() << "\n";
			}
		}
	}
}

void StationRepository::save(const MyString& filename) const
{
	std::ofstream ofs(filename.getString(), std::ios::binary);
	if (!ofs.is_open()) {
		std::cerr << "Failed to open file for saving: " << filename << "\n";
		return;
	}

	size_t stationCount = stations.getSize();
	ofs.write(reinterpret_cast<const char*>(&stationCount), sizeof(stationCount));

	for (size_t i = 0; i < stationCount; ++i) {
		stations[i]->save(ofs);
	}
}

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