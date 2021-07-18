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

#ifndef ONH_PARSER_PARSERCOMMANDS_WRITEINTCOMMAND_H_
#define ONH_PARSER_PARSERCOMMANDS_WRITEINTCOMMAND_H_

#include "../IParserCommand.h"
#include "../CommandParserException.h"
#include "../../db/ParserDB.h"
#include "../../driver/ProcessWriter.h"

namespace onh {

/**
 * Parser WRITE_INT command
 */
class WriteIntCommand: public IParserCommand {
	public:
		/**
		 * WRITE_INT command constructor
		 *
		 * @param parserDB Parser database
		 * @param pr Process reader
		 * @param commandData String with command data
		 */
		WriteIntCommand(std::shared_ptr<ParserDB> parserDB,
						std::shared_ptr<ProcessWriter> pw,
						const std::string& commandData);

		/**
		 * Command Destructor
		 */
		virtual ~WriteIntCommand() = default;

		/**
		 * Execute parser command and get reply
		 *
		 * @return String with reply
		 */
		std::string execute() override;

	private:
		/// Parser database access
		std::shared_ptr<ParserDB> db;
		/// Process writer
		std::shared_ptr<ProcessWriter> prWriter;
		/// command data
		const std::string data;
};

}  // namespace onh

#endif  // ONH_PARSER_PARSERCOMMANDS_WRITEINTCOMMAND_H_
