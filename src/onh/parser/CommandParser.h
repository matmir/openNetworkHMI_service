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

#ifndef ONH_PARSER_COMMANDPARSER_H_
#define ONH_PARSER_COMMANDPARSER_H_

#include <string>
#include <vector>
#include "IParser.h"
#include "IParserCommand.h"
#include "../driver/ProcessReader.h"
#include "../driver/ProcessWriter.h"
#include "../thread/ThreadCycleControllers.h"
#include "CommandList.h"
#include "../utils/logger/TextLogger.h"
#include "CommandParserException.h"
#include "../db/ParserDB.h"
#include "../db/DBCredentials.h"
#include "../thread/ThreadExitData.h"
#include "../utils/GuardDataController.h"

namespace onh {

/**
 * Command parser class
 */
class CommandParser: public IParser {
	public:
		/**
		 * Parser constructor
		 *
		 * @param pr Process reader
		 * @param pw Process writer
		 * @param dbc DB data
		 * @param cc Thread cycle controllers
		 * @param gdcTED Thread exit controller
		 * @param connDescriptor Socket connection descriptor
		 */
		CommandParser(const ProcessReader& pr,
						const ProcessWriter& pw,
						const DBCredentials& dbc,
						const ThreadCycleControllers& cc,
						const GuardDataController<ThreadExitData> &gdcTED,
						int connDescriptor);

		/**
		 * Copy constructor - inactive
		 */
		CommandParser(const CommandParser&) = delete;

		~CommandParser() override;

		/**
		 * Assignment operator - inactive
		 */
		CommandParser& operator=(const CommandParser&) = delete;

		/**
		 * Get string reply for a given query
		 *
		 * @param query String with query from socket client
		 * @return String with reply
		 */
		std::string getReply(const std::string& query) override;

	private:
		/// Process data reader
		std::shared_ptr<ProcessReader> prReader;

		/// Process data writer
		std::shared_ptr<ProcessWriter> prWriter;

		/// Thread exit data controller
		GuardDataController<ThreadExitData> thExitController;

		/// Thread cycle controllers
		ThreadCycleControllers cycleController;

		/// DB access
		std::shared_ptr<ParserDB> db;

		/// Logger object
		std::unique_ptr<ILogger> log;

		/**
		 * Get parser command
		 *
		 * @param query String with qury
		 * @return Parser command pointer
		 */
		ParserCommandPtr getCommand(const std::string& query);
};

}  // namespace onh

#endif  // ONH_PARSER_COMMANDPARSER_H_
