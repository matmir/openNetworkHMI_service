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

#ifndef ONH_DRIVER_DRIVERPROCESSREADER_H_
#define ONH_DRIVER_DRIVERPROCESSREADER_H_

#include <vector>
#include "DriverRegisterTypes.h"
#include "ProcessDataTypes.h"

namespace onh {

/**
 * Base driver process data reader class
 */
class DriverProcessReader {
	public:
		DriverProcessReader();
		virtual ~DriverProcessReader();

		/**
		 * Get bit value from process data
		 *
		 * @param addr Process data address
		 *
		 * @return Bit value
		 */
		virtual bool getBitValue(processDataAddress addr) = 0;

		/**
		 * Get bits value from process data
		 *
		 * @param addr Process data addresses
		 *
		 * @return Bits values
		 */
		virtual std::vector<bool> getBitsValue(std::vector<processDataAddress> addr) = 0;

		/**
		 * Get byte value from process data
		 *
		 * @param addr Process data address
		 *
		 * @return Byte value
		 */
		virtual BYTE getByte(processDataAddress addr) = 0;

		/**
		 * Get word value from process data
		 *
		 * @param addr Process data address
		 *
		 * @return Word value
		 */
		virtual WORD getWord(processDataAddress addr) = 0;

		/**
		 * Get double word value from process data
		 *
		 * @param addr Process data address
		 *
		 * @return Double word value
		 */
		virtual DWORD getDWord(processDataAddress addr) = 0;

		/**
		 * Get int value from process data
		 *
		 * @param addr Process data address
		 *
		 * @return Int value
		 */
		virtual int getInt(processDataAddress addr) = 0;

		/**
		 * Get real value from process data
		 *
		 * @param addr Process data address
		 *
		 * @return Real value
		 */
		virtual float getReal(processDataAddress addr) = 0;

		/**
		 * Update reader process data (copy from driver)
		 */
		virtual void updateProcessData() = 0;

		/**
		 * Create new driver process reader
		 *
		 * @return Pointer to the new driver process reader
		 */
		virtual DriverProcessReader* createNew() = 0;
};

}  // namespace onh

#endif  // ONH_DRIVER_DRIVERPROCESSREADER_H_
