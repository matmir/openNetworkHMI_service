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

#ifndef TESTS_DRIVER_SHM_SHMDRIVERBITTESTS_H_
#define TESTS_DRIVER_SHM_SHMDRIVERBITTESTS_H_

#include <gtest/gtest.h>
#include "ShmDriverTestsFixtures.h"

/**
 * Check driver set input bit value
 */
TEST_F(shmDriverTests, setInputBit) {

	// Test address
	onh::processDataAddress testAddr = {onh::PDA_INPUT, 1, 3};

	ASSERT_FALSE(shmReader->getBitValue(testAddr));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	shmDriver->setBit(testAddr);

	// Wait on synchronization
	waitOnSyncBit();

	ASSERT_TRUE(shmReader->getBitValue(testAddr));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		if (i == 1) {
			ASSERT_EQ(8, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		}

		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}
}

/**
 * Check driver set output bit value
 */
TEST_F(shmDriverTests, setOutputBit) {

	// Test address
	onh::processDataAddress testAddr = {onh::PDA_OUTPUT, 1, 3};

	ASSERT_FALSE(shmReader->getBitValue(testAddr));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	shmDriver->setBit(testAddr);

	// Wait on synchronization
	waitOnSyncBit();

	ASSERT_TRUE(shmReader->getBitValue(testAddr));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		if (i == 1) {
			ASSERT_EQ(8, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		}

		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}
}

/**
 * Check driver set memory bit value
 */
TEST_F(shmDriverTests, setMemoryBit) {

	// Test address
	onh::processDataAddress testAddr = {onh::PDA_MEMORY, 10, 4};

	ASSERT_FALSE(shmReader->getBitValue(testAddr));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	shmDriver->setBit(testAddr);

	// Wait on synchronization
	waitOnSyncBit();

	ASSERT_TRUE(shmReader->getBitValue(testAddr));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		if (i == 10) {
			ASSERT_EQ(16, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
		}

		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
	}
}

/**
 * Check exception on set bit (byte address wrong)
 */
