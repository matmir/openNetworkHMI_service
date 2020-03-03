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

#include "ModbusTCP.h"
#include "ModbusTCPUpdater.h"
#include "ModbusTCPUtils.h"
#include <iostream>

using namespace onh;

ModbusTCP::ModbusTCP(const std::string& addr, WORD registersCount, BYTE slaveId, int port):
	Driver("modbus_"), regCount(registersCount), maxByteCount(0), processDT(registersCount)
{
	// Check registers count
	if (regCount < 1) {
		triggerError("Register count need to be greater than 0", "ModbusTCP::ModbusTCP");
	}

	// Create Modbus protocol
	modbus = new modbusTCP::ModbusTCPMaster(addr, slaveId, port);
	getLog().write("ModbusTCP initialized");

	// Initialize registers
	buff.holdingReg = new WORD[regCount];
	buff.inputReg = new WORD[regCount];
	// Clear registers
	for (int i=0; i<regCount; ++i) {
		buff.holdingReg[i] = 0;
		buff.inputReg[i] = 0;
	}
	getLog().write("ModbusTCP::init: Process registers prepared");

	// Max Byte count
	maxByteCount = regCount*2;

	// Connect to the controller
	connect();
}

ModbusTCP::~ModbusTCP()
{
	getLog().write("ModbusTCP driver closed");

    if (modbus)
        delete modbus;

    if (buff.holdingReg)
        delete [] buff.holdingReg;

    if (buff.inputReg)
        delete [] buff.inputReg;
}

void ModbusTCP::triggerError(const std::string& msg, const std::string& fName) {

    std::string s = fName + ": " + msg;
    getLog().write(s);
    throw DriverException(msg, fName);
}

void ModbusTCP::connect() {

	try {

		// Connect to the controller
		getLog().write("ModbusTCP::init: Connecting to the controller...");
		modbus->connect();
		getLog().write("ModbusTCP::init: Connected");

	} catch (modbusTCP::ModbusTCPException &e) {

		triggerError(e.what(), "ModbusTCP::init:");
	}
}

void ModbusTCP::updateProcessData() {

    bufferLock.lock();

    // Copy data from buffer registers to the process data registers
    processDT.update(buff);

    bufferLock.unlock();
}

void ModbusTCP::setBit(processDataAddress addr) {

    // Check process address
	ModbusTCPUtils::ModbusTCPUtils::checkProcessAddress(addr, maxByteCount, 0, true);

    // Reg address
    WORD regAddr = ModbusTCPUtils::getRegisterAddress(addr);

    // Modbus register
    WORD reg = 0;

    modbusLock.lock();

    try {

        // Read current status of the register
        modbus->READ_HOLDING_REGISTERS(regAddr, 1, &reg);

        // Calculate bit position in WORD register
        BYTE bitPos = (addr.byteAddr % 2)?(addr.bitAddr+8):(addr.bitAddr);

        // Update register
        reg |= (1 << bitPos);

        // Write register
        modbus->WRITE_SINGLE_REGISTER(regAddr, reg);

    } catch (modbusTCP::ModbusTCPException &e) {
        modbusLock.unlock();

        triggerError(e.what(), "ModbusTCP::setBit");
    }

    modbusLock.unlock();
}

void ModbusTCP::resetBit(processDataAddress addr) {

    // Check process address
    ModbusTCPUtils::checkProcessAddress(addr, maxByteCount, 0, true);

    // Reg address
    WORD regAddr = ModbusTCPUtils::getRegisterAddress(addr);

    // Modbus register
    WORD reg = 0;

    modbusLock.lock();

    try {

        // Read current status of the register
        modbus->READ_HOLDING_REGISTERS(regAddr, 1, &reg);

        // Calculate bit position in WORD register
        BYTE bitPos = (addr.byteAddr % 2)?(addr.bitAddr+8):(addr.bitAddr);

        // Update register
        reg &= ~(1 << bitPos);

        // Write register
        modbus->WRITE_SINGLE_REGISTER(regAddr, reg);

    } catch (modbusTCP::ModbusTCPException &e) {
        modbusLock.unlock();

        triggerError(e.what(), "ModbusTCP::resetBit");
    }

    modbusLock.unlock();
}

void ModbusTCP::invertBit(processDataAddress addr) {

    // Check process address
    ModbusTCPUtils::checkProcessAddress(addr, maxByteCount, 0, true);

    // Reg address
    WORD regAddr = ModbusTCPUtils::getRegisterAddress(addr);

    // Modbus register
    WORD reg = 0;

    modbusLock.lock();

    try {

        // Read current status of the register
        modbus->READ_HOLDING_REGISTERS(regAddr, 1, &reg);

        // Calculate bit position in WORD register
        BYTE bitPos = (addr.byteAddr % 2)?(addr.bitAddr+8):(addr.bitAddr);

        // Update register
        reg ^= (1 << bitPos);

        // Write register
        modbus->WRITE_SINGLE_REGISTER(regAddr, reg);

    } catch (modbusTCP::ModbusTCPException &e) {
        modbusLock.unlock();

        triggerError(e.what(), "ModbusTCP::invertBit");
    }

    modbusLock.unlock();
}

