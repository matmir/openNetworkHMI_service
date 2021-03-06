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

#ifndef SRC_DRIVER_DRIVER_H_
#define SRC_DRIVER_DRIVER_H_

#include <vector>
#include "../utils/Logger.h"
#include "DriverBuffer.h"
#include "DriverUtils.h"
#include "DriverProcessReader.h"
#include "DriverProcessWriter.h"
#include "DriverProcessUpdater.h"
#include "DriverException.h"
#include "DriverRegisterTypes.h"
#include "ProcessDataTypes.h"

namespace onh {

	/**
	 * Base driver abstract class
	 */
	class Driver {

		public:

			/**
			 * Default constructor
			 *
			 * @param logName Logger name
			 */
			Driver(const std::string& logName);

			/**
			 * Copy constructor - inactive
			 */
			Driver(const Driver&) = delete;

			virtual ~Driver();

			/**
			 * Assign operator - inactive
			 */
			Driver& operator=(const Driver&) = delete;

			/**
			 * Get driver buffer handle
			 *
			 * @return Driver buffer handle
			 */
			virtual DriverBuffer* getBuffer() = 0;

			/**
			 * Get driver process data reader
			 *
			 * @return Driver process data reader handle
			 */
			virtual DriverProcessReader* getReader() = 0;

			/**
			 * Get driver process data writer
			 *
			 * @return Driver process data writer handle
			 */
			virtual DriverProcessWriter* getWriter() = 0;

			/**
			 * Get driver process data updater
			 *
			 * @return Driver process data updater handle
			 */
			virtual DriverProcessUpdater* getUpdater() = 0;

		protected:

			/**
			 * Get driver logger
			 *
			 * @return Driver logger
			 */
			Logger& getLog();

		private:

			/// Logger object
			Logger *log;
	};

}

#endif /* SRC_DRIVER_DRIVER_H_ */
