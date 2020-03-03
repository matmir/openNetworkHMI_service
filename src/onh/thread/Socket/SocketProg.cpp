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
#include "SocketConnectionThread.h"
#include <stdlib.h>
#include <sstream>

using namespace onh;

SocketProgram::SocketProgram(const SocketThreadData &thData):
    ThreadProgram(thData.thController, "socket", "serv_"), socketThData(thData), thCounter(0)
{
    // Socket
    sock = new Socket(thData.port, thData.maxConn);
}

SocketProgram::~SocketProgram()
{
    if (sock) {
    	getLogger().write("Close socket");
        delete sock;
    }
}

void SocketProgram::run() {

    try {
        // Initialize socket
        sock->init();

        // Attach socket file descriptor to exit controller (for shutdown from application)
        getThreadController().getExitController().setSocketFD(sock->getSocketDescriptor());

        int conn = 0;

        while (!getThreadController().getExitController().exitThread()) {

        	// Wait on connection
        	conn = sock->waitOnConnection();

        	// Create thread
        	createConnectionThread(conn);
        }

    } catch (SocketException &e) {

    	// Log error when socket exception (not caused by shutdown command)
    	if (!getThreadController().getExitController().exitThread()) {

    		getLogger().write(e.what());

			// Exit application
			getThreadController().getExitController().exit("Socket Thread");
    	}
    } catch (Exception &e) {

    	getLogger().write(e.what());

        // Exit application
    	getThreadController().getExitController().exit("Socket Thread");
    }

    // Wait on clients
    waitOnThreads();

    // Remove file descriptor from exit controller (socket will be closed by socket program)
	getThreadController().getExitController().setSocketFD(0);
}

void SocketProgram::createConnectionThread(int connFD) {

	// Prepare data for new thread
	SocketConnectionThreadData *thData = new SocketConnectionThreadData{
		connFD,
		socketThData
	};

	// Start thread
	if (pthread_create(&tConn[thCounter++], NULL, &socketConnection_thread, (void*)thData)) {
		throw Exception("Socket connection thread creation failed");
	}

	// Check counter
	if (thCounter == (THREADS_POOL-1)) {

		// Check old threads
		for (int i=0; i<THREADS_POOL-1; ++i) {

			pthread_join(tConn[i], NULL);
		}

		// Move last thread on the first place
		pthread_t last = tConn[THREADS_POOL-1];
		tConn[0] = last;

		// Change counter value
		thCounter = 1;
	}
}

void SocketProgram::waitOnThreads() {

	// Check threads finished
	for (int i=0; i<thCounter; ++i) {

		pthread_join(tConn[i], NULL);
	}
}
