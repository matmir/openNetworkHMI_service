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
#include "GetBitsCommand.h"
#include "../CommandList.h"
#include "../../utils/StringUtils.h"

namespace onh {

GetBitsCommand::GetBitsCommand(std::shared_ptr<ParserDB> parserDB,
								std::shared_ptr<ProcessReader> pr,
								const std::string& commandData):
	db(parserDB), prReader(pr), data(commandData) {
	// Check readers
	if (!db)
		throw Exception("No database object", "GetBitsCommand::GetBitsCommand");
	if (!prReader)
		throw Exception("No process reader object", "GetBitsCommand::GetBitsCommand");
}

std::string GetBitsCommand::execute() {
	std::stringstream s;
	std::vector<std::string> v;
	std::vector<Tag> vTag;
	std::vector<bool> TagValues;

	// Check data string
	if (data.length() == 0)
		throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "GetBitsCommand::execute");

	// Explode tag names
	v = StringUtils::explode(data, CMD_TAGS_SEPARATOR);
	if (v.size() == 0)
		throw CommandParserException(CommandParserException::WRONG_DATA, "No valid data", "GetBitsCommand::execute");

	// Read tag data from DB
	vTag = db->getTags(v);

	// Get bits values
	TagValues = prReader->getBitsValue(vTag);

	if (TagValues.size() != v.size())
		throw CommandParserException(CommandParserException::WRONG_DATA_COUNT,
										"Not all data read",
										"GetBitsCommand::execute");

	if (TagValues.size() == 0)
		throw CommandParserException(CommandParserException::WRONG_DATA,
										"No data from controller",
										"GetBitsCommand::execute");

	// Prepare answer
	s << GET_BITS << CMD_SEPARATOR;
	for (unsigned int i=0; i < TagValues.size(); ++i) {
		s << ((TagValues[i])?("1"):("0"));

		if (i < TagValues.size()-1) {
			s << CMD_TAGS_SEPARATOR;
		}
	}

	return s.str();
}

}  // namespace onh
