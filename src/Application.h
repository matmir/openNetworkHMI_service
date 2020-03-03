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

#ifndef APPLICATION_H
#define APPLICATION_H

#include "onh/driver/ProcessManager.h"
#include "onh/driver/SHM/ShmDriver.h"
#include "onh/driver/Modbus/ModbusTCP.h"
#include "onh/thread/ThreadProgram.h"
#include "onh/thread/ThreadManager.h"
#include "onh/utils/Logger.h"
#include "onh/db/DBManager.h"
#include "onh/db/Config.h"
#include "onh/thread/Socket/SocketThreadData.h"
#include "onh/thread/DriverPolling/DriverPollingThreadData.h"
#include "onh/thread/ProcessUpdater/ProcessUpdaterThreadData.h"
#include "onh/thread/TagLogger/TagLoggerThreadData.h"
#include "onh/thread/TagLogger/TagLoggerWriterThreadData.h"
#include "onh/thread/TagLogger/TagLoggerBufferContainer.h"
#include "onh/thread/Alarming/AlarmingThreadData.h"
#include "onh/thread/Script/ScriptThreadData.h"

namespace onh {

    /**
	 * Application class
	 */
    class Application {

        public:

            /**
             * Application constructor
             * @param test Test environment flag
             */
            Application(bool test);

            /**
             * Start application
             *
             * @return Return value to the system
             */
            int start();

            virtual ~Application();

        private:

            /**
             * Initialize database
             */
            void initDB();

            /**
             * Initialize driver
             */
            void initDriver();

            /**
             * Initialize driver buffer
             */
            void initDriverBuffer();

            /**
             * Initialize Process Manager
             */
            void initProcessManager();

            /**
             * Initialize Thread manager
             */
            void initThreadManager();

            /**
             * Initialize Driver buffer updater thread data
             *
             * @return Driver buffer thread data
             */
            DriverPollingThreadData initDriverPollingThreadData();

            /**
             * Initialize Process updater thread data
             *
             * @return Process updater thread data
             */
            ProcessUpdaterThreadData initProcessUpdaterThreadData();

            /**
             * Initialize Socket thread data
             *
             * @return Socket thread data
             */
            SocketThreadData initSocketThreadData();

            /**
             * Initialize Tag logger thread data
             *
             * @return Tag logger thread data
             */
            TagLoggerThreadData initTagLoggerThreadData();

            /**
			 * Initialize Tag logger writer thread data
			 *
			 * @return Tag logger writer thread data
			 */
			TagLoggerWriterThreadData initTagLoggerWriterThreadData();

            /**
             * Initialize Alarming thread data
             *
             * @return Alarming thread data
             */
            AlarminThreadData initAlarmingThreadData();

            /**
             * Initialize Script system thread data
             *
             * @return Script system thread data
             */
            ScriptThreadData initScriptThreadData();

            /**
             * Run all threads
             */
            void runThreads();

            /// Main program logger
            Logger *log;

            /// Controller driver
            Driver *drv;
            /// Controller driver buffer
            DriverBuffer *drvBuffer;

            /// Process data manager
            ProcessManager *pr;

            /// Thread manager
            ThreadManager *thManager;

            /// Database manager
            DBManager *dbManager;

            /// Config DB access
            Config *cfg;

            /// Tag logger buffer container
            TagLoggerBufferContainer *tagLoggerBuffer;

            /// Test environment flag
            bool testEnv;
    };

}

#endif // APPLICATION_H
