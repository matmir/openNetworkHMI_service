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

#include "ModbusUpdater.h"
#include <iostream>

namespace onh {

ModbusUpdater::ModbusUpdater(modbusM::ModbusMasterPtr drv,
								const MutexAccess &drvLock,
								const GuardDataController<ModbusProcessData> &mbuff):
	driver(drv), driverLock(drvLock), buff(mbuff), tempBuff{nullptr, nullptr, 0, 0} {
	ModbusProcessData tmp;
	// Init temporary buffer
	buff.getData(tmp);

	tempBuff.regCount = tmp.getRegCount();
	tempBuff.maxByteCount = tmp.getMaxByte();
	tempBuff.holdingReg = new WORD[tempBuff.regCount];
	tempBuff.inputReg = new WORD[tempBuff.regCount];
}

ModbusUpdater::~ModbusUpdater() {
	if (tempBuff.holdingReg)
		delete [] tempBuff.holdingReg;

	if (tempBuff.inputReg)
		delete [] tempBuff.inputReg;
}

void ModbusUpdater::updateBuffer() {
	// Check driver
	if (!driver)
		throw DriverException("Missing driver instance", "ModbusUpdater::updateBuffer");

	// Clear temporary load buffers
	clearTempReg();

	driverLock.lock();

	try {
		// Read input registers
		driver->READ_INPUT_REGISTERS(0x00, tempBuff.regCount, tempBuff.inputReg);

		// Read holding registers
		driver->READ_HOLDING_REGISTERS(0x00, tempBuff.regCount, tempBuff.holdingReg);
	} catch (modbusM::ModbusException &e) {
		driverLock.unlock();

		throw DriverException(e.what(), "ModbusUpdater::updateBuffer");
	}

	driverLock.unlock();

	// Copy loaded data to the buffer
	buff.setData(ModbusProcessData(tempBuff));
}

void ModbusUpdater::clearTempReg() {
	if ((tempBuff.holdingReg != nullptr) && (tempBuff.inputReg != nullptr)) {
		for (int i=0; i < tempBuff.regCount; ++i) {
			tempBuff.holdingReg[i] = 0;
			tempBuff.inputReg[i] = 0;
		}
	}
}

}  // namespace onh
