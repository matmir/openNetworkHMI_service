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
#include "SetBitsCommand.h"
#include "../CommandList.h"
#include "../../utils/StringUtils.h"

namespace onh {

SetBitsCommand::SetBitsCommand(std::shared_ptr<ParserDB> parserDB,
								std::shared_ptr<ProcessWriter> pw,
								const std::string& commandData):
	db(parserDB), prWriter(pw), data(commandData) {
	// Check readers
	if (!db)
		throw Exception("No database object", "SetBitsCommand::SetBitsCommand");
	if (!prWriter)
		throw Exception("No process writer object", "SetBitsCommand::SetBitsCommand");
}

std::string SetBitsCommand::execute() {
	std::stringstream s;
	std::vector<std::string> v;
	std::vector<Tag> vTag;

	// Check data string
	if (data.length() == 0)
		throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "SetBitsCommand::execute");

	// Explode tag names
	v = StringUtils::explode(data, CMD_TAGS_SEPARATOR);
	if (v.size() == 0)
		throw CommandParserException(CommandParserException::WRONG_DATA, "No valid data", "SetBitsCommand::execute");

	// Read tag data from DB
	vTag = db->getTags(v);

	// Set bits
	prWriter->setBits(vTag);

	// Prepare answer
	s << SET_BITS << CMD_SEPARATOR << OK;

	return s.str();
}

}  // namespace onh
