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

#include "modbustcpmaster.h"
#include <sstream>

using namespace modbusTCP;

ModbusTCPMaster::ModbusTCPMaster(const std::string& addr, BYTE slaveId, int port):
    slaveIP(addr), slavePort(port), slaveID(slaveId)
{
	// Initialize modbus driver
	mb = modbus_new_tcp(slaveIP.c_str(), slavePort);
	if (mb==NULL) {
		throw ModbusTCPException("Unable to allocate libmodbus context", "ModbusTCPMaster::ModbusTCPMaster");
	}

	// SlaveID
	if (modbus_set_slave(mb, slaveID)) {
		throw ModbusTCPException("Invalid slave ID", "ModbusTCPMaster::ModbusTCPMaster");
	}

	// Response timeout (1s)
	if (modbus_set_response_timeout(mb, 1, 0)) {
		throw ModbusTCPException("Can not set response timeout", "ModbusTCPMaster::ModbusTCPMaster");
	}
}

ModbusTCPMaster::~ModbusTCPMaster()
{
	if(mb!=NULL) {
		modbus_free(mb);
	}

}

void ModbusTCPMaster::connect() {

    // Connect to the slave
    if (modbus_connect(mb)) {
    	std::stringstream s;
    	s << "Connection failed: " << modbus_strerror(errno);
    	throw ModbusTCPException(s.str(), "ModbusTCPMaster::connect");
    }
}

void ModbusTCPMaster::disconnect() {

	modbus_close(mb);
}

void ModbusTCPMaster::READ_INPUT_REGISTERS(WORD regAddress, WORD quantity, WORD *buff) {

	// Read input registers
	if (modbus_read_input_registers(mb, regAddress, quantity, buff) == -1) {
		std::stringstream s;
		s << "Read input registers failed: " << modbus_strerror(errno);
		throw ModbusTCPException(s.str(), "ModbusTCPMaster::READ_INPUT_REGISTERS");
	}
}

void ModbusTCPMaster::WRITE_SINGLE_REGISTER(WORD regAddress, WORD value) {

	// Write holding register
	if (modbus_write_register(mb, regAddress, value) == -1) {
		std::stringstream s;
		s << "Write register failed: " << modbus_strerror(errno);
		throw ModbusTCPException(s.str(), "ModbusTCPMaster::WRITE_SINGLE_REGISTER");
	}
}

void ModbusTCPMaster::READ_HOLDING_REGISTERS(WORD regAddress, WORD quantity, WORD *buff) {

	// Read holding register
	if (modbus_read_registers(mb, regAddress, quantity, buff) == -1) {
		std::stringstream s;
		s << "Read holding registers failed: " << modbus_strerror(errno);
		throw ModbusTCPException(s.str(), "ModbusTCPMaster::READ_HOLDING_REGISTERS");
	}
}

void ModbusTCPMaster::WRITE_MULTIPLE_REGISTERS(WORD regAddress, WORD quantity, WORD *values) {

	// Write multiple holding registers
	if (modbus_write_registers(mb, regAddress, quantity, values) == -1) {
		std::stringstream s;
		s << "Write holding registers failed: " << modbus_strerror(errno);
		throw ModbusTCPException(s.str(), "ModbusTCPMaster::WRITE_MULTIPLE_REGISTERS");
	}
}
