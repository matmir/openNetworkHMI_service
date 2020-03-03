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

#ifndef SRC_ONH_DRIVER_MODBUS_MODBUSTCPPROCESSREADER_H_
#define SRC_ONH_DRIVER_MODBUS_MODBUSTCPPROCESSREADER_H_

#include "../DriverProcessReader.h"
#include "ModbusTCPProcessData.h"
#include "../../utils/MutexAccess.h"
#include "ModbusTCPProcessDataController.h"

namespace onh {

	/// Forward declaration
	class ModbusTCP;

	/**
	 * ModbusTCP driver process data reader class
	 */
	class ModbusTCPProcessReader: public DriverProcessReader {

		public:

			friend class ModbusTCP;

			virtual ~ModbusTCPProcessReader();

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
			 * Constructor (allowed only from ModbusTCP)
			 */
			ModbusTCPProcessReader();

			/**
			 * Constructor (allowed only from ModbusTCP)
			 *
			 * @param spdc ModbusTCP process data controller
			 */
			ModbusTCPProcessReader(const ModbusTCPProcessDataController& spdc);

			/// Maximum Byte address
			unsigned int maxByteCount;

			/// Copy of the driver process data
			ModbusTCPProcessData process;

			/// Driver process data controller
			ModbusTCPProcessDataController driverProcess;

			/**
			 * Trigger error
			 *
			 * @param msg Exception message
			 * @param fName Function from which exception was throwed
			 */
			void triggerError(const std::string& msg, const std::string& fName);
	};

}

#endif /* SRC_ONH_DRIVER_MODBUS_MODBUSTCPPROCESSREADER_H_ */
