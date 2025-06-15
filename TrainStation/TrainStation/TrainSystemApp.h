#pragma once
#include "MyString.h"
#include "MyVector.hpp"
#include "AdminRepository.h"
#include "StationRepository.h"
#include "Admin.h"
#include "DiscountCardRepository.h"

class TrainSystemApp
{
    bool running = true;

    AdminRepository adminRepo;
    StationRepository stationRepo;
    DiscountCardRepository discountCardRepo;

    void loadData();
    void saveData();
    void commandLoop();
    void handleCommand(const MyString& line);
    MyVector<MyString> split(const MyString& line) const;

public:
    TrainSystemApp();
    void run();

    StationRepository& getStationRepo();
    AdminRepository& getAdminRepo();
    DiscountCardRepository& getDiscountCardRepo();

    void stop();
    bool isRunning() const;
};

