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
#include <onhSHMc/processDataAccess.h>
#include <onhSHMc/sMemoryServerProg.h>
#include <onhSHMc/sCommands.h>

class shmServerClearTest: public ::testing::Test {
	protected:
		void SetUp() override {
			// Clear local process data
			PROCESS_DATA_CLEAR(&procDT);

			// Clear SHM data
			shm_clearProcessData(ssdt.shm);
			shm_clearCSCommandData(ssdt.shm);
			shm_clearCSSyncData(ssdt.shm);

			exitFlag = 0;

			serverErr = SERVER_ERROR_NONE;
			shmErr = SHM_ERROR_NONE;
			procErr = PROCESS_ERROR_NONE;
		}

		void TearDown() override {

		}

		// Local process data
		processData procDT;

		// Exit program flag
		int exitFlag;

		// Error number
		int serverErr;
		int shmErr;
		int procErr;
};

#endif /* FIXTURES_SHMSERVERCLEARTEST_H_ */