void ModbusTCP::setBits(std::vector<processDataAddress> addr) {

    for (unsigned int i=0; i<addr.size(); ++i) {

        // Set one bit
        setBit(addr[i]);
    }
}

void ModbusTCP::writeByte(processDataAddress addr, BYTE val) {

    // Check process address
    ModbusTCPUtils::checkProcessAddress(addr, maxByteCount, 0, true);

    // Reg address
    WORD regAddr = ModbusTCPUtils::getRegisterAddress(addr);

    // Modbus register
    WORD reg = 0;

    modbusLock.lock();

    try {

        // Read current status of the register
        modbus->READ_HOLDING_REGISTERS(regAddr, 1, &reg);

        // Low byte of the register
        BYTE bLO = reg & 0x00FF;
        // High byte of the register
        BYTE bHI = (reg & 0xFF00) >> 8;

        // Update byte
        if (addr.byteAddr % 2) {
            bHI = val;
        } else {
            bLO = val;
        }

        // Update register
        reg = bHI;
        reg = reg << 8;
        reg = (reg | bLO);

        // Write register
        modbus->WRITE_SINGLE_REGISTER(regAddr, reg);

    } catch (modbusTCP::ModbusTCPException &e) {
        modbusLock.unlock();

        triggerError(e.what(), "ModbusTCP::writeByte");
    }

    modbusLock.unlock();
}

void ModbusTCP::writeWord(processDataAddress addr, WORD val) {

    // Check process address
    ModbusTCPUtils::checkProcessAddress(addr, maxByteCount, 1, true);

    // Reg address
    WORD regAddr = ModbusTCPUtils::getRegisterAddress(addr);

    // Modbus register
    WORD reg = 0;

    modbusLock.lock();

    try {

        // Read current status of the register
        modbus->READ_HOLDING_REGISTERS(regAddr, 1, &reg);

        // Update register
        reg = val;

        // Write register
        modbus->WRITE_SINGLE_REGISTER(regAddr, reg);

    } catch (modbusTCP::ModbusTCPException &e) {
        modbusLock.unlock();

        triggerError(e.what(), "ModbusTCP::writeWord");
    }

    modbusLock.unlock();
}

void ModbusTCP::writeDWord(processDataAddress addr, DWORD val) {

    // Check process address
    ModbusTCPUtils::checkProcessAddress(addr, maxByteCount, 3, true);

    // Reg address
    WORD regAddr = ModbusTCPUtils::getRegisterAddress(addr);

    // Modbus registers
    WORD reg[2] = {0};

    modbusLock.lock();

    try {

        // Update registers
        reg[0] = val & 0x0000FFFF;
        reg[1] = ((val & 0xFFFF0000) >> 16);

        // Write register
        modbus->WRITE_MULTIPLE_REGISTERS(regAddr, 2, reg);

    } catch (modbusTCP::ModbusTCPException &e) {
        modbusLock.unlock();

        triggerError(e.what(), "ModbusTCP::writeDWord");
    }

    modbusLock.unlock();
}

void ModbusTCP::writeInt(processDataAddress addr, int val) {

    // Check process address
    ModbusTCPUtils::checkProcessAddress(addr, maxByteCount, 3, true);

    // Reg address
    WORD regAddr = ModbusTCPUtils::getRegisterAddress(addr);

    // Modbus registers
    WORD reg[2] = {0};

    // Pointer to int
    int* v = 0;
    // Point to the register area
    v = (int *)&reg[0];

    // Update register value
    *v = val;

    modbusLock.lock();

    try {

        // Write registers
        modbus->WRITE_MULTIPLE_REGISTERS(regAddr, 2, reg);

    } catch (modbusTCP::ModbusTCPException &e) {
        modbusLock.unlock();

        triggerError(e.what(), "ModbusTCP::writeInt");
    }

    modbusLock.unlock();
}

void ModbusTCP::writeReal(processDataAddress addr, float val) {

    // Check process address
    ModbusTCPUtils::checkProcessAddress(addr, maxByteCount, 3, true);

    // Reg address
    WORD regAddr = ModbusTCPUtils::getRegisterAddress(addr);

    // Modbus registers
    WORD reg[2] = {0};

    // Pointer to float
    float* v = 0;
    // Point to the register area
    v = (float *)&reg[0];

    // Update register value
    memcpy(v, &val, sizeof val);

    modbusLock.lock();

    try {

        // Write registers
        modbus->WRITE_MULTIPLE_REGISTERS(regAddr, 2, reg);

    } catch (modbusTCP::ModbusTCPException &e) {
        modbusLock.unlock();

        triggerError(e.what(), "ModbusTCP::writeReal");
    }

    modbusLock.unlock();
}

DriverBuffer* ModbusTCP::getBuffer() {

    return new ModbusTCPUpdater(
                    modbus,
                    buff,
                    regCount,
                    modbusLock.getAccess(),
                    bufferLock.getAccess()
    );

}

DriverProcessReader* ModbusTCP::getReader() {

	return new ModbusTCPProcessReader(processDT.getController());
}
