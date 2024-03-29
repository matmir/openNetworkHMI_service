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

#include "ModbusUtils.h"
#include "../DriverUtils.h"
#include "../DriverException.h"

namespace onh {

void ModbusUtils::checkProcessAddress(processDataAddress addr,
										unsigned int maxByteCount,
										unsigned int byteFactor,
										bool writeOperation) {
	// Check bit address
	DriverUtils::checkBitAddress(addr);

	// Check byte address
	if (addr.byteAddr >= (maxByteCount-byteFactor)) {
		throw DriverException("Byte address is out of range", "ModbusUtils::checkProcessAddress");
	}

	// Check area
	if (addr.area == PDA_MEMORY) {
		throw DriverException("Memory area not allowed", "ModbusUtils::checkProcessAddress");
	}
	if ((addr.area != PDA_INPUT) && (addr.area != PDA_OUTPUT)) {
		throw DriverException("Area out of range", "ModbusUtils::checkProcessAddress");
	}
	if (writeOperation && addr.area == PDA_INPUT) {
		throw DriverException("Write to input area not allowed", "ModbusUtils::checkProcessAddress");
	}
}

WORD ModbusUtils::getRegisterAddress(processDataAddress addr) {
	return addr.byteAddr/2;
}

}  // namespace onh
