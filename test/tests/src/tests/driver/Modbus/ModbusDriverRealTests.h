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

#ifndef TESTS_DRIVER_MODBUS_MODBUSDRIVERREALTESTS_H_
#define TESTS_DRIVER_MODBUS_MODBUSDRIVERREALTESTS_H_

#include <gtest/gtest.h>
#include "ModbusDriverTestsFixtures.h"

/**
 * Check driver set output REAL value
 */
TEST_F(modbusDriverTests, writeOutputReal1) {

	// Check all process data
	for (unsigned int i=0; i<maxBytes; ++i) {
		ASSERT_EQ(0, mbReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
	}

	mbWriter->writeReal({onh::PDA_OUTPUT, 2, 0}, -49.709);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<maxBytes; ++i) {
		if (i == 2) {
			ASSERT_EQ((float)-49.709, mbReader->getReal({onh::PDA_OUTPUT, i, 0}));
			// Skip checking bytes in float
			i += 3;
		} else {
			ASSERT_EQ(0, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
		}
	}
	for (unsigned int i=0; i<maxBytes; ++i) {
		ASSERT_EQ(0, mbReader->getByte({onh::PDA_INPUT, i, 0}));
	}
}

TEST_F(modbusDriverTests, writeOutputReal2) {

	// Check all process data
	for (unsigned int i=0; i<maxBytes; ++i) {
		ASSERT_EQ(0, mbReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
	}

	mbWriter->writeReal({onh::PDA_OUTPUT, 7, 0}, -49.709);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<maxBytes; ++i) {
		if (i == 7) {
			ASSERT_EQ((float)-49.709, mbReader->getReal({onh::PDA_OUTPUT, i, 0}));
			// Skip checking bytes in float
			i += 3;
		} else {
			ASSERT_EQ(0, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
		}
	}
	for (unsigned int i=0; i<maxBytes; ++i) {
		ASSERT_EQ(0, mbReader->getByte({onh::PDA_INPUT, i, 0}));
	}
}

/**
 * Check exception on write REAL (byte address wrong)
 */
TEST_F(modbusDriverTests, exceptionWriteReal1) {

	try {

		mbWriter->writeReal({onh::PDA_OUTPUT, maxBytes-3, 0}, -49.709);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on write REAL (bit address wrong)
 */
TEST_F(modbusDriverTests, exceptionWriteReal2) {

	try {

		mbWriter->writeReal({onh::PDA_OUTPUT, 80, 9}, -49.709);

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
TEST_F(modbusDriverTests, exceptionWriteReal3) {

	try {

		mbWriter->writeReal({(onh::processDataArea)8, 2, 4}, -49.709);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Area out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on write REAL (area address wrong)
 */
TEST_F(modbusDriverTests, exceptionWriteReal4) {

	try {

		mbWriter->writeReal({onh::PDA_INPUT, 2, 4}, 45);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Write to input area not allowed");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on write Real (area address wrong)
 */
TEST_F(modbusDriverTests, exceptionWriteReal5) {

	try {

		mbWriter->writeReal({onh::PDA_MEMORY, 2, 4}, 45);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Memory area not allowed");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on read REAL (byte address wrong)
 */
TEST_F(modbusDriverTests, exceptionReadReal1) {

	try {

		mbReader->getReal({onh::PDA_OUTPUT, maxBytes-3, 0});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on read REAL (bit address wrong)
 */
TEST_F(modbusDriverTests, exceptionReadReal2) {

	try {

		mbReader->getReal({onh::PDA_OUTPUT, 80, 9});

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
TEST_F(modbusDriverTests, exceptionReadReal3) {

	try {

		mbReader->getReal({(onh::processDataArea)8, 2, 4});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Area out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on read REAL (area address wrong)
 */
TEST_F(modbusDriverTests, exceptionReadReal4) {

	try {

		mbReader->getReal({onh::PDA_MEMORY, 2, 4});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Memory area not allowed");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

#endif /* TESTS_DRIVER_MODBUS_MODBUSDRIVERREALTESTS_H_ */
