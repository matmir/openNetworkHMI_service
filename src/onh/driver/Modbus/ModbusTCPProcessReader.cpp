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

#include "ModbusTCPProcessReader.h"
#include "ModbusTCPUtils.h"
#include "../DriverException.h"
#include <string.h>

using namespace onh;

ModbusTCPProcessReader::ModbusTCPProcessReader():
	DriverProcessReader(), maxByteCount(0), driverProcess()
{
	process.holdingReg = 0;
	process.inputReg = 0;
}

ModbusTCPProcessReader::ModbusTCPProcessReader(const ModbusTCPProcessDataController& spdc):
	driverProcess(spdc)
{
	process.holdingReg = new WORD[driverProcess.getRegistersCount()];
	process.inputReg = new WORD[driverProcess.getRegistersCount()];
	// Clear registers
	for (int i=0; i<driverProcess.getRegistersCount(); ++i) {
		process.holdingReg[i] = 0;
		process.inputReg[i] = 0;
	}

	maxByteCount = driverProcess.getRegistersCount()*2;
}

ModbusTCPProcessReader::~ModbusTCPProcessReader() {

	if (process.holdingReg) {
		delete process.holdingReg;
	}
	if (process.inputReg) {
		delete process.inputReg;
	}
}

void ModbusTCPProcessReader::triggerError(const std::string& msg, const std::string& fName) {

    throw DriverException(msg, fName);
}

bool ModbusTCPProcessReader::getBitValue(processDataAddress addr) {

    // Check process address
    ModbusTCPUtils::checkProcessAddress(addr, maxByteCount);

    // Reg address
    WORD regAddr = ModbusTCPUtils::getRegisterAddress(addr);

    // Modbus register
    WORD reg = 0;
    switch (addr.area) {
        case PDA_INPUT: reg = process.inputReg[regAddr]; break;
        case PDA_OUTPUT: reg = process.holdingReg[regAddr]; break;
        default: reg = 0;
    }

    // Low byte of the register
    BYTE bLO = reg & 0x00FF;
    // High byte of the register
    BYTE bHI = (reg & 0xFF00) >> 8;

    BYTE b = (addr.byteAddr % 2)?(bHI):(bLO);

    // Read bit value
    bool v = (b >> addr.bitAddr & 0x01);

    return v;

}

std::vector<bool> ModbusTCPProcessReader::getBitsValue(std::vector<processDataAddress> addr) {

    std::vector<bool> retV;

    for (unsigned int i=0; i<addr.size(); ++i) {

        // Get one bit
        retV.push_back(getBitValue(addr[i]));

    }

    return retV;

}

BYTE ModbusTCPProcessReader::getByte(processDataAddress addr) {

    // Check process address
    ModbusTCPUtils::checkProcessAddress(addr, maxByteCount);

    // Reg address
    WORD regAddr = ModbusTCPUtils::getRegisterAddress(addr);

    // Modbus register
    WORD reg = 0;
    switch (addr.area) {
        case PDA_INPUT: reg = process.inputReg[regAddr]; break;
        case PDA_OUTPUT: reg = process.holdingReg[regAddr]; break;
        default: reg = 0;
    }

    // Low byte of the register
    BYTE bLO = reg & 0x00FF;
    // High byte of the register
    BYTE bHI = (reg & 0xFF00) >> 8;

    // Get byte
    BYTE b = (addr.byteAddr % 2)?(bHI):(bLO);

    return b;
}

WORD ModbusTCPProcessReader::getWord(processDataAddress addr) {

    // Check process address
    ModbusTCPUtils::checkProcessAddress(addr, maxByteCount, 1);

    // Reg address
    WORD regAddr = ModbusTCPUtils::getRegisterAddress(addr);

    // Modbus register
    WORD reg = 0;
    switch (addr.area) {
        case PDA_INPUT: reg = process.inputReg[regAddr]; break;
        case PDA_OUTPUT: reg = process.holdingReg[regAddr]; break;
        default: reg = 0;
    }

    return reg;

}

DWORD ModbusTCPProcessReader::getDWord(processDataAddress addr) {

    // Check process address
    ModbusTCPUtils::checkProcessAddress(addr, maxByteCount, 3);

    // Reg address
    WORD regAddr = ModbusTCPUtils::getRegisterAddress(addr);

    DWORD reg = 0;

    // Modbus registers
    WORD regLo = 0;
    WORD regHi = 0;
    switch (addr.area) {
        case PDA_INPUT: {
            regLo = process.inputReg[regAddr];
            regHi = process.inputReg[regAddr+1];
        } break;
        case PDA_OUTPUT: {
            regLo = process.holdingReg[regAddr];
            regHi = process.holdingReg[regAddr+1];
        } break;
        default: {
            regLo = 0;
            regHi = 0;
        }
    }

    // DWord
    reg = regHi;
    reg = reg << 16;
    reg = (reg | regLo);

    return reg;

}

int ModbusTCPProcessReader::getInt(processDataAddress addr) {

    // Check process address
    ModbusTCPUtils::checkProcessAddress(addr, maxByteCount, 3);

    // Reg address
    WORD regAddr = ModbusTCPUtils::getRegisterAddress(addr);

    // Get int
    int* v = 0;
    int def = 0;

    // Read Modbus registers
    switch (addr.area) {
        case PDA_INPUT: v = (int*)&process.inputReg[regAddr]; break;
        case PDA_OUTPUT: v = (int*)&process.holdingReg[regAddr]; break;
        default: v = &def;
    }

    return *v;

}

float ModbusTCPProcessReader::getReal(processDataAddress addr) {

    // Check process address
    ModbusTCPUtils::checkProcessAddress(addr, maxByteCount, 3);

    // Reg address
    WORD regAddr = ModbusTCPUtils::getRegisterAddress(addr);

    // Get float
    float v = 0;
    float def = 0;

    // Read Modbus registers
    switch (addr.area) {
    	case PDA_INPUT: memcpy(&v, &process.inputReg[regAddr], sizeof v); break;
    	case PDA_OUTPUT: memcpy(&v, &process.holdingReg[regAddr], sizeof v); break;
        default: v = def;
    }

    return v;

}

void ModbusTCPProcessReader::updateProcessData() {

	driverProcess.getProcessDataCopy(&process);
}

DriverProcessReader* ModbusTCPProcessReader::createNew() {

	return new ModbusTCPProcessReader(driverProcess);
}
