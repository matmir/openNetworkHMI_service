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

#ifndef THREADCYCLECONTAINER_H
#define THREADCYCLECONTAINER_H

#include "../utils/MutexContainer.h"
#include "../utils/CycleTime.h"
#include "ThreadCycleContainerController.h"

namespace onh {

    /**
     * Thread cycle time container class
     */
    class ThreadCycleContainer {

        public:

    		/**
    		 * Constructor
    		 */
            ThreadCycleContainer();

            /**
			 * Copy constructor - inactive
			 */
			ThreadCycleContainer(const ThreadCycleContainer&) = delete;

            virtual ~ThreadCycleContainer();

            /**
			 * Assign operator - inactive
			 */
            ThreadCycleContainer& operator=(const ThreadCycleContainer&) = delete;

            /**
             * Get cycle time container controller object
             *
             * @param readOnly Read only flag
             *
             * @return Cycle time container controller object
             */
            ThreadCycleContainerController getController(bool readOnly = false);

        private:

            /// Mutex for protecting data
            MutexContainer tccLock;

            /// Cycle time data
            CycleTimeData cycle;
    };

}

#endif // THREADCYCLECONTAINER_H
