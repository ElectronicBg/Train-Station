#pragma once
#include "Command.h"

class AddWagonCommand : public Command {
public:
	void execute(const MyVector<MyString>& args, TrainSystemApp& app) const override;
};
