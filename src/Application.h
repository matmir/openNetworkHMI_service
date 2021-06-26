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

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <memory>
#include "onh/driver/DriverManager.h"
#include "onh/driver/SHM/ShmDriver.h"
#include "onh/driver/Modbus/ModbusDriver.h"
#include "onh/thread/ThreadManager.h"
#include "onh/utils/Logger.h"
#include "onh/db/DBManager.h"
#include "onh/db/Config.h"
#include "onh/thread/TagLogger/TagLoggerBufferContainer.h"

namespace onh {

/**
 * Application class
 */
class Application {
	public:
		/**
		 * Application constructor
		 *
		 * @param test Test environment flag
		 */
		explicit Application(bool test);

		/**
		 * Copy constructor - inactive
		 */
		Application(const Application&) = delete;

		virtual ~Application();

		/**
		 * Assignment operator - inactive
		 */
		Application& operator=(const Application&) = delete;

		/**
		 * Start application
		 *
		 * @return Return value to the system
		 */
		int start();

	private:
		/**
		 * Initialize database
		 */
		void initDB();

		/**
		 * Initialize driver
		 */
		void initDriver();

		/**
		 * Initialize Thread manager
		 */
		void initThreadManager();

		/**
		 * Run all threads
		 */
		void runThreads();

		/// Main program logger
		std::unique_ptr<Logger> log;

		/// Driver manager
		std::unique_ptr<DriverManager> drvManager;

		/// Thread manager
		std::unique_ptr<ThreadManager> thManager;

		/// Database manager
		std::unique_ptr<DBManager> dbManager;

		/// Config DB access
		std::unique_ptr<Config> cfg;

		/// Test environment flag
		bool testEnv;
};

}  // namespace onh

#endif  // APPLICATION_H_
