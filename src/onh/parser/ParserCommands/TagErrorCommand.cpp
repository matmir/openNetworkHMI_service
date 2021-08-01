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

#include "TagErrorCommand.h"
#include "../CommandList.h"
#include <sstream>

namespace onh {

TagErrorCommand::TagErrorCommand(const TagException::ExceptionType& et):
	exType(et) {
}

std::string TagErrorCommand::execute() {
	std::stringstream s;
	parserReply rp = INTERNAL_ERR;

	switch (exType) {
		case TagException::NONE: rp = INTERNAL_ERR; break;
		case TagException::WRONG_ID: rp = UNKNOWN_CMD; break;
		case TagException::WRONG_NAME: rp = UNKNOWN_CMD; break;
		case TagException::WRONG_TYPE: rp = WRONG_TAG_TYPE; break;
		case TagException::WRONG_AREA: rp = WRONG_TAG_AREA; break;
		case TagException::BYTE_ADDRESS_OUT_OF_RANGE: rp = WRONG_ADDR; break;
		case TagException::BIT_ADDRESS_OUT_OF_RANGE: rp = WRONG_ADDR; break;
		case TagException::NOT_EXIST: rp = NOT_EXIST; break;
	}

	s << NOK << CMD_SEPARATOR << rp;

	return s.str();
}

}  // namespace onh
