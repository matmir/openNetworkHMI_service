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

#ifndef SRC_DRIVER_SHMSERVER_SHMSERVER_H_
#define SRC_DRIVER_SHMSERVER_SHMSERVER_H_

#include "sMemory.h"
#include "processData.h"
#include "MutexContainer.h"
#include "processDataAccess.h"
#include "PDTag.h"

namespace onh {

	/**
	 * Shared memory server class
	 */
	class ShmServer {

		public:
			/**
			 * Shared memory server constructor
			 *
			 * @param shmSegmentName Shared memory segment name
			 */
			ShmServer(const std::string& shmSegmentName);

			virtual ~ShmServer();

			/**
			 * Parse client commands
			 */
			void parseClientCommand();

			/**
			 * Copy internal process data to the shared memory
			 *
			 * @return True if copy performed
			 */
			bool copyProcessData();

			/**
			 * Check exit program flag
			 *
			 * @return Exit program flag (True - program need to be closed)
			 */
			bool isExitFlag() const;

			/**
			 * Clear exit flag
			 */
			void clearExitFlag();

			/**
			 * Clear all SHM and process data
			 */
			void clearAllData();

			/**
			 * Clear process data
			 *
			 * @param internalDT Internal process data
			 * @param shmDT Shared memory process data
			 */
			void clearProcessData(bool internalDT = true, bool shmDT = true);

			/**
			 * Get process data access object
			 *
			 * @return Process data access object
			 */
			processDataAccess getProcessAccess();

			/**
			 * Get process tag
			 *
			 * @param tagAddr Tag address
			 * @return Process tag
			 */
			template <class T>
			PDTag<T> getTag(const processDataAddress &tagAddr);

		private:
			/// Exit program flag
			bool exitProgram;

			/// Shared memory size
			const int smSize = sizeof(sMemory);

			/// Shared memory id
			int sfd;

			/// Shared memory segment name
			std::string smName;

			/// Shared memory structure
			sMemory *shm;

			/// Internal process data
			processData process;

			/// Mutex for protecting internal process data
			MutexContainer processLock;

			/// Request command data
			extCMD requestDT;

			/// Reply command data
			extCMD replyDT;

			/// Process data access
			processDataAccess *pda;

			/**
			 * Clear internal command data
			 */
			void clearInternalCommandData();

			/**
			 * Clear Client-Server command data
			 */
			void clearCSCommandData();

			/**
			 * Clear Client-Server synchronization data
			 */
			void clearCSSyncData();

			/**
			 * Check if in SHM is request and read command
			 */
			bool isRequest();

			/**
			 * Put reply into SHM
			 */
			void putReply();

			/**
			 * Parse DRV_CMD_EXIT
			 */
			void CMD_EXIT();

			/**
			 * Parse DRV_CMD_PING
			 */
			void CMD_PING();

			/**
			 * Parse DRV_SET_BIT
			 */
			void CMD_SET_BIT();

			/**
			 * Parse DRV_RESET_BIT
			 */
			void CMD_RESET_BIT();

			/**
			 * Parse DRV_INVERT_BIT
			 */
			void CMD_INVERT_BIT();

			/**
			 * Parse DRV_SET_BITS
			 */
			void CMD_SET_BITS();

			/**
			 * Parse DRV_WRITE_BYTE
			 */
			void CMD_WRITE_BYTE();

			/**
			 * Parse DRV_WRITE_WORD
			 */
			void CMD_WRITE_WORD();

			/**
			 * Parse DRV_WRITE_DWORD
			 */
			void CMD_WRITE_DWORD();

			/**
			 * Parse DRV_WRITE_INT
			 */
			void CMD_WRITE_INT();

			/**
			 * Parse DRV_WRITE_REAL
			 */
			void CMD_WRITE_REAL();
	};

}

#endif /* SRC_DRIVER_SHMSERVER_SHMSERVER_H_ */
