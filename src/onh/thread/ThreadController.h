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

#ifndef THREADCONTROLLER_H
#define THREADCONTROLLER_H

#include <string>
#include <pthread.h>
#include "../utils/Exception.h"
#include "ThreadExitController.h"
#include "ThreadCycleContainerController.h"

namespace onh {

    /// Forward declaration
	class ThreadManager;

    /**
     * Thread controller class
     */
    class ThreadController {

        public:

            friend class ThreadManager;

            /**
             * Copy constructor
             *
             * @param tc ThreadController object to copy
             */
            ThreadController(const ThreadController &tc);

            virtual ~ThreadController();

            /**
             * Set cycle time of the thread
             *
             * @param tpc Thread cycle time
             */
            void setCycleTime(CycleTimeData tpc);

            /**
             * Get Exit Controller object
             *
             * @return Thread Exit Controller
             */
            ThreadExitController& getExitController();

            /**
             * Get cycle time container controller
             *
             * @return Thread cycle time container controller
             */
            ThreadCycleContainerController& getCycleController();

        private:

            /**
             * Default constructor (allowed only from ThreadManager)
             */
            ThreadController();

            /**
             * Constructor (allowed only from ThreadManager)
             *
             * @param tec Thread Exit Controller object
             */
            ThreadController(const ThreadExitController &tec);

            /**
             * Constructor (allowed only from ThreadManager)
             *
             * @param tec Thread Exit Controller object
             * @param tccc Thread cycle time container controller object
             */
            ThreadController(const ThreadExitController &tec, const ThreadCycleContainerController &tccc);

            /**
             * Assign operator
             */
            ThreadController& operator=(const ThreadController &tc);

            /// Thread exit controller
            ThreadExitController *thExit;

            /// Thread cycle time container controller
            ThreadCycleContainerController *cycleTime;
    };

}

#endif // THREADCONTROLLER_H
