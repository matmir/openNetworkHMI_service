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
	connDesc(connDescriptor),
	pReader(std::make_unique<ProcessReader>(pr)),
	pWriter(std::make_unique<ProcessWriter>(pw)),
	dbCredentials(db),
	thExit(gdcTED),
	cycleController(cc),
	parser(std::make_unique<CommandParser>(pr, pw, db, cc, thExit, connDescriptor)) {
	// Create logger
	std::stringstream s;
	s << "connection_th_" << connDescriptor << "_";
	log = std::make_unique<Logger>("parser", s.str());
}

ConnectionProgram::ConnectionProgram(const ConnectionProgram& rhs):
	connDesc(rhs.connDesc),
	pReader(std::make_unique<ProcessReader>(*rhs.pReader)),
	pWriter(std::make_unique<ProcessWriter>(*rhs.pWriter)),
	dbCredentials(rhs.dbCredentials),
	thExit(rhs.thExit),
	cycleController(rhs.cycleController),
	parser(std::make_unique<CommandParser>(*rhs.pReader,
											*rhs.pWriter,
											dbCredentials,
											cycleController,
											thExit,
											connDesc))  {
	// Create logger
	std::stringstream s;
	s << "connection_th_" << connDesc << "_";
	log = std::make_unique<Logger>("parser", s.str());
}

ConnectionProgram::~ConnectionProgram() {
}

void ConnectionProgram::operator()() {
	// Buffer
	char buffer[MAX_BUFF_SIZE] = {0};

	try {
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
		log->write(e.what());
	}

	// Close connection descriptor
	close(connDesc);
}

}  // namespace onh
