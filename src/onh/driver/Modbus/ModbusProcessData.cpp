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

#include "ModbusProcessData.h"
#include "ModbusUtils.h"
#include "../DriverException.h"
#include <string.h>

using namespace onh;

ModbusProcessData::ModbusProcessData():
	mreg{nullptr, nullptr, 0, 0}
{
}

ModbusProcessData::ModbusProcessData(WORD regCnt):
	mreg{nullptr, nullptr, regCnt, static_cast<unsigned int>(regCnt*2)}
{
	mreg.holdingReg = new WORD[mreg.regCount];
	mreg.inputReg = new WORD[mreg.regCount];

	// Clear all registers
	clear();
}

ModbusProcessData::ModbusProcessData(const ModbusRegisters &mr):
	mreg{nullptr, nullptr, mr.regCount, mr.maxByteCount}
{
	mreg.holdingReg = new WORD[mreg.regCount];
	mreg.inputReg = new WORD[mreg.regCount];

	// Copy registers
	for (int i=0; i<mreg.regCount; ++i) {
		mreg.holdingReg[i] = mr.holdingReg[i];
		mreg.inputReg[i] = mr.inputReg[i];
	}
}

ModbusProcessData::ModbusProcessData(const ModbusProcessData &mpd):
	mreg{nullptr, nullptr, mpd.mreg.regCount, mpd.mreg.maxByteCount}
{
	mreg.holdingReg = new WORD[mreg.regCount];
	mreg.inputReg = new WORD[mreg.regCount];

	// Clear all registers
	clear();
}

ModbusProcessData::~ModbusProcessData() {
	if (mreg.holdingReg)
		delete [] mreg.holdingReg;

	if (mreg.inputReg)
		delete [] mreg.inputReg;
}

ModbusProcessData& ModbusProcessData::operator=(const ModbusProcessData &mpd) {

	// Check self assignment
	if (this == &mpd) {
		return *this;
	}

	// Release memory
	if (mreg.holdingReg)
		delete [] mreg.holdingReg;
	if (mreg.inputReg)
		delete [] mreg.inputReg;

	// Registers count
	mreg.regCount = mpd.mreg.regCount;
	mreg.maxByteCount = mpd.mreg.maxByteCount;

	mreg.holdingReg = new WORD[mreg.regCount];
	mreg.inputReg = new WORD[mreg.regCount];

	// Copy registers
	for (int i=0; i<mreg.regCount; ++i) {
		mreg.holdingReg[i] = mpd.mreg.holdingReg[i];
		mreg.inputReg[i] = mpd.mreg.inputReg[i];
	}

	return *this;
}

