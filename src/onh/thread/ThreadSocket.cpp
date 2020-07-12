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

#include "ThreadSocket.h"
#include "../utils/Exception.h"

using namespace onh;

ThreadSocket::ThreadSocket(const ThreadExitController &thEC,
		const std::string& dirName,
		const std::string& fPrefix)
{
    // Thread exit controller
	thExitControll = new ThreadExitController(thEC);

    // Create logger
    log = new Logger(dirName, fPrefix);
    log->write("Initialize thread logger");
}

ThreadSocket::~ThreadSocket()
{
    if (thExitControll)
        delete thExitControll;

    if (log) {
        log->write("Closing thread logger");

        delete log;
    }
}

bool ThreadSocket::isExitFlag() const {

	if (!thExitControll)
		throw Exception("Thread exit controller object does not exist", "ThreadSocket::isExitFlag");

	return thExitControll->exitThread();
}

void ThreadSocket::exit(const std::string& info) {

	if (!thExitControll)
		throw Exception("Thread exit controller object does not exist", "ThreadSocket::exit");

	// Trigger application exit
	thExitControll->exit(info);
}

void ThreadSocket::setSocketFD(int sockFD) {

	if (!thExitControll)
		throw Exception("Thread exit controller object does not exist", "ThreadSocket::setSocketFD");

	thExitControll->setSocketFD(sockFD);
}

Logger& ThreadSocket::getLogger() {

	if (!log)
		throw Exception("Logger object does not exist", "ThreadSocket::getLogger");

	return *log;
}
