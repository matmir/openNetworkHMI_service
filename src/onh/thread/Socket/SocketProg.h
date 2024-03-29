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

#ifndef ONH_THREAD_SOCKET_SOCKETPROG_H_
#define ONH_THREAD_SOCKET_SOCKETPROG_H_

#define THREADS_POOL 20

#include <thread>
#include <vector>
#include "Socket.h"
#include "../ThreadSocket.h"
#include "../ThreadCycleControllers.h"
#include "../../driver/ProcessReader.h"
#include "../../driver/ProcessWriter.h"
#include "../../db/DBCredentials.h"

namespace onh {

/**
 * Socket program class
 */
class SocketProgram: public ThreadSocket {
	public:
		/**
		 * Constructor
		 *
		 * @param pr Process reader
		 * @param pw Process writer
		 * @param dbc DB data
		 * @param port Socket port
		 * @param maxConn Socket max connection number
		 * @param cc Thread cycle controllers
		 * @param gdcTED Thread exit data controller
		 * @param gdcSockDesc Socket file descriptor controller
		 */
		SocketProgram(const ProcessReader& pr,
						const ProcessWriter& pw,
						const DBCredentials& dbc,
						int port,
						int maxConn,
						const ThreadCycleControllers& cc,
						const GuardDataController<ThreadExitData> &gdcTED,
						const GuardDataController<int> &gdcSockDesc);

		/**
		 * Copy constructor - inactive
		 */
		SocketProgram(const SocketProgram&) = delete;

		~SocketProgram() override;

		/**
		 * Thread program function
		 */
		void operator()() override;

		/**
		 * Assignment operator - inactive
		 */
		SocketProgram& operator=(const SocketProgram&) = delete;

	private:
		/// Socket thread data
		std::unique_ptr<ProcessReader> pReader;
		std::unique_ptr<ProcessWriter> pWriter;
		DBCredentials dbCredentials;
		ThreadCycleControllers cycleController;
		int sPort;
		int sMaxConn;

		/// Socket object
		std::unique_ptr<Socket> sock;

		/// Connection threads pool
		std::vector<std::thread*> tConn;

		/**
		 * Create connection thread
		 *
		 * @param connFD Connection file descriptor
		 */
		void createConnectionThread(int connFD);

		/**
		 * Wait on threads
		 */
		void waitOnThreads();
};

}  // namespace onh

#endif  // ONH_THREAD_SOCKET_SOCKETPROG_H_
