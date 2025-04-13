/**
 * This file is part of openNetworkHMI.
 * Copyright (c) 2025 Mateusz Mirosławski.
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

#include <chrono>
#include <thread>
#include "ModbusDriver.h"
#include "ModbusUpdater.h"
#include "ModbusUtils.h"
#include "ModbusProcessReader.h"
#include "ModbusProcessWriter.h"
#include "ModbusProcessUpdater.h"

namespace {
	// Reconnect wait time (seconds)
	constexpr int MB_RECONNECT_TIME = 10;
}

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
	modbus = std::make_shared<modbusM::ModbusMaster>(cfg);
	getLog() << LOG_INFO("ModbusDriver initialized");

	// Initialize registers
	ModbusProcessData clearProcess(regCount);
	maxByteCount = clearProcess.getMaxByte();
	process = std::make_unique<GuardDataContainer<ModbusProcessData>>(clearProcess);
	buff = std::make_unique<GuardDataContainer<ModbusProcessData>>(clearProcess);

	getLog() << LOG_INFO("Process registers prepared");
}

ModbusDriver::~ModbusDriver() {
	if (modbus) {
		modbus->disconnect();
	}

	getLog() << LOG_INFO("ModbusDriver driver closed");
}

void ModbusDriver::triggerError(const std::string& msg,
		const std::string& fName) {
	getLog() << LOG_ERROR(fName << ": " << msg);
	throw DriverException(msg, fName);
}

void ModbusDriver::connect() {
	bool connected = false;

	while (!connected)
	{
		try {
			// Connect to the controller
			getLog() << LOG_INFO("Connecting to the controller...");
			modbus->connect();
			connected = true;
		} catch (modbusM::ModbusException &e) {
			getLog() << LOG_ERROR("Driver not connected - reconnecting");
			std::this_thread::sleep_for(std::chrono::seconds(MB_RECONNECT_TIME));
		}
	}

	getLog() << LOG_INFO("Connected");
}

DriverBufferPtr ModbusDriver::getBuffer() {
	return DriverBufferPtr(new ModbusUpdater(modbus, driverLock.getAccess(), buff->getController(false)));
}

DriverProcessReaderPtr ModbusDriver::getReader() {
	return DriverProcessReaderPtr(new ModbusProcessReader(process->getController()));
}

DriverProcessWriterPtr ModbusDriver::getWriter() {
	return DriverProcessWriterPtr(new ModbusProcessWriter(modbus, driverLock.getAccess(), maxByteCount));
}

DriverProcessUpdaterPtr ModbusDriver::getUpdater() {
	return DriverProcessUpdaterPtr(new ModbusProcessUpdater(buff->getController(), process->getController(false)));
}

}  // namespace onh
