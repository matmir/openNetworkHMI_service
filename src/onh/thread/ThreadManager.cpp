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

#include "ThreadManager.h"
#include <sys/socket.h>

using namespace onh;

ThreadManager::ThreadManager()
{
}

ThreadManager::~ThreadManager()
{
}

ThreadController ThreadManager::getController(ThreadControllerType tct) {

    // Create controller object
    if (tct == TCT_PROCESS_UPDATER) {
        return ThreadController(tmExit.getExitController(), cycleProcessUpdater.getController());
    } else if (tct == TCT_ALARMING) {
        return ThreadController(tmExit.getExitController(), cycleAlarming.getController());
    } else if (tct == TCT_TAG_LOGGER) {
        return ThreadController(tmExit.getExitController(), cycleLogger.getController());
    } else if (tct == TCT_TAG_LOGGER_WRITER) {
        return ThreadController(tmExit.getExitController(), cycleLoggerWriter.getController());
    } else if (tct == TCT_SCRIPT) {
        return ThreadController(tmExit.getExitController(), cycleScript.getController());
    } else if (tct == TCT_DRIVER_POLLING) {
        return ThreadController(tmExit.getExitController(), cycleDriverPolling.getController());
    } else {
        return ThreadController(tmExit.getExitController());
    }
}

ThreadCycleContainerController ThreadManager::getCycleTimeReader(ThreadControllerType tct) {

    // Create cycle time reader object
    if (tct == TCT_PROCESS_UPDATER) {
        return ThreadCycleContainerController(cycleProcessUpdater.getController(true));
    } else if (tct == TCT_ALARMING) {
        return ThreadCycleContainerController(cycleAlarming.getController(true));
    } else if (tct == TCT_TAG_LOGGER) {
        return ThreadCycleContainerController(cycleLogger.getController(true));
    } else if (tct == TCT_TAG_LOGGER_WRITER) {
        return ThreadCycleContainerController(cycleLoggerWriter.getController(true));
    } else if (tct == TCT_SCRIPT) {
        return ThreadCycleContainerController(cycleScript.getController(true));
    } else if (tct == TCT_DRIVER_POLLING) {
        return ThreadCycleContainerController(cycleDriverPolling.getController(true));
    } else {
        throw Exception("Can not create cycle time reader for default thread controller", "ThreadManager::getCycleTimeReader");
    }
}

void ThreadManager::exitMain() {

    tmExit.exit();
}

std::string ThreadManager::getExitInfo() {

	return tmExit.getExitInfo();
}

void ThreadManager::shutdownSocket() {

	int sockFD = tmExit.getSocketFD();

	// Shutdown socket
	if (sockFD != 0 && sockFD != -1) {

		if (shutdown(sockFD, SHUT_RD)) {
			throw Exception("Can not shutdown socket", "ThreadManager::shutdownSocket");
		}
	}
}
