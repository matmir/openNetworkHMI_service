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

#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <string>
#include <thread>
#include <vector>
#include "ThreadProgram.h"
#include "ThreadSocket.h"
#include "../utils/GuardDataContainer.h"
#include "TagLogger/TagLoggerBufferContainer.h"
#include "ThreadExitData.h"
#include "../driver/DriverBufferUpdater.h"
#include "../driver/ProcessUpdater.h"
#include "../driver/ProcessReader.h"
#include "../driver/ProcessWriter.h"
#include "../db/AlarmingDB.h"
#include "../db/TagLoggerDB.h"
#include "../db/ScriptDB.h"
#include "../db/DBCredentials.h"
#include "../utils/Exception.h"

namespace onh {

    /**
	 * Thread manager class
	 */
    class ThreadManager {

        public:

    		/**
    		 * Constructor
    		 */
            ThreadManager();

            /**
             * Copy constructor - inactive
             */
            ThreadManager(const ThreadManager&) = delete;

            /**
             * Destructor
             */
            virtual ~ThreadManager();

            /**
             * Assignment operator - inactive
             */
            ThreadManager& operator=(const ThreadManager&) = delete;

            /**
			 * Initialize Process updater thread
			 *
			 * @param pu Process updater
			 * @param updateInterval Thread update interval (milliseconds)
			 */
			void initProcessUpdater(const ProcessUpdater& pu, unsigned int updateInterval);

            /**
             * Initialize driver buffer thread
             *
             * @param dbu Driver buffer updater
             * @param updateInterval Thread update interval (milliseconds)
             */
            void initDriverPolling(const DriverBufferUpdater& dbu, unsigned int updateInterval);

            /**
             * Initialize Alarming thread
             *
             * @param pr Process reader
             * @param pw Process writer
             * @param adb Alarming DB
             * @param updateInterval Thread update interval (milliseconds)
             */
            void initAlarmingThread(const ProcessReader& pr,
									const ProcessWriter& pw,
									const AlarmingDB& adb,
									unsigned int updateInterval);

            /**
             * Initialize Tag logger thread
             *
             * @param pr Process reader
             * @param tldb Tag logger DB
             * @param updateInterval Thread update interval (milliseconds)
             */
            void initTagLoggerThread(const ProcessReader& pr,
            							const TagLoggerDB& tldb,
										unsigned int updateInterval);

            /**
             * Initialize Tag logger writer thread
             *
             * @param tldb Tag logger DB
             * @param updateInterval Thread update interval (milliseconds)
             */
            void initTagLoggerWriterThread(const TagLoggerDB& tldb,
											unsigned int updateInterval);

            /**
             * Initialize Script system thread
             *
             * @param pr Process reader
             * @param pw Process writer
             * @param sdb Script DB
             * @param updateInterval Thread update interval (milliseconds)
             * @param executeScript Full path to the main execute script
             * @param testEnv Test environment flag
             */
            void initScriptThread(const ProcessReader& pr,
            						const ProcessWriter& pw,
									const ScriptDB& sdb,
									unsigned int updateInterval,
									const std::string& executeScript,
									bool testEnv);

            /**
             * Initialize Socket thread
             *
             * @param pr Process reader
             * @param pw Process writer
             * @param dbc DB credentials
             * @param port Socket port
             * @param maxConn Socket maximum connected clients
             */
            void initSocketThread(const ProcessReader& pr,
            						const ProcessWriter& pw,
									const DBCredentials& dbc,
									int port,
									int maxConn);

            /**
             * Run threads
             */
            void run();

            /**
             * Trigger exit
             */
            void exitMain();

            /**
             * Get exit information
             *
             * @return Additional information about exit
             */
            std::string getExitInfo();

            /**
             * Shutdown socket
             */
            void shutdownSocket();

        private:

            /**
             * Thread program data structure
             */
            typedef struct {
            	/// Cycle time container
            	GuardDataContainer<CycleTimeData> cycleContainer;
            	/// Thread program
            	ThreadProgram *thProgram;
			} threadProgramData;

            /// Thread exit
			GuardDataContainer<ThreadExitData> tmExit;

			/// Socket file descriptor
			GuardDataContainer<int> tmSockDesc;

            /// Thread data for Process Updater
            threadProgramData thProcessUpdater;

            /// Thread data for Driver polling
            threadProgramData thDriverPolling;

            /// Thread data for Alarming system
            threadProgramData thAlarming;

            /// Thread data for Tag logger system
            threadProgramData thLogger;

            /// Thread data for Tag logger writer system
            threadProgramData thLoggerWriter;

            /// Tag logger buffer container
			TagLoggerBufferContainer tagLoggerBuffer;

            /// Thread data for Script system
            threadProgramData thScript;

            /// Thread data for Socket
			ThreadSocket *thSocket;

			/// Socket thread
			std::thread *threadSocket;

			/// Program threads
			std::vector<std::thread*> threadProgs;
    };

}

#endif // THREADMANAGER_H
