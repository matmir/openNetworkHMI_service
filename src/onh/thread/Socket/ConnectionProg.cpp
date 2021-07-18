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

#include <string.h>
#include <unistd.h>
#include <sstream>
#include "ConnectionProg.h"
#include "Socket.h"

namespace onh {

ConnectionProgram::ConnectionProgram(int connDescriptor,
										const ProcessReader& pr,
										const ProcessWriter& pw,
										const ThreadCycleControllers& cc,
										const DBCredentials& db,
										const GuardDataController<ThreadExitData> &gdcTED):
	BaseThreadProgram(gdcTED, "parser", std::string("connection_th_" + std::to_string(connDescriptor) + "_"), false),
	connDesc(connDescriptor),
	pReader(std::make_unique<ProcessReader>(pr)),
	pWriter(std::make_unique<ProcessWriter>(pw)),
	dbCredentials(db),
	cycleController(cc) {
}

ConnectionProgram::ConnectionProgram(const ConnectionProgram& rhs):
	BaseThreadProgram(rhs.getExitController(), "parser", "connection_th_" + std::to_string(rhs.connDesc) + "_", false),
	connDesc(rhs.connDesc),
	pReader(std::make_unique<ProcessReader>(*rhs.pReader)),
	pWriter(std::make_unique<ProcessWriter>(*rhs.pWriter)),
	dbCredentials(rhs.dbCredentials),
	cycleController(rhs.cycleController)  {
}

ConnectionProgram::~ConnectionProgram() {
}

void ConnectionProgram::operator()() {
	// Buffer
	char buffer[MAX_BUFF_SIZE] = {0};

	try {
		// Parser
		std::unique_ptr<IParser> parser = std::make_unique<CommandParser>(*pReader,
																			*pWriter,
																			dbCredentials,
																			cycleController,
																			getExitController(),
																			connDesc);

		// Read client data
		if (read(connDesc, buffer, MAX_BUFF_SIZE) == -1) {
			throw SocketException("Error while socket read data", errno, "ConnectionProgram::operator()");
		}

		// Prepare reply
		std::string reply = parser->getReply(buffer);

		// Send reply
		if (send(connDesc, reply.c_str(), strlen(reply.c_str()), 0) == -1) {
			throw SocketException("Error while socket send data", errno, "ConnectionProgram::operator()");
		}
	} catch (Exception &e) {
		getLogger() << LOG_ERROR(e.what());
	}

	// Close connection descriptor
	close(connDesc);
}

}  // namespace onh
