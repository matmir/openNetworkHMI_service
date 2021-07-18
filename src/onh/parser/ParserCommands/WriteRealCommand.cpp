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
#include "WriteRealCommand.h"
#include "../CommandList.h"
#include "../../utils/StringUtils.h"

namespace onh {

WriteRealCommand::WriteRealCommand(std::shared_ptr<ParserDB> parserDB,
								std::shared_ptr<ProcessWriter> pw,
								const std::string& commandData):
	db(parserDB), prWriter(pw), data(commandData) {
	// Check readers
	if (!db)
		throw Exception("No database object", "WriteRealCommand::WriteRealCommand");
	if (!prWriter)
		throw Exception("No process writer object", "WriteRealCommand::WriteRealCommand");
}

std::string WriteRealCommand::execute() {
	std::stringstream s;
	std::vector<std::string> v;

	// Check data string
	if (data.length() == 0)
		throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "WriteRealCommand::execute");

	// Explode command on tag and value
	v = StringUtils::explode(data, CMD_TAG_VALUE_SEPARATOR);
	if (v.size() != 2)
		throw CommandParserException(CommandParserException::WRONG_DATA, "No valid data", "WriteRealCommand::execute");

	// Read Tag data from DB
	Tag t(db->getTag(v[0]));

	// Prepare value
	float val;
	std::istringstream iss(v[1]);
	iss >> val;

	// Write real
	prWriter->writeReal(t, val);

	// Prepare answer
	s << WRITE_REAL << CMD_SEPARATOR << OK;

	return s.str();
}

}  // namespace onh