TEST_F(shmDriverTests, exceptionSetBit1) {

	try {

		shmDriver->setBit({onh::PDA_INPUT, PROCESS_DT_SIZE+10, 0});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ShmDriver::modifyBit: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on set bit (bit address wrong)
 */
TEST_F(shmDriverTests, exceptionSetBit2) {

	try {

		shmDriver->setBit({onh::PDA_INPUT, 45, 9});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "DriverUtils::checkBitAddress: Wrong bit address");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on set bit (area wrong)
 */
TEST_F(shmDriverTests, exceptionSetBit3) {

	try {

		shmDriver->setBit({(onh::processDataArea)70, 45, 3});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ShmDriver::modifyBit: Wrong address area");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on get bit (byte address wrong)
 */
TEST_F(shmDriverTests, exceptionGetBit1) {

	try {

		shmReader->getBitValue({onh::PDA_INPUT, PROCESS_DT_SIZE+10, 0});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ShmProcessReader::getBitValue: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on sgt bit (bit address wrong)
 */
TEST_F(shmDriverTests, exceptionGetBit2) {

	try {

		shmReader->getBitValue({onh::PDA_INPUT, 45, 9});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "DriverUtils::checkBitAddress: Wrong bit address");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on get bit (area wrong)
 */
TEST_F(shmDriverTests, exceptionGetBit3) {

	try {

		shmReader->getBitValue({(onh::processDataArea)70, 45, 3});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ShmProcessReader::getBitValue: Wrong address area");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check driver invert input bit value
 */
TEST_F(shmDriverTests, invertInputBit) {

	// Test address
	onh::processDataAddress testAddr = {onh::PDA_INPUT, 6, 3};

	ASSERT_FALSE(shmReader->getBitValue(testAddr));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	shmDriver->invertBit(testAddr);

	// Wait on synchronization
	waitOnSyncBit();

	ASSERT_TRUE(shmReader->getBitValue(testAddr));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		if (i == 6) {
			ASSERT_EQ(8, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		}

		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}
}

/**
 * Check driver invert output bit value
 */
TEST_F(shmDriverTests, invertOutputBit) {

	// Test address
	onh::processDataAddress testAddr = {onh::PDA_OUTPUT, 6, 3};

	ASSERT_FALSE(shmReader->getBitValue(testAddr));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	shmDriver->invertBit(testAddr);

	// Wait on synchronization
	waitOnSyncBit();

	ASSERT_TRUE(shmReader->getBitValue(testAddr));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		if (i == 6) {
			ASSERT_EQ(8, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		}

		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}
}

/**
 * Check driver invert memory bit value
 */
TEST_F(shmDriverTests, invertMemoryBit) {

	// Test address
	onh::processDataAddress testAddr = {onh::PDA_MEMORY, 6, 3};

	ASSERT_FALSE(shmReader->getBitValue(testAddr));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	shmDriver->invertBit(testAddr);

	// Wait on synchronization
	waitOnSyncBit();

	ASSERT_TRUE(shmReader->getBitValue(testAddr));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		if (i == 6) {
			ASSERT_EQ(8, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
		}

		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
	}
}

/**
 * Check driver reset input bit value
 */
TEST_F(shmDriverTests, resetInputBit) {

	// Test address
	onh::processDataAddress testAddr = {onh::PDA_INPUT, 6, 3};

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	ASSERT_FALSE(shmReader->getBitValue(testAddr));

	// 1001 1110
	shmDriver->writeByte(testAddr, 158);

	// Wait on synchronization
	waitOnSyncBit();

	ASSERT_TRUE(shmReader->getBitValue(testAddr));

	shmDriver->resetBit(testAddr);

	// Wait on synchronization
	waitOnSyncBit();

	ASSERT_FALSE(shmReader->getBitValue(testAddr));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 6) {
			ASSERT_EQ(150, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		}
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}
}

/**
 * Check driver reset output bit value
 */
TEST_F(shmDriverTests, resetOutputBit) {

	// Test address
	onh::processDataAddress testAddr = {onh::PDA_OUTPUT, 6, 3};

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	ASSERT_FALSE(shmReader->getBitValue(testAddr));

	// 1001 1110
	shmDriver->writeByte(testAddr, 158);

	// Wait on synchronization
	waitOnSyncBit();

	ASSERT_TRUE(shmReader->getBitValue(testAddr));

	shmDriver->resetBit(testAddr);

	// Wait on synchronization
	waitOnSyncBit();

	ASSERT_FALSE(shmReader->getBitValue(testAddr));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 6) {
			ASSERT_EQ(150, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		}
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}
}

/**
 * Check driver reset memory bit value
 */
TEST_F(shmDriverTests, resetMemoryBit) {

	// Test address
	onh::processDataAddress testAddr = {onh::PDA_MEMORY, 6, 3};

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	ASSERT_FALSE(shmReader->getBitValue(testAddr));

	// 1001 1110
	shmDriver->writeByte(testAddr, 158);

	// Wait on synchronization
	waitOnSyncBit();

	ASSERT_TRUE(shmReader->getBitValue(testAddr));

	shmDriver->resetBit(testAddr);

	// Wait on synchronization
	waitOnSyncBit();

	ASSERT_FALSE(shmReader->getBitValue(testAddr));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 6) {
			ASSERT_EQ(150, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
		}
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
	}
}

/**
 * Check driver set input bits
 */
TEST_F(shmDriverTests, setInputBits) {

	// Prepare addresses to set
	std::vector<onh::processDataAddress> addr;
	addr.push_back({onh::PDA_INPUT, 1, 0});
	addr.push_back({onh::PDA_INPUT, 1, 2});
	addr.push_back({onh::PDA_INPUT, 1, 3});

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	// 00001101
	shmDriver->setBits(addr);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 1) {
			ASSERT_EQ(13, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		}
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
	}
}

/**
 * Check driver set output bits
 */
TEST_F(shmDriverTests, setOutputBits) {

	// Prepare addresses to set
	std::vector<onh::processDataAddress> addr;
	addr.push_back({onh::PDA_OUTPUT, 1, 0});
	addr.push_back({onh::PDA_OUTPUT, 1, 2});
	addr.push_back({onh::PDA_OUTPUT, 1, 3});

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	// 00001101
	shmDriver->setBits(addr);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 1) {
			ASSERT_EQ(13, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		}
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
	}
}

/**
 * Check driver set memory bits
 */
TEST_F(shmDriverTests, setMemoryBits) {

	// Prepare addresses to set
	std::vector<onh::processDataAddress> addr;
	addr.push_back({onh::PDA_MEMORY, 1, 0});
	addr.push_back({onh::PDA_MEMORY, 1, 2});
	addr.push_back({onh::PDA_MEMORY, 1, 3});

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	// 00001101
	shmDriver->setBits(addr);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 1) {
			ASSERT_EQ(13, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
		}
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
	}
}

/**
 * Check driver set bits
 */
TEST_F(shmDriverTests, setBits1) {

	// Prepare addresses to set
	std::vector<onh::processDataAddress> addr;
	addr.push_back({onh::PDA_MEMORY, 1, 0});
	addr.push_back({onh::PDA_MEMORY, 1, 2});
	addr.push_back({onh::PDA_INPUT, 100, 5});
	addr.push_back({onh::PDA_OUTPUT, 4800, 7});

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	shmDriver->setBits(addr);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 1) {
			ASSERT_EQ(5, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
		}

		if (i == 100) {
			ASSERT_EQ(32, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		}

		if (i == 4800) {
			ASSERT_EQ(128, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		}
	}
}

/**
 * Check driver set bits exception (byte address wrong)
 */
TEST_F(shmDriverTests, exceptionSetBits1) {

	// Prepare addresses to set
	std::vector<onh::processDataAddress> addr;
	addr.push_back({onh::PDA_MEMORY, 1, 0});
	addr.push_back({onh::PDA_MEMORY, PROCESS_DT_SIZE+10, 2});
	addr.push_back({onh::PDA_INPUT, 100, 5});
	addr.push_back({onh::PDA_OUTPUT, 4800, 7});

	try {

		shmDriver->setBits(addr);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ShmDriver::setBits: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check driver set bits exception (bit address wrong)
 */
TEST_F(shmDriverTests, exceptionSetBits2) {

	// Prepare addresses to set
	std::vector<onh::processDataAddress> addr;
	addr.push_back({onh::PDA_MEMORY, 1, 0});
	addr.push_back({onh::PDA_MEMORY, 10, 2});
	addr.push_back({onh::PDA_INPUT, 100, 14});
	addr.push_back({onh::PDA_OUTPUT, 4800, 7});

	try {

		shmDriver->setBits(addr);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "DriverUtils::checkBitAddress: Wrong bit address");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check driver set bits exception (area wrong)
 */
TEST_F(shmDriverTests, exceptionSetBits3) {

	// Prepare addresses to set
	std::vector<onh::processDataAddress> addr;
	addr.push_back({onh::PDA_MEMORY, 1, 0});
	addr.push_back({onh::PDA_MEMORY, 10, 2});
	addr.push_back({(onh::processDataArea)5, 100, 4});
	addr.push_back({onh::PDA_OUTPUT, 4800, 7});

	try {

		shmDriver->setBits(addr);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ShmDriver::setBits: Wrong address area");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check driver set bits exception (too much tags to set)
 */
TEST_F(shmDriverTests, exceptionSetBits4) {

	// Maximum number bits to set (one bit need 3 ints of data)
	unsigned int maxTags = CMD_DATA_SIZE / 3;

	// Addresses
	std::vector<onh::processDataAddress> addr;

	// Prepare addresses to set (Add one tag more to trigger error)
	for (unsigned int i=0; i<(maxTags+1); ++i) {
		addr.push_back({onh::PDA_INPUT, i, 0});
	}

	try {

		shmDriver->setBits(addr);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		std::stringstream s;
		s << "ShmDriver::setBits: ";
		s << "Too much bits to set - max numbers bits to set is " << maxTags << " received " << addr.size();

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check driver get bits
 */
TEST_F(shmDriverTests, getBits1) {

	// Return vector
	std::vector<bool> ret;

	// Prepare addresses to set
	std::vector<onh::processDataAddress> addr;
	addr.push_back({onh::PDA_MEMORY, 1, 0});
	addr.push_back({onh::PDA_MEMORY, 1, 2});
	addr.push_back({onh::PDA_INPUT, 100, 5});
	addr.push_back({onh::PDA_OUTPUT, 4800, 7});

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	shmDriver->setBits(addr);

	// Wait on synchronization
	waitOnSyncBit();

	addr.push_back({onh::PDA_OUTPUT, 4801, 7});

	ret = shmReader->getBitsValue(addr);

	ASSERT_TRUE(ret[0]);
	ASSERT_TRUE(ret[1]);
	ASSERT_TRUE(ret[2]);
	ASSERT_TRUE(ret[3]);
	ASSERT_FALSE(ret[4]);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 1) {
			ASSERT_EQ(5, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
		}

		if (i == 100) {
			ASSERT_EQ(32, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		}

		if (i == 4800) {
			ASSERT_EQ(128, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		}
	}
}

/**
 * Check driver get bits exception (byte address wrong)
 */
TEST_F(shmDriverTests, exceptionGetBits1) {

	// Prepare addresses to set
	std::vector<onh::processDataAddress> addr;
	addr.push_back({onh::PDA_MEMORY, 1, 0});
	addr.push_back({onh::PDA_MEMORY, PROCESS_DT_SIZE+10, 2});
	addr.push_back({onh::PDA_INPUT, 100, 5});
	addr.push_back({onh::PDA_OUTPUT, 4800, 7});

	try {

		shmReader->getBitsValue(addr);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ShmProcessReader::getBitValue: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check driver get bits exception (bit address wrong)
 */
TEST_F(shmDriverTests, exceptionGetBits2) {

	// Prepare addresses to set
	std::vector<onh::processDataAddress> addr;
	addr.push_back({onh::PDA_MEMORY, 1, 0});
	addr.push_back({onh::PDA_MEMORY, 8, 2});
	addr.push_back({onh::PDA_INPUT, 100, 15});
	addr.push_back({onh::PDA_OUTPUT, 4800, 7});

	try {

		shmReader->getBitsValue(addr);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "DriverUtils::checkBitAddress: Wrong bit address");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check driver get bits exception (area address wrong)
 */
TEST_F(shmDriverTests, exceptionGetBits3) {

	// Prepare addresses to set
	std::vector<onh::processDataAddress> addr;
	addr.push_back({onh::PDA_MEMORY, 1, 0});
	addr.push_back({(onh::processDataArea)5, 8, 2});
	addr.push_back({onh::PDA_INPUT, 100, 5});
	addr.push_back({onh::PDA_OUTPUT, 4800, 7});

	try {

		shmReader->getBitsValue(addr);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ShmProcessReader::getBitValue: Wrong address area");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

#endif /* TESTS_DRIVER_SHM_SHMDRIVERBITTESTS_H_ */
