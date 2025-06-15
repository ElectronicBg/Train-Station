#pragma once
#include "Command.h"

class BuyTicketDiscountCommand : public Command {
public:
    void execute(const MyVector<MyString>& args, TrainSystemApp& app) const override;
};
