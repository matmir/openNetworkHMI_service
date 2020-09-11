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

#ifndef SRC_ONH_DRIVER_SHM_SHMPROCESSUPDATER_H_
#define SRC_ONH_DRIVER_SHM_SHMPROCESSUPDATER_H_

#include "../DriverProcessUpdater.h"
#include "ShmProcessData.h"
#include "../../utils/GuardDataController.h"
#include "sMemory.h"

namespace onh {

	/// Forward declaration
	class ShmDriver;

	/**
	 * SHM driver process data updater class
	 */
	class ShmProcessUpdater: public DriverProcessUpdater {

		public:

			friend class ShmDriver;

			/**
			 * Copy constructor - inactive
			 */
			ShmProcessUpdater(const ShmProcessUpdater&) = delete;

			virtual ~ShmProcessUpdater() override;

			/**
			 * Assign operator - inactive
			 */
			ShmProcessUpdater& operator=(const ShmProcessUpdater&) = delete;

			/**
			 * Update process data (copy from device)
			 */
			virtual void updateProcessData() override;

			/**
			 * Create new driver process updater
			 *
			 * @return Pointer to the new driver process updater
			 */
			virtual DriverProcessUpdater* createNew() override;

		private:

			/**
			 * Constructor with parameters (allowed only from ShmDriver)
			 *
			 * @param segmentName Shared memory segment name
			 * @param smem SHM structure handle
			 * @param gdc SHM process data controller (write mode)
			 * @param lock Mutex for protecting driver
			 */
			ShmProcessUpdater(const std::string& segmentName, sMemory *smem, const GuardDataController<ShmProcessData> &gdc, const MutexAccess& lock);

			/// Shared memory segment name
			std::string shmName;

			/// Shared memory structure handle
			sMemory *shm;

			/// Driver process data controller (write mode)
			GuardDataController<ShmProcessData> process;

			/// Mutex for protecting driver
			MutexAccess driverLock;
	};

}

#endif /* SRC_ONH_DRIVER_SHM_SHMPROCESSUPDATER_H_ */
