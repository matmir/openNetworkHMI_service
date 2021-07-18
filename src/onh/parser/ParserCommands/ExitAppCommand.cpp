/**
 * This file is part of openNetworkHMI.
 * Copyright (c) 2021 Mateusz Mirosławski.
 *
 * openNetworkHMI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * openNetworkHMI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with openNetworkHMI.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <sstream>
#include "ExitAppCommand.h"
#include "../CommandList.h"

namespace onh {

ExitAppCommand::ExitAppCommand(const GuardDataController<ThreadExitData> &gdcTED,
								const std::string& commandData):
	thExitController(gdcTED), data(commandData) {
}

std::string ExitAppCommand::execute() {
	std::stringstream s;

	// Check data string
	if (data.length() == 0)
		throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "ExitAppCommand::execute");

	if (data != "1")
		throw CommandParserException(CommandParserException::WRONG_DATA, "Wrong data", "ExitAppCommand::execute");

	// Exit application
	ThreadExitData ex;
	ex.exit = true;
	ex.additionalInfo = "EXIT_APP from socket client";

	// Trigger application exit
	thExitController.setData(ex);

	// Prepare answer
	s << EXIT_APP << CMD_SEPARATOR << OK;

	return s.str();
}

}  // namespace onh
