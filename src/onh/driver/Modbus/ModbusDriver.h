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

#ifndef ONH_DRIVER_MODBUS_MODBUSDRIVER_H_
#define ONH_DRIVER_MODBUS_MODBUSDRIVER_H_

#include "../Driver.h"
#include "modbusmaster.h"
#include "ModbusProcessData.h"
#include "../../utils/GuardDataContainer.h"

namespace onh {

/**
 * Modbus driver class
 */
class ModbusDriver: public Driver {
	public:
		/**
		 * ModbusDriver Constructor
		 *
		 * @param cfg Modbus configuration structure
		 * @param connId Driver connection identifier
		 */
		ModbusDriver(const modbusM::ModbusCfg& cfg, unsigned int connId);

		/**
		 * Copy constructor - inactive
		 */
		ModbusDriver(const ModbusDriver&) = delete;

		virtual ~ModbusDriver();

		/**
		 * Assign operator - inactive
		 */
		ModbusDriver& operator=(const ModbusDriver&) = delete;

		/**
		 * Get driver buffer handle
		 *
		 * @return Driver buffer handle
		 */
		DriverBuffer* getBuffer() override;

		/**
		 * Get driver process data reader
		 *
		 * @return Driver process data reader handle
		 */
		DriverProcessReader* getReader() override;

		/**
		 * Get driver process data writer
		 *
		 * @return Driver process data writer handle
		 */
		DriverProcessWriter* getWriter() override;

		/**
		 * Get driver process data updater
		 *
		 * @return Driver process data updater handle
		 */
		DriverProcessUpdater* getUpdater() override;

	private:
		/// Process registers count
		WORD regCount;

		/// Maximum Byte address
		unsigned int maxByteCount;

		/// Modbus process data
		GuardDataContainer<ModbusProcessData> *process;

		/// Modbus process data buffer
		GuardDataContainer<ModbusProcessData> *buff;

		/// Modbus Master protocol
		modbusM::ModbusMaster *modbus;

		/// Mutex for protecting driver
		MutexContainer driverLock;

		/**
		 * Connect to the slave device
		 */
		void connect();

		/**
		 * Trigger error (write log and throw exception)
		 *
		 * @param msg Exception message
		 * @param fName Function from which exception was throwed
		 */
		void triggerError(const std::string& msg, const std::string& fName);
};

}  // namespace onh

#endif  // ONH_DRIVER_MODBUS_MODBUSDRIVER_H_
