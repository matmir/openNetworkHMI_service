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

#include "Config.h"
#include <sstream>
#include "../driver/Modbus/modbusmasterCfg.h"

namespace onh {

Config::Config(MYSQL *connDB):
	DB(connDB) {
}

Config::Config(const Config &cDB):
	DB(cDB) {
}

Config::~Config() {
}

std::string Config::getStringValue(const std::string& field) {
	if (field == "")
		throw Exception("Field is empty", "Config::getStringValue");

	DBResult *res = 0;

	// Return value
	std::string val;

	try {
		// Query
		res = executeQuery("SELECT * FROM configuration WHERE cName='"+field+"'");

		// Load data
		res->nextRow();

		// Parse data
		val = res->getString("cValue");
	} catch (DBException &e) {
		std::stringstream s;
		s << "Config::getStringValue (" << field << ")";
		throw Exception(e.what(), s.str());
	}

	// Release memory
	delete res;

	return val;
}

int Config::getIntValue(const std::string& field) {
	if (field == "")
		throw Exception("Field is empty", "Config::getIntValue");

	DBResult *res = 0;

	// Return value
	int iVal;

	try {
		// Query
		res = executeQuery("SELECT * FROM configuration WHERE cName='"+field+"'");

		// Load data
		res->nextRow();

		// Parse data
		iVal = res->getInt("cValue");
	} catch (DBException &e) {
		std::stringstream s;
		s << "Config::getIntValue (" << field << ")";
		throw Exception(e.what(), s.str());
	}

	// Release memory
	delete res;

	return iVal;
}

unsigned int Config::getUIntValue(const std::string& field) {
	if (field == "")
		throw Exception("Field is empty", "Config::getUIntValue");

	DBResult *res = 0;

	// Return value
	unsigned int iVal;

	try {
		// Query
		res = executeQuery("SELECT * FROM configuration WHERE cName='"+field+"'");

		// Load data
		res->nextRow();

		// Parse data
		iVal = res->getUInt("cValue");
	} catch (DBException &e) {
		std::stringstream s;
		s << "Config::getUIntValue (" << field << ")";
		throw Exception(e.what(), s.str());
	}

	// Release memory
	delete res;

	return iVal;
}

void Config::setValue(const std::string& field, int val) {
	if (field == "")
		throw Exception("Field is empty", "Config::setValue (int)");

	// Convert to string
	std::stringstream ss;
	ss << val;

	try {
		// Query
		executeSaveQuery("UPDATE configuration SET cValue='"+ss.str()+"' WHERE cName='"+field+"'");
	} catch (DBException &e) {
		std::stringstream s;
		s << "Config::setValue (int) (" << field << ")";
		throw Exception(e.what(), s.str());
	}
}

void Config::setValue(const std::string& field, const std::string& val) {
	if (field == "")
		throw Exception("Field is empty", "Config::setValue (string)");

	try {
		// Query
		executeSaveQuery("UPDATE configuration SET cValue='"+val+"' WHERE cName='"+field+"'");
	} catch (DBException &e) {
		std::stringstream s;
		s << "Config::setValue (string) (" << field << ")";
		throw Exception(e.what(), s.str());
	}
}

std::string Config::getShmCfg(unsigned int id) {
	// No data
	bool noData = false;

	// Query
	std::stringstream q;

	// Return value
	std::string shm = "";

	DBResult *result = 0;

	try {
		// Prepare query
		q << "SELECT * FROM driver_shm WHERE dsId = "<< id << ";";

		// Query
		result = executeQuery(q.str());

		if (result->rowsCount() == 1) {
			// Read data
			result->nextRow();

			// Get SHM region name
			shm = result->getString("dsSegment");

			// Release memory
			delete result;
			result = nullptr;

		} else {
			noData = true;
		}
	} catch (DBException &e) {
		if (result)
			delete result;

		throw Exception(e.what(), "Config::getShmCfg");
	}

	if (noData)
		throw Exception("SHM configuration does not exist in DB", "Config::getShmCfg");

	return shm;
}

modbusM::ModbusCfg Config::getModbusCfg(unsigned int id) {
	// No data
	bool noData = false;

	// Query
	std::stringstream q;

	// Return value
	modbusM::ModbusCfg mb;

	DBResult *result = 0;

	try {
		// Prepare query
		q << "SELECT * FROM driver_modbus WHERE dmId = "<< id << ";";

		// Query
		result = executeQuery(q.str());

		if (result->rowsCount() == 1) {
			// Read data
			result->nextRow();

			// Get data
			mb.mode = ((result->getUInt("dmMode") == modbusM::MM_RTU)?(modbusM::MM_RTU):(modbusM::MM_TCP));
			mb.slaveID = result->getInt("dmSlaveID");
			mb.registerCount = result->getInt("dmRegCount");
			mb.polling = result->getUInt("dmPollingInterval");

			if (mb.mode == modbusM::MM_RTU) {
				mb.RTU_port = result->getString("dmRTU_port");
				mb.RTU_baud = result->getInt("dmRTU_baud");
				mb.RTU_parity = result->getString("dmRTU_parity")[0];
				mb.RTU_dataBit = result->getInt("dmRTU_dataBit");
				mb.RTU_stopBit = result->getInt("dmRTU_stopBit");
			} else {
				mb.TCP_addr = result->getString("dmTCP_addr");
				mb.TCP_port = result->getInt("dmTCP_port");
				mb.TCP_use_slaveID = result->getInt("dmTCP_use_slaveID");
			}

			// Release memory
			delete result;
			result = 0;

		} else {
			noData = true;
		}
	} catch (DBException &e) {
		if (result)
			delete result;

		throw Exception(e.what(), "Config::getModbusCfg");
	}

	if (noData)
		throw Exception("Modbus configuration does not exist in DB", "Config::getModbusCfg");

	return mb;
}

std::vector<DriverConnection> Config::getDriverConnections(bool enabled) {
	// Check driver connection limit
	checkDriverConnectionLimit();

	// Query
	std::stringstream q;

	// Return vector
	std::vector<DriverConnection> vConn;

	// Return value
	DriverConnection dc, dcp;

	DBResult *result = 0;

	try {
		// Prepare query
		q << "SELECT * FROM driver_connections WHERE dcEnable=" << ((enabled)?("1"):("0")) << ";";

		// Query
		result = executeQuery(q.str());

		// Read data
		while (result->nextRow()) {
			// Clear put variable
			dcp = dc;

			dcp.setId(result->getUInt("dcId"));
			dcp.setName(result->getString("dcName"));
			dcp.setType(static_cast<DriverType>(result->getUInt("dcType")));
			dcp.setEnable(((result->getInt("dcEnable") == 1)?(true):(false)));

			if (dcp.getType() == DriverType::DT_Modbus) {
				dcp.setModbusCfg(getModbusCfg(result->getUInt("dcConfigModbus")));
			} else {
				dcp.setShmCfg(getShmCfg(result->getUInt("dcConfigSHM")));
			}

			// Put into the vector
			vConn.push_back(dcp);
		}

		// Release memory
		delete result;
		result = 0;
	} catch (DBException &e) {
		if (result)
			delete result;

		throw Exception(e.what(), "Config::getDriverConnections");
	}

	return vConn;
}

void Config::checkDriverConnectionLimit() {
	DBResult *result = 0;
	std::string q;
	unsigned int cnt = 0;

	try {
		// Prepare query
		q = "SELECT count(*) as 'cnt' FROM driver_connections;";

		// Query
		result = executeQuery(q);

		// Read data
		result->nextRow();
		cnt = result->getUInt("cnt");

		// Release memory
		delete result;
		result = 0;
	} catch (DBException &e) {
		if (result)
			delete result;

		throw Exception(e.what(), "Config::getDriverConnections");
	}

	// Check limit
	if (cnt > DriverConnection::MAX_CONN) {
		throw Exception("Driver connection limit exceeded. Max allowed connections number is "
							+std::to_string(DriverConnection::MAX_CONN),
							"Config::checkDriverConnectionLimit");
	}
}

}  // namespace onh
