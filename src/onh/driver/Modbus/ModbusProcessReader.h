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

#ifndef ONH_DRIVER_MODBUS_MODBUSPROCESSREADER_H_
#define ONH_DRIVER_MODBUS_MODBUSPROCESSREADER_H_

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
		bool getBitValue(processDataAddress addr) override;

		/**
		 * Get bits value from process data
		 *
		 * @param addr Process data addresses
		 *
		 * @return Bits values
		 */
		std::vector<bool> getBitsValue(std::vector<processDataAddress> addr) override;

		/**
		 * Get byte value from process data
		 *
		 * @param addr Process data address
		 *
		 * @return Byte value
		 */
		BYTE getByte(processDataAddress addr) override;

		/**
		 * Get word value from process data
		 *
		 * @param addr Process data address
		 *
		 * @return Word value
		 */
		WORD getWord(processDataAddress addr) override;

		/**
		 * Get double word value from process data
		 *
		 * @param addr Process data address
		 *
		 * @return Double word value
		 */
		DWORD getDWord(processDataAddress addr) override;

		/**
		 * Get int value from process data
		 *
		 * @param addr Process data address
		 *
		 * @return Int value
		 */
		int getInt(processDataAddress addr) override;

		/**
		 * Get real value from process data
		 *
		 * @param addr Process data address
		 *
		 * @return Real value
		 */
		float getReal(processDataAddress addr) override;

		/**
		 * Update reader process data (copy from driver)
		 */
		void updateProcessData() override;

		/**
		 * Create new driver process reader
		 *
		 * @return Pointer to the new driver process reader
		 */
		DriverProcessReader* createNew() override;

	private:
		/**
		 * Constructor (allowed only from ModbusDriver)
		 *
		 * @param gdc Modbus process data controller
		 */
		explicit ModbusProcessReader(const GuardDataController<ModbusProcessData> &gdc);

		/// Copy of the driver process data
		ModbusProcessData process;

		/// Driver process data controller
		GuardDataController<ModbusProcessData> driverProcess;
};

}  // namespace onh

#endif  // ONH_DRIVER_MODBUS_MODBUSPROCESSREADER_H_
