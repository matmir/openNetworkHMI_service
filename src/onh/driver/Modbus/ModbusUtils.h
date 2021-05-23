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

#ifndef ONH_DRIVER_MODBUS_MODBUSUTILS_H_
#define ONH_DRIVER_MODBUS_MODBUSUTILS_H_

#include "../ProcessDataTypes.h"
#include "../DriverRegisterTypes.h"

namespace onh {

/**
 * Modbus utils class
 */
class ModbusUtils {
	public:
		/**
		 * Check process data address
		 *
		 * @param addr Process data address
		 * @param maxByteCount Maximum Byte address
		 * @param byteFactor Byte address correction factor
		 * @param writeOperation Write flag
		 */
		static void checkProcessAddress(processDataAddress addr,
										unsigned int maxByteCount,
										unsigned int byteFactor = 0,
										bool writeOperation = false);

		/**
		 * Get register address from process data address
		 *
		 * @param addr Process data address
		 *
		 * @return Register address
		 */
		static WORD getRegisterAddress(processDataAddress addr);
};

}  // namespace onh

#endif  // ONH_DRIVER_MODBUS_MODBUSUTILS_H_
