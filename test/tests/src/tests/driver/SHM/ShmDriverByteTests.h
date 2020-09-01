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

#ifndef TESTS_DRIVER_SHM_SHMDRIVERBYTETESTS_H_
#define TESTS_DRIVER_SHM_SHMDRIVERBYTETESTS_H_

#include <gtest/gtest.h>
#include "ShmDriverTestsFixtures.h"

/**
 * Check driver set input byte value
 */
TEST_F(shmDriverTests, writeInputByte) {

	// Test address
	onh::processDataAddress testAddr = {onh::PDA_INPUT, 2, 0};

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	shmWriter->writeByte(testAddr, 45);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		if (i == 2) {
			ASSERT_EQ(45, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		}

		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}
}

/**
 * Check driver set output byte value
 */
TEST_F(shmDriverTests, writeOutputByte) {

	// Test address
	onh::processDataAddress testAddr = {onh::PDA_OUTPUT, 2, 0};

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	shmWriter->writeByte(testAddr, 45);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		if (i == 2) {
			ASSERT_EQ(45, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		}

		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}
}

/**
 * Check driver set memory byte value
 */
TEST_F(shmDriverTests, writeMemoryByte) {

	// Test address
	onh::processDataAddress testAddr = {onh::PDA_MEMORY, 2, 0};

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	shmWriter->writeByte(testAddr, 45);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		if (i == 2) {
			ASSERT_EQ(45, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
		}

		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
	}
}

/**
 * Check exception on write byte (byte address wrong)
 */
TEST_F(shmDriverTests, exceptionWriteByte1) {

	try {

		shmWriter->writeByte({onh::PDA_INPUT, PROCESS_DT_SIZE+10, 0}, 45);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ShmProcessWriter::writeByte: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on write byte (bit address wrong)
 */
TEST_F(shmDriverTests, exceptionWriteByte2) {

	try {

		shmWriter->writeByte({onh::PDA_INPUT, 2, 9}, 45);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "DriverUtils::checkBitAddress: Wrong bit address");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on write byte (area address wrong)
 */
TEST_F(shmDriverTests, exceptionWriteByte3) {

	try {

		shmWriter->writeByte({(onh::processDataArea)8, 2, 4}, 45);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ShmProcessWriter::writeByte: Wrong address area");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on read byte (byte address wrong)
 */
TEST_F(shmDriverTests, exceptionReadByte1) {

	try {

		shmReader->getByte({onh::PDA_INPUT, PROCESS_DT_SIZE+10, 0});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ShmProcessData::getByte: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on read byte (bit address wrong)
 */
TEST_F(shmDriverTests, exceptionReadByte2) {

	try {

		shmReader->getByte({onh::PDA_INPUT, 2, 9});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "DriverUtils::checkBitAddress: Wrong bit address");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on read byte (area address wrong)
 */
TEST_F(shmDriverTests, exceptionReadByte3) {

	try {

		shmReader->getByte({(onh::processDataArea)8, 2, 4});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ShmProcessData::getByte: Wrong address area");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

#endif /* TESTS_DRIVER_SHM_SHMDRIVERBYTETESTS_H_ */
