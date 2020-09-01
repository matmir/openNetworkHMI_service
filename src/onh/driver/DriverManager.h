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

#ifndef SRC_DRIVER_DRIVERMANAGER_H_
#define SRC_DRIVER_DRIVERMANAGER_H_

#include "Driver.h"
#include "ProcessReader.h"
#include "ProcessWriter.h"
#include "ProcessUpdaterData.h"
#include "DriverBufferUpdater.h"
#include "DriverBufferUpdaterData.h"
#include "../utils/Exception.h"
#include "../utils/MutexContainer.h"
#include "../db/objs/DriverConnection.h"
#include <vector>
#include <map>

namespace onh {

	/**
	 * Driver manager class
	 */
	class DriverManager {

        public:

            /**
             * Constructor
             *
             * @param dcv Driver connection configuration
             */
			DriverManager(const std::vector<DriverConnection>& dcv);

            /**
			 * Copy constructor - inactive
			 */
			DriverManager(const DriverManager&) = delete;

            virtual ~DriverManager();

            /**
			 * Assign operator - inactive
			 */
            DriverManager& operator=(const DriverManager&) = delete;

            /**
             * Get updater objects
             *
             * @return ProcessUpdater objects
             */
            std::vector<ProcessUpdaterData> getProcessUpdaters();

            /**
             * Get reader object
             *
             * @return ProcessReader object
             */
            ProcessReader getProcessReader();

            /**
             * Get writer object
             *
             * @return ProcessWriter object
             */
            ProcessWriter getProcessWriter();

            /**
             * Get driver buffer updater data
             *
             * @return DriverBufferUpdater data
             */
            std::vector<DriverBufferUpdaterData> getDriverBufferUpdaters();

        private:

            /**
			 * Driver buffer data structure
			 */
			typedef struct {
				/// Buffer updater connection driver id
				unsigned int connId;
				/// Buffer update interval
				unsigned int updateInterval;
				/// Driver buffer
				DriverBuffer *buff;
			} DriverBufferData;

            /// Driver handle
            std::map<unsigned int, Driver*> driver;

            /// Driver buffer handle
            std::vector<DriverBufferData> driverBuffer;
	};

}

#endif /* SRC_DRIVER_DRIVERMANAGER_H_ */
