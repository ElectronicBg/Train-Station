#include "ValidateDiscountCardCommand.h"
#include <iostream>

void ValidateDiscountCardCommand::execute(const MyVector<MyString>& args, TrainSystemApp& app) const {
    if (args.getSize() != 2) {
        std::cout << "Usage: validate-discount-card <code>\n";
        return;
    }

    int code = args[1].parseToInt();

    const auto& repo = app.getDiscountCardRepo();
    if (repo.isCodeValid(code)) {
        std::cout << "Discount card with code " << code << " is valid.\n";
    }
    else {
        std::cout << "No valid discount card found with code " << code << ".\n";
    }
}
