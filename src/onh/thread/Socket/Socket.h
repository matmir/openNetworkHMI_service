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

#ifndef ONH_THREAD_SOCKET_SOCKET_H_
#define ONH_THREAD_SOCKET_SOCKET_H_

/// Maximal buffer size (bytes)
#define MAX_BUFF_SIZE 10000

#include <netinet/in.h>
#include "Parser/CommandParser.h"
#include "SocketException.h"

namespace onh {

/**
 * Simple socket class
 */
class Socket {
	public:
		/**
		 * Socket constructor
		 *
		 * @param port Socket port
		 * @param maxConn Maximum number of connections
		 */
		Socket(int port, int maxConn);

		/**
		 * Copy constructor - inactive
		 */
		Socket(const Socket&) = delete;

		~Socket();

		/**
		 * Assign operator - inactive
		 */
		Socket& operator=(const Socket&) = delete;

		/**
		 * Initialize socket
		 */
		void init();

		/**
		 * Wait on new data
		 */
		void waitOnData();

		/**
		 * Wait on incoming connection
		 *
		 * @return Connection file descriptor
		 */
		int waitOnConnection();

		/**
		 * Get received data
		 *
		 * @return Received data
		 */
		std::string getData() const;

		/**
		 * Send reply
		 *
		 * @param reply Reply data
		 */
		void sendReply(const std::string &reply);

		/**
		 * Get socket descriptor
		 *
		 * @return Socket descriptor
		 */
		int getSocketDescriptor();

	private:
		/**
		 * Clear socket buffer
		 */
		void clearBuffer();

		/// Socket port
		int itsPort;

		/// Max. connection number
		int itsMaxConn;

		/// Socket variables
		int socketFD, newConn;
		struct sockaddr_in address;
		int addrlen;

		/// Buffer
		char buffer[MAX_BUFF_SIZE];

		/// Flag informs that socket is ready
		bool socketReady;
};

}  // namespace onh

#endif  // ONH_THREAD_SOCKET_SOCKET_H_
