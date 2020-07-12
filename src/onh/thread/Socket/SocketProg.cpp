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

#include "SocketProg.h"
#include "ConnectionProg.h"
#include <stdlib.h>
#include <sstream>

using namespace onh;

SocketProgram::SocketProgram(const ProcessReader& pr,
								const ProcessWriter& pw,
								const DBCredentials& dbc,
								int port,
								int maxConn,
								const ThreadCycleControllers& cc,
								const ThreadExitController &thEC):
	ThreadSocket(thEC, "socket", "serv_"), dbCredentials(dbc), cycleController(cc), sPort(port), sMaxConn(maxConn), thCounter(0)
{
	// Process reader
	pReader = new ProcessReader(pr);

	// Process writer
	pWriter = new ProcessWriter(pw);

	// Thread exit controller
	thExit = new ThreadExitController(thEC);

    // Socket
    sock = new Socket(port, maxConn);
}

SocketProgram::~SocketProgram()
{
	if (pReader)
		delete pReader;

	if (pWriter)
		delete pWriter;

	if (thExit)
		delete thExit;

    if (sock) {
    	getLogger().write("Close socket");
        delete sock;
    }
}

void SocketProgram::operator()() {

    try {
        // Initialize socket
        sock->init();

        // Attach socket file descriptor to exit controller (for shutdown from application)
        setSocketFD(sock->getSocketDescriptor());

        int conn = 0;

        while (!isExitFlag()) {

        	// Wait on connection
        	conn = sock->waitOnConnection();

        	// Create thread
        	createConnectionThread(conn);
        }

    } catch (SocketException &e) {

    	// Log error when socket exception (not caused by shutdown command)
    	if (!isExitFlag()) {

    		getLogger().write(e.what());

			// Exit application
			exit("Socket Thread");
    	}
    } catch (Exception &e) {

    	getLogger().write(e.what());

        // Exit application
    	exit("Socket Thread");
    }

    // Wait on clients
    waitOnThreads();

    // Remove file descriptor from exit controller (socket will be closed by socket program)
	setSocketFD(0);
}

void SocketProgram::createConnectionThread(int connFD) {

	// Start thread
	std::thread* newThread = new std::thread((ConnectionProgram(connFD,
																*pReader,
																*pWriter,
																cycleController,
																dbCredentials,
																*thExit)));

	// Check connection vector
	if (tConn.size() >= (THREADS_POOL-1)) {

		// Check old threads
		for (unsigned int i=0; i<tConn.size(); ++i) {

			tConn[i]->join();
			delete tConn[i];
		}

		// Clear connection vector
		tConn.clear();
	}

	// Add connection thread to the vector
	tConn.push_back(newThread);
}

void SocketProgram::waitOnThreads() {

	// Check threads finished
	for (unsigned int i=0; i<tConn.size(); ++i) {

		tConn[i]->join();
		delete tConn[i];
	}

	tConn.clear();
}
