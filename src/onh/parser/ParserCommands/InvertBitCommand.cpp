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
#include "InvertBitCommand.h"
#include "../CommandList.h"

namespace onh {

InvertBitCommand::InvertBitCommand(std::shared_ptr<ParserDB> parserDB,
								std::shared_ptr<ProcessWriter> pw,
								const std::string& commandData):
	db(parserDB), prWriter(pw), data(commandData) {
	// Check readers
	if (!db)
		throw Exception("No database object", "InvertBitCommand::InvertBitCommand");
	if (!prWriter)
		throw Exception("No process writer object", "InvertBitCommand::InvertBitCommand");
}

std::string InvertBitCommand::execute() {
	std::stringstream s;

	// Check data string
	if (data.length() == 0)
		throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "InvertBitCommand::execute");

	// Get Tag
	Tag t(db->getTag(data));

	// Reset bit
	prWriter->invertBit(t);

	// Prepare answer
	s << INVERT_BIT << CMD_SEPARATOR << OK;

	return s.str();
}

}  // namespace onh
