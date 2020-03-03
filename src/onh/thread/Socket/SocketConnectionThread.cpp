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

#include "SocketConnectionThread.h"
#include "Parser/CommandParser.h"
#include "Socket.h"
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <sstream>

using namespace onh;

void* socketConnection_thread(void* data) {

    // Initialize thread data
    SocketConnectionThreadData *thDT = (SocketConnectionThreadData *) data;

	Logger *log = 0;
	CommandParser *parser = 0;

	// Create logger
	std::stringstream s;
	s << "connection_th_" << thDT->connDescriptor << " ";
	log = new Logger("parser", s.str());

	try {

		// Create parser
		parser = new CommandParser(*thDT);

		// Buffer
		char buffer[MAX_BUFF_SIZE] = {0};

		// Read client data
		if (read(thDT->connDescriptor, buffer, MAX_BUFF_SIZE) == -1) {

			throw SocketException("Error while socket read data", errno, "Socket::waitOnData");
		}

		// Prepare reply
		std::string reply = parser->getReply(buffer);

		// Send reply
		if (send(thDT->connDescriptor, reply.c_str(), strlen(reply.c_str()), 0 ) == -1) {

			throw SocketException("Error while socket send data", errno, "Socket::sendReply");
		}

	} catch (Exception &e) {

    	log->write(e.what());
    }

	close(thDT->connDescriptor);

    if (parser)
    	delete parser;

    if (log)
    	delete log;

    delete thDT;

    pthread_exit(NULL);
}
