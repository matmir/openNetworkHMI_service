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

#ifndef DRIVERPOLLINGPROG_H
#define DRIVERPOLLINGPROG_H

#include "../../driver/DriverBufferUpdater.h"
#include "../../utils/Delay.h"
#include "../ThreadProgram.h"

namespace onh {

    /**
	 * Driver polling program class
	 */
    class DriverPollingProg: public ThreadProgram {

        public:

            /**
             * Constructor
             *
             * @param dbu Driver buffer updater
             * @param connId Driver connection identifier
             * @param updateInterval Thread update interval (milliseconds)
             * @param gdcTED Thread exit data controller
             * @param gdcCTD Thread cycle time controller
             */
            DriverPollingProg(const DriverBufferUpdater& dbu,
            					unsigned int connId,
            					unsigned int updateInterval,
								const GuardDataController<ThreadExitData> &gdcTED,
								const GuardDataController<CycleTimeData> &gdcCTD);

            /**
			 * Copy constructor - inactive
			 */
			DriverPollingProg(const DriverPollingProg&) = delete;

            virtual ~DriverPollingProg();

            /**
			 * Thread program function
			 */
			virtual void operator()();

			/**
			 * Assignment operator - inactive
			 */
			DriverPollingProg& operator=(const DriverPollingProg&) = delete;

        private:

            /// Driver buffer updater
            DriverBufferUpdater *drvUpdater;
    };

}

#endif // DRIVERPOLLINGPROG_H
