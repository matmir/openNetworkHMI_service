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

#ifndef TESTS_DRIVER_MODBUS_MODBUSDRIVERDWORDTESTS_H_
#define TESTS_DRIVER_MODBUS_MODBUSDRIVERDWORDTESTS_H_

#include <gtest/gtest.h>
#include "ModbusDriverTestsFixtures.h"

/**
 * Check driver set output DWORD value
 */
TEST_F(modbusDriverTests, writeOutputDWord1) {

	// Check all process data
	for (unsigned int i=0; i<maxBytes; ++i) {
		ASSERT_EQ(0, mbReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
	}

	// 1110 0010 1100 0110 0101 0001 1101 1100
	mbWriter->writeDWord({onh::PDA_OUTPUT, 2, 0}, 3804647900);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<maxBytes; ++i) {
		switch (i) {
			case 2: {
					ASSERT_EQ((DWORD)3804647900, mbReader->getDWord({onh::PDA_OUTPUT, i, 0}));
					ASSERT_EQ(20956, mbReader->getWord({onh::PDA_OUTPUT, i, 0}));
					ASSERT_EQ(220, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
				}; break;
			case 3: {
					ASSERT_EQ(50769, mbReader->getWord({onh::PDA_OUTPUT, i, 0}));
					ASSERT_EQ(81, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
				}; break;
			case 4: {
					ASSERT_EQ(58054, mbReader->getWord({onh::PDA_OUTPUT, i, 0}));
					ASSERT_EQ(198, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
				}; break;
			case 5: {
					ASSERT_EQ(226, mbReader->getWord({onh::PDA_OUTPUT, i, 0}));
					ASSERT_EQ(226, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
				}; break;
			default: ASSERT_EQ(0, mbReader->getByte({onh::PDA_OUTPUT, i, 0})) << " i: " << i; break;
		}

		ASSERT_EQ(0, mbReader->getByte({onh::PDA_INPUT, i, 0}));
	}
}

TEST_F(modbusDriverTests, writeOutputDWord2) {

	// Check all process data
	for (unsigned int i=0; i<maxBytes; ++i) {
		ASSERT_EQ(0, mbReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
	}

	// 1110 0010 1100 0110 0101 0001 1101 1100
	mbWriter->writeDWord({onh::PDA_OUTPUT, 7, 0}, 3804647900);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<maxBytes; ++i) {
		switch (i) {
			case 7: {
					ASSERT_EQ((DWORD)3804647900, mbReader->getDWord({onh::PDA_OUTPUT, i, 0}));
					ASSERT_EQ(20956, mbReader->getWord({onh::PDA_OUTPUT, i, 0}));
					ASSERT_EQ(220, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
				}; break;
			case 8: {
					ASSERT_EQ(50769, mbReader->getWord({onh::PDA_OUTPUT, i, 0}));
					ASSERT_EQ(81, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
				}; break;
			case 9: {
					ASSERT_EQ(58054, mbReader->getWord({onh::PDA_OUTPUT, i, 0}));
					ASSERT_EQ(198, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
				}; break;
			case 10: {
					ASSERT_EQ(226, mbReader->getWord({onh::PDA_OUTPUT, i, 0}));
					ASSERT_EQ(226, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
				}; break;
			default: ASSERT_EQ(0, mbReader->getByte({onh::PDA_OUTPUT, i, 0})) << " i: " << i; break;
		}

		ASSERT_EQ(0, mbReader->getByte({onh::PDA_INPUT, i, 0}));
	}
}

/**
 * Check exception on write DWORD (byte address wrong)
 */
TEST_F(modbusDriverTests, exceptionWriteDWord1) {

	try {

		mbWriter->writeDWord({onh::PDA_OUTPUT, maxBytes-3, 0}, 3804647900);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on write DWORD (bit address wrong)
 */
TEST_F(modbusDriverTests, exceptionWriteDWord2) {

	try {

		mbWriter->writeDWord({onh::PDA_OUTPUT, 80, 9}, 3804647900);

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
TEST_F(modbusDriverTests, exceptionWriteDWord3) {

	try {

		mbWriter->writeDWord({(onh::processDataArea)8, 2, 4}, 3804647900);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Area out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on write DWORD (area address wrong)
 */
TEST_F(modbusDriverTests, exceptionWriteDWord4) {

	try {

		mbWriter->writeDWord({onh::PDA_INPUT, 2, 4}, 45);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Write to input area not allowed");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on write DWORD (area address wrong)
 */
TEST_F(modbusDriverTests, exceptionWriteDWord5) {

	try {

		mbWriter->writeDWord({onh::PDA_MEMORY, 2, 4}, 45);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Memory area not allowed");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on read DWORD (byte address wrong)
 */
TEST_F(modbusDriverTests, exceptionReadDWord1) {

	try {

		mbReader->getDWord({onh::PDA_OUTPUT, maxBytes-1, 0});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on write DWORD (bit address wrong)
 */
TEST_F(modbusDriverTests, exceptionReadDWord2) {

	try {

		mbReader->getDWord({onh::PDA_OUTPUT, 80, 9});

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
TEST_F(modbusDriverTests, exceptionReadDWord3) {

	try {

		mbReader->getDWord({(onh::processDataArea)8, 2, 4});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Area out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on read DWORD (area address wrong)
 */
TEST_F(modbusDriverTests, exceptionReadDWord4) {

	try {

		mbReader->getDWord({onh::PDA_MEMORY, 2, 4});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Memory area not allowed");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

#endif /* TESTS_DRIVER_MODBUS_MODBUSDRIVERDWORDTESTS_H_ */
