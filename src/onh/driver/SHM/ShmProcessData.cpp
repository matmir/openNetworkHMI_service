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

#include "ShmProcessData.h"
#include "../DriverUtils.h"
#include "../DriverException.h"
#include <string.h>

using namespace onh;

ShmProcessData::ShmProcessData():
	process(nullptr)
{
	// Create process data
	process = new processData();

	// Clear all data
	clear();
}

ShmProcessData::ShmProcessData(const ShmProcessData &spd):
	process(nullptr)
{
	// Create process data
	process = new processData();

	// Copy data
	*process = *spd.process;
}

ShmProcessData::ShmProcessData(const processData &pd):
	process(nullptr)
{
	// Create process data
	process = new processData();

	// Copy data
	*process = pd;
}

ShmProcessData::~ShmProcessData() {
	if (process)
		delete process;
}

ShmProcessData& ShmProcessData::operator=(const ShmProcessData &spd) {

	// Check self assignment
	if (this == &spd) {
		return *this;
	}

	// Release memory
	if (process)
		delete process;

	// Create process data
	process = new processData();

	// Copy data
	*process = *spd.process;

	return *this;
}

bool ShmProcessData::getBit(processDataAddress addr) const {

    // Check bit address
    DriverUtils::checkBitAddress(addr);

    // Check byte address
    if (addr.byteAddr >= PROCESS_DT_SIZE) {

    	throw DriverException("Byte address is out of range", "ShmProcessData::getBitValue");
    }

    // Get byte
    BYTE b = 0;

    switch (addr.area) {
        case PDA_INPUT: b = process->in[addr.byteAddr]; break;
        case PDA_OUTPUT: b = process->out[addr.byteAddr]; break;
        case PDA_MEMORY: b = process->mem[addr.byteAddr]; break;
        default: throw DriverException("Wrong address area", "ShmProcessData::getBitValue"); break;
    }

    // Read bit value
    bool v = (b >> addr.bitAddr & 0x01);

    return v;
}

std::vector<bool> ShmProcessData::getBits(const std::vector<processDataAddress>& addr) const {

    std::vector<bool> retV;

    for (unsigned int i=0; i<addr.size(); ++i) {

        // Read bit value
        retV.push_back(getBit(addr[i]));

    }

    return retV;
}

BYTE ShmProcessData::getByte(processDataAddress addr) const {

    // Check bit address
    DriverUtils::checkBitAddress(addr);

    // Check byte address
    if (addr.byteAddr >= PROCESS_DT_SIZE) {

    	throw DriverException("Byte address is out of range", "ShmProcessData::getByte");
    }

    // Get byte
    BYTE b = 0;

    switch (addr.area) {
        case PDA_INPUT: b = process->in[addr.byteAddr]; break;
        case PDA_OUTPUT: b = process->out[addr.byteAddr]; break;
        case PDA_MEMORY: b = process->mem[addr.byteAddr]; break;
        default: throw DriverException("Wrong address area", "ShmProcessData::getByte"); break;
    }

    return b;
}

WORD ShmProcessData::getWord(processDataAddress addr) const {

    // Check bit address
    DriverUtils::checkBitAddress(addr);

    // Check byte address
    if (addr.byteAddr >= PROCESS_DT_SIZE-1) {

    	throw DriverException("Byte address is out of range", "ShmProcessData::getWord");
    }

    // Prepare data
    BYTE b1 = 0;
    BYTE b2 = 0;
    WORD w = 0;
    WORD wt = 0;

    switch (addr.area) {
        case PDA_INPUT: {
            b1 = process->in[addr.byteAddr];
            b2 = process->in[addr.byteAddr+1];
        } break;
        case PDA_OUTPUT: {
            b1 = process->out[addr.byteAddr];
            b2 = process->out[addr.byteAddr+1];
        } break;
        case PDA_MEMORY: {
            b1 = process->mem[addr.byteAddr];
            b2 = process->mem[addr.byteAddr+1];
        } break;
        default: throw DriverException("Wrong address area", "ShmProcessData::getWord"); break;
    }

    // Highest byte
    w = b2;
    w = w << 8;

    // Lower byte
    wt = b1;

    // One word
    w = (w | wt);

    return w;
}

