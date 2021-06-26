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

#ifndef ONH_DRIVER_DRIVERPROCESSWRITER_H_
#define ONH_DRIVER_DRIVERPROCESSWRITER_H_

#include <vector>
#include <memory>
#include "DriverRegisterTypes.h"
#include "ProcessDataTypes.h"

namespace onh {

/**
 * Base driver process data writer class
 */
class DriverProcessWriter {
	public:
		DriverProcessWriter();

		virtual ~DriverProcessWriter();

		/**
		 * Set bit in device process data
		 *
		 * @param addr Process data address
		 */
		virtual void setBit(processDataAddress addr) = 0;

		/**
		 * Reset bit in device process data
		 *
		 * @param addr Process data address
		 */
		virtual void resetBit(processDataAddress addr) = 0;

		/**
		 * Invert bit in device process data
		 *
		 * @param addr Process data address
		 */
		virtual void invertBit(processDataAddress addr) = 0;

		/**
		 * Set bits in device process data
		 *
		 * @param addr Process data address
		 */
		virtual void setBits(std::vector<processDataAddress> addr) = 0;

		/**
		 * Write byte in device process data
		 *
		 * @param addr Process data address
		 * @param val Value to write
		 */
		virtual void writeByte(processDataAddress addr, BYTE val) = 0;

		/**
		 * Write word in device process data
		 *
		 * @param addr Process data address
		 * @param val Value to write
		 */
		virtual void writeWord(processDataAddress addr, WORD val) = 0;

		/**
		 * Write double word in device process data
		 *
		 * @param addr Process data address
		 * @param val Value to write
		 */
		virtual void writeDWord(processDataAddress addr, DWORD val) = 0;

		/**
		 * Write int in device process data
		 *
		 * @param addr Process data address
		 * @param val Value to write
		 */
		virtual void writeInt(processDataAddress addr, int val) = 0;

		/**
		 * Write real in device process data
		 *
		 * @param addr Process data address
		 * @param val Value to write
		 */
		virtual void writeReal(processDataAddress addr, float val) = 0;

		/**
		 * Create new driver process writer
		 *
		 * @return Pointer to the new driver process writer
		 */
		virtual std::unique_ptr<DriverProcessWriter> createNew() = 0;
};

using DriverProcessWriterPtr = std::unique_ptr<DriverProcessWriter>;

}  // namespace onh

#endif  // ONH_DRIVER_DRIVERPROCESSWRITER_H_
