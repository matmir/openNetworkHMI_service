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

#include "ModbusTCPUpdater.h"
#include <iostream>

using namespace onh;

ModbusTCPUpdater::ModbusTCPUpdater():
    driver(0), regCount(0)
{
    buff.holdingReg = 0;
    buff.inputReg = 0;

    tempBuff.holdingReg = 0;
    tempBuff.inputReg = 0;
}

ModbusTCPUpdater::ModbusTCPUpdater(const ModbusTCPUpdater &mtu) {

    driver = mtu.driver;
    regCount = mtu.regCount;

    // Copy buffer pointers
    buff.holdingReg = mtu.buff.holdingReg;
    buff.inputReg = mtu.buff.inputReg;

    // Prepare temporary buffers
    tempBuff.holdingReg = new WORD[regCount];
    tempBuff.inputReg = new WORD[regCount];

    // Copy lock protections
    driverLock = mtu.driverLock;
    bufferLock = mtu.bufferLock;
}

ModbusTCPUpdater::ModbusTCPUpdater(modbusTCP::ModbusTCPMaster* drv,
                                   ModbusTCPProcessData buffH,
                                   WORD cnt,
                                   const MutexAccess &malDriver,
                                   const MutexAccess &malBuff)
{
    driver = drv;
    regCount = cnt;

    // Copy buffer pointers
    buff.holdingReg = buffH.holdingReg;
    buff.inputReg = buffH.inputReg;

    // Prepare temporary buffers
    tempBuff.holdingReg = new WORD[regCount];
    tempBuff.inputReg = new WORD[regCount];

    // Copy lock protections
    driverLock = malDriver;
    bufferLock = malBuff;
}

ModbusTCPUpdater::~ModbusTCPUpdater()
{
    if (tempBuff.holdingReg)
        delete [] tempBuff.holdingReg;

    if (tempBuff.inputReg)
        delete [] tempBuff.inputReg;
}

ModbusTCPUpdater& ModbusTCPUpdater::operator=(const ModbusTCPUpdater &mtu) {

    driver = mtu.driver;
    regCount = mtu.regCount;

    // Copy buffer pointers
    buff.holdingReg = mtu.buff.holdingReg;
    buff.inputReg = mtu.buff.inputReg;

    // Prepare temporary buffers
    if (tempBuff.holdingReg)
        delete [] tempBuff.holdingReg;

    if (tempBuff.inputReg)
        delete [] tempBuff.inputReg;

    tempBuff.holdingReg = new WORD[regCount];
    tempBuff.inputReg = new WORD[regCount];

    // Copy lock protections
    driverLock = mtu.driverLock;
    bufferLock = mtu.bufferLock;

    return *this;
}

void ModbusTCPUpdater::updateBuffer() {

    // Clear load buffers
    clearTempRegisters();

    driverLock.lock();

    try {

        // Read input registers
        driver->READ_INPUT_REGISTERS(0x00, regCount, tempBuff.inputReg);

        // Read holding registers
        driver->READ_HOLDING_REGISTERS(0x00, regCount, tempBuff.holdingReg);

    } catch (modbusTCP::ModbusTCPException &e) {

        driverLock.unlock();

        throw DriverException(e.what(), "ModbusTCPUpdater::updateBuffer");

    }

    driverLock.unlock();

    // Copy loaded data to the buffer
    copyTempRegistersToBuffer();

}

void ModbusTCPUpdater::clearTempRegisters() {

    // Clear registers
    for (int i=0; i<regCount; ++i) {
        tempBuff.holdingReg[i] = 0;
        tempBuff.inputReg[i] = 0;
    }
}

void ModbusTCPUpdater::copyTempRegistersToBuffer() {

    bufferLock.lock();

    // Check buffers
    if (!buff.holdingReg) {
        throw DriverException("Buffers for holding registers not initialized", "ModbusTCPUpdater::copyTempRegistersToBuffer");
    }
    if (!buff.inputReg) {
        throw DriverException("Buffers for input registers not initialized", "ModbusTCPUpdater::copyTempRegistersToBuffer");
    }

    // Copy data from load registers to the buffer
    for (int i=0; i<regCount; ++i) {
        buff.holdingReg[i] = tempBuff.holdingReg[i];
        buff.inputReg[i] = tempBuff.inputReg[i];
    }

    bufferLock.unlock();
}
