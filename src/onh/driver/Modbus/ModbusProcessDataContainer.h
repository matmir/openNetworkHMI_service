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

#ifndef SRC_ONH_DRIVER_SHM_MODBUSPROCESSDATACONTAINER_H_
#define SRC_ONH_DRIVER_SHM_MODBUSPROCESSDATACONTAINER_H_

#include "../../utils/MutexContainer.h"
#include "ModbusProcessData.h"
#include "ModbusProcessDataController.h"

namespace onh {

	/**
	 * Modbus process data container class
	 */
	class ModbusProcessDataContainer {

		public:

			/**
			 * Constructor
			 *
			 * @param regCount Max number modbus registers to read
			 */
			ModbusProcessDataContainer(WORD regCount);

			virtual ~ModbusProcessDataContainer();

			/**
			 * Get Modbus process data container controller object
			 *
			 * @return Modbus process data container controller object
			 */
			ModbusProcessDataController getController();

			/**
			 * Update internal process data
			 *
			 * @param newDT New process data
			 */
			void update(const ModbusProcessData& newDT);

			/**
			 * Clear process data
			 */
			void clear();

		private:

			/**
			 * Copy constructor
			 */
			ModbusProcessDataContainer(const ModbusProcessDataContainer&) {};

			/**
			 * Assign operator
			 */
			void operator=(const ModbusProcessDataContainer&) {};

			/// Process data
			ModbusProcessData process;

			/// Mutex for protecting process data
			MutexContainer processLock;

			/// Modbus register count
			WORD registersCount;
	};

}

#endif /* SRC_ONH_DRIVER_SHM_MODBUSPROCESSDATACONTAINER_H_ */
