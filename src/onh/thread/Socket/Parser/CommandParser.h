/**
 * This file is part of openNetworkHMI.
 * Copyright (c) 2020 Mateusz Mirosławski.
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

#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <string>
#include <vector>
#include "../../../driver/ProcessReader.h"
#include "../../../driver/ProcessWriter.h"
#include "../../ThreadCycleControllers.h"
#include "CommandList.h"
#include "../../../utils/Logger.h"
#include "CommandParserException.h"
#include "../../../db/ParserDB.h"
#include "../../../db/DBCredentials.h"
#include "../../ThreadExitController.h"

namespace onh {

    /**
	 * Command parser class
	 */
    class CommandParser {

        public:

            /**
             * Parser constructor
             *
             * @param pr Process reader
             * @param pw Process writer
             * @param dbc DB data
             * @param cc Thread cycle controllers
             * @param thEC Thread exit controller
             * @param connDescriptor Socket connection descriptor
             */
            CommandParser(const ProcessReader& pr,
							const ProcessWriter& pw,
							const DBCredentials& dbc,
							const ThreadCycleControllers& cc,
							const ThreadExitController &thEC,
							int connDescriptor);

            /**
             * Copy constructor - inactive
             */
            CommandParser(const CommandParser&) = delete;

            virtual ~CommandParser();

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
            std::string getReply(const std::string& query);

        private:
            /// Process data reader
            ProcessReader *prReader;

            /// Process data writer
            ProcessWriter *prWriter;

            /// Thread exit controller
            ThreadExitController *thExitController;

            /// Thread cycle controllers
            ThreadCycleControllers cycleController;

            /// DB access
            ParserDB *db;

            /// Logger object
            Logger* log;

            /**
             * Get reply from multi command request
             *
             * @param cmd String with command
             *
             * @return String data with reply
             */
            std::string getReplyFromMultiCMD(const std::string& cmd);

            /**
             * Parse command number
             *
             * @param cmd String with command number
             *
             * @return parserCMD value
             */
            parserCMD parseCMD(const std::string& cmd);

            /**
             * Check if command number exist
             *
             * @param cmdNr Command number
             *
             * @return True if command exist
             */
            bool checkCMD(int cmdNr);

            /**
             * Prepare reply - OK
             *
             * @param cmd Parser command
             * @param data Command additional data (STRING)
             *
             * @return String with reply
             */
            std::string replyOK(parserCMD cmd, const std::string& data="");

            /**
             * Prepare reply - OK
             *
             * @param cmd Parser command
             * @param data Command additional data (vector BOOL)
             *
             * @return String with reply
             */
            std::string replyOK(parserCMD cmd, const std::vector<bool>& data);

            /**
             * Prepare reply - OK
             *
             * @param data Command additional data (BYTE)
             *
             * @return String with reply
             */
            std::string replyOK(BYTE data);

            /**
             * Prepare reply - OK
             *
             * @param data Command additional data (WORD)
             *
             * @return String with reply
             */
            std::string replyOK(WORD data);

            /**
             * Prepare reply - OK
             *
             * @param data Command additional data (DWORD)
             *
             * @return String with reply
             */
            std::string replyOK(DWORD data);

            /**
             * Prepare reply - OK
             *
             * @param data Command additional data (INT)
             *
             * @return String with reply
             */
            std::string replyOK(int data);

            /**
             * Prepare reply - OK
             *
             * @param data Command additional data (REAL)
             *
             * @return String with reply
             */
            std::string replyOK(float data);

            /**
             * Prepare reply - OK
             *
             * @param data Command additional data (vector with string reply from multi command)
             *
             * @return String with reply
             */
            std::string replyOK(std::vector<std::string> data);

            /**
             * Prepare reply - OK
             *
             * @param tpcUpdater Cycle time of the Process updater thread
             * @param tpcLogger Cycle time of the Tag logger thread
             * @param tpcLoggerWriter Cycle time of the Tag logger writer thread
             * @param tpcAlarming Cycle time of the Alarming thread
             * @param tpcScript Cycle time of the Script system thread
             * @param tpcPolling Cycle time of the Driver polling thread
             *
             * @return String with reply
             */
            std::string replyOK(CycleTimeData tpcUpdater,
                                CycleTimeData tpcLogger,
								CycleTimeData tpcLoggerWriter,
                                CycleTimeData tpcAlarming,
                                CycleTimeData tpcScript,
                                CycleTimeData tpcPolling);

            /**
             * Prepare reply - Error
             *
             * @param rp Command reply error
             *
             * @return String with reply
             */
            std::string replyError(parserReply rp);

            /**
             * Parse command
             *
             * @param cmd Command
             * @param data Command additional data
             *
             * @return String with reply
             */
            std::string parseCommand(parserCMD cmd, const std::string& data);

            /**
             * Command: GET_BIT
             *
             * @param data Command additional data (tag name)
             *
             * @return String with reply
             */
            std::string CMD_GET_BIT(const std::string& data);

            /**
             * Command: SET_BIT
             *
             * @param data Command additional data (tag name)
             *
             * @return String with reply
             */
            std::string CMD_SET_BIT(const std::string& data);

            /**
             * Command: RESET_BIT
             *
             * @param data Command additional data (tag name)
             *
             * @return String with reply
             */
            std::string CMD_RESET_BIT(const std::string& data);

            /**
             * Command: INVERT_BIT
             *
             * @param data Command additional data (tag name)
             *
             * @return String with reply
             */
            std::string CMD_INVERT_BIT(const std::string& data);

            /**
             * Command: GET_BITS
             *
             * @param data Command additional data (tags names)
             *
             * @return String with reply
             */
            std::string CMD_GET_BITS(const std::string& data);

            /**
             * Command: SET_BITS
             *
             * @param data Command additional data (tags names)
             * @return String with reply
             */
            std::string CMD_SET_BITS(const std::string& data);

            /**
             * Command: GET_BYTE
             *
             * @param data Command additional data (tag name)
             *
             * @return String with reply
             */
            std::string CMD_GET_BYTE(const std::string& data);

            /**
             * Command: WRITE_BYTE
             *
             * @param data Command additional data (tag name)
             *
             * @return String with reply
             */
            std::string CMD_WRITE_BYTE(const std::string& data);

            /**
             * Command: GET_WORD
             *
             * @param data Command additional data (tag name)
             *
             * @return String with reply
             */
            std::string CMD_GET_WORD(const std::string& data);

            /**
             * Command: WRITE_WORD
             *
             * @param data Command additional data (tag name)
             *
             * @return String with reply
             */
            std::string CMD_WRITE_WORD(const std::string& data);

            /**
             * Command: GET_DWORD
             *
             * @param data Command additional data (tag name)
             *
             * @return String with reply
             */
            std::string CMD_GET_DWORD(const std::string& data);

            /**
             * Command: WRITE_DWORD
             *
             * @param data Command additional data (tag name)
             *
             * @return String with reply
             */
            std::string CMD_WRITE_DWORD(const std::string& data);

            /**
             * Command: GET_INT
             *
             * @param data Command additional data (tag name)
             *
             * @return String with reply
             */
            std::string CMD_GET_INT(const std::string& data);

            /**
             * Command: WRITE_INT
             *
             * @param data Command additional data (tag name)
             *
             * @return String with reply
             */
            std::string CMD_WRITE_INT(const std::string& data);

            /**
             * Command: GET_REAL
             *
             * @param data Command additional data (tag name)
             *
             * @return String with reply
             */
            std::string CMD_GET_REAL(const std::string& data);

            /**
             * Command: WRITE_REAL
             *
             * @param data Command additional data (tag name)
             *
             * @return String with reply
             */
            std::string CMD_WRITE_REAL(const std::string& data);

            /**
             * Command: MULTI_CMD
             *
             * @param data Command additional data (commands)
             *
             * @return String with reply
             */
            std::string CMD_MULTI_CMD(const std::string& data);

            /**
             * Command: ACK_ALARM
             *
             * @param data Command additional data (commands)
             *
             * @return String with reply
             */
            std::string CMD_ACK_ALARM(const std::string& data);

            /**
             * Command: GET_THREAD_CYCLE_TIME
             *
             * @param data Command additional data (commands)
             *
             * @return String with reply
             */
            std::string CMD_GET_THREAD_CYCLE_TIME(const std::string& data);

            /**
             * Command: EXIT_APP
             *
             * @param data Command additional data (commands)
             *
             * @return String with reply
             */
            std::string CMD_EXIT_APP(const std::string& data);
    };

}

#endif // COMMANDPARSER_H
