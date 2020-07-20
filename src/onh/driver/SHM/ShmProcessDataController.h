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

#ifndef SRC_ONH_DRIVER_SHM_SHMPROCESSDATACONTROLLER_H_
#define SRC_ONH_DRIVER_SHM_SHMPROCESSDATACONTROLLER_H_

#include "../../utils/MutexAccess.h"
#include "processData.h"

namespace onh {

	/// Forward declaration
	class ShmProcessDataContainer;

	/**
	 * Shm process data controller class
	 */
	class ShmProcessDataController {

		public:

			friend class ShmProcessDataContainer;

			/**
			 * Copy constructor
			 *
			 * @param spdc Shm process data controller object to copy
			 */
			ShmProcessDataController(const ShmProcessDataController& spdc);

			virtual ~ShmProcessDataController();

			/**
			 * Assign operator - inactive
			 */
			ShmProcessDataController& operator=(const ShmProcessDataController&) = delete;

			/**
			 * Get copy of the driver process data
			 *
			 * @return Process data copy
			 */
			processData getProcessDataCopy();

		private:

			/**
			 * Constructor (allowed only from ShmProcessDataContainer)
			 *
			 * @param pdLock MutexAccess object for protecting process data
			 * @param procDT Pointer to process data
			 */
			ShmProcessDataController(const MutexAccess &pdLock, processData *procDT);

			/// Pointer to the process data
			processData *process;

			/// Mutex for protecting process data
			MutexAccess processLock;
	};

}

#endif /* SRC_ONH_DRIVER_SHM_SHMPROCESSDATACONTROLLER_H_ */