bool ModbusProcessData::getBit(processDataAddress addr) const {

    // Check process address
    ModbusUtils::checkProcessAddress(addr, mreg.maxByteCount);

    // Reg address
    WORD regAddr = ModbusUtils::getRegisterAddress(addr);

    // Modbus register
    WORD reg = 0;
    switch (addr.area) {
        case PDA_INPUT: reg = mreg.inputReg[regAddr]; break;
        case PDA_OUTPUT: reg = mreg.holdingReg[regAddr]; break;
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

std::vector<bool> ModbusProcessData::getBits(const std::vector<processDataAddress>& addr) const {

    std::vector<bool> retV;

    for (unsigned int i=0; i<addr.size(); ++i) {

        // Get one bit
        retV.push_back(getBit(addr[i]));

    }

    return retV;
}

BYTE ModbusProcessData::getByte(processDataAddress addr) const {

    // Check process address
    ModbusUtils::checkProcessAddress(addr, mreg.maxByteCount);

    // Reg address
    WORD regAddr = ModbusUtils::getRegisterAddress(addr);

    // Modbus register
    WORD reg = 0;
    switch (addr.area) {
        case PDA_INPUT: reg = mreg.inputReg[regAddr]; break;
        case PDA_OUTPUT: reg = mreg.holdingReg[regAddr]; break;
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

WORD ModbusProcessData::getWord(processDataAddress addr) const {

    // Check process address
    ModbusUtils::checkProcessAddress(addr, mreg.maxByteCount, 1);

    // Reg address
    WORD regAddr = ModbusUtils::getRegisterAddress(addr);

    // Check register overlapping
	bool regOverlap = (addr.byteAddr % 2)?(true):(false);

	// Temp BYTE registers
	BYTE tmp[4] = {0};

	// Pointer to WORD value
	WORD *pWord = nullptr;

    // Modbus register
    WORD reg = 0;

    // Get registers
    if (regOverlap) {

    	if (addr.area == PDA_INPUT) {
    		// Copy registers to temp BYTE array
			memcpy(tmp, &mreg.inputReg[regAddr], 4);
    	} else {
    		// Copy registers to temp BYTE array
			memcpy(tmp, &mreg.holdingReg[regAddr], 4);
    	}

		// Set pointer to hi BYTE of the first WORD register
		pWord = (WORD*)&tmp[1];

		// Get value
		reg = *pWord;

	} else {

		if (addr.area == PDA_INPUT) {
			reg = mreg.inputReg[regAddr];
		} else {
			reg = mreg.holdingReg[regAddr];
		}
	}

    return reg;
}

DWORD ModbusProcessData::getDWord(processDataAddress addr) const {

    // Check process address
    ModbusUtils::checkProcessAddress(addr, mreg.maxByteCount, 3);

    // Reg address
    WORD regAddr = ModbusUtils::getRegisterAddress(addr);

    // Check register overlapping
	bool regOverlap = (addr.byteAddr % 2)?(true):(false);

	// Temp BYTE registers
	BYTE tmp[6] = {0};

	// Pointer to DWORD value
	DWORD *pDWord = nullptr;

    DWORD reg = 0;

    // Get registers
	if (regOverlap) {

		if (addr.area == PDA_INPUT) {
			// Copy registers to temp BYTE array
			memcpy(tmp, &mreg.inputReg[regAddr], 6);
		} else {
			// Copy registers to temp BYTE array
			memcpy(tmp, &mreg.holdingReg[regAddr], 6);
		}

		// Set pointer to hi BYTE of the first WORD register
		pDWord = (DWORD*)&tmp[1];

		// Get value
		reg = *pDWord;

	} else {

		if (addr.area == PDA_INPUT) {
			// Set pointer to hi BYTE of the first WORD register
			pDWord = (DWORD*)&mreg.inputReg[regAddr];

			// Get value
			reg = *pDWord;
		} else {
			// Set pointer to hi BYTE of the first WORD register
			pDWord = (DWORD*)&mreg.holdingReg[regAddr];

			// Get value
			reg = *pDWord;
		}
	}

    return reg;
}

int ModbusProcessData::getInt(processDataAddress addr) const {

    // Check process address
    ModbusUtils::checkProcessAddress(addr, mreg.maxByteCount, 3);

    // Reg address
    WORD regAddr = ModbusUtils::getRegisterAddress(addr);

    // Check register overlapping
	bool regOverlap = (addr.byteAddr % 2)?(true):(false);

	// Temp BYTE registers
	BYTE tmp[6] = {0};

    // Get int
    int* pInt = nullptr;
    int ret = 0;

    // Get registers
	if (regOverlap) {

		if (addr.area == PDA_INPUT) {
			// Copy registers to temp BYTE array
			memcpy(tmp, &mreg.inputReg[regAddr], 6);
		} else {
			// Copy registers to temp BYTE array
			memcpy(tmp, &mreg.holdingReg[regAddr], 6);
		}

		// Set pointer to hi BYTE of the first WORD register
		pInt = (int*)&tmp[1];

		// Get value
		ret = *pInt;

	} else {

		if (addr.area == PDA_INPUT) {
			// Set pointer to hi BYTE of the first WORD register
			pInt = (int*)&mreg.inputReg[regAddr];

			// Get value
			ret = *pInt;
		} else {
			// Set pointer to hi BYTE of the first WORD register
			pInt = (int*)&mreg.holdingReg[regAddr];

			// Get value
			ret = *pInt;
		}
	}

    return ret;
}

float ModbusProcessData::getReal(processDataAddress addr) const {

    // Check process address
    ModbusUtils::checkProcessAddress(addr, mreg.maxByteCount, 3);

    // Reg address
    WORD regAddr = ModbusUtils::getRegisterAddress(addr);

    // Check register overlapping
	bool regOverlap = (addr.byteAddr % 2)?(true):(false);

	// Temp BYTE registers
	BYTE tmp[6] = {0};

    // Get float
    float *pFloat = nullptr;
    float ret = 0;

    // Get registers
	if (regOverlap) {

		if (addr.area == PDA_INPUT) {
			// Copy registers to temp BYTE array
			memcpy(tmp, &mreg.inputReg[regAddr], 6);
		} else {
			// Copy registers to temp BYTE array
			memcpy(tmp, &mreg.holdingReg[regAddr], 6);
		}

		// Set pointer to hi BYTE of the first WORD register
		pFloat = (float*)&tmp[1];

		// Set value
		memcpy(&ret, pFloat, sizeof ret);

	} else {

		if (addr.area == PDA_INPUT) {
			// Set pointer to hi BYTE of the first WORD register
			pFloat = (float*)&mreg.inputReg[regAddr];

			// Set value
			memcpy(&ret, pFloat, sizeof ret);
		} else {
			// Set pointer to hi BYTE of the first WORD register
			pFloat = (float*)&mreg.holdingReg[regAddr];

			// Set value
			memcpy(&ret, pFloat, sizeof ret);
		}
	}

    return ret;
}

unsigned int ModbusProcessData::getMaxByte() const {

	return mreg.maxByteCount;
}

void ModbusProcessData::clear() {

	for (int i=0; i<mreg.regCount; ++i) {
		mreg.holdingReg[i] = 0;
		mreg.inputReg[i] = 0;
	}
}

WORD ModbusProcessData::getRegCount() const {

	return mreg.regCount;
}
