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

#ifndef ONH_PARSER_PARSERCOMMANDS_TAGERRORCOMMAND_H_
#define ONH_PARSER_PARSERCOMMANDS_TAGERRORCOMMAND_H_

#include "../IParserCommand.h"
#include "../../db/objs/TagException.h"

namespace onh {

/**
 * Parser Tag error command
 */
class TagErrorCommand: public IParserCommand {
	public:
		/**
		 * Error command constructor
		 *
		 * @param et Exception type
		 */
		explicit TagErrorCommand(const TagException::ExceptionType& et);

		/**
		 * Command Destructor
		 */
		~TagErrorCommand() = default;

		/**
		 * Execute parser command and get reply
		 *
		 * @return String with reply
		 */
		std::string execute() override;

	private:
		/// Exception type
		const TagException::ExceptionType exType;
};

}  // namespace onh

#endif  // ONH_PARSER_PARSERCOMMANDS_TAGERRORCOMMAND_H_
