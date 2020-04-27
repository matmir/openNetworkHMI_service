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

#include "ModbusProcessDataController.h"

using namespace onh;

ModbusProcessDataController::ModbusProcessDataController():
	process(0), processLock(), registersCount(0)
{
}

ModbusProcessDataController::ModbusProcessDataController(const ModbusProcessDataController& spdc):
	process(spdc.process), processLock(spdc.processLock), registersCount(spdc.registersCount)
{
}

ModbusProcessDataController::ModbusProcessDataController(const MutexAccess &pdLock, ModbusProcessData *procDT, WORD regCount):
	process(procDT), processLock(pdLock), registersCount(regCount)
{
}

ModbusProcessDataController::~ModbusProcessDataController() {
}

void ModbusProcessDataController::getProcessDataCopy(ModbusProcessData *dest) {

	if (!process)
		throw Exception("Process data handle not initialized", "ModbusProcessDataController::getProcessDataCopy");

	// Lock access to the process data
	processLock.lock();

	// Copy data
	for (int i=0; i<registersCount; ++i) {
		dest->holdingReg[i] = process->holdingReg[i];
		dest->inputReg[i] = process->inputReg[i];
	}

	// Unlock access to the process data
	processLock.unlock();
}

WORD ModbusProcessDataController::getRegistersCount() const {

	return registersCount;
}
