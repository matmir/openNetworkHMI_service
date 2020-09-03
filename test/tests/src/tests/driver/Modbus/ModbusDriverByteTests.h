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

#ifndef TESTS_DRIVER_MODBUS_MODBUSDRIVERBYTETESTS_H_
#define TESTS_DRIVER_MODBUS_MODBUSDRIVERBYTETESTS_H_

#include <gtest/gtest.h>
#include "ModbusDriverTestsFixtures.h"

/**
 * Check driver set byte value
 */
TEST_F(modbusDriverTests, writeByte) {

	// Test address
	onh::processDataAddress testAddr = {onh::PDA_OUTPUT, 2, 0};

	// Check all process data
	for (unsigned int i=0; i<maxBytes; ++i) {
		ASSERT_EQ(0, mbReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
	}

	mbWriter->writeByte(testAddr, 45);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<maxBytes; ++i) {

		if (i == 2) {
			ASSERT_EQ(45, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
		}

		ASSERT_EQ(0, mbReader->getByte({onh::PDA_INPUT, i, 0}));
	}
}

/**
 * Check exception on write byte (byte address wrong)
 */
TEST_F(modbusDriverTests, exceptionWriteByte1) {

	try {

		mbWriter->writeByte({onh::PDA_OUTPUT, maxBytes+10, 0}, 45);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on write byte (bit address wrong)
 */
TEST_F(modbusDriverTests, exceptionWriteByte2) {

	try {

		mbWriter->writeByte({onh::PDA_OUTPUT, 2, 9}, 45);

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
TEST_F(modbusDriverTests, exceptionWriteByte3) {

	try {

		mbWriter->writeByte({(onh::processDataArea)8, 2, 4}, 45);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Area out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on write byte (area address wrong)
 */
TEST_F(modbusDriverTests, exceptionWriteByte4) {

	try {

		mbWriter->writeByte({onh::PDA_INPUT, 2, 4}, 45);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Write to input area not allowed");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on write byte (area address wrong)
 */
TEST_F(modbusDriverTests, exceptionWriteByte5) {

	try {

		mbWriter->writeByte({onh::PDA_MEMORY, 2, 4}, 45);

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Memory area not allowed");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on read byte (byte address wrong)
 */
TEST_F(modbusDriverTests, exceptionReadByte1) {

	try {

		mbReader->getByte({onh::PDA_OUTPUT, maxBytes+10, 0});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on read byte (bit address wrong)
 */
TEST_F(modbusDriverTests, exceptionReadByte2) {

	try {

		mbReader->getByte({onh::PDA_OUTPUT, 2, 9});

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
TEST_F(modbusDriverTests, exceptionReadByte3) {

	try {

		mbReader->getByte({(onh::processDataArea)8, 2, 4});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Area out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on read byte (area address wrong)
 */
TEST_F(modbusDriverTests, exceptionReadByte4) {

	try {

		mbReader->getByte({onh::PDA_MEMORY, 2, 4});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Memory area not allowed");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

#endif /* TESTS_DRIVER_MODBUS_MODBUSDRIVERBYTETESTS_H_ */
