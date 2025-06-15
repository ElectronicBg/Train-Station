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
    bool hasOccupiedSeats() const;
    void occupySeat(int idx);

    void setId(int newId);
    void setBasePrice(double price);
    void setSeatCount(int count);
    void clearSeats();
    void pushSeat(bool isFree);

    virtual double calculatePrice(int seatIndex, double extraParam) const = 0;

   virtual void saveWagonsToFile(std::ofstream& ofs) const=0;
   virtual void loadWagonsFromFile(std::ifstream& ifs)=0;
};

static void removeWagonAtIndex(MyVector<std::shared_ptr<Wagon>>& wagons, size_t index) {
    MyVector<std::shared_ptr<Wagon>> temp;
    for (size_t i = 0; i < wagons.getSize(); ++i) {
        if (i != index) {
            temp.pushBack(wagons[i]);
        }
    }
    wagons = temp;
}