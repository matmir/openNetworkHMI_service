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

#include "ErrorCommand.h"
#include "../CommandList.h"
#include <sstream>

namespace onh {

ErrorCommand::ErrorCommand(const CommandParserException::ExceptionType& et):
	exType(et) {
}

std::string ErrorCommand::execute() {
	std::stringstream s;
	parserReply rp;

	switch (exType) {
		case CommandParserException::NONE: rp = INTERNAL_ERR; break;
		case CommandParserException::WRONG_DATA: rp = UNKNOWN_CMD; break;
		case CommandParserException::WRONG_DATA_COUNT: rp = UNKNOWN_CMD; break;
		case CommandParserException::CONVERSION_COMMAND: rp = UNKNOWN_CMD; break;
		case CommandParserException::UNKNOWN_COMMAND: rp = UNKNOWN_CMD; break;
	}

	s << NOK << CMD_SEPARATOR << rp;

	return s.str();
}

}  // namespace onh
