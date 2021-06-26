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

#include "DriverConnection.h"
#include "../../utils/Exception.h"
#include "../DB.h"

namespace onh {

DriverConnection::DriverConnection():
	dcId(0), dcName(""), dcType(DriverType::DT_SHM), modbus(nullptr), shm(""), dcEnable(false) {
}

DriverConnection::DriverConnection(const DriverConnection& dc):
	dcId(dc.dcId), dcName(dc.dcName), dcType(dc.dcType), modbus(nullptr), shm(dc.shm), dcEnable(dc.dcEnable) {
	if (dc.modbus != nullptr) {
		setModbusCfg(*dc.modbus);
	}
}

DriverConnection::~DriverConnection() {
}

DriverConnection& DriverConnection::operator=(const DriverConnection& dc) {
	if (this == &dc)
		return *this;

	dcId = dc.dcId;
	dcName = dc.dcName;
	dcType = dc.dcType;
	shm = dc.shm;
	dcEnable = dc.dcEnable;

	modbus.reset();

	if (dc.modbus) {
		setModbusCfg(*dc.modbus);
	}

	return *this;
}

void DriverConnection::checkId(unsigned int id) const {
	if (id == 0)
		throw Exception("Invalid Driver connection identifier", "DriverConnection::checkId");
}

void DriverConnection::checkName(const std::string& nm) const {
	// Check empty
	if (nm.size() == 0)
		throw Exception("Driver connection name is empty", "DriverConnection::checkName");

	// Check invalid characters
	if (!DB::checkStringValue(nm))
		throw Exception("Driver connection name contains invalid characters", "DriverConnection::checkName");
}

void DriverConnection::checkType(const DriverType& type) const {
	bool typeOK = false;

	// Check type
	switch (type) {
		case DT_SHM: typeOK = true; break;
		case DT_Modbus: typeOK = true; break;
	}

	if (!typeOK)
		throw Exception("Driver connection has wrong type", "DriverConnection::checkType");
}

unsigned int DriverConnection::getId() const {
	checkId(dcId);

	return dcId;
}

void DriverConnection::setId(unsigned int id) {
	checkId(id);

	dcId = id;
}

std::string DriverConnection::getName() const {
	checkName(dcName);

	return dcName;
}

void DriverConnection::setName(const std::string& nm) {
	checkName(nm);

	dcName = nm;
}

DriverType DriverConnection::getType() const {
	checkType(dcType);

	return dcType;
}

void DriverConnection::setType(const DriverType& type) {
	checkType(type);

	dcType = type;
}

const modbusM::ModbusCfg& DriverConnection::getModbusCfg() const {
	if (dcType != DriverType::DT_Modbus)
			throw Exception("Driver connection wrong driver type", "DriverConnection::getModbusCfg");

	if (modbus == nullptr)
		throw Exception("Driver connection missing modbus configuration", "DriverConnection::getModbusCfg");

	return *modbus;
}

void DriverConnection::setModbusCfg(const modbusM::ModbusCfg& cfg) {
	if (dcType != DriverType::DT_Modbus)
			throw Exception("Driver connection wrong driver type", "DriverConnection::setModbusCfg");

	if (modbus == nullptr)
		modbus = std::make_unique<modbusM::ModbusCfg>();

	*modbus = cfg;
}

void DriverConnection::checkShmCfg(const std::string& cfg) const {
	if (dcType != DriverType::DT_SHM)
		throw Exception("Driver connection wrong driver type", "DriverConnection::checkShmCfg");

	// Check empty
	if (cfg.size() == 0)
		throw Exception("Driver SHM name is empty", "DriverConnection::checkShmCfg");
}

const std::string& DriverConnection::getShmCfg() const {
	checkShmCfg(shm);

	return shm;
}

void DriverConnection::setShmCfg(const std::string& cfg) {
	checkShmCfg(cfg);

	shm = cfg;
}

bool DriverConnection::isEnabled() const {
	return dcEnable;
}

void DriverConnection::setEnable(bool enable) {
	dcEnable = enable;
}

}  // namespace onh
