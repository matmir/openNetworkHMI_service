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

#include "ModbusProcessDataContainer.h"

using namespace onh;

ModbusProcessDataContainer::ModbusProcessDataContainer(WORD regCount):
	registersCount(regCount)
{
	// Initialize registers
	process.holdingReg = new WORD[regCount];
	process.inputReg = new WORD[regCount];
	// Clear registers
	for (int i=0; i<registersCount; ++i) {
		process.holdingReg[i] = 0;
		process.inputReg[i] = 0;
	}
}

ModbusProcessDataContainer::~ModbusProcessDataContainer() {

	if (process.holdingReg) {
		delete process.holdingReg;
	}
	if (process.inputReg) {
		delete process.inputReg;
	}
}

ModbusProcessDataController ModbusProcessDataContainer::getController() {

	return ModbusProcessDataController(processLock.getAccess(), &process, registersCount);
}

void ModbusProcessDataContainer::update(const ModbusProcessData& newDT) {

	// Check registers
	if (!process.holdingReg) {
		throw Exception("Missing holding register instance", "ModbusProcessDataContainer::update");
	}
	if (!process.inputReg) {
		throw Exception("Missing input register instance", "ModbusProcessDataContainer::update");
	}

	// Lock access to the process data
	processLock.lock();

	// Update data
	for (int i=0; i<registersCount; ++i) {
		process.holdingReg[i] = newDT.holdingReg[i];
		process.inputReg[i] = newDT.inputReg[i];
	}

	// Unlock access to the process data
	processLock.unlock();
}

void ModbusProcessDataContainer::clear() {

	// Lock access to the process data
	processLock.lock();

	// Clear registers
	for (int i=0; i<registersCount; ++i) {
		process.holdingReg[i] = 0;
		process.inputReg[i] = 0;
	}

	// Unlock access to the process data
	processLock.unlock();
}
