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

#include "ModbusProcessReader.h"
#include "ModbusUtils.h"
#include "../DriverException.h"
#include <string.h>

using namespace onh;

ModbusProcessReader::ModbusProcessReader(const GuardDataController<ModbusProcessData> &gdc):
	driverProcess(gdc)
{
	// Init process data
	driverProcess.getData(process);
}

ModbusProcessReader::~ModbusProcessReader() {
}

bool ModbusProcessReader::getBitValue(processDataAddress addr) {

    return process.getBit(addr);
}

std::vector<bool> ModbusProcessReader::getBitsValue(std::vector<processDataAddress> addr) {

    return process.getBits(addr);
}

BYTE ModbusProcessReader::getByte(processDataAddress addr) {

    return process.getByte(addr);
}

WORD ModbusProcessReader::getWord(processDataAddress addr) {

    return process.getWord(addr);
}

DWORD ModbusProcessReader::getDWord(processDataAddress addr) {

    return process.getDWord(addr);
}

int ModbusProcessReader::getInt(processDataAddress addr) {

    return process.getInt(addr);
}

float ModbusProcessReader::getReal(processDataAddress addr) {

    return process.getReal(addr);
}

void ModbusProcessReader::updateProcessData() {

	driverProcess.getData(process);
}

DriverProcessReader* ModbusProcessReader::createNew() {

	return new ModbusProcessReader(driverProcess);
}
