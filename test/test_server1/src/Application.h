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

#ifndef SRC_APPLICATION_H_
#define SRC_APPLICATION_H_

#include <onhSHMcpp/ShmServer.h>

/**
 * Shared memory server application class
 */
class Application {

	public:

		/**
		 * Application constructor
		 *
		 * @param smem Shared memory segment name
		 * @param exSignal Exit signal pointer
		 */
		Application(const std::string &smem, bool *exSignal);

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
		 * Run application
		 */
		void run();

	private:

		/// SHM server
		onh::ShmServer shmServer;

		onh::processDataAccess* pda;

		/// Exit program flag
		bool exitProg;

		/// Handle for exit signal flag
		bool *exitSignal;

		/**
		 * Check application control bits
		 */
		void checkControlBits();

		/**
		 * Tag logger data simulate
		 */
		void tagLoggerSim();
};

#endif /* SRC_APPLICATION_H_ */
