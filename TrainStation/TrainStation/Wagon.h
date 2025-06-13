#pragma once
#include "MyVector.hpp"

enum class WagonType { FirstClass, SecondClass, Sleeper };

class Wagon
{
    int id;
    WagonType type;
    double basePrice;
    MyVector<bool> seats;
    int seatCount;

public:
    Wagon(int id, WagonType type, double basePrice, int seatCount);

    virtual ~Wagon() = default;

    int getId() const;
    WagonType getType() const;
    double getBasePrice() const;
    int getSeatCount() const;
    bool isSeatFree(int idx) const;
    void occupySeat(int idx);

    virtual double calculatePrice(int seatIndex, double extraParam) const = 0;
};

