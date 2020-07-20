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

#include "ShmProcessReader.h"
#include "../DriverUtils.h"
#include "../DriverException.h"

using namespace onh;

ShmProcessReader::ShmProcessReader(const ShmProcessDataController& spdc):
	driverProcess(spdc)
{
	updateProcessData();
}

ShmProcessReader::~ShmProcessReader() {
}

void ShmProcessReader::triggerError(const std::string& msg, const std::string& fName) {

    throw DriverException(msg, fName);
}

bool ShmProcessReader::getBitValue(processDataAddress addr) {

    // Check bit address
    DriverUtils::checkBitAddress(addr);

    // Check byte address
    if (addr.byteAddr >= PROCESS_DT_SIZE) {

        triggerError("Byte address is out of range", "ShmProcessReader::getBitValue");
    }

    // Get byte
    BYTE b = 0;

    switch (addr.area) {
        case PDA_INPUT: b = process.in[addr.byteAddr]; break;
        case PDA_OUTPUT: b = process.out[addr.byteAddr]; break;
        case PDA_MEMORY: b = process.mem[addr.byteAddr]; break;
        default: triggerError("Wrong address area", "ShmProcessReader::getBitValue"); break;
    }

    // Read bit value
    bool v = (b >> addr.bitAddr & 0x01);

    return v;

}

std::vector<bool> ShmProcessReader::getBitsValue(std::vector<processDataAddress> addr) {

    std::vector<bool> retV;

    for (unsigned int i=0; i<addr.size(); ++i) {

        // Read bit value
        retV.push_back(getBitValue(addr[i]));

    }

    return retV;

}

BYTE ShmProcessReader::getByte(processDataAddress addr) {

    // Check bit address
    DriverUtils::checkBitAddress(addr);

    // Check byte address
    if (addr.byteAddr >= PROCESS_DT_SIZE) {

        triggerError("Byte address is out of range", "ShmProcessReader::getByte");
    }

    // Get byte
    BYTE b = 0;

    switch (addr.area) {
        case PDA_INPUT: b = process.in[addr.byteAddr]; break;
        case PDA_OUTPUT: b = process.out[addr.byteAddr]; break;
        case PDA_MEMORY: b = process.mem[addr.byteAddr]; break;
        default: triggerError("Wrong address area", "ShmProcessReader::getByte"); break;
    }

    return b;

}

WORD ShmProcessReader::getWord(processDataAddress addr) {

    // Check bit address
    DriverUtils::checkBitAddress(addr);

    // Check byte address
    if (addr.byteAddr >= PROCESS_DT_SIZE-1) {

        triggerError("Byte address is out of range", "ShmProcessReader::getWord");
    }

    // Prepare data
    BYTE b1 = 0;
    BYTE b2 = 0;
    WORD w = 0;
    WORD wt = 0;

    switch (addr.area) {
        case PDA_INPUT: {
            b1 = process.in[addr.byteAddr];
            b2 = process.in[addr.byteAddr+1];
        } break;
        case PDA_OUTPUT: {
            b1 = process.out[addr.byteAddr];
            b2 = process.out[addr.byteAddr+1];
        } break;
        case PDA_MEMORY: {
            b1 = process.mem[addr.byteAddr];
            b2 = process.mem[addr.byteAddr+1];
        } break;
        default: triggerError("Wrong address area", "ShmProcessReader::getWord"); break;
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

DWORD ShmProcessReader::getDWord(processDataAddress addr) {

    // Check bit address
    DriverUtils::checkBitAddress(addr);

    // Check byte address
    if (addr.byteAddr >= PROCESS_DT_SIZE-3) {

        triggerError("Byte address is out of range", "ShmProcessReader::getDWord");
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
            b1 = process.in[addr.byteAddr];
            b2 = process.in[addr.byteAddr+1];
            b3 = process.in[addr.byteAddr+2];
            b4 = process.in[addr.byteAddr+3];
        } break;
        case PDA_OUTPUT: {
            b1 = process.out[addr.byteAddr];
            b2 = process.out[addr.byteAddr+1];
            b3 = process.out[addr.byteAddr+2];
            b4 = process.out[addr.byteAddr+3];
        } break;
        case PDA_MEMORY: {
            b1 = process.mem[addr.byteAddr];
            b2 = process.mem[addr.byteAddr+1];
            b3 = process.mem[addr.byteAddr+2];
            b4 = process.mem[addr.byteAddr+3];
        } break;
        default: triggerError("Wrong address area", "ShmProcessReader::getDWord"); break;
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

int ShmProcessReader::getInt(processDataAddress addr) {

    // Check bit address
    DriverUtils::checkBitAddress(addr);

    // Check byte address
    if (addr.byteAddr >= PROCESS_DT_SIZE-3) {

        triggerError("Byte address is out of range", "ShmProcessReader::getInt");
    }

    // Get int
    int* v = 0;

    switch (addr.area) {
        case PDA_INPUT: v = (int*)&process.in[addr.byteAddr]; break;
        case PDA_OUTPUT: v = (int*)&process.out[addr.byteAddr]; break;
        case PDA_MEMORY: v = (int*)&process.mem[addr.byteAddr]; break;
        default: triggerError("Wrong address area", "ShmProcessReader::getInt"); break;
    }

    return *v;

}

float ShmProcessReader::getReal(processDataAddress addr) {

    // Check bit address
    DriverUtils::checkBitAddress(addr);

    // Check byte address
    if (addr.byteAddr >= PROCESS_DT_SIZE-3) {

        triggerError("Byte address is out of range", "ShmProcessReader::getReal");
    }

    // Get float
    float f = 0;

    switch (addr.area) {
    	case PDA_INPUT: memcpy(&f, &process.in[addr.byteAddr], sizeof f); break;
    	case PDA_OUTPUT: memcpy(&f, &process.out[addr.byteAddr], sizeof f); break;
    	case PDA_MEMORY: memcpy(&f, &process.mem[addr.byteAddr], sizeof f); break;
        default: triggerError("Wrong address area", "ShmProcessReader::getReal"); break;
    }

    return f;
}

void ShmProcessReader::updateProcessData() {

	process = driverProcess.getProcessDataCopy();
}

DriverProcessReader* ShmProcessReader::createNew() {

	return new ShmProcessReader(driverProcess);
}
