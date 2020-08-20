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

#include <stdio.h>
#include <stdlib.h>
#include <sstream>

#include "Application.h"

using namespace onh;

Application::Application(bool test):
    drv(nullptr), drvBuffer(nullptr), pr(nullptr), thManager(nullptr), dbManager(nullptr), cfg(nullptr), testEnv(test)
{
    // Create logger
    log = new Logger("mainProg","main_");
}

Application::~Application() {

    if (drv) {
        delete drv;
	}
	if (drvBuffer) {
        delete drvBuffer;
	}
	if (pr) {
        delete pr;
	}
	if (thManager) {
        delete thManager;
	}
	if (cfg) {
        delete cfg;
	}
	if (dbManager) {
        delete dbManager;
	}

	log->write("Bye");

    if (log) {
        delete log;
    }
}

int Application::start() {

    int ret = 0;

    try {

    	log->write("Application starting...");

        // Initialize database connection
        initDB();

        // Initialize application driver
        initDriver();

        // Initialize application driver buffer
        initDriverBuffer();

        // Initialize process manager
        initProcessManager();

        // Initialize thread manager
        initThreadManager();

        // Run all threads
        runThreads();

    } catch (std::exception &e) {

        log->write(e.what());

        ret = EXIT_FAILURE;
    } catch (...) {

        log->write("Unknown exception");

        ret = EXIT_FAILURE;

    }

    return ret;

}

void Application::runThreads() {

	log->write("Starting threads...");
    thManager->run();

    log->write("All threads are closed");
    log->write("Application closed by: "+thManager->getExitInfo());
}

void Application::initDB() {

    // Get DB connection data
    std::ifstream confFile("dbConn.conf");

    // Check if file is opened without errors
    if (confFile.fail()) {
    	throw Exception("DB configuration file is not opened", "Application::initDB");
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
    dbManager = new DBManager(dbConf[0], dbConf[1], dbConf[2], dbConf[3]);

    cfg = new Config(dbManager->getConfigDB());

    // Clear restart flag
    cfg->setValue("serverRestart", 0);
}

void Application::initDriver() {

    // Get driver name
    std::string driverName = cfg->getStringValue("connectionDriver");

    // Create driver
    if (driverName == "Modbus") {

    	modbusM::ModbusCfg modbusCfg;
    	std::string modbusMode = cfg->getStringValue("modbusMode");

    	if (modbusMode == "TCP") {

    		modbusCfg.mode = modbusM::MM_TCP;
			modbusCfg.registerCount = cfg->getIntValue("modbusRegCount");
			modbusCfg.slaveID = cfg->getIntValue("modbusSlaveID");

			modbusCfg.TCP_addr = cfg->getStringValue("modbusTCP_addr");
			modbusCfg.TCP_port = cfg->getIntValue("modbusTCP_port");

    	} else if (modbusMode == "RTU") {

    		modbusCfg.mode = modbusM::MM_RTU;
			modbusCfg.registerCount = cfg->getIntValue("modbusRegCount");
			modbusCfg.slaveID = cfg->getIntValue("modbusSlaveID");

			modbusCfg.RTU_port = cfg->getStringValue("modbusRTU_port");
			modbusCfg.RTU_baud = cfg->getIntValue("modbusRTU_baud");
			modbusCfg.RTU_parity = cfg->getStringValue("modbusRTU_parity")[0];
			modbusCfg.RTU_dataBit = cfg->getIntValue("modbusRTU_dataBit");
			modbusCfg.RTU_stopBit = cfg->getIntValue("modbusRTU_stopBit");

    	} else {
    		throw Exception("Unknown modbus mode selected", "Application::initDriver");
    	}

        // Driver
        drv = new ModbusDriver(modbusCfg);

    } else if (driverName == "SHM") {

    	// Shared memory segment name
    	std::string shmName = cfg->getStringValue("shmSegmentName");

    	// Driver
        drv = new ShmDriver(shmName);

    } else {
        throw Exception("Unknown driver selected", "Application::initDriver");
    }
}

void Application::initDriverBuffer() {

    if (!drv) {
        throw Exception("Can not create driver buffer - missing driver instance", "Application::initDriverBuffer");
    }

    // Driver buffer
    drvBuffer = drv->getBuffer();
}

void Application::initProcessManager() {

    // Initialize process manager
    pr = new ProcessManager(drv, drvBuffer);
}

void Application::initThreadManager() {

	// Check process manager
	if (!pr)
		throw Exception("Process manager not initialized", "Application::initThreadManager");

	if (!dbManager)
		throw Exception("Database manager not initialized", "Application::initThreadManager");

	if (!cfg)
		throw Exception("Configuration not initialized", "Application::initThreadManager");

    // Initialize thread manager
    thManager = new ThreadManager();

    // Init process updater thread
	thManager->initProcessUpdater(pr->getUpdater(), cfg->getUIntValue("processUpdateInterval"));

    // Init driver polling thread
	if (drvBuffer) {
		thManager->initDriverPolling(pr->getDriverBufferUpdater(), cfg->getUIntValue("modbusPollingInterval"));
	}

    // Init alarming thread
    thManager->initAlarmingThread(pr->getReader(),
									pr->getWriter(),
									dbManager->getAlarmingDB(),
									cfg->getUIntValue("alarmingUpdateInterval"));

    // Init tag logger thread
    thManager->initTagLoggerThread(pr->getReader(),
									dbManager->getTagLoggerDB(),
									cfg->getUIntValue("tagLoggerUpdateInterval"));

    // Init tag logger writer thread
    thManager->initTagLoggerWriterThread(dbManager->getTagLoggerWriterDB(),
											cfg->getUIntValue("tagLoggerUpdateInterval"));

    // Init script thread
    thManager->initScriptThread(pr->getReader(),
								pr->getWriter(),
								dbManager->getScriptDB(),
								cfg->getUIntValue("scriptSystemUpdateInterval"),
								cfg->getStringValue("scriptSystemExecuteScript"),
								testEnv);

    // Init socket thread
    thManager->initSocketThread(pr->getReader(),
								pr->getWriter(),
								dbManager->getCredentials(),
								cfg->getIntValue("socketPort"),
								cfg->getIntValue("socketMaxConn"));
}
