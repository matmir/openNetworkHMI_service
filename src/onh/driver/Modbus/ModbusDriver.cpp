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

#include "ModbusDriver.h"
#include "ModbusUpdater.h"
#include "ModbusUtils.h"
#include "ModbusProcessReader.h"
#include "ModbusProcessWriter.h"
#include "ModbusProcessUpdater.h"

namespace onh {

ModbusDriver::ModbusDriver(const modbusM::ModbusCfg& cfg, unsigned int connId):
	Driver("modbus_"+std::to_string(connId)+"_"),
	regCount(cfg.registerCount),
	maxByteCount(0),
	process(nullptr),
	buff(nullptr),
	modbus(nullptr) {
	// Check registers count
	if (regCount < 1) {
		triggerError("Register count need to be greater than 0",
						"ModbusDriver::ModbusDriver");
	}

	// Create Modbus protocol
	modbus = new modbusM::ModbusMaster(cfg);
	getLog().write("ModbusDriver initialized");

	// Initialize registers
	ModbusProcessData clearProcess(regCount);
	maxByteCount = clearProcess.getMaxByte();
	process = new GuardDataContainer<ModbusProcessData>(clearProcess);
	buff = new GuardDataContainer<ModbusProcessData>(clearProcess);

	getLog().write("ModbusDriver::init: Process registers prepared");

	// Connect to the controller
	connect();
}

ModbusDriver::~ModbusDriver() {
	getLog().write("ModbusDriver driver closed");

	if (modbus) {
		modbus->disconnect();
		delete modbus;
	}

	if (buff)
		delete buff;

	if (process)
		delete process;
}

void ModbusDriver::triggerError(const std::string& msg,
		const std::string& fName) {
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

DriverBuffer* ModbusDriver::getBuffer() {
	return new ModbusUpdater(
					modbus,
					driverLock.getAccess(),
					buff->getController(false)
	);
}

DriverProcessReader* ModbusDriver::getReader() {
	return new ModbusProcessReader(process->getController());
}

DriverProcessWriter* ModbusDriver::getWriter() {
	return new ModbusProcessWriter(modbus, driverLock.getAccess(), maxByteCount);
}

DriverProcessUpdater* ModbusDriver::getUpdater() {
	return new ModbusProcessUpdater(buff->getController(), process->getController(false));
}

}  // namespace onh
