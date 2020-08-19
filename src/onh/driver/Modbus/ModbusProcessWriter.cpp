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

#include "ModbusProcessWriter.h"
#include "../DriverUtils.h"
#include "ModbusUtils.h"
#include "../DriverException.h"

using namespace onh;

ModbusProcessWriter::ModbusProcessWriter(modbusM::ModbusMaster *mbus, const MutexAccess& lock, unsigned int maxBytes):
	modbus(mbus), driverLock(lock), maxByteCount(maxBytes)
{
}

ModbusProcessWriter::~ModbusProcessWriter() {
}

void ModbusProcessWriter::setBit(processDataAddress addr) {

    driverLock.lock();

    try {
    	// Check Modbus
    	if (!modbus) {
    		throw DriverException("Modbus protocol is not initialized", "ModbusProcessWriter::setBit");
    	}

    	// Check process address
		ModbusUtils::checkProcessAddress(addr, maxByteCount, 0, true);

		// Reg address
		WORD regAddr = ModbusUtils::getRegisterAddress(addr);

		// Modbus register
		WORD reg = 0;

        // Read current status of the register
        modbus->READ_HOLDING_REGISTERS(regAddr, 1, &reg);

        // Calculate bit position in WORD register
        BYTE bitPos = (addr.byteAddr % 2)?(addr.bitAddr+8):(addr.bitAddr);

        // Update register
        reg |= (1 << bitPos);

        // Write register
        modbus->WRITE_SINGLE_REGISTER(regAddr, reg);

        driverLock.unlock();

    } catch (modbusM::ModbusException &e) {
    	driverLock.unlock();

        throw DriverException(e.what(), "ModbusProcessWriter::setBit");
    } catch (...) {
    	driverLock.unlock();

    	throw;
    }
}

void ModbusProcessWriter::resetBit(processDataAddress addr) {

	driverLock.lock();

	try {
		// Check Modbus
		if (!modbus) {
			throw DriverException("Modbus protocol is not initialized", "ModbusProcessWriter::resetBit");
		}

		// Check process address
		ModbusUtils::checkProcessAddress(addr, maxByteCount, 0, true);

		// Reg address
		WORD regAddr = ModbusUtils::getRegisterAddress(addr);

		// Modbus register
		WORD reg = 0;

        // Read current status of the register
        modbus->READ_HOLDING_REGISTERS(regAddr, 1, &reg);

        // Calculate bit position in WORD register
        BYTE bitPos = (addr.byteAddr % 2)?(addr.bitAddr+8):(addr.bitAddr);

        // Update register
        reg &= ~(1 << bitPos);

        // Write register
        modbus->WRITE_SINGLE_REGISTER(regAddr, reg);

        driverLock.unlock();

    } catch (modbusM::ModbusException &e) {
    	driverLock.unlock();

    	throw DriverException(e.what(), "ModbusProcessWriter::resetBit");
    } catch (...) {
    	driverLock.unlock();

    	throw;
    }
}

void ModbusProcessWriter::invertBit(processDataAddress addr) {

	driverLock.lock();

	try {
		// Check Modbus
		if (!modbus) {
			throw DriverException("Modbus protocol is not initialized", "ModbusProcessWriter::invertBit");
		}

		// Check process address
		ModbusUtils::checkProcessAddress(addr, maxByteCount, 0, true);

		// Reg address
		WORD regAddr = ModbusUtils::getRegisterAddress(addr);

		// Modbus register
		WORD reg = 0;

        // Read current status of the register
        modbus->READ_HOLDING_REGISTERS(regAddr, 1, &reg);

        // Calculate bit position in WORD register
        BYTE bitPos = (addr.byteAddr % 2)?(addr.bitAddr+8):(addr.bitAddr);

        // Update register
        reg ^= (1 << bitPos);

        // Write register
        modbus->WRITE_SINGLE_REGISTER(regAddr, reg);

        driverLock.unlock();

    } catch (modbusM::ModbusException &e) {
    	driverLock.unlock();

    	throw DriverException(e.what(), "ModbusProcessWriter::invertBit");
    } catch (...) {
    	driverLock.unlock();

    	throw;
    }
}

void ModbusProcessWriter::setBits(std::vector<processDataAddress> addr) {

    for (unsigned int i=0; i<addr.size(); ++i) {

        // Set one bit
        setBit(addr[i]);
    }
}

