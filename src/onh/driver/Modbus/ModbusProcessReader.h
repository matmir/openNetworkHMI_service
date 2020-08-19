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

#ifndef SRC_ONH_DRIVER_MODBUS_MODBUSPROCESSREADER_H_
#define SRC_ONH_DRIVER_MODBUS_MODBUSPROCESSREADER_H_

#include "../DriverProcessReader.h"
#include "ModbusProcessData.h"
#include "../../utils/GuardDataController.h"

namespace onh {

	/// Forward declaration
	class ModbusDriver;

	/**
	 * Modbus driver process data reader class
	 */
	class ModbusProcessReader: public DriverProcessReader {

		public:

			friend class ModbusDriver;

			/**
			 * Copy constructor - inactive
			 */
			ModbusProcessReader(const ModbusProcessReader&) = delete;

			virtual ~ModbusProcessReader();

			/**
			 * Assign operator - inactive
			 */
			ModbusProcessReader& operator=(const ModbusProcessReader&) = delete;

			/**
			 * Get bit value from process data
			 *
			 * @param addr Process data address
			 *
			 * @return Bit value
			 */
			virtual bool getBitValue(processDataAddress addr);

			/**
			 * Get bits value from process data
			 *
			 * @param addr Process data addresses
			 *
			 * @return Bits values
			 */
			virtual std::vector<bool> getBitsValue(std::vector<processDataAddress> addr);

			/**
			 * Get byte value from process data
			 *
			 * @param addr Process data address
			 *
			 * @return Byte value
			 */
			virtual BYTE getByte(processDataAddress addr);

			/**
			 * Get word value from process data
			 *
			 * @param addr Process data address
			 *
			 * @return Word value
			 */
			virtual WORD getWord(processDataAddress addr);

			/**
			 * Get double word value from process data
			 *
			 * @param addr Process data address
			 *
			 * @return Double word value
			 */
			virtual DWORD getDWord(processDataAddress addr);

			/**
			 * Get int value from process data
			 *
			 * @param addr Process data address
			 *
			 * @return Int value
			 */
			virtual int getInt(processDataAddress addr);

			/**
			 * Get real value from process data
			 *
			 * @param addr Process data address
			 *
			 * @return Real value
			 */
			virtual float getReal(processDataAddress addr);

			/**
			 * Update reader process data (copy from driver)
			 */
			virtual void updateProcessData();

			/**
			 * Create new driver process reader
			 *
			 * @return Pointer to the new driver process reader
			 */
			virtual DriverProcessReader* createNew();

		private:

			/**
			 * Constructor (allowed only from ModbusDriver)
			 *
			 * @param gdc Modbus process data controller
			 */
			ModbusProcessReader(const GuardDataController<ModbusProcessData> &gdc);

			/// Copy of the driver process data
			ModbusProcessData process;

			/// Driver process data controller
			GuardDataController<ModbusProcessData> driverProcess;
	};

}

#endif /* SRC_ONH_DRIVER_MODBUS_MODBUSPROCESSREADER_H_ */
