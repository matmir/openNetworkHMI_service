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

#ifndef FIXTURES_SHMSERVERCLEARTEST_H_
#define FIXTURES_SHMSERVERCLEARTEST_H_

#include <gtest/gtest.h>
#include "../pdaTestGlobalData.h"

class shmServerClearTest: public ::testing::Test {
	protected:
		void SetUp() override {

			// Clear all SHM data
			shmServer->clearAllData();
			shmServer->clearExitFlag();

			// Create Process data access object
			pda = new onh::processDataAccess(shmServer->getProcessAccess());
			// Clear all process data
			pda->clear();

			openClientSHM();
		}

		void TearDown() override {

			closeClientSHM();

			if (pda)
				delete pda;
		}

		void openClientSHM() {

			// Open shared memory segment
			sfd = shm_open(SHM_SEGMENT_NAME, O_RDWR, 0666);

			// Map shared memory segment in the address space of the process
			shm = (sMemory*) mmap(NULL, smSize, PROT_READ | PROT_WRITE, MAP_SHARED, sfd, 0);

			if (shm == MAP_FAILED) {
				throw ShmException("SHM is not initialized", "shmServerClearTest::openClientSHM");
			}
		}

		void closeClientSHM() {

			// Unmap shared memory
			munmap(shm, smSize);

			// Close shared memory object
			close(sfd);
		}

		// Process data access instance
		onh::processDataAccess *pda;

		// Shared memory structure
		sMemory *shm;

	private:
		/// Shared memory id
		int sfd;

		/// Shared memory size
		const int smSize = sizeof(sMemory);


};

#endif /* FIXTURES_SHMSERVERCLEARTEST_H_ */
