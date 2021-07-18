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
#include "GetWordCommand.h"
#include "../CommandList.h"

namespace onh {

GetWordCommand::GetWordCommand(std::shared_ptr<ParserDB> parserDB,
								std::shared_ptr<ProcessReader> pr,
								const std::string& commandData):
	db(parserDB), prReader(pr), data(commandData) {
	// Check readers
	if (!db)
		throw Exception("No database object", "GetWordCommand::GetWordCommand");
	if (!prReader)
		throw Exception("No process reader object", "GetWordCommand::GetWordCommand");
}

std::string GetWordCommand::execute() {
	std::stringstream s;
	WORD w;

	// Check data string
	if (data.length() == 0)
		throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "GetWordCommand::execute");

	// Read Tag data from DB
	Tag t(db->getTag(data));

	// Get Word from controller
	w = prReader->getWord(t);

	// Prepare answer
	s << GET_WORD << CMD_SEPARATOR << (WORD)w;

	return s.str();
}

}  // namespace onh
