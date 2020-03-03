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

#ifndef SRC_DRIVER_PROCESSMANAGER_H_
#define SRC_DRIVER_PROCESSMANAGER_H_

#include "Driver.h"
#include "ProcessReader.h"
#include "ProcessWriter.h"
#include "ProcessUpdater.h"
#include "DriverBufferUpdater.h"
#include "../utils/Exception.h"
#include "../utils/MutexContainer.h"

namespace onh {

	/**
	 * Process data manager class
	 */
	class ProcessManager {

        public:
            /**
             * Constructor
             *
             * @param drv Driver handle
             * @param drvBuffHandle Driver buffer handle
             */
            ProcessManager(Driver* drv, DriverBuffer* drvBuffHandle);

            virtual ~ProcessManager();

            /**
             * Get updater object
             *
             * @return ProcessUpdater object
             */
            ProcessUpdater getUpdater();

            /**
             * Get reader object
             *
             * @return ProcessReader object
             */
            ProcessReader getReader();

            /**
             * Get writer object
             *
             * @return ProcessWriter object
             */
            ProcessWriter getWriter();

            /**
             * Get driver buffer updater object
             *
             * @return DriverBufferUpdater object
             */
            DriverBufferUpdater getDriverBufferUpdater();

        private:
            /// Driver handle
            Driver* driver;

            /// Driver buffer handle
            DriverBuffer* driverBuffer;

            /// Mutex for protecting driver
            MutexContainer itsLock;
	};

}

#endif /* SRC_DRIVER_PROCESSMANAGER_H_ */
