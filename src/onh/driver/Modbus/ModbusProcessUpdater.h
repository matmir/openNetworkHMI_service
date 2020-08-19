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

#ifndef SRC_ONH_DRIVER_MODBUS_MODBUSPROCESSUPDATER_H_
#define SRC_ONH_DRIVER_MODBUS_MODBUSPROCESSUPDATER_H_

#include "../DriverProcessUpdater.h"
#include "ModbusProcessData.h"
#include "../../utils/GuardDataController.h"

namespace onh {

	/// Forward declaration
	class ModbusDriver;

	/**
	 * Modbus driver process data updater class
	 */
	class ModbusProcessUpdater: public DriverProcessUpdater {

		public:

			friend class ModbusDriver;

			/**
			 * Copy constructor - inactive
			 */
			ModbusProcessUpdater(const ModbusProcessUpdater&) = delete;

			virtual ~ModbusProcessUpdater();

			/**
			 * Assign operator - inactive
			 */
			ModbusProcessUpdater& operator=(const ModbusProcessUpdater&) = delete;

			/**
			 * Update process data (copy from load buffer)
			 */
			virtual void updateProcessData();

			/**
			 * Create new driver process updater
			 *
			 * @return Pointer to the new driver process updater
			 */
			virtual DriverProcessUpdater* createNew();

		private:

			/**
			 * Constructor with parameters (allowed only from ShmDriver)
			 *
			 * @param mbuff Buffer data controller
			 * @param gdc Process data controller (write mode)
			 */
			ModbusProcessUpdater(const GuardDataController<ModbusProcessData> &mbuff, const GuardDataController<ModbusProcessData> &gdc);

			/// Driver buffer data controller
			GuardDataController<ModbusProcessData> buff;

			/// Driver process data controller (write mode)
			GuardDataController<ModbusProcessData> process;
	};

}

#endif /* SRC_ONH_DRIVER_MODBUS_MODBUSPROCESSUPDATER_H_ */
