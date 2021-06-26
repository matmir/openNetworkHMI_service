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

#include <sys/socket.h>
#include "ThreadManager.h"
#include "Alarming/AlarmingProg.h"
#include "DriverPolling/DriverPollingProg.h"
#include "ProcessUpdater/ProcessUpdaterProg.h"
#include "Script/ScriptProg.h"
#include "Socket/SocketProg.h"
#include "TagLogger/TagLoggerProg.h"
#include "TagLogger/TagLoggerWriterProg.h"
#include "ThreadCycleControllers.h"

namespace onh {

ThreadManager::ThreadManager():
	thSocket(nullptr), threadSocket(nullptr), updatersInited(false), driverBuffersInited(false) {
	thProgramData.clear();
	threadProgs.clear();
}

ThreadManager::~ThreadManager() {
}

void ThreadManager::initProcessUpdater(const std::vector<ProcessUpdaterData>& pu, unsigned int updateInterval) {
	if (updatersInited)
		throw Exception("Process updater threads already initialized", "ThreadManager::initProcessUpdater");

	std::string nm = "";

	// Prepare all updaters thread program data
	for (unsigned int i=0; i < pu.size(); ++i) {
		// Prepare updater name
		nm = "Updater_"+std::to_string(pu[i].connId);

		auto inserted = thProgramData.insert(std::pair<std::string, threadProgramData>(nm, threadProgramData())).first;
		inserted->second.thProgram = std::make_unique<ProcessUpdaterProg>(pu[i].procUpdater,
															pu[i].connId,
															updateInterval,
															tmExit.getController(false),
															inserted->second.cycleContainer.getController(false));
	}

	updatersInited = true;
}

void ThreadManager::initDriverPolling(const std::vector<DriverBufferUpdaterData>& dbu) {
	if (driverBuffersInited)
		throw Exception("Driver polling thread already initialized", "ThreadManager::initDriverPolling");

	std::string nm = "";

	// Prepare all buffers thread program data
	for (unsigned int i=0; i < dbu.size(); ++i) {
		// Prepare buffer name
		nm = "DriverBuffer_"+std::to_string(dbu[i].connId);

		auto inserted = thProgramData.insert(std::pair<std::string, threadProgramData>(nm, threadProgramData())).first;
		inserted->second.thProgram = std::make_unique<DriverPollingProg>(dbu[i].buffUpdater,
														dbu[i].connId,
														dbu[i].updateInterval,
														tmExit.getController(false),
														inserted->second.cycleContainer.getController(false));
	}

	driverBuffersInited = true;
}

void ThreadManager::initAlarmingThread(const ProcessReader& pr,
										const ProcessWriter& pw,
										const AlarmingDB& adb,
										unsigned int updateInterval) {
	std::string nm = "Alarming";

	if (thProgramData.count(nm) != 0)
		throw Exception("Alarming thread already initialized", "ThreadManager::initAlarmingThread");

	auto inserted = thProgramData.insert(std::pair<std::string, threadProgramData>(nm, threadProgramData())).first;
	inserted->second.thProgram = std::make_unique<AlarmingProg>(pr,
											pw,
											adb,
											updateInterval,
											tmExit.getController(false),
											inserted->second.cycleContainer.getController(false));
}

void ThreadManager::initTagLoggerThread(const ProcessReader& pr,
										const TagLoggerDB& tldb,
										unsigned int updateInterval) {
	std::string nm = "TagLogger";

	if (thProgramData.count(nm) != 0)
		throw Exception("Tag logger thread already initialized", "ThreadManager::initTagLoggerThread");

	auto inserted = thProgramData.insert(std::pair<std::string, threadProgramData>(nm, threadProgramData())).first;
	inserted->second.thProgram = std::make_unique<TagLoggerProg>(pr,
											tldb,
											tagLoggerBuffer.getController(),
											updateInterval,
											tmExit.getController(false),
											inserted->second.cycleContainer.getController(false));
}

void ThreadManager::initTagLoggerWriterThread(const TagLoggerDB& tldb,
												unsigned int updateInterval) {
	std::string nm = "TagLoggerWriter";

	if (thProgramData.count(nm) != 0)
		throw Exception("Tag logger writer thread already initialized", "ThreadManager::initTagLoggerWriterThread");

	auto inserted = thProgramData.insert(std::pair<std::string, threadProgramData>(nm, threadProgramData())).first;
	inserted->second.thProgram = std::make_unique<TagLoggerWriterProg>(tldb,
																tagLoggerBuffer.getController(true),
																updateInterval,
																tmExit.getController(false),
																inserted->second.cycleContainer.getController(false));
}

void ThreadManager::initScriptThread(const ProcessReader& pr,
										const ProcessWriter& pw,
										const ScriptDB& sdb,
										unsigned int updateInterval,
										const std::string& executeScript,
										bool testEnv) {
	std::string nm = "Script";

	if (thProgramData.count(nm) != 0)
		throw Exception("Script thread already initialized", "ThreadManager::initScriptThread");

	auto inserted = thProgramData.insert(std::pair<std::string, threadProgramData>(nm, threadProgramData())).first;
	inserted->second.thProgram = std::make_unique<ScriptProg>(pr,
													pw,
													sdb,
													updateInterval,
													executeScript,
													testEnv,
													tmExit.getController(false),
													inserted->second.cycleContainer.getController(false));
}

void ThreadManager::initSocketThread(const ProcessReader& pr,
										const ProcessWriter& pw,
										const DBCredentials& dbc,
										int port,
										int maxConn) {
	if (thSocket)
		throw Exception("Socket thread already initialized", "ThreadManager::initSocketThread");

	ThreadCycleControllers cc;

	for (auto& thProg : thProgramData) {
		cc.insert(CycleControllerPair(thProg.first, thProg.second.cycleContainer.getController()));
	}

	thSocket = std::make_unique<SocketProgram>(pr,
									pw,
									dbc,
									port,
									maxConn,
									cc,
									tmExit.getController(false),
									tmSockDesc.getController(false));
}

void ThreadManager::run() {
	// Check thread initialization
	if (!updatersInited)
		throw Exception("Process updater thread not initialized", "ThreadManager::run");

	if (thProgramData.count("Alarming") == 0)
		throw Exception("Alarming thread not initialized", "ThreadManager::run");

	if (thProgramData.count("TagLogger") == 0)
		throw Exception("TagLogger thread not initialized", "ThreadManager::run");

	if (thProgramData.count("TagLoggerWriter") == 0)
		throw Exception("Logger writer thread not initialized", "ThreadManager::run");

	if (thProgramData.count("Script") == 0)
		throw Exception("Script thread not initialized", "ThreadManager::run");

	if (!thSocket)
		throw Exception("Socket thread not initialized", "ThreadManager::run");

	if (!threadProgs.empty())
		throw Exception("Thread vector is not empty", "ThreadManager::run");

	// Start threads
	for (auto& thData : thProgramData) {
		threadProgs.push_back(std::thread(std::ref(*thData.second.thProgram)));
	}

	// Run socket thread
	threadSocket = std::make_unique<std::thread>(std::ref(*thSocket));

	// Join threads
	for (auto& thProg : threadProgs) {
		thProg.join();
	}

	// Close socket
	shutdownSocket();
	threadSocket->join();
}

void ThreadManager::exitMain() {
	ThreadExitData ex;
	ex.exit = true;
	ex.additionalInfo = "Exit from main";

	// Trigger application exit
	tmExit.getController(false).setData(ex);
}

std::string ThreadManager::getExitInfo() {
	ThreadExitData ex;
	tmExit.getController().getData(ex);

	return ex.additionalInfo;
}

void ThreadManager::shutdownSocket() {
	int sockFD = 0;
	tmSockDesc.getController().getData(sockFD);

	// Shutdown socket
	if (sockFD != 0 && sockFD != -1) {
		if (shutdown(sockFD, SHUT_RD)) {
			throw Exception("Can not shutdown socket", "ThreadManager::shutdownSocket");
		}
	}
}

}  // namespace onh
