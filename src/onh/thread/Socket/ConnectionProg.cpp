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

#include "ConnectionProg.h"
#include "Socket.h"
#include <string.h>
#include <sstream>
#include <unistd.h>

using namespace onh;

ConnectionProgram::ConnectionProgram(int connDescriptor,
										const ProcessReader& pr,
										const ProcessWriter& pw,
										const ThreadCycleControllers& cc,
										const DBCredentials& db,
										const ThreadExitController &thEC):
	connDesc(connDescriptor), dbCredentials(db), cycleController(cc)
{
	// Process reader
	pReader = new ProcessReader(pr);

	// Process writer
	pWriter = new ProcessWriter(pw);

	// Thread exit controller
	thExit = new ThreadExitController(thEC);

	// Create logger
	std::stringstream s;
	s << "connection_th_" << connDescriptor << "_";
	log = new Logger("parser", s.str());

	// Create parser
	parser = new CommandParser(pr,
								pw,
								db,
								cc,
								thEC,
								connDescriptor);
}

ConnectionProgram::ConnectionProgram(const ConnectionProgram& rhs):
	connDesc(rhs.connDesc), dbCredentials(rhs.dbCredentials), cycleController(rhs.cycleController)
{
	// Process reader
	pReader = new ProcessReader(*rhs.pReader);

	// Process writer
	pWriter = new ProcessWriter(*rhs.pWriter);

	// Thread exit controller
	thExit = new ThreadExitController(*rhs.thExit);

	// Create logger
	std::stringstream s;
	s << "connection_th_" << connDesc << "_";
	log = new Logger("parser", s.str());

	// Create parser
	parser = new CommandParser(*pReader,
								*pWriter,
								dbCredentials,
								cycleController,
								*thExit,
								connDesc);
}

ConnectionProgram::~ConnectionProgram() {

	if (pReader)
		delete pReader;

	if (pWriter)
		delete pWriter;

	if (thExit)
		delete thExit;

	if (parser)
		delete parser;

	if (log)
		delete log;
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
		if (send(connDesc, reply.c_str(), strlen(reply.c_str()), 0 ) == -1) {

			throw SocketException("Error while socket send data", errno, "ConnectionProgram::operator()");
		}

	} catch (Exception &e) {

		log->write(e.what());
	}

	// Close connection descriptor
	close(connDesc);
}
