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

#include "ModbusDriver.h"
#include "ModbusUpdater.h"
#include "ModbusUtils.h"
#include <iostream>

using namespace onh;

ModbusDriver::ModbusDriver(const modbusM::ModbusCfg& cfg):
	Driver("modbus_"), regCount(cfg.registerCount), maxByteCount(0), processDT(cfg.registerCount)
{
	// Check registers count
	if (regCount < 1) {
		triggerError("Register count need to be greater than 0", "ModbusDriver::ModbusDriver");
	}

	// Create Modbus protocol
	modbus = new modbusM::ModbusMaster(cfg);
	getLog().write("ModbusDriver initialized");

	// Initialize registers
	buff.holdingReg = new WORD[regCount];
	buff.inputReg = new WORD[regCount];
	// Clear registers
	for (int i=0; i<regCount; ++i) {
		buff.holdingReg[i] = 0;
		buff.inputReg[i] = 0;
	}
	getLog().write("ModbusDriver::init: Process registers prepared");

	// Max Byte count
	maxByteCount = regCount*2;

	// Connect to the controller
	connect();
}

ModbusDriver::~ModbusDriver()
{
	getLog().write("ModbusDriver driver closed");

    if (modbus)
        delete modbus;

    if (buff.holdingReg)
        delete [] buff.holdingReg;

    if (buff.inputReg)
        delete [] buff.inputReg;
}

void ModbusDriver::triggerError(const std::string& msg, const std::string& fName) {

    std::string s = fName + ": " + msg;
    getLog().write(s);
    throw DriverException(msg, fName);
}

void ModbusDriver::connect() {

	try {

		// Connect to the controller
		getLog().write("ModbusDriver::init: Connecting to the controller...");
		modbus->connect();
		getLog().write("ModbusDriver::init: Connected");

	} catch (modbusM::ModbusException &e) {

		triggerError(e.what(), "ModbusDriver::init:");
	}
}

void ModbusDriver::updateProcessData() {

    bufferLock.lock();

    // Copy data from buffer registers to the process data registers
    processDT.update(buff);

    bufferLock.unlock();
}

void ModbusDriver::setBit(processDataAddress addr) {

    // Check process address
	ModbusUtils::checkProcessAddress(addr, maxByteCount, 0, true);

    // Reg address
    WORD regAddr = ModbusUtils::getRegisterAddress(addr);

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

    } catch (modbusM::ModbusException &e) {
        modbusLock.unlock();

        triggerError(e.what(), "ModbusDriver::setBit");
    }

    modbusLock.unlock();
}

void ModbusDriver::resetBit(processDataAddress addr) {

    // Check process address
    ModbusUtils::checkProcessAddress(addr, maxByteCount, 0, true);

    // Reg address
    WORD regAddr = ModbusUtils::getRegisterAddress(addr);

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

    } catch (modbusM::ModbusException &e) {
        modbusLock.unlock();

        triggerError(e.what(), "ModbusDriver::resetBit");
    }

    modbusLock.unlock();
}

void ModbusDriver::invertBit(processDataAddress addr) {

    // Check process address
    ModbusUtils::checkProcessAddress(addr, maxByteCount, 0, true);

    // Reg address
    WORD regAddr = ModbusUtils::getRegisterAddress(addr);

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

    } catch (modbusM::ModbusException &e) {
        modbusLock.unlock();

        triggerError(e.what(), "ModbusDriver::invertBit");
    }

    modbusLock.unlock();
}

void ModbusDriver::setBits(std::vector<processDataAddress> addr) {

    for (unsigned int i=0; i<addr.size(); ++i) {

        // Set one bit
        setBit(addr[i]);
    }
}

void ModbusDriver::writeByte(processDataAddress addr, BYTE val) {

    // Check process address
    ModbusUtils::checkProcessAddress(addr, maxByteCount, 0, true);

    // Reg address
    WORD regAddr = ModbusUtils::getRegisterAddress(addr);

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

    } catch (modbusM::ModbusException &e) {
        modbusLock.unlock();

        triggerError(e.what(), "ModbusDriver::writeByte");
    }

    modbusLock.unlock();
}

void ModbusDriver::writeWord(processDataAddress addr, WORD val) {

    // Check process address
    ModbusUtils::checkProcessAddress(addr, maxByteCount, 1, true);

    // Reg address
    WORD regAddr = ModbusUtils::getRegisterAddress(addr);

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

    } catch (modbusM::ModbusException &e) {
        modbusLock.unlock();

        triggerError(e.what(), "ModbusDriver::writeWord");
    }

    modbusLock.unlock();
}

void ModbusDriver::writeDWord(processDataAddress addr, DWORD val) {

    // Check process address
    ModbusUtils::checkProcessAddress(addr, maxByteCount, 3, true);

    // Reg address
    WORD regAddr = ModbusUtils::getRegisterAddress(addr);

    // Modbus registers
    WORD reg[2] = {0};

    modbusLock.lock();

    try {

        // Update registers
        reg[0] = val & 0x0000FFFF;
        reg[1] = ((val & 0xFFFF0000) >> 16);

        // Write register
        modbus->WRITE_MULTIPLE_REGISTERS(regAddr, 2, reg);

    } catch (modbusM::ModbusException &e) {
        modbusLock.unlock();

        triggerError(e.what(), "ModbusDriver::writeDWord");
    }

    modbusLock.unlock();
}

void ModbusDriver::writeInt(processDataAddress addr, int val) {

    // Check process address
    ModbusUtils::checkProcessAddress(addr, maxByteCount, 3, true);

    // Reg address
    WORD regAddr = ModbusUtils::getRegisterAddress(addr);

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

    } catch (modbusM::ModbusException &e) {
        modbusLock.unlock();

        triggerError(e.what(), "ModbusDriver::writeInt");
    }

    modbusLock.unlock();
}

void ModbusDriver::writeReal(processDataAddress addr, float val) {

    // Check process address
    ModbusUtils::checkProcessAddress(addr, maxByteCount, 3, true);

    // Reg address
    WORD regAddr = ModbusUtils::getRegisterAddress(addr);

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

    } catch (modbusM::ModbusException &e) {
        modbusLock.unlock();

        triggerError(e.what(), "ModbusDriver::writeReal");
    }

    modbusLock.unlock();
}

DriverBuffer* ModbusDriver::getBuffer() {

    return new ModbusUpdater(
                    modbus,
                    buff,
                    regCount,
                    modbusLock.getAccess(),
                    bufferLock.getAccess()
    );

}

DriverProcessReader* ModbusDriver::getReader() {

	return new ModbusProcessReader(processDT.getController());
}
