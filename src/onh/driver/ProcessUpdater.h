/**
 * This file is part of openNetworkHMI.
 * Copyright (c) 2021 Mateusz Mirosławski.
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

#ifndef ONH_DRIVER_PROCESSUPDATER_H_
#define ONH_DRIVER_PROCESSUPDATER_H_

#include "DriverProcessUpdater.h"

namespace onh {

/// Forward declaration
class DriverManager;

/**
 * Process updater class
 */
class ProcessUpdater {
	public:
		friend class DriverManager;

		/**
		 * Copy constructor
		 *
		 * @param pu ProcessUpdater to copy
		 */
		ProcessUpdater(const ProcessUpdater &pu);

		virtual ~ProcessUpdater();

		/**
		 * Assign operator - inactive
		 */
		ProcessUpdater& operator=(const ProcessUpdater&) = delete;

		/**
		 * Update process data (read from controller)
		 */
		void update();

	private:
		/**
		 * Constructor with parameters (allowed only from ProcessManager)
		 *
		 * @param dpu Pointer to the driver process data updater
		 */
		explicit ProcessUpdater(DriverProcessUpdaterPtr dpu);

		/// Driver process data updater
		DriverProcessUpdaterPtr driverUpdater;
};

}  // namespace onh

#endif  // ONH_DRIVER_PROCESSUPDATER_H_
