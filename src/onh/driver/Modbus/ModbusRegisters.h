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

#ifndef SRC_ONH_DRIVER_MODBUS_MODBUSREGISTERS_H_
#define SRC_ONH_DRIVER_MODBUS_MODBUSREGISTERS_H_

#include "../DriverRegisterTypes.h"

namespace onh {

	/**
	 * Modbus registers structure
	 */
    typedef struct {
        /// Modbus holding registers
        WORD *holdingReg;

        /// Modbus input registers
        WORD *inputReg;

        /// Registers count
		WORD regCount;

		/// Maximum Byte count
		unsigned int maxByteCount;
    } ModbusRegisters;

}

#endif /* SRC_ONH_DRIVER_MODBUS_MODBUSREGISTERS_H_ */
