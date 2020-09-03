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

#include <modbus.h>
#include <string>

/**
 * Modbus server application class
 */
class Application {

	public:

		/**
		 * Application constructor
		 *
		 * @param addr Modbus server IP address
		 * @param port Modbus server port
		 * @param regCount Modbus registers count
		 * @param exSignal Exit signal pointer
		 */
		Application(const std::string &addr, const unsigned int& port, const unsigned int& regCount, bool *exSignal);

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

		modbus_t *ctx;
		modbus_mapping_t *mb_mapping;

		uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];

		/// Exit program flag
		bool exitProg;

		/// Handle for exit signal flag
		bool *exitSignal;

		/// Flags
		bool clearProcess, exit, simData, simData1;

		/**
		 * Update control flags
		 */
		void updateControlFlags();

		/**
		 * Check application control bits
		 */
		void checkControlBits();

		/**
		 * Tag logger data simulate
		 */
		void tagLoggerSim();

		/**
		 * Clear modbus query
		 */
		void clearQuery();
};

#endif /* SRC_APPLICATION_H_ */
