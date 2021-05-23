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

#ifndef ONH_DRIVER_SHM_SHMPROCESSWRITER_H_
#define ONH_DRIVER_SHM_SHMPROCESSWRITER_H_

#include <vector>
#include "../DriverProcessWriter.h"
#include "processData.h"
#include "../../utils/MutexAccess.h"
#include "sMemory.h"

namespace onh {

/// Forward declaration
class ShmDriver;

/**
 * SHM driver process data writer class
 */
class ShmProcessWriter: public DriverProcessWriter {
	public:
		friend class ShmDriver;

		/**
		 * Copy constructor - inactive
		 */
		ShmProcessWriter(const ShmProcessWriter&) = delete;

		virtual ~ShmProcessWriter();

		/**
		 * Assign operator - inactive
		 */
		ShmProcessWriter& operator=(const ShmProcessWriter&) = delete;

		/**
		 * Set bit in device process data
		 *
		 * @param addr Process data address
		 */
		void setBit(processDataAddress addr) override;

		/**
		 * Reset bit in device process data
		 *
		 * @param addr Process data address
		 */
		void resetBit(processDataAddress addr) override;

		/**
		 * Invert bit in device process data
		 *
		 * @param addr Process data address
		 */
		void invertBit(processDataAddress addr) override;

		/**
		 * Set bits in device process data
		 *
		 * @param addr Process data address
		 */
		void setBits(std::vector<processDataAddress> addr) override;

		/**
		 * Write byte in device process data
		 *
		 * @param addr Process data address
		 * @param val Value to write
		 */
		void writeByte(processDataAddress addr, BYTE val) override;

		/**
		 * Write word in device process data
		 *
		 * @param addr Process data address
		 * @param val Value to write
		 */
		void writeWord(processDataAddress addr, WORD val) override;

		/**
		 * Write double word in device process data
		 *
		 * @param addr Process data address
		 * @param val Value to write
		 */
		void writeDWord(processDataAddress addr, DWORD val) override;

		/**
		 * Write int in device process data
		 *
		 * @param addr Process data address
		 * @param val Value to write
		 */
		void writeInt(processDataAddress addr, int val) override;

		/**
		 * Write real in device process data
		 *
		 * @param addr Process data address
		 * @param val Value to write
		 */
		void writeReal(processDataAddress addr, float val) override;

		/**
		 * Create new driver process writer
		 *
		 * @return Pointer to the new driver process writer
		 */
		DriverProcessWriter* createNew() override;

		/**
		 * Send exit command to the server
		 */
		void sendServerExitCommand();

	private:
		/**
		 * Constructor with parameters (allowed only from ShmDriver)
		 *
		 * @param segmentName Shared memory segment name
		 * @param smem SHM structure handle
		 * @param lock Mutex for protecting driver
		 */
		ShmProcessWriter(const std::string& segmentName, sMemory *smem, const MutexAccess& lock);

		/// Shared memory segment name
		std::string shmName;

		/// Shared memory structure handle
		sMemory *shm;

		/// Mutex for protecting driver
		MutexAccess driverLock;

		/**
		 * Puts a request to server
		 *
		 * @param cmd The command
		 *
		 * @return Server reply command
		 */
		extCMD putRequest(extCMD cmd);

		/**
		 * Modify bit in process memory
		 *
		 * @param addr The command
		 * @param drvFunc Bit function
		 */
		void modifyBit(processDataAddress addr, int drvFunc);
};

}  // namespace onh

#endif  // ONH_DRIVER_SHM_SHMPROCESSWRITER_H_
