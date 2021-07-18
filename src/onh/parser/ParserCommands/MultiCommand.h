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

#ifndef ONH_PARSER_PARSERCOMMANDS_MULTICOMMAND_H_
#define ONH_PARSER_PARSERCOMMANDS_MULTICOMMAND_H_

#include "../IParserCommand.h"
#include "../CommandParserException.h"
#include "../../db/ParserDB.h"
#include "../../driver/ProcessWriter.h"
#include "../../driver/ProcessReader.h"
#include "../../thread/ThreadExitData.h"
#include "../../utils/GuardDataController.h"

namespace onh {

/**
 * Parser MULTI_CMD command
 */
class MultiCommand: public IParserCommand {
	public:
		/**
		 * MULTI_CMD command constructor
		 *
		 * @param parserDB Parser database
		 * @param pr Process reader
		 * @param pw Process writer
		 * @param gdcTED Thread exit controller
		 * @param commandData String with command data
		 */
		MultiCommand(std::shared_ptr<ParserDB> parserDB,
						std::shared_ptr<ProcessReader> pr,
						std::shared_ptr<ProcessWriter> pw,
						const GuardDataController<ThreadExitData> &gdcTED,
						const std::string& commandData);

		/**
		 * Command Destructor
		 */
		virtual ~MultiCommand() = default;

		/**
		 * Execute parser command and get reply
		 *
		 * @return String with reply
		 */
		std::string execute() override;

	private:
		/// Parser database access
		std::shared_ptr<ParserDB> db;
		/// Process data reader
		std::shared_ptr<ProcessReader> prReader;
		/// Process data writer
		std::shared_ptr<ProcessWriter> prWriter;
		/// Thread exit data controller
		GuardDataController<ThreadExitData> thExitController;
		/// command data
		const std::string data;

		/**
		 * Get reply from one command request
		 *
		 * @param cmd String with command
		 * @return String data with reply
		 */
		std::string parseOneCommand(const std::string& cmd);

		/**
		 * Prepare reply
		 *
		 * @param reply Command reply data
		 * @return String with reply
		 */
		std::string prepareReply(const std::vector<std::string>& reply);
};

}  // namespace onh

#endif  // ONH_PARSER_PARSERCOMMANDS_MULTICOMMAND_H_
