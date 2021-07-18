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
#include "AckAlarmCommand.h"
#include "../CommandList.h"

namespace onh {

AckAlarmCommand::AckAlarmCommand(std::shared_ptr<ParserDB> parserDB,
								const std::string& commandData):
	db(parserDB), data(commandData) {
	// Check readers
	if (!db)
		throw Exception("No database object", "AckAlarmCommand::AckAlarmCommand");
}

std::string AckAlarmCommand::execute() {
	std::stringstream s;

	// Check data string
	if (data.length() == 0)
		throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "AckAlarmCommand::execute");

	// Get pending alaram identifier
	unsigned int paid = 0;
	std::istringstream iss(data);
	iss >> paid;

	// Acknowledge alarm
	db->getAlarmDB().ackAlarm(paid);

	// Prepare answer
	s << ACK_ALARM << CMD_SEPARATOR << OK;

	return s.str();
}

}  // namespace onh
