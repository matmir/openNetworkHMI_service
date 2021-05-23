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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include "Socket.h"

namespace onh {

Socket::Socket(int port, int maxConn):
	itsPort(port), itsMaxConn(maxConn) {
	addrlen = sizeof(address);
	newConn = 0;
	socketFD = 0;

	socketReady = false;
}

Socket::~Socket() {
	if (newConn) {
		// Close socket
		close(newConn);
	}

	if (socketFD) {
		// Close socket
		close(socketFD);
	}
}

void Socket::clearBuffer() {
	for (int i=0; i < MAX_BUFF_SIZE; ++i) {
		buffer[i] = 0;
	}
}

void Socket::init() {
	// Creating socket file descriptor
	if ((socketFD = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		throw SocketException("Can not create socket file descriptor", errno, "Socket::init");
	}

	int opt = 1;
	if (setsockopt(socketFD, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		throw SocketException("Error while set socket options", errno, "Socket::init");
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(itsPort);

	// Attach socket to the port
	if (bind(socketFD, (struct sockaddr *)&address, sizeof(address)) < 0) {
		std::stringstream s;
		s << "Error while attaching socket to the port " << itsPort;

		throw SocketException(s.str(), errno, "Socket::init");
	}

	if (listen(socketFD, itsMaxConn) < 0) {
		throw SocketException("Error while socket listen", errno, "Socket::waitOnData");
	}

	socketReady = true;
}

void Socket::waitOnData() {
	// Check socket
	if (!socketReady)
		throw SocketException("Socket not ready", "Socket::waitOnData");

	// Clear socket buffer
	clearBuffer();

	if ((newConn = accept(socketFD, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
		throw SocketException("Error while socket accept", errno, "Socket::waitOnData");
	}

	// Read command
	if (read(newConn, buffer, MAX_BUFF_SIZE) == -1) {
		throw SocketException("Error while socket read data", errno, "Socket::waitOnData");
	}
}

int Socket::waitOnConnection() {
	int connFD = 0;

	// Check socket
	if (!socketReady)
		throw SocketException("Socket not ready", "Socket::waitOnData");

	// Clear socket buffer
	clearBuffer();

	if ((connFD = accept(socketFD, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
		throw SocketException("Error while socket accept", errno, "Socket::waitOnData");
	}

	return connFD;
}

std::string Socket::getData() const {
	// Check socket
	if (!socketReady)
		throw SocketException("Socket not ready", "Socket::getData");

	return buffer;
}

void Socket::sendReply(const std::string &reply) {
	// Check socket
	if (!socketReady)
		throw SocketException("Socket not ready", "Socket::sendReply");

	// Send reply
	if (send(newConn, reply.c_str(), strlen(reply.c_str()), 0) == -1) {
		throw SocketException("Error while socket send data", errno, "Socket::sendReply");
	}

	close(newConn);
	newConn = 0;
}

int Socket::getSocketDescriptor() {
	if (socketFD == 0 || socketFD == -1) {
		throw SocketException("Socket not created", "Socket::getSocketDescriptor");
	}

	return socketFD;
}

}  // namespace onh
