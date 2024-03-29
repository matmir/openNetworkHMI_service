/**
 * Copyright (c) 2022 Mateusz Mirosławski
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

#include <iostream>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <gtest/gtest.h>

#include "pdaTestGlobalData.h"
#include "pdaByteTests.h"
#include "pdaBitTests.h"
#include "pdaWordTests.h"
#include "pdaDWordTests.h"
#include "pdaIntTests.h"
#include "pdaRealTests.h"
#include "shmServerTests.h"
#include "PDTagIdTests.h"
#include "PDTagBitTests.h"
#include "PDTagByteTests.h"
#include "PDTagWordTests.h"
#include "PDTagDWordTests.h"
#include "PDTagIntTests.h"
#include "PDTagRealTests.h"

using namespace std;

int main(int argc, char **argv) {

	cout << "\nC++ SHM server tests\n" << endl;

	// Create server
	shmServer = new onh::ShmServer(SHM_SEGMENT_NAME);

	// Run tests
	testing::InitGoogleTest(&argc, argv);
	int tstRes = RUN_ALL_TESTS();

	delete shmServer;

	cout << "\nSHM closed\n" << endl;

	return tstRes;
}
