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

#ifndef THREADCYCLECONTAINERCONTROLLER_H
#define THREADCYCLECONTAINERCONTROLLER_H

#include "../utils/MutexAccess.h"
#include "../utils/CycleTime.h"

namespace onh {

    /// Forward declaration
	class ThreadCycleContainer;

	/**
     * Thread cycle time container controller class
     */
    class ThreadCycleContainerController {

        public:

            friend class ThreadCycleContainer;

            /**
             * Copy constructor
             *
             * @param tccc ThreadCycleContainerController object to copy
             */
            ThreadCycleContainerController(const ThreadCycleContainerController& tccc);

            virtual ~ThreadCycleContainerController();

            /**
             * Set thread cycle time
             *
             * @param cycleData Cycle time data structure
             */
            void setCycleTime(const CycleTimeData &cycleData);

            /**
             * Get thread cycle time
             *
             * @return CycleTimeData Cycle time data structure
             */
            CycleTimeData getCycleTime();

        private:

            /**
             * Default constructor (allowed only from ThreadCycleContainer)
             */
            ThreadCycleContainerController();

            /**
             * Constructor (allowed only from ThreadCycleContainer)
             *
             * @param mal MutexAccess object
             * @param readOnlyFlag Read only flag
             * @param pThCycleData Thread cycle time data handle
             */
            ThreadCycleContainerController(const MutexAccess &mal, CycleTimeData *pThCycleData, bool readOnlyFlag = false);

            /**
             * Assign operator
             */
            void operator=(const ThreadCycleContainerController&) {};

            /// Mutex for protecting data
            MutexAccess maLock;

            /// Handle for cycle time data structure
            CycleTimeData* pCycle;

            /// Read only flag
            bool readOnly;
    };

}

#endif // THREADCYCLECONTAINERCONTROLLER_H
