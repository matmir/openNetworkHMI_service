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
#include <pthread.h>
#include "ThreadController.h"
#include "ThreadCycleContainerController.h"
#include "ThreadExit.h"
#include "ThreadCycleContainer.h"
#include "../utils/Exception.h"

namespace onh {

    /**
	 * Thread controller types
	 */
    typedef enum {
        TCT_PROCESS_UPDATER,
        TCT_TAG_LOGGER,
		TCT_TAG_LOGGER_WRITER,
        TCT_ALARMING,
        TCT_SCRIPT,
        TCT_DRIVER_POLLING,
        TCT_DEFAULT
    } ThreadControllerType;

    /**
	 * Thread manager class
	 */
    class ThreadManager {

        public:

            ThreadManager();

            virtual ~ThreadManager();

            /**
             * Get thread controller object
             *
             * @param tct Thread controller type
             *
             * @return Thread controller object
             */
            ThreadController getController(ThreadControllerType tct=TCT_DEFAULT);

            /**
             * Get thread cycle time container controller object
             *
             * @param tct Thread controller type
             *
             * @return Thread cycle time cycle time container controller object
             */
            ThreadCycleContainerController getCycleTimeReader(ThreadControllerType tct);

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
            /// Thread exit
            ThreadExit tmExit;

            /// Cycle time of the Process Updater
            ThreadCycleContainer cycleProcessUpdater;

            /// Cycle time of the Driver polling
            ThreadCycleContainer cycleDriverPolling;

            /// Cycle time of the Alarming system
            ThreadCycleContainer cycleAlarming;

            /// Cycle time of the Tag logger system
            ThreadCycleContainer cycleLogger;

            /// Cycle time of the Tag logger writer system
			ThreadCycleContainer cycleLoggerWriter;

            /// Cycle time of the Script system
            ThreadCycleContainer cycleScript;
    };

}

#endif // THREADMANAGER_H
