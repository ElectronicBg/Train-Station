#include "TrainSystemApp.h"
#include "CommandFactory.h"
#include <iostream>
#include <sstream>

namespace CONSTANTS {
	MyString adminsFile = "admins.txt";
	MyString stationsFile = "stations.dat";
}

TrainSystemApp::TrainSystemApp() 
{
	loadData();
}

void TrainSystemApp::run() {
	commandLoop();
}

void TrainSystemApp::loadData() {
	adminRepo.load(CONSTANTS::adminsFile);
	stationRepo.load(CONSTANTS::stationsFile);
}

void TrainSystemApp::saveData() {
	stationRepo.save(CONSTANTS::stationsFile);
}

void TrainSystemApp::commandLoop() {
	while (running) {
		std::cout << "> ";
		MyString line;
		char ch;

		while (std::cin.get(ch) && ch != '\n') {
			line.pushBack(ch);
		}

		if (!std::cin) break;
		if (line.empty()) continue;

		handleCommand(line);
		saveData();
	}
}

MyVector<MyString> TrainSystemApp::split(const MyString& line) const {
	MyVector<MyString> tokens;
	MyString current;

	for (size_t i = 0; i < line.getSize(); ++i) {
		char c = line[i];
		if (c == ' ') {
			if (!current.empty()) {
				tokens.pushBack(current);
				current.clear();
			}
		}
		else {
			current.pushBack(c);
		}
	}
	if (!current.empty()) {
		tokens.pushBack(current);
	}

	return tokens;
}

void TrainSystemApp::handleCommand(const MyString& line) {
	MyVector<MyString> args = split(line);
	if (args.empty()) return;

	Command* cmd = CommandFactory::create(args[0]);
	if (!cmd) {
		std::cout << "Unknown command: " << args[0].getString() << '\n';
		return;
	}

	cmd->execute(args, *this);
	delete cmd;
}

StationRepository& TrainSystemApp::getStationRepo() {
	return stationRepo;
}

AdminRepository& TrainSystemApp::getAdminRepo() {
	return adminRepo;
}

const Admin* TrainSystemApp::getCurrentAdmin() const 
{
	return currentAdmin;
}

void TrainSystemApp::setCurrentAdmin(const Admin* admin) 
{
	currentAdmin = admin;
}

void TrainSystemApp::logoutAdmin() 
{
	currentAdmin = nullptr;
}

bool TrainSystemApp::isAdminLoggedIn() const 
{
	return currentAdmin != nullptr;
}

void TrainSystemApp::stop() {
	running = false;
}

bool TrainSystemApp::isRunning() const {
	return running;
}
