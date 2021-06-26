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

#ifndef ONH_DRIVER_MODBUS_MODBUSUPDATER_H_
#define ONH_DRIVER_MODBUS_MODBUSUPDATER_H_

#include "../DriverBuffer.h"
#include "../DriverException.h"
#include "modbusmaster.h"
#include "ModbusProcessData.h"
#include "../../utils/GuardDataController.h"

namespace onh {

/// Forward declaration
class ModbusDriver;

/**
 * Modbus updater class
 */
class ModbusUpdater: public DriverBuffer {
	public:
		friend class ModbusDriver;

		/**
		 * Copy constructor - inactive
		 */
		ModbusUpdater(const ModbusUpdater&) = delete;

		virtual ~ModbusUpdater();

		/**
		 * Assign operator - inactive
		 */
		ModbusUpdater& operator=(const ModbusUpdater&) = delete;

		/**
		 * Update driver buffer (Get data from controller)
		 */
		void updateBuffer() override;

	private:
		/**
		 * Constructor with parameters (allowed only from ModbusDriver)
		 *
		 * @param drv Driver instance
		 * @param drvLock Driver Mutex locking structure
		 * @param mbuff Driver buffer data controller (write mode)
		 */
		ModbusUpdater(modbusM::ModbusMasterPtr drv,
							const MutexAccess &drvLock,
							const GuardDataController<ModbusProcessData> &mbuff);

		void clearTempReg();

		/// Driver instance
		modbusM::ModbusMasterPtr driver;
		MutexAccess driverLock;

		/// Driver buffer data controller (write mode)
		GuardDataController<ModbusProcessData> buff;

		/// Modbus temporary registers
		ModbusRegisters tempBuff;
};

}  // namespace onh

#endif  // ONH_DRIVER_MODBUS_MODBUSUPDATER_H_
