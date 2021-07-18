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

#include "CommandParser.h"
#include <sstream>
#include "../db/objs/DriverConnection.h"
#include "../db/objs/Tag.h"
#include "../utils/StringUtils.h"
#include "ParserCommands/ErrorCommand.h"
#include "ParserCommands/TagErrorCommand.h"
#include "ParserCommands/GetBitCommand.h"
#include "ParserCommands/SetBitCommand.h"
#include "ParserCommands/ResetBitCommand.h"
#include "ParserCommands/InvertBitCommand.h"
#include "ParserCommands/GetBitsCommand.h"
#include "ParserCommands/SetBitsCommand.h"
#include "ParserCommands/GetByteCommand.h"
#include "ParserCommands/WriteByteCommand.h"
#include "ParserCommands/GetWordCommand.h"
#include "ParserCommands/WriteWordCommand.h"
#include "ParserCommands/GetDWordCommand.h"
#include "ParserCommands/WriteDWordCommand.h"
#include "ParserCommands/GetIntCommand.h"
#include "ParserCommands/WriteIntCommand.h"
#include "ParserCommands/GetRealCommand.h"
#include "ParserCommands/WriteRealCommand.h"
#include "ParserCommands/AckAlarmCommand.h"
#include "ParserCommands/GetThreadCycleTimeCommand.h"
#include "ParserCommands/ExitAppCommand.h"
#include "ParserCommands/MultiCommand.h"

namespace onh {

CommandParser::CommandParser(const ProcessReader& pr,
								const ProcessWriter& pw,
								const DBCredentials& dbc,
								const ThreadCycleControllers& cc,
								const GuardDataController<ThreadExitData> &gdcTED,
								int connDescriptor):
	prReader(std::make_shared<ProcessReader>(pr)),
	prWriter(std::make_shared<ProcessWriter>(pw)),
	thExitController(gdcTED),
	cycleController(cc),
	db(std::make_shared<ParserDB>(dbc)) {
	// Create logger
	std::stringstream s;
	s << "parser_th_" << connDescriptor << "_";
	log = std::make_unique<TextLogger>("parser", s.str());
}

CommandParser::~CommandParser() {
}

std::string CommandParser::getReply(const std::string& query) {
	std::string s;

	try {
		// Check readers
		if (!prReader)
			throw Exception("No process reader object", "CommandParser::getReply");
		if (!prWriter)
			throw Exception("No process writer object", "CommandParser::getReply");

		// Update process reader
		prReader->updateProcessData();

		// Parse command
		auto cmd = getCommand(query);

		// Parse whole command
		s = cmd->execute();
	} catch(CommandParserException &e) {
		log->write(LOG_ERROR(e.what()));

		ErrorCommand errCmd(e.getType());
		s = errCmd.execute();
	} catch (TagException &e) {
		log->write(LOG_ERROR(e.what()));

		TagErrorCommand errCmd(e.getType());
		s = errCmd.execute();
	} catch (Exception &e) {
		log->write(LOG_ERROR(e.what()));

		ErrorCommand errCmd(CommandParserException::NONE);
		s = errCmd.execute();
	}

	return s;
}

ParserCommandPtr CommandParser::getCommand(const std::string& query) {
	std::vector<std::string> v;

	// Check if there is query string
	if (query.length() == 0)
		throw CommandParserException(CommandParserException::WRONG_DATA, "Query string is empty", "CommandParser::getReply");

	// Explode command and data
	v = StringUtils::explode(query, CMD_SEPARATOR);

	// Check exploded data count
	if (v.size() != 2)
		throw CommandParserException(CommandParserException::WRONG_DATA_COUNT,
										"Wrong exploded data count",
										"CommandParser::getReply");

	int val = 0;
	std::istringstream iss(v[0]);
	iss >> val;

	switch (val) {
		case GET_BIT: return ParserCommandPtr(new GetBitCommand(db, prReader, v[1])); break;
		case SET_BIT: return ParserCommandPtr(new SetBitCommand(db, prWriter, v[1])); break;
		case RESET_BIT: return ParserCommandPtr(new ResetBitCommand(db, prWriter, v[1])); break;
		case INVERT_BIT: return ParserCommandPtr(new InvertBitCommand(db, prWriter, v[1])); break;
		case GET_BITS: return ParserCommandPtr(new GetBitsCommand(db, prReader, v[1])); break;
		case SET_BITS: return ParserCommandPtr(new SetBitsCommand(db, prWriter, v[1])); break;
		case GET_BYTE: return ParserCommandPtr(new GetByteCommand(db, prReader, v[1])); break;
		case WRITE_BYTE: return ParserCommandPtr(new WriteByteCommand(db, prWriter, v[1])); break;
		case GET_WORD: return ParserCommandPtr(new GetWordCommand(db, prReader, v[1])); break;
		case WRITE_WORD: return ParserCommandPtr(new WriteWordCommand(db, prWriter, v[1])); break;
		case GET_DWORD: return ParserCommandPtr(new GetDWordCommand(db, prReader, v[1])); break;
		case WRITE_DWORD: return ParserCommandPtr(new WriteDWordCommand(db, prWriter, v[1])); break;
		case GET_INT: return ParserCommandPtr(new GetIntCommand(db, prReader, v[1])); break;
		case WRITE_INT: return ParserCommandPtr(new WriteIntCommand(db, prWriter, v[1])); break;
		case GET_REAL: return ParserCommandPtr(new GetRealCommand(db, prReader, v[1])); break;
		case WRITE_REAL: return ParserCommandPtr(new WriteRealCommand(db, prWriter, v[1])); break;
		case MULTI_CMD: return ParserCommandPtr(new MultiCommand(db, prReader, prWriter, thExitController, v[1])); break;
		case ACK_ALARM: return ParserCommandPtr(new AckAlarmCommand(db, v[1])); break;
		case GET_THREAD_CYCLE_TIME: return ParserCommandPtr(new GetThreadCycleTimeCommand(cycleController, v[1])); break;
		case EXIT_APP: return ParserCommandPtr(new ExitAppCommand(thExitController, v[1])); break;
		default: throw CommandParserException(CommandParserException::UNKNOWN_COMMAND,
												"Unknown command: "+v[0],
												"CommandParser::parseCMD");
	}
}

}  // namespace onh
