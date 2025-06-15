#include "CommandFactory.h"
#include "PrintStationsCommand.h"
#include "LoginCommand.h"
#include "AddStationCommand.h"
#include "AddTrainCommand.h"
#include "AddWagonCommand.h"
#include "RemoveWagonCommand.h"
#include "MoveWagonCommand.h"
#include "CreateDiscountCardCommand.h"
#include "ValidateDiscountCardCommand.h"
#include "PrintScheduleCommand.h"
#include "PrintScheduleDestinationCommand.h"
#include "PrintScheduleTimeCommand.h"
#include "PrintTrainCommand.h"
#include "PrintWagonCommand.h"
#include "BuyTicketCommand.h"
#include "BuyTicketDiscountCommand.h"

Command* CommandFactory::create(const MyString& commandType) {
	if (commandType == "print-stations") {
		return new PrintStationsCommand();
	}
	else if (commandType == "login") {
		return new LoginCommand();
	}
	else if (commandType == "add-station") {
		return new AddStationCommand();
	}
	else if (commandType == "add-train") {
		return new AddTrainCommand();
	}
	else if (commandType == "add-wagon") {
		return new AddWagonCommand();
	}
	else if (commandType == "remove-wagon") {
		return new RemoveWagonCommand();
	}
	else if (commandType == "move-wagon") {
		return new MoveWagonCommand();
	}
	else if (commandType == "create-discount-card") {
		return new CreateDiscountCardCommand();
	}
	else if (commandType == "validate-discount-card") {
		return new ValidateDiscountCardCommand();
	}
	else if (commandType == "print-schedule") {
		return new PrintScheduleCommand();
	}
	else if (commandType == "print-schedule-destination") {
		return new PrintScheduleDestinationCommand();
	}
	else if (commandType == "print-schedule-time") {
		return new PrintScheduleTimeCommand();
	}
	else if (commandType == "print-train") {
		return new PrintTrainCommand();
	}
	else if (commandType == "print-wagon") {
		return new PrintWagonCommand();
	}
	else if (commandType == "buy-ticket") {
		return new BuyTicketCommand();
	}
	else if (commandType == "buy-ticket-discount") {
		return new BuyTicketDiscountCommand();
	}

	return nullptr;
}