DWORD ShmProcessData::getDWord(processDataAddress addr) const {

    // Check bit address
    DriverUtils::checkBitAddress(addr);

    // Check byte address
    if (addr.byteAddr >= PROCESS_DT_SIZE-3) {

    	throw DriverException("Byte address is out of range", "ShmProcessData::getDWord");
    }

    // Prepare data
    BYTE b1 = 0;
    BYTE b2 = 0;
    BYTE b3 = 0;
    BYTE b4 = 0;
    WORD w1 = 0;
    WORD w2 = 0;
    WORD wt = 0;
    DWORD dw = 0;
    DWORD dwt = 0;

    switch (addr.area) {
        case PDA_INPUT: {
            b1 = process->in[addr.byteAddr];
            b2 = process->in[addr.byteAddr+1];
            b3 = process->in[addr.byteAddr+2];
            b4 = process->in[addr.byteAddr+3];
        } break;
        case PDA_OUTPUT: {
            b1 = process->out[addr.byteAddr];
            b2 = process->out[addr.byteAddr+1];
            b3 = process->out[addr.byteAddr+2];
            b4 = process->out[addr.byteAddr+3];
        } break;
        case PDA_MEMORY: {
            b1 = process->mem[addr.byteAddr];
            b2 = process->mem[addr.byteAddr+1];
            b3 = process->mem[addr.byteAddr+2];
            b4 = process->mem[addr.byteAddr+3];
        } break;
        default: throw DriverException("Wrong address area", "ShmProcessData::getDWord"); break;
    }

    // Highest word
    w2 = b4;
    w2 = w2 << 8;
    wt = b3;
    w2 = (w2 | wt);

    // Lower word
    w1 = b2;
    w1 = w1 << 8;
    wt = b1;
    w1 = (w1 | wt);

    // Dword
    dw = w2;
    dw = dw << 16;
    dwt = w1;
    dw = (dw | dwt);

    return dw;
}

int ShmProcessData::getInt(processDataAddress addr) const {

    // Check bit address
    DriverUtils::checkBitAddress(addr);

    // Check byte address
    if (addr.byteAddr >= PROCESS_DT_SIZE-3) {

    	throw DriverException("Byte address is out of range", "ShmProcessData::getInt");
    }

    // Get int
    int* v = 0;

    switch (addr.area) {
        case PDA_INPUT: v = (int*)&process->in[addr.byteAddr]; break;
        case PDA_OUTPUT: v = (int*)&process->out[addr.byteAddr]; break;
        case PDA_MEMORY: v = (int*)&process->mem[addr.byteAddr]; break;
        default: throw DriverException("Wrong address area", "ShmProcessData::getInt"); break;
    }

    return *v;
}

float ShmProcessData::getReal(processDataAddress addr) const {

    // Check bit address
    DriverUtils::checkBitAddress(addr);

    // Check byte address
    if (addr.byteAddr >= PROCESS_DT_SIZE-3) {

    	throw DriverException("Byte address is out of range", "ShmProcessData::getReal");
    }

    // Get float
    float f = 0;

    switch (addr.area) {
    	case PDA_INPUT: memcpy(&f, &process->in[addr.byteAddr], sizeof f); break;
    	case PDA_OUTPUT: memcpy(&f, &process->out[addr.byteAddr], sizeof f); break;
    	case PDA_MEMORY: memcpy(&f, &process->mem[addr.byteAddr], sizeof f); break;
        default: throw DriverException("Wrong address area", "ShmProcessData::getReal"); break;
    }

    return f;
}

void ShmProcessData::clear() {

	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		process->in[i] = 0;
		process->out[i] = 0;
		process->mem[i] = 0;
	}
}
