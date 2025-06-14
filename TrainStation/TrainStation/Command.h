#pragma once
#include "TrainSystemApp.h"
#include "MyVector.hpp"
#include "MyString.h"

class Command {
public:
	virtual void execute(const MyVector<MyString>& args, TrainSystemApp& app) const = 0;
	virtual ~Command() = default;
};

