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

#include "ShmProcessReader.h"
#include "../DriverUtils.h"
#include "../DriverException.h"

namespace onh {

ShmProcessReader::ShmProcessReader(const GuardDataController<ShmProcessData>& gdc):
	driverProcess(gdc) {
	updateProcessData();
}

ShmProcessReader::~ShmProcessReader() {
}

bool ShmProcessReader::getBitValue(processDataAddress addr) {
	return process.getBit(addr);
}

std::vector<bool> ShmProcessReader::getBitsValue(std::vector<processDataAddress> addr) {
	return process.getBits(addr);
}

BYTE ShmProcessReader::getByte(processDataAddress addr) {
	return process.getByte(addr);
}

WORD ShmProcessReader::getWord(processDataAddress addr) {
	return process.getWord(addr);
}

DWORD ShmProcessReader::getDWord(processDataAddress addr) {
	return process.getDWord(addr);
}

int ShmProcessReader::getInt(processDataAddress addr) {
	return process.getInt(addr);
}

float ShmProcessReader::getReal(processDataAddress addr) {
	return process.getReal(addr);
}

void ShmProcessReader::updateProcessData() {
	// Copy data from driver
	driverProcess.getData(process);
}

DriverProcessReaderPtr ShmProcessReader::createNew() {
	return DriverProcessReaderPtr(new ShmProcessReader(driverProcess));
}

}  // namespace onh
