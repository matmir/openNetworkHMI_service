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
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <pthread.h>
#include <sstream>

#include "Application.h"

#include "onh/thread/Alarming/AlarmingThread.h"
#include "onh/thread/DriverPolling/DriverPollingThread.h"
#include "onh/thread/ProcessUpdater/ProcessUpdaterThread.h"
#include "onh/thread/Script/ScriptThread.h"
#include "onh/thread/Socket/SocketProg.h"
#include "onh/thread/Socket/SocketThread.h"
#include "onh/thread/TagLogger/TagLoggerThread.h"
#include "onh/thread/TagLogger/TagLoggerWriterThread.h"

using namespace onh;

Application::Application(bool test):
    drv(0), drvBuffer(0), pr(0), thManager(0), dbManager(0), cfg(0), testEnv(test)
{
    // Create logger
    log = new Logger("mainProg","main_");
    log->write("Application starting...");

    // Create tag logger buffer container
    tagLoggerBuffer = new TagLoggerBufferContainer();
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
	if (tagLoggerBuffer) {
		delete tagLoggerBuffer;
	}

	log->write("Bye");

    if (log) {
        delete log;
    }
}

int Application::start() {

    int ret = 0;

    try {

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

    } catch (Exception &e) {

        log->write(e.what());

        ret = EXIT_FAILURE;
    } catch (...) {

        log->write("Unknown exception");

        ret = EXIT_FAILURE;

    }

    return ret;

}

DriverPollingThreadData Application::initDriverPollingThreadData() {

    // Driver polling thread data structure
    DriverPollingThreadData thDT = {
        pr->getDriverBufferUpdater(),
        thManager->getController(TCT_DRIVER_POLLING),
        cfg->getUIntValue("modbusPollingInterval")
    };

    return thDT;

}

ProcessUpdaterThreadData Application::initProcessUpdaterThreadData() {

    // Process updater thread data structure
    ProcessUpdaterThreadData thDT = {
        pr->getUpdater(),
        thManager->getController(TCT_PROCESS_UPDATER),
        cfg->getUIntValue("processUpdateInterval")
    };

    return thDT;

}

SocketThreadData Application::initSocketThreadData() {

    // Socket thread data structure
    SocketThreadData thDT = {
        pr->getReader(),
        pr->getWriter(),
        thManager->getController(),
        dbManager->getCredentials(),
        cfg->getIntValue("socketPort"),
        cfg->getIntValue("socketMaxConn"),
        thManager->getCycleTimeReader(TCT_PROCESS_UPDATER),
        thManager->getCycleTimeReader(TCT_ALARMING),
        thManager->getCycleTimeReader(TCT_TAG_LOGGER),
		thManager->getCycleTimeReader(TCT_TAG_LOGGER_WRITER),
        thManager->getCycleTimeReader(TCT_SCRIPT),
        thManager->getCycleTimeReader(TCT_DRIVER_POLLING)
    };

    return thDT;

}

TagLoggerThreadData Application::initTagLoggerThreadData() {

    // Tag logger thread data structure
    TagLoggerThreadData thDT = {
        pr->getReader(),
        thManager->getController(TCT_TAG_LOGGER),
        dbManager->getTagLoggerDB(),
		tagLoggerBuffer->getController(),
        cfg->getUIntValue("tagLoggerUpdateInterval")
    };

    return thDT;
}

TagLoggerWriterThreadData Application::initTagLoggerWriterThreadData() {

    // Tag logger writer thread data structure
    TagLoggerWriterThreadData thDT = {
        thManager->getController(TCT_TAG_LOGGER_WRITER),
        dbManager->getTagLoggerWriterDB(),
		tagLoggerBuffer->getController(true),
        cfg->getUIntValue("tagLoggerUpdateInterval")
    };

    return thDT;
}

AlarminThreadData Application::initAlarmingThreadData() {

    // Alarming thread data structure
    AlarminThreadData thDT = {
        pr->getReader(),
        pr->getWriter(),
        thManager->getController(TCT_ALARMING),
        dbManager->getAlarmingDB(),
        cfg->getUIntValue("alarmingUpdateInterval")
    };

    return thDT;
}

ScriptThreadData Application::initScriptThreadData() {

    // Script system thread data structure
    ScriptThreadData thDT = {
        pr->getReader(),
        pr->getWriter(),
        thManager->getController(TCT_SCRIPT),
        dbManager->getScriptDB(),
        cfg->getUIntValue("scriptSystemUpdateInterval"),
        cfg->getStringValue("scriptSystemExecuteScript"),
		testEnv
    };

    return thDT;
}

