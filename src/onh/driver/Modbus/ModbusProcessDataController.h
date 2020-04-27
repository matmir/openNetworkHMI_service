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

#ifndef SRC_ONH_DRIVER_SHM_MODBUSPROCESSDATACONTROLLER_H_
#define SRC_ONH_DRIVER_SHM_MODBUSPROCESSDATACONTROLLER_H_

#include "../../utils/MutexAccess.h"
#include "ModbusProcessData.h"

namespace onh {

	/// Forward declaration
	class ModbusProcessDataContainer;

	/**
	 * Modbus process data controller class
	 */
	class ModbusProcessDataController {

		public:

			friend class ModbusProcessDataContainer;

			/**
			 * Default constructor
			 */
			ModbusProcessDataController();

			/**
			 * Copy constructor
			 *
			 * @param spdc Shm process data controller object to copy
			 */
			ModbusProcessDataController(const ModbusProcessDataController& spdc);

			virtual ~ModbusProcessDataController();

			/**
			 * Get copy of the driver process data
			 *
			 * @param dest Destination process data
			 */
			void getProcessDataCopy(ModbusProcessData *dest);

			/**
			 * Get registers count
			 *
			 * @return Registers count
			 */
			WORD getRegistersCount() const;

		private:

			/**
			 * Constructor (allowed only from ModbusProcessDataContainer)
			 *
			 * @param pdLock MutexAccess object for protecting process data
			 * @param procDT Pointer to process data
			 * @param registersCount Max number modbus registers to read
			 */
			ModbusProcessDataController(const MutexAccess &pdLock, ModbusProcessData *procDT, WORD regCount);

			/**
			 * Assign operator
			 */
			void operator=(const ModbusProcessDataController&) {};

			/// Pointer to the process data
			ModbusProcessData *process;

			/// Mutex for protecting process data
			MutexAccess processLock;

			/// Modbus register count
			WORD registersCount;
	};

}

#endif /* SRC_ONH_DRIVER_SHM_MODBUSPROCESSDATACONTROLLER_H_ */
