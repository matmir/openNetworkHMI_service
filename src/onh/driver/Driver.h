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

#ifndef ONH_DRIVER_DRIVER_H_
#define ONH_DRIVER_DRIVER_H_

#include <vector>
#include "../utils/logger/TextLogger.h"
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
		explicit Driver(const std::string& logName);

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
		virtual DriverBufferPtr getBuffer() = 0;

		/**
		 * Get driver process data reader
		 *
		 * @return Driver process data reader handle
		 */
		virtual DriverProcessReaderPtr getReader() = 0;

		/**
		 * Get driver process data writer
		 *
		 * @return Driver process data writer handle
		 */
		virtual DriverProcessWriterPtr getWriter() = 0;

		/**
		 * Get driver process data updater
		 *
		 * @return Driver process data updater handle
		 */
		virtual DriverProcessUpdaterPtr getUpdater() = 0;

	protected:
		/**
		 * Get driver logger
		 *
		 * @return Driver logger
		 */
		ILogger& getLog();

	private:
		/// Logger object
		std::unique_ptr<ILogger> log;
};

using DriverPtr = std::shared_ptr<Driver>;

}  // namespace onh

#endif  // ONH_DRIVER_DRIVER_H_
