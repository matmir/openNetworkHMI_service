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
#include "Alarming/AlarmingProg.h"
#include "DriverPolling/DriverPollingProg.h"
#include "ProcessUpdater/ProcessUpdaterProg.h"
#include "Script/ScriptProg.h"
#include "Socket/SocketProg.h"
#include "TagLogger/TagLoggerProg.h"
#include "TagLogger/TagLoggerWriterProg.h"
#include "ThreadCycleControllers.h"
#include <sys/socket.h>

using namespace onh;

ThreadManager::ThreadManager():
	threadSocket(nullptr)
{
	thProcessUpdater.thProgram = nullptr;
	thDriverPolling.thProgram = nullptr;
	thAlarming.thProgram = nullptr;
	thLogger.thProgram = nullptr;
	thLoggerWriter.thProgram = nullptr;
	thScript.thProgram = nullptr;
	thSocket = nullptr;
}

ThreadManager::~ThreadManager()
{
	if (thProcessUpdater.thProgram)
		delete thProcessUpdater.thProgram;

	if (thDriverPolling.thProgram)
		delete thDriverPolling.thProgram;

	if (thAlarming.thProgram)
		delete thAlarming.thProgram;

	if (thLogger.thProgram)
		delete thLogger.thProgram;

	if (thLoggerWriter.thProgram)
		delete thLoggerWriter.thProgram;

	if (thScript.thProgram)
		delete thScript.thProgram;

	if (thSocket)
		delete thSocket;

	if (threadSocket)
		delete threadSocket;

	for (auto thProg : threadProgs) {
		delete thProg;
	}
}

void ThreadManager::initProcessUpdater(const ProcessUpdater& pu, unsigned int updateInterval) {

	if (thProcessUpdater.thProgram)
		throw Exception("Process updater thread already initialized", "ThreadManager::initProcessUpdater");

	thProcessUpdater.thProgram = new ProcessUpdaterProg(pu,
														updateInterval,
														tmExit.getExitController(),
														thProcessUpdater.cycleContainer.getController());
}

void ThreadManager::initDriverPolling(const DriverBufferUpdater& dbu, unsigned int updateInterval) {

	if (thDriverPolling.thProgram)
		throw Exception("Driver polling thread already initialized", "ThreadManager::initDriverPolling");

	thDriverPolling.thProgram = new DriverPollingProg(dbu,
														updateInterval,
														tmExit.getExitController(),
														thDriverPolling.cycleContainer.getController());
}

void ThreadManager::initAlarmingThread(const ProcessReader& pr,
										const ProcessWriter& pw,
										const AlarmingDB& adb,
										unsigned int updateInterval)
{
	if (thAlarming.thProgram)
		throw Exception("Alarming thread already initialized", "ThreadManager::initAlarmingThread");

	thAlarming.thProgram = new AlarmingProg(pr,
											pw,
											adb,
											updateInterval,
											tmExit.getExitController(),
											thAlarming.cycleContainer.getController());
}

void ThreadManager::initTagLoggerThread(const ProcessReader& pr,
										const TagLoggerDB& tldb,
										const TagLoggerBufferController& tlbc,
										unsigned int updateInterval)
{
	if (thLogger.thProgram)
		throw Exception("Tag logger thread already initialized", "ThreadManager::initTagLoggerThread");

	thLogger.thProgram = new TagLoggerProg(pr,
											tldb,
											tlbc,
											updateInterval,
											tmExit.getExitController(),
											thLogger.cycleContainer.getController());
}

void ThreadManager::initTagLoggerWriterThread(const TagLoggerDB& tldb,
												const TagLoggerBufferController& tlbc,
												unsigned int updateInterval)
{
	if (thLoggerWriter.thProgram)
		throw Exception("Tag logger writer thread already initialized", "ThreadManager::initTagLoggerWriterThread");

	thLoggerWriter.thProgram = new TagLoggerWriterProg(tldb,
														tlbc,
														updateInterval,
														tmExit.getExitController(),
														thLoggerWriter.cycleContainer.getController());
}

void ThreadManager::initScriptThread(const ProcessReader& pr,
										const ProcessWriter& pw,
										const ScriptDB& sdb,
										unsigned int updateInterval,
										const std::string& executeScript,
										bool testEnv)
{
	if (thScript.thProgram)
		throw Exception("Script thread already initialized", "ThreadManager::initScriptThread");

	thScript.thProgram = new ScriptProg(pr,
										pw,
										sdb,
										updateInterval,
										executeScript,
										testEnv,
										tmExit.getExitController(),
										thScript.cycleContainer.getController());
}

void ThreadManager::initSocketThread(const ProcessReader& pr,
										const ProcessWriter& pw,
										const DBCredentials& dbc,
										int port,
										int maxConn)
{
	if (thSocket)
		throw Exception("Socket thread already initialized", "ThreadManager::initSocketThread");

	ThreadCycleControllers cc = {
		thProcessUpdater.cycleContainer.getController(true),
		thAlarming.cycleContainer.getController(true),
		thLogger.cycleContainer.getController(true),
		thLoggerWriter.cycleContainer.getController(true),
		thScript.cycleContainer.getController(true),
		thDriverPolling.cycleContainer.getController(true),
	};

	thSocket = new SocketProgram(pr,
									pw,
									dbc,
									port,
									maxConn,
									cc,
									tmExit.getExitController());
}

void ThreadManager::run() {

	// Check thread initialization
	if (!thProcessUpdater.thProgram)
		throw Exception("Process updater thread not initialized", "ThreadManager::run");

	if (!thAlarming.thProgram)
		throw Exception("Alarming thread not initialized", "ThreadManager::run");

	if (!thLogger.thProgram)
		throw Exception("Logger thread not initialized", "ThreadManager::run");

	if (!thLoggerWriter.thProgram)
		throw Exception("Logger writer thread not initialized", "ThreadManager::run");

	if (!thScript.thProgram)
		throw Exception("Script thread not initialized", "ThreadManager::run");

	if (!thSocket)
		throw Exception("Socket thread not initialized", "ThreadManager::run");

	if (!threadProgs.empty())
		throw Exception("Thread vector is not empty", "ThreadManager::run");

	// Check driver polling
	if (thDriverPolling.thProgram) {
		threadProgs.push_back(new std::thread(std::ref(*thDriverPolling.thProgram)));
	}
	// Run rest of the threads
	threadProgs.push_back(new std::thread(std::ref(*thProcessUpdater.thProgram)));
	threadProgs.push_back(new std::thread(std::ref(*thAlarming.thProgram)));
	threadProgs.push_back(new std::thread(std::ref(*thLogger.thProgram)));
	threadProgs.push_back(new std::thread(std::ref(*thLoggerWriter.thProgram)));
	threadProgs.push_back(new std::thread(std::ref(*thScript.thProgram)));

	// Run socket thread
	threadSocket = new std::thread(std::ref(*thSocket));

	// Join threads
	for (auto thProg : threadProgs) {
		thProg->join();
	}

	// Close socket
	shutdownSocket();
	threadSocket->join();
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
