/**
 * This file is part of openNetworkHMI.
 * Copyright (c) 2020 Mateusz Mirosławski.
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

#ifndef TESTS_DRIVER_SHM_SHMDRIVERREALTESTS_H_
#define TESTS_DRIVER_SHM_SHMDRIVERREALTESTS_H_

#include <gtest/gtest.h>
#include "ShmDriverTestsFixtures.h"

/**
 * Check driver set input REAL value
 */
TEST_F(shmDriverTests, writeInputReal) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	shmDriver->writeReal({onh::PDA_INPUT, 2, 0}, -49.709);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_EQ((float)-49.709, shmReader->getReal({onh::PDA_INPUT, i, 0}));
			// Skip checking bytes in float
			i += 3;
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}
}

/**
 * Check driver set output REAL value
 */
TEST_F(shmDriverTests, writeOutputReal) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	shmDriver->writeReal({onh::PDA_OUTPUT, 2, 0}, -49.709);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_EQ((float)-49.709, shmReader->getReal({onh::PDA_OUTPUT, i, 0}));
			// Skip checking bytes in float
			i += 3;
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}
}

/**
 * Check driver set memory REAL value
 */
TEST_F(shmDriverTests, writeMemoryReal) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	shmDriver->writeReal({onh::PDA_MEMORY, 2, 0}, -49.709);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_EQ((float)-49.709, shmReader->getReal({onh::PDA_MEMORY, i, 0}));
			// Skip checking bytes in float
			i += 3;
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
	}
}

/**
 * Check exception on write REAL (byte address wrong)
 */
TEST_F(shmDriverTests, exceptionWriteReal1) {

	try {

		shmDriver->writeReal({onh::PDA_INPUT, PROCESS_DT_SIZE-3, 0}, -49.709);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ShmDriver::writeReal: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on write REAL (bit address wrong)
 */
TEST_F(shmDriverTests, exceptionWriteReal2) {

	try {

		shmDriver->writeReal({onh::PDA_INPUT, 80, 9}, -49.709);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "DriverUtils::checkBitAddress: Wrong bit address");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on write REAL (area address wrong)
 */
TEST_F(shmDriverTests, exceptionWriteReal3) {

	try {

		shmDriver->writeReal({(onh::processDataArea)8, 2, 4}, -49.709);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ShmDriver::writeReal: Wrong address area");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on read REAL (byte address wrong)
 */
TEST_F(shmDriverTests, exceptionReadReal1) {

	try {

		shmReader->getReal({onh::PDA_INPUT, PROCESS_DT_SIZE-3, 0});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ShmProcessReader::getReal: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on read REAL (bit address wrong)
 */
TEST_F(shmDriverTests, exceptionReadReal2) {

	try {

		shmReader->getReal({onh::PDA_INPUT, 80, 9});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "DriverUtils::checkBitAddress: Wrong bit address");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on read REAL (area address wrong)
 */
TEST_F(shmDriverTests, exceptionReadReal3) {

	try {

		shmReader->getReal({(onh::processDataArea)8, 2, 4});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ShmProcessReader::getReal: Wrong address area");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

#endif /* TESTS_DRIVER_SHM_SHMDRIVERREALTESTS_H_ */
