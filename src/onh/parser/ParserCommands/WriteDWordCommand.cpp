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
#include "WriteDWordCommand.h"
#include "../CommandList.h"
#include "../../utils/StringUtils.h"

namespace onh {

WriteDWordCommand::WriteDWordCommand(std::shared_ptr<ParserDB> parserDB,
								std::shared_ptr<ProcessWriter> pw,
								const std::string& commandData):
	db(parserDB), prWriter(pw), data(commandData) {
	// Check readers
	if (!db)
		throw Exception("No database object", "WriteDWordCommand::WriteDWordCommand");
	if (!prWriter)
		throw Exception("No process writer object", "WriteDWordCommand::WriteDWordCommand");
}

std::string WriteDWordCommand::execute() {
	std::stringstream s;
	std::vector<std::string> v;

	// Check data string
	if (data.length() == 0)
		throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "WriteDWordCommand::execute");

	// Explode command on tag and value
	v = StringUtils::explode(data, CMD_TAG_VALUE_SEPARATOR);
	if (v.size() != 2)
		throw CommandParserException(CommandParserException::WRONG_DATA, "No valid data", "WriteDWordCommand::execute");

	// Read Tag data from DB
	Tag t(db->getTag(v[0]));

	// Prepare value
	DWORD val;
	std::istringstream iss(v[1]);
	iss >> val;

	// Write byte
	prWriter->writeDWord(t, val);

	// Prepare answer
	s << WRITE_DWORD << CMD_SEPARATOR << OK;

	return s.str();
}

}  // namespace onh
