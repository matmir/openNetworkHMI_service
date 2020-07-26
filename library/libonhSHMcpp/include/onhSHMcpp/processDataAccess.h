/**
 * Copyright (c) 2020 Mateusz Mirosławski
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of mosquitto nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SRC_DRIVER_SHMSERVER_PROCESSDATAACCESS_H_
#define SRC_DRIVER_SHMSERVER_PROCESSDATAACCESS_H_

#include <vector>
#include "MutexAccess.h"
#include "processData.h"
#include "ProcessDataTypes.h"

namespace onh {

	/// Forward declaration
	class ShmServer;

	/**
	 * Process data access class
	 */
	class processDataAccess {

		friend class ShmServer;

		public:

			/**
			 * Copy constructor
			 *
			 * @param pda processDataAccess object to copy
			 */
			processDataAccess(const processDataAccess& pda);

			virtual ~processDataAccess();

			/**
			 * Assign operator - inactive
			 */
			processDataAccess& operator=(const processDataAccess&) = delete;

			/**
			 * Get bit from process data
			 *
			 * @param addr Process data address
			 *
			 * @return Bit value from process data
			 */
			bool getBit(processDataAddress addr);

			/**
			 * Get bits from process data
			 *
			 * @param addr Vector with bits addresses
			 *
			 * @return Vector with bits value
			 */
			std::vector<bool> getBits(const std::vector<processDataAddress>& addr);

			/**
			 * Get byte from process data
			 *
			 * @param addr Process data address
			 *
			 * @return Byte value from process data
			 */
			BYTE getByte(processDataAddress addr);

			/**
			 * Get WORD from process data
			 *
			 * @param addr Process data address
			 *
			 * @return Word value from process data
			 */
			WORD getWord(processDataAddress addr);

			/**
			 * Get DWORD from process data
			 *
			 * @param addr Process data address
			 *
			 * @return Double word value from process data
			 */
			DWORD getDWord(processDataAddress addr);

			/**
			 * Get INT from process data
			 *
			 * @param addr Process data address
			 *
			 * @return Int value from process data
			 */
			int getInt(processDataAddress addr);

			/**
			 * Get REAL from process data
			 *
			 * @param addr Process data address
			 *
			 * @return Real value from process data
			 */
			float getReal(processDataAddress addr);

			/**
			 * Set bit in process data
			 *
			 * @param addr Process data address
			 */
			void setBit(processDataAddress addr);

			/**
			 * Write bit in process data
			 *
			 * @param addr Process data address
			 * @param val Bit value
			 */
			void writeBit(processDataAddress addr, bool val);

			/**
			 * Set bits in process data
			 *
			 * @param addr Vector with bits addresses
			 */
			void setBits(const std::vector<processDataAddress>& addr);

			/**
			 * Reset bit in process data
			 *
			 * @param addr Process data address
			 */
			void resetBit(processDataAddress addr);

			/**
			 * Invert bit in process data
			 *
			 * @param addr Process data address
			 */
			void invertBit(processDataAddress addr);

			/**
			 * Write BYTE in process data
			 *
			 * @param addr Process data address
			 * @param val Byte value
			 */
			void writeByte(processDataAddress addr, BYTE val);

			/**
			 * Write WORD in process data
			 *
			 * @param addr Process data address
			 * @param val WORD value
			 */
			void writeWord(processDataAddress addr, WORD val);

			/**
			 * Write DWORD in process data
			 *
			 * @param addr Process data address
			 * @param val	DWORD value
			 */
			void writeDWord(processDataAddress addr, DWORD val);

			/**
			 * Write INT in process data
			 *
			 * @param addr Process data address
			 * @param val Int value
			 */
			void writeInt(processDataAddress addr, int val);

			/**
			 * Write REAL in process data
			 *
			 * @param addr rocess data address
			 * @param val Real value
			 */
			void writeReal(processDataAddress addr, float val);

			/**
			 * Clear process data
			 *
			 * @param processIn Flags clears input process data
			 * @param processOut Flags clears output process data
			 * @param processMem Flags clears memory process data
			 */
			void clear(bool processIn = true, bool processOut = true, bool processMem = true);

		private:

			/**
			 * Constructor with parameters (allowed only from ShmServer)
			 *
			 * @param processDT Process data pointer
			 * @param lock Mutex access for protecting process data
			 */
			processDataAccess(processData *processDT, const MutexAccess& lock);

			/**
			 * Check bit address in address
			 *
			 * @param addr Process data address
			 */
			void checkBitAddress(processDataAddress addr);

			/**
			 * Check area value
			 *
			 * @param addr Process data address
			 */
			void checkArea(processDataAddress addr);

			/// Internal process data handle
			processData *process;

			/// Mutex for protecting internal process data
			MutexAccess processLock;
	};

}

#endif /* SRC_DRIVER_SHMSERVER_PROCESSDATAACCESS_H_ */
