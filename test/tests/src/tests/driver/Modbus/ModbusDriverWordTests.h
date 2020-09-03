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

#ifndef TESTS_DRIVER_MODBUS_MODBUSDRIVERWORDTESTS_H_
#define TESTS_DRIVER_MODBUS_MODBUSDRIVERWORDTESTS_H_

#include <gtest/gtest.h>
#include "ModbusDriverTestsFixtures.h"

/**
 * Check driver set WORD value
 */
TEST_F(modbusDriverTests, writeOutputWord1) {

	// Check all process data
	for (unsigned int i=0; i<maxBytes; ++i) {
		ASSERT_EQ(0, mbReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
	}

	mbWriter->writeWord({onh::PDA_OUTPUT, 2, 0}, 45801);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<maxBytes; ++i) {
		if (i == 2) {
			ASSERT_EQ(45801, mbReader->getWord({onh::PDA_OUTPUT, i, 0}));
			ASSERT_EQ(233, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
		} else if (i==3) {
			ASSERT_EQ(178, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
		}

		ASSERT_EQ(0, mbReader->getByte({onh::PDA_INPUT, i, 0}));
	}
}

TEST_F(modbusDriverTests, writeOutputWord2) {

	// Check all process data
	for (unsigned int i=0; i<maxBytes; ++i) {
		ASSERT_EQ(0, mbReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
	}

	mbWriter->writeWord({onh::PDA_OUTPUT, 3, 0}, 45801);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<maxBytes; ++i) {
		if (i == 3) {
			ASSERT_EQ(45801, mbReader->getWord({onh::PDA_OUTPUT, i, 0}));
			ASSERT_EQ(233, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
		} else if (i==4) {
			ASSERT_EQ(178, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
		}

		ASSERT_EQ(0, mbReader->getByte({onh::PDA_INPUT, i, 0}));
	}
}

/**
 * Check exception on write WORD (byte address wrong)
 */
TEST_F(modbusDriverTests, exceptionWriteWord1) {

	try {

		mbWriter->writeWord({onh::PDA_OUTPUT, maxBytes-1, 0}, 45);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on write WORD (bit address wrong)
 */
TEST_F(modbusDriverTests, exceptionWriteWord2) {

	try {

		mbWriter->writeWord({onh::PDA_OUTPUT, 80, 9}, 45);

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
TEST_F(modbusDriverTests, exceptionWriteWord3) {

	try {

		mbWriter->writeWord({(onh::processDataArea)8, 2, 4}, 45);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Area out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on write WORD (area address wrong)
 */
TEST_F(modbusDriverTests, exceptionWriteWord4) {

	try {

		mbWriter->writeWord({onh::PDA_INPUT, 2, 4}, 45);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Write to input area not allowed");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on write WORD (area address wrong)
 */
TEST_F(modbusDriverTests, exceptionWriteWord5) {

	try {

		mbWriter->writeWord({onh::PDA_MEMORY, 2, 4}, 45);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Memory area not allowed");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on read WORD (byte address wrong)
 */
TEST_F(modbusDriverTests, exceptionReadWord1) {

	try {

		mbReader->getWord({onh::PDA_OUTPUT, maxBytes-1, 0});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on write WORD (bit address wrong)
 */
TEST_F(modbusDriverTests, exceptionReadWord2) {

	try {

		mbReader->getWord({onh::PDA_OUTPUT, 80, 9});

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
TEST_F(modbusDriverTests, exceptionReadWord3) {

	try {

		mbReader->getWord({(onh::processDataArea)8, 2, 4});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Area out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on read WORD (area address wrong)
 */
TEST_F(modbusDriverTests, exceptionReadWord4) {

	try {

		mbReader->getWord({onh::PDA_MEMORY, 2, 4});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Memory area not allowed");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

#endif /* TESTS_DRIVER_MODBUS_MODBUSDRIVERWORDTESTS_H_ */
