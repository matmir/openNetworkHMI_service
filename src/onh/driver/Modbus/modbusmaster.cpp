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

#include "modbusmaster.h"
#include <sstream>

using namespace modbusM;

ModbusMaster::ModbusMaster(const ModbusCfg& cfg):
	config(cfg)
{
	// Initialize modbus driver
	if (config.mode == MM_TCP) {
		mb = modbus_new_tcp(config.TCP_addr.c_str(), config.TCP_port);
	} else if (config.mode == MM_RTU) {
		mb = modbus_new_rtu(config.RTU_port.c_str(), config.RTU_baud, config.RTU_parity, config.RTU_dataBit, config.RTU_stopBit);
	} else {
		throw ModbusException("Invalid Mobdus mode", "ModbusMaster::ModbusMaster");
	}

	if (mb==NULL) {
		throw ModbusException("Unable to allocate libmodbus context", "ModbusMaster::ModbusMaster");
	}

	// SlaveID
	if (config.mode == MM_RTU || (config.mode == MM_TCP && config.TCP_use_slaveID)) {
		if (modbus_set_slave(mb, config.slaveID)) {
			throw ModbusException("Invalid slave ID", "ModbusMaster::ModbusMaster");
		}
	}

	// Response timeout (1s)
	if (modbus_set_response_timeout(mb, 1, 0)) {
		throw ModbusException("Can not set response timeout", "ModbusMaster::ModbusMaster");
	}
}

ModbusMaster::~ModbusMaster()
{
	if(mb!=NULL) {
		modbus_free(mb);
	}

}

void ModbusMaster::connect() {

    // Connect to the slave
    if (modbus_connect(mb)) {
    	std::stringstream s;
    	s << "Connection failed: " << modbus_strerror(errno);
    	throw ModbusException(s.str(), "ModbusMaster::connect");
    }
}

void ModbusMaster::disconnect() {

	modbus_close(mb);
}

void ModbusMaster::READ_INPUT_REGISTERS(WORD regAddress, WORD quantity, WORD *buff) {

	// Read input registers
	if (modbus_read_input_registers(mb, regAddress, quantity, buff) == -1) {
		std::stringstream s;
		s << "Read input registers failed: " << modbus_strerror(errno);
		throw ModbusException(s.str(), "ModbusMaster::READ_INPUT_REGISTERS");
	}
}

void ModbusMaster::WRITE_SINGLE_REGISTER(WORD regAddress, WORD value) {

	// Write holding register
	if (modbus_write_register(mb, regAddress, value) == -1) {
		std::stringstream s;
		s << "Write register failed: " << modbus_strerror(errno);
		throw ModbusException(s.str(), "ModbusMaster::WRITE_SINGLE_REGISTER");
	}
}

void ModbusMaster::READ_HOLDING_REGISTERS(WORD regAddress, WORD quantity, WORD *buff) {

	// Read holding register
	if (modbus_read_registers(mb, regAddress, quantity, buff) == -1) {
		std::stringstream s;
		s << "Read holding registers failed: " << modbus_strerror(errno);
		throw ModbusException(s.str(), "ModbusMaster::READ_HOLDING_REGISTERS");
	}
}

void ModbusMaster::WRITE_MULTIPLE_REGISTERS(WORD regAddress, WORD quantity, WORD *values) {

	// Write multiple holding registers
	if (modbus_write_registers(mb, regAddress, quantity, values) == -1) {
		std::stringstream s;
		s << "Write holding registers failed: " << modbus_strerror(errno);
		throw ModbusException(s.str(), "ModbusMaster::WRITE_MULTIPLE_REGISTERS");
	}
}
