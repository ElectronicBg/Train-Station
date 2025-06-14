#include "PrintStationsCommand.h"

void PrintStationsCommand::execute(const MyVector<MyString>& args, TrainSystemApp& app) const
{
	try {
		const MyVector<std::shared_ptr<Station>>& stations = app.getStationRepo().getAllStations();

		if (stations.getSize() == 0) {
			std::cout << "No stations available.\n";
			return;
		}

		std::cout << "Available stations:\n";
		for (size_t i = 0; i < stations.getSize(); ++i) {
			if (stations[i]) {
				std::cout << "- " << stations[i]->getName() << "\n";
			}
			else {
				std::cout << "- [Invalid station]\n";
			}
		}
	}
	catch (const std::exception& ex) {
		std::cout << "Error while retrieving stations: " << ex.what() << "\n";
	}
}
