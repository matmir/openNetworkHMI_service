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

#ifndef TESTS_DRIVER_SHM_SHMDRIVERWORDTESTS_H_
#define TESTS_DRIVER_SHM_SHMDRIVERWORDTESTS_H_

#include <gtest/gtest.h>
#include "ShmDriverTestsFixtures.h"

/**
 * Check driver set input WORD value
 */
TEST_F(shmDriverTests, writeInputWord) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	shmWriter->writeWord({onh::PDA_INPUT, 2, 0}, 45801);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_EQ(45801, shmReader->getWord({onh::PDA_INPUT, i, 0}));
			ASSERT_EQ(233, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		} else if (i==3) {
			ASSERT_EQ(178, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		}

		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}
}

/**
 * Check driver set output WORD value
 */
TEST_F(shmDriverTests, writeOutputWord) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	shmWriter->writeWord({onh::PDA_OUTPUT, 2, 0}, 45801);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_EQ(45801, shmReader->getWord({onh::PDA_OUTPUT, i, 0}));
			ASSERT_EQ(233, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		} else if (i==3) {
			ASSERT_EQ(178, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		}

		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}
}

/**
 * Check driver set memory WORD value
 */
TEST_F(shmDriverTests, writeMemoryWord) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	shmWriter->writeWord({onh::PDA_MEMORY, 2, 0}, 45801);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_EQ(45801, shmReader->getWord({onh::PDA_MEMORY, i, 0}));
			ASSERT_EQ(233, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
		} else if (i==3) {
			ASSERT_EQ(178, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
		}

		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
	}
}

/**
 * Check exception on write WORD (byte address wrong)
 */
TEST_F(shmDriverTests, exceptionWriteWord1) {

	try {

		shmWriter->writeWord({onh::PDA_INPUT, PROCESS_DT_SIZE-1, 0}, 45);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ShmProcessWriter::writeWord: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on write WORD (bit address wrong)
 */
TEST_F(shmDriverTests, exceptionWriteWord2) {

	try {

		shmWriter->writeWord({onh::PDA_INPUT, 80, 9}, 45);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "DriverUtils::checkBitAddress: Wrong bit address");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on write WORD (area address wrong)
 */
TEST_F(shmDriverTests, exceptionWriteWord3) {

	try {

		shmWriter->writeWord({(onh::processDataArea)8, 2, 4}, 45);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ShmProcessWriter::writeWord: Wrong address area");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on read WORD (byte address wrong)
 */
TEST_F(shmDriverTests, exceptionReadWord1) {

	try {

		shmReader->getWord({onh::PDA_INPUT, PROCESS_DT_SIZE-1, 0});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ShmProcessData::getWord: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on write WORD (bit address wrong)
 */
TEST_F(shmDriverTests, exceptionReadWord2) {

	try {

		shmReader->getWord({onh::PDA_INPUT, 80, 9});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "DriverUtils::checkBitAddress: Wrong bit address");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on read WORD (area address wrong)
 */
TEST_F(shmDriverTests, exceptionReadWord3) {

	try {

		shmReader->getWord({(onh::processDataArea)8, 2, 4});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ShmProcessData::getWord: Wrong address area");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

#endif /* TESTS_DRIVER_SHM_SHMDRIVERWORDTESTS_H_ */
