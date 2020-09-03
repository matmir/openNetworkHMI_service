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

#ifndef TESTS_DRIVER_MODBUS_MODBUSDRIVERBITTESTS_H_
#define TESTS_DRIVER_MODBUS_MODBUSDRIVERBITTESTS_H_

#include <gtest/gtest.h>
#include "ModbusDriverTestsFixtures.h"

/**
 * Check driver set bit value
 */
TEST_F(modbusDriverTests, setBit) {

	// Test address
	onh::processDataAddress testAddr = {onh::PDA_OUTPUT, 1, 3};

	ASSERT_FALSE(mbReader->getBitValue(testAddr));

	// Check all process data
	for (unsigned int i=0; i<maxBytes; ++i) {
		ASSERT_EQ(0, mbReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
	}

	mbWriter->setBit(testAddr);

	// Wait on synchronization
	waitOnSyncBit();

	ASSERT_TRUE(mbReader->getBitValue(testAddr));

	// Check all process data
	for (unsigned int i=0; i<maxBytes; ++i) {

		if (i == 1) {
			ASSERT_EQ(8, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
		}

		ASSERT_EQ(0, mbReader->getByte({onh::PDA_INPUT, i, 0}));
	}
}

/**
 * Check exception on set bit (byte address wrong)
 */
TEST_F(modbusDriverTests, exceptionSetBit1) {

	try {

		mbWriter->setBit({onh::PDA_OUTPUT, maxBytes+10, 0});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on set bit (bit address wrong)
 */
TEST_F(modbusDriverTests, exceptionSetBit2) {

	try {

		mbWriter->setBit({onh::PDA_OUTPUT, 2, 9});

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
TEST_F(modbusDriverTests, exceptionSetBit3) {

	try {

		mbWriter->setBit({(onh::processDataArea)70, 45, 3});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Area out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on set bit (area wrong)
 */
TEST_F(modbusDriverTests, exceptionSetBit4) {

	try {

		mbWriter->setBit({onh::PDA_INPUT, 45, 3});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Write to input area not allowed");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on set bit (area wrong)
 */
TEST_F(modbusDriverTests, exceptionSetBit5) {

	try {

		mbWriter->setBit({onh::PDA_MEMORY, 45, 3});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Memory area not allowed");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on get bit (byte address wrong)
 */
TEST_F(modbusDriverTests, exceptionGetBit1) {

	try {

		mbReader->getBitValue({onh::PDA_OUTPUT, maxBytes+10, 0});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on get bit (bit address wrong)
 */
TEST_F(modbusDriverTests, exceptionGetBit2) {

	try {

		mbReader->getBitValue({onh::PDA_OUTPUT, 2, 9});

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
TEST_F(modbusDriverTests, exceptionGetBit3) {

	try {

		mbReader->getBitValue({(onh::processDataArea)70, 45, 3});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Area out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on get bit (area wrong)
 */
TEST_F(modbusDriverTests, exceptionGetBit4) {

	try {

		mbReader->getBitValue({onh::PDA_MEMORY, 45, 3});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Memory area not allowed");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check driver invert bit value
 */
TEST_F(modbusDriverTests, invertBit) {

	// Test address
	onh::processDataAddress testAddr = {onh::PDA_OUTPUT, 6, 3};

	ASSERT_FALSE(mbReader->getBitValue(testAddr));

	// Check all process data
	for (unsigned int i=0; i<maxBytes; ++i) {
		ASSERT_EQ(0, mbReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
	}

	mbWriter->invertBit(testAddr);

	// Wait on synchronization
	waitOnSyncBit();

	ASSERT_TRUE(mbReader->getBitValue(testAddr));

	// Check all process data
	for (unsigned int i=0; i<maxBytes; ++i) {

		if (i == 6) {
			ASSERT_EQ(8, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
		}

		ASSERT_EQ(0, mbReader->getByte({onh::PDA_INPUT, i, 0}));
	}
}

/**
 * Check exception on invert bit (byte address wrong)
 */
TEST_F(modbusDriverTests, exceptionInvertBit1) {

	try {

		mbWriter->invertBit({onh::PDA_OUTPUT, maxBytes+10, 0});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on invert bit (bit address wrong)
 */
TEST_F(modbusDriverTests, exceptionInvertBit2) {

	try {

		mbWriter->invertBit({onh::PDA_OUTPUT, 2, 9});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "DriverUtils::checkBitAddress: Wrong bit address");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on invert bit (area wrong)
 */
TEST_F(modbusDriverTests, exceptionInvertBit3) {

	try {

		mbWriter->invertBit({(onh::processDataArea)70, 45, 3});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Area out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on invert bit (area wrong)
 */
TEST_F(modbusDriverTests, exceptionInvertBit4) {

	try {

		mbWriter->invertBit({onh::PDA_INPUT, 45, 3});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Write to input area not allowed");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on invert bit (area wrong)
 */
TEST_F(modbusDriverTests, exceptionInvertBit5) {

	try {

		mbWriter->invertBit({onh::PDA_MEMORY, 45, 3});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Memory area not allowed");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check driver reset bit value
 */
TEST_F(modbusDriverTests, resetBit) {

	// Test address
	onh::processDataAddress testAddr = {onh::PDA_OUTPUT, 6, 3};

	// Check all process data
	for (unsigned int i=0; i<maxBytes; ++i) {
		ASSERT_EQ(0, mbReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
	}

	ASSERT_FALSE(mbReader->getBitValue(testAddr));

	// 1001 1110
	mbWriter->writeByte(testAddr, 158);

	// Wait on synchronization
	waitOnSyncBit();

	ASSERT_TRUE(mbReader->getBitValue(testAddr));

	mbWriter->resetBit(testAddr);

	// Wait on synchronization
	waitOnSyncBit();

	ASSERT_FALSE(mbReader->getBitValue(testAddr));

	// Check all process data
	for (unsigned int i=0; i<maxBytes; ++i) {
		if (i == 6) {
			ASSERT_EQ(150, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
		}
		ASSERT_EQ(0, mbReader->getByte({onh::PDA_INPUT, i, 0}));
	}
}

/**
 * Check exception on reset bit (byte address wrong)
 */
TEST_F(modbusDriverTests, exceptionResetBit1) {

	try {

		mbWriter->resetBit({onh::PDA_OUTPUT, maxBytes+10, 0});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on reset bit (bit address wrong)
 */
TEST_F(modbusDriverTests, exceptionResetBit2) {

	try {

		mbWriter->resetBit({onh::PDA_OUTPUT, 2, 9});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "DriverUtils::checkBitAddress: Wrong bit address");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on reset bit (area wrong)
 */
TEST_F(modbusDriverTests, exceptionResetBit3) {

	try {

		mbWriter->resetBit({(onh::processDataArea)70, 45, 3});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Area out of range");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on reset bit (area wrong)
 */
TEST_F(modbusDriverTests, exceptionResetBit4) {

	try {

		mbWriter->resetBit({onh::PDA_INPUT, 45, 3});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Write to input area not allowed");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check exception on reset bit (area wrong)
 */
TEST_F(modbusDriverTests, exceptionResetBit5) {

	try {

		mbWriter->resetBit({onh::PDA_MEMORY, 45, 3});

		FAIL() << "Expected onh::DriverException";

	} catch (onh::DriverException &e) {

		ASSERT_STREQ(e.what(), "ModbusUtils::checkProcessAddress: Memory area not allowed");

	} catch(...) {
		FAIL() << "Expected onh::DriverException";
	}
}

/**
 * Check driver set bits
 */
TEST_F(modbusDriverTests, setBits) {

	// Prepare addresses to set
	std::vector<onh::processDataAddress> addr;
	addr.push_back({onh::PDA_OUTPUT, 1, 0});
	addr.push_back({onh::PDA_OUTPUT, 1, 2});
	addr.push_back({onh::PDA_OUTPUT, 1, 3});

	// Check all process data
	for (unsigned int i=0; i<maxBytes; ++i) {
		ASSERT_EQ(0, mbReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
	}

	// 00001101
	mbWriter->setBits(addr);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<maxBytes; ++i) {
		if (i == 1) {
			ASSERT_EQ(13, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
		}
		ASSERT_EQ(0, mbReader->getByte({onh::PDA_INPUT, i, 0}));
	}
}

/**
 * Check driver get bits
 */
TEST_F(modbusDriverTests, getBits1) {

	// Return vector
	std::vector<bool> ret;

	// Prepare addresses to set
	std::vector<onh::processDataAddress> addr;
	addr.push_back({onh::PDA_OUTPUT, 1, 0});
	addr.push_back({onh::PDA_OUTPUT, 1, 2});
	addr.push_back({onh::PDA_OUTPUT, 45, 5});
	addr.push_back({onh::PDA_OUTPUT, 14, 7});

	// Check all process data
	for (unsigned int i=0; i<maxBytes; ++i) {
		ASSERT_EQ(0, mbReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
	}

	mbWriter->setBits(addr);

	// Wait on synchronization
	waitOnSyncBit();

	addr.push_back({onh::PDA_OUTPUT, 15, 7});

	ret = mbReader->getBitsValue(addr);

	ASSERT_TRUE(ret[0]);
	ASSERT_TRUE(ret[1]);
	ASSERT_TRUE(ret[2]);
	ASSERT_TRUE(ret[3]);
	ASSERT_FALSE(ret[4]);

	// Check all process data
	for (unsigned int i=0; i<maxBytes; ++i) {
		if (i == 1) {
			ASSERT_EQ(5, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
		} else if (i == 14) {
			ASSERT_EQ(128, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
		} else if (i == 45) {
			ASSERT_EQ(32, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, mbReader->getByte({onh::PDA_OUTPUT, i, 0}));
		}

		ASSERT_EQ(0, mbReader->getByte({onh::PDA_INPUT, i, 0}));
	}
}


#endif /* TESTS_DRIVER_MODBUS_MODBUSDRIVERBITTESTS_H_ */
