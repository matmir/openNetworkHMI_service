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

#include "DriverManager.h"
#include "SHM/ShmDriver.h"
#include "Modbus/ModbusDriver.h"

using namespace onh;

DriverManager::DriverManager(const std::vector<DriverConnection>& dcv)
{
	// Check drivers count
	if (dcv.size() == 0) {
		throw Exception("Missing driver configuration", "DriverManager::DriverManager");
	}

	driver.clear();
	driverBuffer.clear();

	// Create drivers
	for (const DriverConnection& driverConn : dcv) {

		// SHM driver
		if (driverConn.getType() == DriverType::DT_SHM) {

			// Create SHM driver
			driver.insert(std::pair<unsigned int, Driver*>(driverConn.getId(), new ShmDriver(driverConn.getShmCfg(), driverConn.getId())));

		} else if (driverConn.getType() == DriverType::DT_Modbus) {

			// Create Modbus driver
			Driver* drv = new ModbusDriver(driverConn.getModbusCfg(), driverConn.getId());
			driver.insert(std::pair<unsigned int, Driver*>(driverConn.getId(), drv));

			// Create Modbus driver buffer
			DriverBufferData dbd;
			dbd.connId = driverConn.getId();
			dbd.updateInterval = driverConn.getModbusCfg().polling;
			dbd.buff = drv->getBuffer();
			driverBuffer.push_back(dbd);
		}
	}
}

DriverManager::~DriverManager() {

	for (auto& drv : driver) {
		delete drv.second;
	}

	for (unsigned int i=0; i<driverBuffer.size(); ++i) {
		delete driverBuffer[i].buff;
	}
}

std::vector<ProcessUpdaterData> DriverManager::getProcessUpdaters() {

	std::vector<ProcessUpdaterData> ret;

	// Prepare all driver updaters
	for (const auto& drv : driver) {

		ret.push_back(ProcessUpdaterData{drv.first, ProcessUpdater(drv.second->getUpdater())});
	}

	return ret;
}

ProcessReader DriverManager::getProcessReader() {

	ProcessReader pr;

	// Add all driver readers
	for (const auto& drv : driver) {

		pr.addReader(drv.first, drv.second->getReader());
	}

	return pr;
}

ProcessWriter DriverManager::getProcessWriter() {

	ProcessWriter pw;

	// Add all driver readers
	for (const auto& drv : driver) {

		pw.addWriter(drv.first, drv.second->getWriter());
	}

	return pw;
}

std::vector<DriverBufferUpdaterData> DriverManager::getDriverBufferUpdaters() {

	std::vector<DriverBufferUpdaterData> ret;

	// Prepare all driver updaters
	for (const DriverBufferData& dBuff : driverBuffer) {

		ret.push_back(DriverBufferUpdaterData{dBuff.connId, dBuff.updateInterval, DriverBufferUpdater(dBuff.buff)});
	}

	return ret;
}
