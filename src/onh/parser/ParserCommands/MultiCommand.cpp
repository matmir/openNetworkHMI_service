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
#include "MultiCommand.h"
#include "../CommandList.h"
#include "../../utils/StringUtils.h"
#include "GetBitCommand.h"
#include "SetBitCommand.h"
#include "ResetBitCommand.h"
#include "InvertBitCommand.h"
#include "GetBitsCommand.h"
#include "SetBitsCommand.h"
#include "GetByteCommand.h"
#include "WriteByteCommand.h"
#include "GetWordCommand.h"
#include "WriteWordCommand.h"
#include "GetDWordCommand.h"
#include "WriteDWordCommand.h"
#include "GetIntCommand.h"
#include "WriteIntCommand.h"
#include "GetRealCommand.h"
#include "WriteRealCommand.h"
#include "AckAlarmCommand.h"
#include "GetThreadCycleTimeCommand.h"
#include "ExitAppCommand.h"

namespace onh {

/// Multicommand command separator
const char MULTI_CMD_SEPARATOR = '!';
/// Multicommand command value separator
const char MULTI_CMD_VALUE_SEPARATOR = '?';

MultiCommand::MultiCommand(std::shared_ptr<ParserDB> parserDB,
							std::shared_ptr<ProcessReader> pr,
							std::shared_ptr<ProcessWriter> pw,
							const GuardDataController<ThreadExitData> &gdcTED,
							const std::string& commandData):
	db(parserDB), prReader(pr),	prWriter(pw), thExitController(gdcTED), data(commandData) {
	// Check readers
	if (!db)
		throw Exception("No database object", "MultiCommand::MultiCommand");
	if (!prReader)
		throw Exception("No process reader object", "MultiCommand::MultiCommand");
	if (!prWriter)
		throw Exception("No process writer object", "MultiCommand::MultiCommand");
}

std::string MultiCommand::execute() {
	std::vector<std::string> v;
	std::vector<std::string> cmdReply;
	std::string cmd;

	// Check data string
	if (data.length() == 0)
		throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "MultiCommand::execute");

	// Explode string on commands
	v = StringUtils::explode(data, MULTI_CMD_SEPARATOR);

	// Check commands
	if (v.size() == 0)
		throw CommandParserException(CommandParserException::WRONG_DATA, "No commands", "MultiCommand::execute");

	// Iterate all commands
	for (unsigned int i=0; i < v.size(); ++i) {
		// Get one command - replace delimiter
		cmd = StringUtils::replaceChar(v[i], MULTI_CMD_VALUE_SEPARATOR, CMD_SEPARATOR);

		// Get command reply
		cmdReply.push_back(parseOneCommand(cmd));
	}

	return prepareReply(cmdReply);
}

std::string MultiCommand::parseOneCommand(const std::string& cmd) {
	std::vector<std::string> v;

	// Explode command and data
	v = StringUtils::explode(cmd, CMD_SEPARATOR);

	// Check exploded data count
	if (v.size() != 2)
		throw CommandParserException(CommandParserException::WRONG_DATA_COUNT,
										"Wrong exploded data count",
										"MultiCommand::parseOneCommand");

	// Parse command number
	int val = 0;
	std::istringstream iss(v[0]);
	iss >> val;

	ParserCommandPtr cm = nullptr;

	switch (val) {
		case GET_BIT: cm.reset(new GetBitCommand(db, prReader, v[1])); break;
		case SET_BIT: cm.reset(new SetBitCommand(db, prWriter, v[1])); break;
		case RESET_BIT: cm.reset(new ResetBitCommand(db, prWriter, v[1])); break;
		case INVERT_BIT: cm.reset(new InvertBitCommand(db, prWriter, v[1])); break;
		case GET_BITS: cm.reset(new GetBitsCommand(db, prReader, v[1])); break;
		case SET_BITS: cm.reset(new SetBitsCommand(db, prWriter, v[1])); break;
		case GET_BYTE: cm.reset(new GetByteCommand(db, prReader, v[1])); break;
		case WRITE_BYTE: cm.reset(new WriteByteCommand(db, prWriter, v[1])); break;
		case GET_WORD: cm.reset(new GetWordCommand(db, prReader, v[1])); break;
		case WRITE_WORD: cm.reset(new WriteWordCommand(db, prWriter, v[1])); break;
		case GET_DWORD: cm.reset(new GetDWordCommand(db, prReader, v[1])); break;
		case WRITE_DWORD: cm.reset(new WriteDWordCommand(db, prWriter, v[1])); break;
		case GET_INT: cm.reset(new GetIntCommand(db, prReader, v[1])); break;
		case WRITE_INT: cm.reset(new WriteIntCommand(db, prWriter, v[1])); break;
		case GET_REAL: cm.reset(new GetRealCommand(db, prReader, v[1])); break;
		case WRITE_REAL: cm.reset(new WriteRealCommand(db, prWriter, v[1])); break;
		case ACK_ALARM: cm.reset(new AckAlarmCommand(db, v[1])); break;
		case EXIT_APP: cm.reset(new ExitAppCommand(thExitController, v[1])); break;
		case GET_THREAD_CYCLE_TIME: throw CommandParserException(CommandParserException::UNKNOWN_COMMAND,
																	"Can not call GET_THREAD_CYCLE_TIME inside multi command",
																	"MultiCommand::parseOneCommand"); break;
		case MULTI_CMD: throw CommandParserException(CommandParserException::UNKNOWN_COMMAND,
														"Multi command inside multi command",
														"MultiCommand::parseOneCommand"); break;
		default: throw CommandParserException(CommandParserException::UNKNOWN_COMMAND,
												"Unknown command: "+v[0],
												"MultiCommand::parseOneCommand");
	}

	return cm->execute();
}

std::string MultiCommand::prepareReply(const std::vector<std::string>& reply) {
	std::stringstream s;

	s << MULTI_CMD << CMD_SEPARATOR;

	// Check data
	if (reply.size() == 0)
		throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "MultiCommand::prepareReply");

	for (unsigned int i=0; i < reply.size(); ++i) {
		// Replace delimiter
		s << StringUtils::replaceChar(reply[i], CMD_SEPARATOR, MULTI_CMD_VALUE_SEPARATOR);

		if (i < reply.size()-1) {
			s << MULTI_CMD_SEPARATOR;
		}
	}

	return s.str();
}

}  // namespace onh
