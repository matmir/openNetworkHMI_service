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

#ifndef ONH_DRIVER_MODBUS_MODBUSMASTER_H_
#define ONH_DRIVER_MODBUS_MODBUSMASTER_H_

#include <string.h>
#include <sys/types.h>
#include <modbus.h>
#include <memory>

#include "modbusmasterCfg.h"
#include "modbusexception.h"
#include "../DriverRegisterTypes.h"

namespace modbusM {

/**
 * ModbusMaster class
 */
class ModbusMaster {
	public:
		/**
		 * Constructor
		 *
		 * @param cfg Modbus configuration structure
		 */
		explicit ModbusMaster(const ModbusCfg& cfg);

		/**
		 * Copy constructor - inactive
		 */
		ModbusMaster(const ModbusMaster&) = delete;

		~ModbusMaster();

		/**
		 * Assign operator - inactive
		 */
		ModbusMaster& operator=(const ModbusMaster&) = delete;

		/**
		 * Connect to the slave
		 *
		 * @return True if connected
		 */
		void connect();

		/**
		 * Disconnect from slave
		 */
		void disconnect();

		/**
		 * Read input registers from controller
		 *
		 * @param regAddress Register start address
		 * @param quantity Number of registers to read
		 * @param buff Buffer on register values
		 */
		void READ_INPUT_REGISTERS(WORD regAddress, WORD quantity, WORD *buff);

		/**
		 * Read holding registers from controller
		 *
		 * @param regAddress Register start address
		 * @param quantity Number of registers to read
		 * @param buff Buffer on register values
		 */
		void READ_HOLDING_REGISTERS(WORD regAddress, WORD quantity, WORD *buff);

		/**
		 * Write single holding register in controller
		 *
		 * @param regAddress Register start address
		 * @param value Register value
		 */
		void WRITE_SINGLE_REGISTER(WORD regAddress, WORD value);

		/**
		 * Write multiple holding registers in controller
		 *
		 * @param regAddress Register start address
		 * @param quantity Number of registers to write
		 * @param values Buffer with register values
		 */
		void WRITE_MULTIPLE_REGISTERS(WORD regAddress, WORD quantity, WORD *values);

	private:
		/// Modbus communication structure
		modbus_t *mb;

		/// Modbus configuration structure
		ModbusCfg config;
};

using ModbusMasterPtr = std::shared_ptr<modbusM::ModbusMaster>;

}  // namespace modbusM

#endif  // ONH_DRIVER_MODBUS_MODBUSMASTER_H_
