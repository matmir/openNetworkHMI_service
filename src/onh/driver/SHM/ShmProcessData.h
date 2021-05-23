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

#ifndef ONH_DRIVER_SHM_SHMPROCESSDATA_H_
#define ONH_DRIVER_SHM_SHMPROCESSDATA_H_

#include "processData.h"
#include <vector>
#include "../DriverRegisterTypes.h"
#include "../ProcessDataTypes.h"

namespace onh {

/**
 * SHM process data class
 */
class ShmProcessData {
	public:
		/**
		 * Default constructor
		 */
		ShmProcessData();

		/**
		 * Constructor
		 *
		 * @param pd SHM process data structure
		 */
		explicit ShmProcessData(const processData &pd);

		/**
		 * Copy constructor
		 */
		ShmProcessData(const ShmProcessData &spd);

		virtual ~ShmProcessData();

		/**
		 * Assign operator
		 */
		ShmProcessData& operator=(const ShmProcessData &spd);

		/**
		 * Get bit from process data
		 *
		 * @param addr Process data address
		 *
		 * @return Bit value from process data
		 */
		bool getBit(processDataAddress addr) const;

		/**
		 * Get bits from process data
		 *
		 * @param addr Vector with bits addresses
		 *
		 * @return Vector with bits value
		 */
		std::vector<bool> getBits(const std::vector<processDataAddress>& addr) const;

		/**
		 * Get byte from process data
		 *
		 * @param addr Process data address
		 *
		 * @return Byte value from process data
		 */
		BYTE getByte(processDataAddress addr) const;

		/**
		 * Get WORD from process data
		 *
		 * @param addr Process data address
		 *
		 * @return Word value from process data
		 */
		WORD getWord(processDataAddress addr) const;

		/**
		 * Get DWORD from process data
		 *
		 * @param addr Process data address
		 *
		 * @return Double word value from process data
		 */
		DWORD getDWord(processDataAddress addr) const;

		/**
		 * Get INT from process data
		 *
		 * @param addr Process data address
		 *
		 * @return Int value from process data
		 */
		int getInt(processDataAddress addr) const;

		/**
		 * Get REAL from process data
		 *
		 * @param addr Process data address
		 *
		 * @return Real value from process data
		 */
		float getReal(processDataAddress addr) const;

		/**
		 * Clear process data
		 */
		void clear();

	private:
		/// SHM process data
		processData *process;
};

}  // namespace onh

#endif  // ONH_DRIVER_SHM_SHMPROCESSDATA_H_
