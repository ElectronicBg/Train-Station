#pragma once
#include "MyString.h"
#include "MyVector.hpp"
#include "AdminRepository.h"
#include "StationRepository.h"
#include "Admin.h"

class TrainSystemApp
{
    bool running = true;
    AdminRepository adminRepo;
    StationRepository stationRepo;

    const Admin* currentAdmin = nullptr;

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

    const Admin* getCurrentAdmin() const;
    void setCurrentAdmin(const Admin* admin);
    void logoutAdmin();
    bool isAdminLoggedIn() const;

    void stop();
    bool isRunning() const;
};

