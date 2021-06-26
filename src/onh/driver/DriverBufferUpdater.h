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

#ifndef ONH_DRIVER_DRIVERBUFFERUPDATER_H_
#define ONH_DRIVER_DRIVERBUFFERUPDATER_H_

#include "DriverBuffer.h"

namespace onh {

/// Forward declaration
class DriverManager;

/**
 * Controller buffer updater class
 */
class DriverBufferUpdater {
	public:
		friend class DriverManager;

		/**
		 * Copy constructor
		 *
		 * @param dbu DriverBufferUpdater to copy
		 */
		DriverBufferUpdater(const DriverBufferUpdater &dbu);

		virtual ~DriverBufferUpdater();

		/**
		 * Assign operator - inactive
		 */
		DriverBufferUpdater& operator=(const DriverBufferUpdater&) = delete;

		/**
		 * Update driver buffer
		 */
		void update();

	private:
		/**
		 * Constructor with parameters (allowed only from ProcessManager)
		 *
		 * @param dbh Driver buffer handle
		 */
		explicit DriverBufferUpdater(DriverBufferPtr dbh);

		/// Driver buffer handle
		DriverBufferPtr drvBuffer;
};

}  // namespace onh

#endif  // ONH_DRIVER_DRIVERBUFFERUPDATER_H_
