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
#include <sstream>

#include "appConfig.h"
#include "Application.h"

namespace onh {

Application::Application(bool test):
	log(std::make_unique<TextLogger>("mainProg", "main_")),
	drvManager(nullptr),
	thManager(nullptr),
	dbManager(nullptr),
	cfg(nullptr),
	testEnv(test) {
}

Application::~Application() {
	log->write(LOG_INFO("Bye"));
}

int Application::start() {
	int ret = 0;

	try {
		log->write(LOG_INFO("Application " << PROJECT_NAME << " (v" << PROJECT_VERSION << ")" << " is starting..."));

		// Initialize database connection
		initDB();

		// Initialize drivers
		initDriver();

		// Initialize thread manager
		initThreadManager();

		// Run all threads
		runThreads();
	} catch (std::exception &e) {
		log->write(LOG_ERROR(e.what()));

		ret = EXIT_FAILURE;
	} catch (...) {
		log->write(LOG_ERROR("Unknown exception"));

		ret = EXIT_FAILURE;
	}

	return ret;
}

void Application::runThreads() {
	log->write(LOG_INFO("Starting threads..."));
	thManager->run();

	log->write(LOG_INFO("All threads are closed"));
	log->write(LOG_INFO("Application closed by: " << thManager->getExitInfo()));
}

void Application::initDB() {
	// Get DB connection data
	std::ifstream confFile("dbConn.conf");

	// Check if file is opened without errors
	if (confFile.fail()) {
		throw Exception("DB configuration file is not opened",
						"Application::initDB");
	}

	std::string confLine;
	std::vector<std::string> dbConf;
	while (std::getline(confFile, confLine)) {
		dbConf.push_back(confLine);
	}

	// Check data
	if (dbConf.size() != 4) {
		throw Exception("Invalid DB configuration file", "Application::initDB");
	}

	// DB access prepare
	dbManager = std::make_unique<DBManager>(dbConf[0], dbConf[1], dbConf[2], dbConf[3]);

	cfg = std::make_unique<Config>(dbManager->getConfigDB());

	// Clear restart flag
	cfg->setValue("serverRestart", 0);
}

void Application::initDriver() {
	if (!dbManager)
		throw Exception("Database manager not initialized",
						"Application::initDriver");

	if (!cfg)
		throw Exception("Configuration not initialized",
						"Application::initDriver");

	// Init driver manager
	drvManager = std::make_unique<DriverManager>(cfg->getDriverConnections());
}

void Application::initThreadManager() {
	// Check managers
	if (!drvManager)
		throw Exception("Driver manager not initialized",
						"Application::initThreadManager");

	if (!dbManager)
		throw Exception("Database manager not initialized",
						"Application::initThreadManager");

	if (!cfg)
		throw Exception("Configuration not initialized",
						"Application::initThreadManager");

	// Initialize thread manager
	thManager = std::make_unique<ThreadManager>();

	// Init process updater threads
	thManager->initProcessUpdater(drvManager->getProcessUpdaters(),
									cfg->getUIntValue("processUpdateInterval"));

	// Init driver polling thread
	thManager->initDriverPolling(drvManager->getDriverBufferUpdaters());

	// Init alarming thread
	thManager->initAlarmingThread(drvManager->getProcessReader(),
									drvManager->getProcessWriter(),
									dbManager->getAlarmingDB(),
									cfg->getUIntValue("alarmingUpdateInterval"));

	// Init tag logger thread
	thManager->initTagLoggerThread(drvManager->getProcessReader(),
									dbManager->getTagLoggerDB(),
									cfg->getUIntValue("tagLoggerUpdateInterval"));

	// Init tag logger writer thread
	thManager->initTagLoggerWriterThread(dbManager->getTagLoggerWriterDB(),
											cfg->getUIntValue("tagLoggerUpdateInterval"));

	// Init script thread
	thManager->initScriptThread(drvManager->getProcessReader(),
								drvManager->getProcessWriter(),
								dbManager->getScriptDB(),
								cfg->getUIntValue("scriptSystemUpdateInterval"),
								cfg->getStringValue("scriptSystemExecuteScript"),
								testEnv);

	// Init socket thread
	thManager->initSocketThread(drvManager->getProcessReader(),
								drvManager->getProcessWriter(),
								dbManager->getCredentials(),
								cfg->getIntValue("socketPort"),
								cfg->getIntValue("socketMaxConn"));
}

}  // namespace onh
