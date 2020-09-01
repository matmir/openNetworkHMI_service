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

#ifndef MODBUSMASTERCFG_H_
#define MODBUSMASTERCFG_H_

#include <string>
#include "../DriverRegisterTypes.h"

namespace modbusM {

	/**
	 * Modbus driver mode (TCP/RTU)
	 */
	typedef enum {
		MM_RTU = 0,
		MM_TCP
	} ModbusMode;

	/**
	 * Modbus configuration structure
	 */
	typedef struct ModbusCfg {

		/**
		 * Common modbus configuration
		 */
		ModbusMode mode;
		BYTE slaveID;
		WORD registerCount;
		unsigned int polling;

		/**
		 * Modbus TCP configuration
		 */
		std::string TCP_addr;
		int TCP_port;

		/**
		 * Modbus RTU configuration
		 */
		std::string RTU_port;
		int RTU_baud;
		char RTU_parity;
		int RTU_dataBit;
		int RTU_stopBit;

		ModbusCfg(): mode(MM_TCP), slaveID(0), registerCount(0), polling(0), TCP_addr(""),
					TCP_port(0), RTU_port(""), RTU_baud(0), RTU_parity(0), RTU_dataBit(0), RTU_stopBit(0) {}
	} ModbusCfg;

}

#endif /* MODBUSMASTERCFG_H_ */
