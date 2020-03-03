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

#ifndef TESTS_DRIVER_SHM_SHMDRIVERDWORDTESTS_H_
#define TESTS_DRIVER_SHM_SHMDRIVERDWORDTESTS_H_

#include <gtest/gtest.h>
#include "ShmDriverTestsFixtures.h"

/**
 * Check driver set input DWORD value
 */
TEST_F(shmDriverTests, writeInputDWord) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	// 1110 0010 1100 0110 0101 0001 1101 1100
	shmDriver->writeDWord({onh::PDA_INPUT, 7, 0}, 3804647900);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		switch (i) {
			case 7: {
					ASSERT_EQ((DWORD)3804647900, shmReader->getDWord({onh::PDA_INPUT, i, 0}));
					ASSERT_EQ(20956, shmReader->getWord({onh::PDA_INPUT, i, 0}));
					ASSERT_EQ(220, shmReader->getByte({onh::PDA_INPUT, i, 0}));
				}; break;
			case 8: {
					ASSERT_EQ(50769, shmReader->getWord({onh::PDA_INPUT, i, 0}));
					ASSERT_EQ(81, shmReader->getByte({onh::PDA_INPUT, i, 0}));
				}; break;
			case 9: {
					ASSERT_EQ(58054, shmReader->getWord({onh::PDA_INPUT, i, 0}));
					ASSERT_EQ(198, shmReader->getByte({onh::PDA_INPUT, i, 0}));
				}; break;
			case 10: {
					ASSERT_EQ(226, shmReader->getWord({onh::PDA_INPUT, i, 0}));
					ASSERT_EQ(226, shmReader->getByte({onh::PDA_INPUT, i, 0}));
				}; break;
			default: ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0})); break;
		}

		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}
}

/**
 * Check driver set output DWORD value
 */
TEST_F(shmDriverTests, writeOutputDWord) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	// 1110 0010 1100 0110 0101 0001 1101 1100
	shmDriver->writeDWord({onh::PDA_OUTPUT, 7, 0}, 3804647900);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		switch (i) {
			case 7: {
					ASSERT_EQ((DWORD)3804647900, shmReader->getDWord({onh::PDA_OUTPUT, i, 0}));
					ASSERT_EQ(20956, shmReader->getWord({onh::PDA_OUTPUT, i, 0}));
					ASSERT_EQ(220, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
				}; break;
			case 8: {
					ASSERT_EQ(50769, shmReader->getWord({onh::PDA_OUTPUT, i, 0}));
					ASSERT_EQ(81, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
				}; break;
			case 9: {
					ASSERT_EQ(58054, shmReader->getWord({onh::PDA_OUTPUT, i, 0}));
					ASSERT_EQ(198, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
				}; break;
			case 10: {
					ASSERT_EQ(226, shmReader->getWord({onh::PDA_OUTPUT, i, 0}));
					ASSERT_EQ(226, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
				}; break;
			default: ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0})); break;
		}

		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}
}

/**
 * Check driver set memory DWORD value
 */
TEST_F(shmDriverTests, writeMemoryDWord) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	// 1110 0010 1100 0110 0101 0001 1101 1100
	shmDriver->writeDWord({onh::PDA_MEMORY, 7, 0}, 3804647900);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		switch (i) {
			case 7: {
					ASSERT_EQ((DWORD)3804647900, shmReader->getDWord({onh::PDA_MEMORY, i, 0}));
					ASSERT_EQ(20956, shmReader->getWord({onh::PDA_MEMORY, i, 0}));
					ASSERT_EQ(220, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
				}; break;
			case 8: {
					ASSERT_EQ(50769, shmReader->getWord({onh::PDA_MEMORY, i, 0}));
					ASSERT_EQ(81, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
				}; break;
			case 9: {
					ASSERT_EQ(58054, shmReader->getWord({onh::PDA_MEMORY, i, 0}));
					ASSERT_EQ(198, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
				}; break;
			case 10: {
					ASSERT_EQ(226, shmReader->getWord({onh::PDA_MEMORY, i, 0}));
					ASSERT_EQ(226, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
				}; break;
			default: ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0})); break;
		}

		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
	}
}

/**
 * Check exception on write DWORD (byte address wrong)
 */
TEST_F(shmDriverTests, exceptionWriteDWord1) {

	try {

		shmDriver->writeDWord({onh::PDA_INPUT, PROCESS_DT_SIZE-3, 0}, 3804647900);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ShmDriver::writeDWord: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on write DWORD (bit address wrong)
 */
TEST_F(shmDriverTests, exceptionWriteDWord2) {

	try {

		shmDriver->writeDWord({onh::PDA_INPUT, 80, 9}, 3804647900);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "DriverUtils::checkBitAddress: Wrong bit address");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on write DWORD (area address wrong)
 */
TEST_F(shmDriverTests, exceptionWriteDWord3) {

	try {

		shmDriver->writeDWord({(onh::processDataArea)8, 2, 4}, 3804647900);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ShmDriver::writeDWord: Wrong address area");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on read DWORD (byte address wrong)
 */
TEST_F(shmDriverTests, exceptionReadDWord1) {

	try {

		shmReader->getDWord({onh::PDA_INPUT, PROCESS_DT_SIZE-1, 0});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ShmProcessReader::getDWord: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on write DWORD (bit address wrong)
 */
TEST_F(shmDriverTests, exceptionReadDWord2) {

	try {

		shmReader->getDWord({onh::PDA_INPUT, 80, 9});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "DriverUtils::checkBitAddress: Wrong bit address");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on read DWORD (area address wrong)
 */
TEST_F(shmDriverTests, exceptionReadDWord3) {

	try {

		shmReader->getDWord({(onh::processDataArea)8, 2, 4});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ShmProcessReader::getDWord: Wrong address area");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

#endif /* TESTS_DRIVER_SHM_SHMDRIVERDWORDTESTS_H_ */
