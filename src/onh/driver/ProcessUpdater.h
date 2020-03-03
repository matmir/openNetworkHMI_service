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

#ifndef PROCESSUPDATER_H
#define PROCESSUPDATER_H

#include "Driver.h"
#include "../utils/MutexAccess.h"

namespace onh {

    /// Forward declaration
	class ProcessManager;

	/**
	 * Process updater class
	 */
    class ProcessUpdater {

        public:

            friend class ProcessManager;

            /**
             * Copy constructor
             *
             * @param pu ProcessUpdater to copy
             */
            ProcessUpdater(const ProcessUpdater &pu);

            virtual ~ProcessUpdater();

            /**
             * Update process data (read from controller)
             */
            void update();

        private:

            /**
             * Default constructor (allowed only from ProcessManager)
             */
            ProcessUpdater();

            /**
             * Assign operator
             */
            void operator=(const ProcessUpdater &pu) {};

            /**
             * Constructor with parameters (allowed only from ProcessManager)
             *
             * @param drv Driver instance
             * @param lock Mutex access
             */
            ProcessUpdater(Driver* drv, const MutexAccess& lock);

            /// Driver instance
			Driver* driver;

			/// Mutex for protecting driver
			MutexAccess driverLock;
    };

}

#endif // PROCESSUPDATER_H