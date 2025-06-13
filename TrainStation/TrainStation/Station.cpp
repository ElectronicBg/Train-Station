#include "Station.h"
#include <iostream>

int Station::assignPlatform(const std::chrono::system_clock::time_point& time)
{
    MyVector<bool> used;

    for (int i = 0; i < platforms; ++i) {
        used.pushBack(false);
    }

    for (int i = 0; i < departures.getSize(); ++i) {
        const auto& train = departures[i];
        if (train->getDepartureTime() == time) {
            int plat = train->getDeparturePlatform();
            if (plat >= 0 && plat < platforms) {
                used[plat] = true;
            }
        }
    }

    for (int i = 0; i < arrivals.getSize(); ++i) {
        if (auto t = arrivals[i].lock()) {
            if (t->getArrivalTime() == time) {
                int plat = t->getArrivalPlatform();
                if (plat >= 0 && plat < platforms) {
                    used[plat] = true;
                }
            }
        }
    }

    for (int p = 0; p < platforms; ++p) {
        if (!used[p]) {
            return p;
        }
    }
    throw std::runtime_error("No free platforms available at specified time");
}

Station::Station(const MyString& name, int platforms) : name(name), platforms(platforms)
{
}

const MyString& Station::getName() const
{
    return name;
}

int Station::getPlatforms() const
{
    return platforms;
}

void Station::addDepartingTrain(const std::shared_ptr<Train>& train)
{
    int depPlat = assignPlatform(train->getDepartureTime());
    train->setDeparturePlatform(depPlat);
    departures.pushBack(train);
}

void Station::addArrivingTrain(const std::shared_ptr<Train>& train)
{
    int arrPlat = assignPlatform(train->getArrivalTime());
    train->setArrivalPlatform(arrPlat);
    arrivals.pushBack(train);
}

std::shared_ptr<Train> Station::addTrain(int id,const MyString& arrivalStationName,const std::chrono::system_clock::time_point& depTime,const std::chrono::system_clock::time_point& arrTime,double distance,double speed) {
    auto train = std::make_shared<Train>(id, name, arrivalStationName, depTime, arrTime, distance, speed);
    addDepartingTrain(train);
    return train;
}

const MyVector<std::shared_ptr<Train>>& Station::getDepartingTrains() const
{
    return departures;
}

const MyVector<std::weak_ptr<Train>>& Station::getArrivingTrains() const
{
    return arrivals;
}
