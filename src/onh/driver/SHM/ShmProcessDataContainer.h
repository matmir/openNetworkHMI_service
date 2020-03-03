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

#ifndef SRC_ONH_DRIVER_SHM_SHMPROCESSDATACONTAINER_H_
#define SRC_ONH_DRIVER_SHM_SHMPROCESSDATACONTAINER_H_

#include "../../utils/MutexContainer.h"
#include "processData.h"
#include "ShmProcessDataController.h"

namespace onh {

	/**
	 * SHM process data container class
	 */
	class ShmProcessDataContainer {

		public:

			ShmProcessDataContainer();

			virtual ~ShmProcessDataContainer();

			/**
			 * Get Shm process data container controller object
			 *
			 * @return Shm process data container controller object
			 */
			ShmProcessDataController getController();

			/**
			 * Update internal process data
			 *
			 * @param newDT New process data
			 */
			void update(const processData& newDT);

			/**
			 * Clear process data
			 */
			void clear();

		private:

			/**
			 * Copy constructor
			 */
			ShmProcessDataContainer(const ShmProcessDataContainer&) {};

			/**
			 * Assign operator
			 */
			void operator=(const ShmProcessDataContainer&) {};

			/// Process data
			processData process;

			/// Mutex for protecting process data
			MutexContainer processLock;
	};

}

#endif /* SRC_ONH_DRIVER_SHM_SHMPROCESSDATACONTAINER_H_ */
