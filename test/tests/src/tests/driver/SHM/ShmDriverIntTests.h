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

#ifndef TESTS_DRIVER_SHM_SHMDRIVERINTTESTS_H_
#define TESTS_DRIVER_SHM_SHMDRIVERINTTESTS_H_

#include <gtest/gtest.h>
#include "ShmDriverTestsFixtures.h"

/**
 * Check driver set input INT value
 */
TEST_F(shmDriverTests, writeInputInt) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	shmWriter->writeInt({onh::PDA_INPUT, 2, 0}, -37489);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_EQ(-37489, shmReader->getInt({onh::PDA_INPUT, i, 0}));
			// Skip checking bytes in int
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
 * Check driver set output INT value
 */
TEST_F(shmDriverTests, writeOutputInt) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	shmWriter->writeInt({onh::PDA_OUTPUT, 2, 0}, -37489);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_EQ(-37489, shmReader->getInt({onh::PDA_OUTPUT, i, 0}));
			// Skip checking bytes in int
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
 * Check driver set memory INT value
 */
TEST_F(shmDriverTests, writeMemoryInt) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	shmWriter->writeInt({onh::PDA_MEMORY, 2, 0}, -37489);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_EQ(-37489, shmReader->getInt({onh::PDA_MEMORY, i, 0}));
			// Skip checking bytes in int
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
 * Check exception on write INT (byte address wrong)
 */
TEST_F(shmDriverTests, exceptionWriteInt1) {

	try {

		shmWriter->writeInt({onh::PDA_INPUT, PROCESS_DT_SIZE-3, 0}, -37489);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ShmProcessWriter::writeInt: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on write INT (bit address wrong)
 */
TEST_F(shmDriverTests, exceptionWriteInt2) {

	try {

		shmWriter->writeInt({onh::PDA_INPUT, 80, 9}, -37489);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "DriverUtils::checkBitAddress: Wrong bit address");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on write INT (area address wrong)
 */
TEST_F(shmDriverTests, exceptionWriteInt3) {

	try {

		shmWriter->writeInt({(onh::processDataArea)8, 2, 4}, -37489);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ShmProcessWriter::writeInt: Wrong address area");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on read INT (byte address wrong)
 */
TEST_F(shmDriverTests, exceptionReadInt1) {

	try {

		shmReader->getInt({onh::PDA_INPUT, PROCESS_DT_SIZE-3, 0});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ShmProcessData::getInt: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on read INT (bit address wrong)
 */
TEST_F(shmDriverTests, exceptionReadInt2) {

	try {

		shmReader->getInt({onh::PDA_INPUT, 80, 9});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "DriverUtils::checkBitAddress: Wrong bit address");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on read INT (area address wrong)
 */
TEST_F(shmDriverTests, exceptionReadInt3) {

	try {

		shmReader->getInt({(onh::processDataArea)8, 2, 4});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ShmProcessData::getInt: Wrong address area");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

#endif /* TESTS_DRIVER_SHM_SHMDRIVERINTTESTS_H_ */