void Application::runThreads() {

    // --------------------- DRIVER POLLING THREAD DATA ---------------------------------
    pthread_t tDriverPolling;
    DriverPollingThreadData tDriverPollingDT = initDriverPollingThreadData();
    // ----------------------------------------------------------------------------------

    // --------------------- PROCESS UPDATE THREAD DATA ---------------------------------
    pthread_t tProcessUpdater;
    ProcessUpdaterThreadData tProcessUpdaterDT = initProcessUpdaterThreadData();
    // ----------------------------------------------------------------------------------

    // --------------------- SOCKET THREAD DATA -----------------------------------------
    pthread_t tSocket;
    SocketThreadData tSocketDT = initSocketThreadData();
    // ----------------------------------------------------------------------------------

    // --------------------- TAG LOGGER THREAD DATA -------------------------------------
    pthread_t tTagLogger;
    TagLoggerThreadData tTagLoggerDT = initTagLoggerThreadData();
    // ----------------------------------------------------------------------------------

    // --------------------- TAG LOGGER WRITER THREAD DATA -------------------------------------
	pthread_t tTagLoggerWriter;
	TagLoggerWriterThreadData tTagLoggerWriterDT = initTagLoggerWriterThreadData();
	// ----------------------------------------------------------------------------------

    // --------------------- ALARMING THREAD DATA ---------------------------------------
    pthread_t tAlarming;
    AlarminThreadData tAlarmingDT = initAlarmingThreadData();
    // ----------------------------------------------------------------------------------

    // --------------------- SCRIPT SYSTEM THREAD DATA ----------------------------------
    pthread_t tScript;
    ScriptThreadData tScriptDT = initScriptThreadData();
    // ----------------------------------------------------------------------------------

    // Create driver polling thread
    if (drvBuffer) {
        if (pthread_create(&tDriverPolling, NULL, &driverPolling_thread, (void*)&tDriverPollingDT)) {
            throw Exception("Driver polling thread creation failed");
        } else {
            log->write("Driver polling thread created");
        }
    } else {
        log->write("Driver polling thread not created");
    }

    // Create process updater thread
    if (pthread_create(&tProcessUpdater, NULL, &processUpdater_thread, (void*)&tProcessUpdaterDT)) {
        throw Exception("Process updater thread creation failed");
    } else {
        log->write("Process updater thread created");
    }
    // Create tag logger thread
    if (pthread_create(&tTagLogger, NULL, &tagLogger_thread, (void*)&tTagLoggerDT)) {
        throw Exception("Tag logger thread creation failed");
    } else {
        log->write("Tag logger thread created");
    }
    // Create tag logger writer thread
	if (pthread_create(&tTagLoggerWriter, NULL, &tagLoggerWriter_thread, (void*)&tTagLoggerWriterDT)) {
		throw Exception("Tag logger writer thread creation failed");
	} else {
		log->write("Tag logger writer thread created");
	}
    // Create alarming thread
    if (pthread_create(&tAlarming, NULL, &alarming_thread, (void*)&tAlarmingDT)) {
        throw Exception("Alarming thread creation failed");
    } else {
        log->write("Alarming thread created");
    }
    // Create script system thread
    if (pthread_create(&tScript, NULL, &script_thread, (void*)&tScriptDT)) {
        throw Exception("Script system thread creation failed");
    } else {
        log->write("Script system thread created");
    }
    // Create socket thread
	if (pthread_create(&tSocket, NULL, &socket_thread, (void*)&tSocketDT)) {
		throw Exception("Socket thread creation failed");
	} else {
		log->write("Socket thread created");
	}

    log->write("Join threads...");

    // Wait on threads
    if (drvBuffer) {
        pthread_join(tDriverPolling, NULL);
    }
    pthread_join(tProcessUpdater, NULL);
    pthread_join(tTagLogger, NULL);
    pthread_join(tTagLoggerWriter, NULL);
    pthread_join(tAlarming, NULL);
    pthread_join(tScript, NULL);

    thManager->shutdownSocket();
    pthread_join(tSocket, NULL);

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
    if (driverName == "ModbusTCP") {
        std::string modbusIP = cfg->getStringValue("modbusIP");
        WORD regCount = cfg->getIntValue("modbusRegCount");
        BYTE modbusSlaveID = cfg->getIntValue("modbusSlaveID");
        int modbusPort = cfg->getIntValue("modbusPort");

        // Driver
        drv = new ModbusTCP(modbusIP, regCount, modbusSlaveID, modbusPort);

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

    // Initialize thread manager
    thManager = new ThreadManager();
}