void ModbusProcessWriter::writeByte(processDataAddress addr, BYTE val) {

	driverLock.lock();

	try {
		// Check Modbus
		if (!modbus) {
			throw DriverException("Modbus protocol is not initialized", "ModbusProcessWriter::writeByte");
		}

		// Check process address
		ModbusUtils::checkProcessAddress(addr, maxByteCount, 0, true);

		// Reg address
		WORD regAddr = ModbusUtils::getRegisterAddress(addr);

		// Modbus register
		WORD reg = 0;

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

        driverLock.unlock();

    } catch (modbusM::ModbusException &e) {
    	driverLock.unlock();

    	throw DriverException(e.what(), "ModbusProcessWriter::writeByte");
    } catch (...) {
    	driverLock.unlock();

    	throw;
    }
}

void ModbusProcessWriter::writeWord(processDataAddress addr, WORD val) {

	driverLock.lock();

	try {
		// Check Modbus
		if (!modbus) {
			throw DriverException("Modbus protocol is not initialized", "ModbusProcessWriter::writeWord");
		}

		// Check process address
		ModbusUtils::checkProcessAddress(addr, maxByteCount, 1, true);

		// Reg address
		WORD regAddr = ModbusUtils::getRegisterAddress(addr);

		// Modbus register
		WORD reg = 0;

        // Read current status of the register
        modbus->READ_HOLDING_REGISTERS(regAddr, 1, &reg);

        // Update register
        reg = val;

        // Write register
        modbus->WRITE_SINGLE_REGISTER(regAddr, reg);

        driverLock.unlock();

    } catch (modbusM::ModbusException &e) {
    	driverLock.unlock();

    	throw DriverException(e.what(), "ModbusProcessWriter::writeWord");
    } catch (...) {
    	driverLock.unlock();

    	throw;
    }
}

void ModbusProcessWriter::writeDWord(processDataAddress addr, DWORD val) {

	driverLock.lock();

	try {
		// Check Modbus
		if (!modbus) {
			throw DriverException("Modbus protocol is not initialized", "ModbusProcessWriter::writeDWord");
		}

		// Check process address
		ModbusUtils::checkProcessAddress(addr, maxByteCount, 3, true);

		// Reg address
		WORD regAddr = ModbusUtils::getRegisterAddress(addr);

		// Modbus registers
		WORD reg[2] = {0};

        // Update registers
        reg[0] = val & 0x0000FFFF;
        reg[1] = ((val & 0xFFFF0000) >> 16);

        // Write register
        modbus->WRITE_MULTIPLE_REGISTERS(regAddr, 2, reg);

        driverLock.unlock();

    } catch (modbusM::ModbusException &e) {
    	driverLock.unlock();

    	throw DriverException(e.what(), "ModbusProcessWriter::writeDWord");
    } catch (...) {
    	driverLock.unlock();

    	throw;
    }
}

void ModbusProcessWriter::writeInt(processDataAddress addr, int val) {

	driverLock.lock();

	try {
		// Check Modbus
		if (!modbus) {
			throw DriverException("Modbus protocol is not initialized", "ModbusProcessWriter::writeInt");
		}

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

        // Write registers
        modbus->WRITE_MULTIPLE_REGISTERS(regAddr, 2, reg);

        driverLock.unlock();

    } catch (modbusM::ModbusException &e) {
    	driverLock.unlock();

    	throw DriverException(e.what(), "ModbusProcessWriter::writeInt");
    } catch (...) {
    	driverLock.unlock();

    	throw;
    }
}

void ModbusProcessWriter::writeReal(processDataAddress addr, float val) {

	driverLock.lock();

	try {
		// Check Modbus
		if (!modbus) {
			throw DriverException("Modbus protocol is not initialized", "ModbusProcessWriter::writeReal");
		}

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

        // Write registers
        modbus->WRITE_MULTIPLE_REGISTERS(regAddr, 2, reg);

        driverLock.unlock();

    } catch (modbusM::ModbusException &e) {
    	driverLock.unlock();

    	throw DriverException(e.what(), "ModbusProcessWriter::writeReal");
    } catch (...) {
    	driverLock.unlock();

    	throw;
    }
}

DriverProcessWriter* ModbusProcessWriter::createNew() {

	return new ModbusProcessWriter(modbus, driverLock, maxByteCount);
}
