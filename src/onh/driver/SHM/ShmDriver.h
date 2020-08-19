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

#ifndef SRC_ONH_DRIVER_SHM_SHMDRIVER_H_
#define SRC_ONH_DRIVER_SHM_SHMDRIVER_H_

#include "../Driver.h"
#include "../../utils/GuardDataContainer.h"
#include "sMemory.h"
#include "ShmProcessData.h"

namespace onh {

	/**
	 * Shared memory client class
	 */
	class ShmDriver: public Driver {

        public:

            /**
             * Default Shared memory client constructor
             *
             * @param segmentName Shared memory segment name
             */
            ShmDriver(const std::string& segmentName);

            /**
			 * Copy constructor - inactive
			 */
            ShmDriver(const ShmDriver&) = delete;

            virtual ~ShmDriver();

            /**
			 * Assign operator - inactive
			 */
            ShmDriver& operator=(const ShmDriver&) = delete;

            /**
             * Get driver buffer handle
             *
             * @return Driver buffer handle
             */
            virtual DriverBuffer* getBuffer();

            /**
			 * Get driver process data reader
			 *
			 * @return Driver process data reader handle
			 */
			virtual DriverProcessReader* getReader();

			/**
			 * Get driver process data writer
			 *
			 * @return Driver process data writer handle
			 */
			virtual DriverProcessWriter* getWriter();

			/**
			 * Get driver process data updater
			 *
			 * @return Driver process data updater handle
			 */
			virtual DriverProcessUpdater* getUpdater();

        private:

            /// Shared memory id
			int sfd;

			/// Shared memory size
            const int smSize = sizeof(sMemory);

            /// Shared memory structure
            sMemory *shm;

            /// Shared memory segment name
            std::string shmName;

            /// Driver access protection
            MutexContainer driverLock;

            /// Copy of the controller process data
            GuardDataContainer<ShmProcessData> process;

            /**
             * Trigger error (write log and throw exception)
             *
             * @param msg Exception message
             * @param fName Function from which exception was thrown
             */
            void triggerError(const std::string& msg, const std::string& fName);
	};

}

#endif /* SRC_ONH_DRIVER_SHM_SHMDRIVER_H_ */
