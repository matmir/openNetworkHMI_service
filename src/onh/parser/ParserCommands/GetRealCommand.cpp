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
#include "GetRealCommand.h"
#include "../CommandList.h"

namespace onh {

GetRealCommand::GetRealCommand(std::shared_ptr<ParserDB> parserDB,
								std::shared_ptr<ProcessReader> pr,
								const std::string& commandData):
	db(parserDB), prReader(pr), data(commandData) {
	// Check readers
	if (!db)
		throw Exception("No database object", "GetRealCommand::GetRealCommand");
	if (!prReader)
		throw Exception("No process reader object", "GetRealCommand::GetRealCommand");
}

std::string GetRealCommand::execute() {
	std::stringstream s;
	float f;

	// Check data string
	if (data.length() == 0)
		throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "GetRealCommand::execute");

	// Read Tag data from DB
	Tag t(db->getTag(data));

	// Get REAL from controller
	f = prReader->getReal(t);

	// Prepare answer
	s << GET_REAL << CMD_SEPARATOR << (float)f;

	return s.str();
}

}  // namespace onh
