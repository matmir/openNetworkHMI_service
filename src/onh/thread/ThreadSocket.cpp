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

#include "ThreadSocket.h"
#include "../utils/Exception.h"

namespace onh {

ThreadSocket::ThreadSocket(const GuardDataController<ThreadExitData> &gdcTED,
							const GuardDataController<int> &gdcSockDesc,
							const std::string& dirName,
							const std::string& fPrefix):
	thExitController(gdcTED),
	thSockDecsController(gdcSockDesc),
	log(std::make_unique<Logger>(dirName, fPrefix)) {
	// Log info
	log->write("Initialize thread logger");
}

ThreadSocket::~ThreadSocket() {
	log->write("Closing thread logger");
}

const GuardDataController<ThreadExitData>& ThreadSocket::getExitController() {
	return thExitController;
}

bool ThreadSocket::isExitFlag() {
	ThreadExitData ex;
	thExitController.getData(ex);

	return ex.exit;
}

void ThreadSocket::exit(const std::string& info) {
	ThreadExitData ex;
	ex.exit = true;
	ex.additionalInfo = info;

	// Trigger application exit
	thExitController.setData(ex);
}

void ThreadSocket::setSocketFD(int sockFD) {
	thSockDecsController.setData(sockFD);
}

Logger& ThreadSocket::getLogger() {
	return *log;
}

}  // namespace onh
