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

#ifndef ONH_DRIVER_SHM_SHMPROCESSREADER_H_
#define ONH_DRIVER_SHM_SHMPROCESSREADER_H_

#include "../DriverProcessReader.h"
#include "ShmProcessData.h"
#include "../../utils/GuardDataController.h"

namespace onh {

/// Forward declaration
class ShmDriver;

/**
 * SHM driver process data reader class
 */
class ShmProcessReader: public DriverProcessReader {
	public:
		friend class ShmDriver;

		/**
		 * Copy constructor - inactive
		 */
		ShmProcessReader(const ShmProcessReader&) = delete;

		virtual ~ShmProcessReader();

		/**
		 * Assign operator - inactive
		 */
		ShmProcessReader& operator=(const ShmProcessReader&) = delete;

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
		DriverProcessReaderPtr createNew() override;

	private:
		/**
		 * Constructor (allowed only from ShmDriver)
		 *
		 * @param gdc Shm process data controller
		 */
		explicit ShmProcessReader(const GuardDataController<ShmProcessData>& gdc);

		/// Copy of the driver process data
		ShmProcessData process;

		/// Driver process data controller
		GuardDataController<ShmProcessData> driverProcess;
};

}  // namespace onh

#endif  // ONH_DRIVER_SHM_SHMPROCESSREADER_H_
