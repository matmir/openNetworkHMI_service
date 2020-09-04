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

#ifndef TESTS_DRIVER_PROCESSWRITERTESTS_H_
#define TESTS_DRIVER_PROCESSWRITERTESTS_H_

#include <gtest/gtest.h>
#include "DriverTestsFixtures.h"

/**
 * Check process writer set bit
 */
TEST_F(driverTests, processWriterSetBit) {

	// Check all process data
	checkAllDataCleared();

	// Check test bit
	ASSERT_FALSE(procReader->getBitValue(testShmTag));
	ASSERT_FALSE(procReader->getBitValue(testModbusTag));

	// Change bit
	procWriter->setBit(testShmTag);

	// Wait on synchronization
	waitOnSyncBit();

	// Check test bit
	ASSERT_TRUE(procReader->getBitValue(testShmTag));
	ASSERT_FALSE(procReader->getBitValue(testModbusTag));

	// Change bit
	procWriter->setBit(testModbusTag);

	// Wait on synchronization
	waitOnSyncBit();

	// Check test bit
	ASSERT_TRUE(procReader->getBitValue(testShmTag));
	ASSERT_TRUE(procReader->getBitValue(testModbusTag));

	// Check all process data
	for (unsigned int i=0; i<maxShmBytes; ++i) {
		if (i == 5) {
			ASSERT_EQ(1, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		} else {
			ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0}))) << " i: " << i;
		}

		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}))) << " i: " << i;
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0}))) << " i: " << i;
	}
	for (unsigned int i=0; i<maxModbusBytes; ++i) {
		if (i == 3) {
			ASSERT_EQ(4, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus)));
		} else {
			ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus))) << " i: " << i;
		}

		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0}, onh::DT_Modbus))) << " i: " << i;
	}
}

/**
 * Check process writer set bit wrong Tag type
 */
TEST_F(driverTests, processWriterSetBitException1) {

	// Check all process data
	checkAllDataCleared();

	testShmTag.setType(onh::TT_BYTE);

	try {

		procWriter->setBit(testShmTag);

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessWriter::setBit: ";
		s << "Tag: " << testShmTag.getName() << " has wrong type";

		ASSERT_STREQ(e.what(), s.str().c_str());
		ASSERT_EQ(onh::TagException::WRONG_TYPE, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

/**
 * Check process writer set bit wrong byte address
 */
TEST_F(driverTests, processWriterSetBitException2) {

	// Check all process data
	checkAllDataCleared();

	testShmTag.setAddress({onh::PDA_INPUT, maxShmBytes+10, 0});

	try {

		procWriter->setBit(testShmTag);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::setBit: (" << testShmTag.getName() << "): ";
		s << "ShmProcessWriter::modifyBit: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

TEST_F(driverTests, processWriterSetBitException3) {

	// Check all process data
	checkAllDataCleared();

	testModbusTag.setAddress({onh::PDA_OUTPUT, maxModbusBytes+10, 0});

	try {

		procWriter->setBit(testModbusTag);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::setBit: (" << testModbusTag.getName() << "): ";
		s << "ModbusUtils::checkProcessAddress: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process writer set bit wrong connection id
 */
TEST_F(driverTests, processWriterSetBitException4) {

	// Check all process data
	checkAllDataCleared();

	onh::Tag tag1(
		15,
		45,
		"tag1",
		onh::TT_BIT,
		{onh::PDA_INPUT, 0, 2}
	);

	try {

		// Check test bit
		procWriter->setBit(tag1);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::setBit: (" << tag1.getName() << "): ";
		s << "Driver process writer with id: " << tag1.getConnId() << " does not exist";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process writer reset bit
 */
TEST_F(driverTests, processWriterResetBit) {

	// Check all process data
	checkAllDataCleared();

	// Change bit
	procWriter->setBit(testShmTag);
	procWriter->setBit(testModbusTag);

	// Wait on synchronization
	waitOnSyncBit();

	// Check test bit
	ASSERT_TRUE(procReader->getBitValue(testShmTag));
	ASSERT_TRUE(procReader->getBitValue(testModbusTag));

	// Reset
	procWriter->resetBit(testShmTag);
	procWriter->resetBit(testModbusTag);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	checkAllDataCleared();
}

/**
 * Check process writer reset bit wrong Tag type
 */
TEST_F(driverTests, processWriterResetBitException1) {

	// Check all process data
	checkAllDataCleared();

	testShmTag.setType(onh::TT_BYTE);

	try {

		procWriter->resetBit(testShmTag);

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessWriter::resetBit: ";
		s << "Tag: " << testShmTag.getName() << " has wrong type";

		ASSERT_STREQ(e.what(), s.str().c_str());
		ASSERT_EQ(onh::TagException::WRONG_TYPE, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

/**
 * Check process writer reset bit wrong byte address
 */
TEST_F(driverTests, processWriterResetBitException2) {

	// Check all process data
	checkAllDataCleared();

	testShmTag.setAddress({onh::PDA_INPUT, maxShmBytes+10, 0});

	try {

		procWriter->resetBit(testShmTag);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::resetBit: (" << testShmTag.getName() << "): ";
		s << "ShmProcessWriter::modifyBit: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

TEST_F(driverTests, processWriterResetBitException3) {

	// Check all process data
	checkAllDataCleared();

	testModbusTag.setAddress({onh::PDA_OUTPUT, maxModbusBytes+10, 0});

	try {

		procWriter->resetBit(testModbusTag);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::resetBit: (" << testModbusTag.getName() << "): ";
		s << "ModbusUtils::checkProcessAddress: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process writer set bit wrong connection id
 */
TEST_F(driverTests, processWriterResetBitException4) {

	// Check all process data
	checkAllDataCleared();

	onh::Tag tag1(
		15,
		45,
		"tag1",
		onh::TT_BIT,
		{onh::PDA_INPUT, 0, 2}
	);

	try {

		// Check test bit
		procWriter->resetBit(tag1);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::resetBit: (" << tag1.getName() << "): ";
		s << "Driver process writer with id: " << tag1.getConnId() << " does not exist";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process writer invert bit
 */
TEST_F(driverTests, processWriterInvertBit) {

	// Check all process data
	checkAllDataCleared();

	// Change bit
	procWriter->invertBit(testShmTag);

	// Wait on synchronization
	waitOnSyncBit();

	// Check test bit
	ASSERT_TRUE(procReader->getBitValue(testShmTag));
	ASSERT_FALSE(procReader->getBitValue(testModbusTag));

	// Change bit
	procWriter->invertBit(testModbusTag);

	// Wait on synchronization
	waitOnSyncBit();

	// Check test bit
	ASSERT_TRUE(procReader->getBitValue(testShmTag));
	ASSERT_TRUE(procReader->getBitValue(testModbusTag));

	// Check all process data
	for (unsigned int i=0; i<maxShmBytes; ++i) {
		if (i == 5) {
			ASSERT_EQ(1, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		} else {
			ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0}))) << " i: " << i;
		}

		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}))) << " i: " << i;
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0}))) << " i: " << i;
	}
	for (unsigned int i=0; i<maxModbusBytes; ++i) {
		if (i == 3) {
			ASSERT_EQ(4, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus)));
		} else {
			ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus))) << " i: " << i;
		}

		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0}, onh::DT_Modbus))) << " i: " << i;
	}

	procWriter->invertBit(testShmTag);
	procWriter->invertBit(testModbusTag);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	checkAllDataCleared();
}

/**
 * Check process writer invert bit wrong Tag type
 */
TEST_F(driverTests, processWriterInvertBitException1) {

	// Check all process data
	checkAllDataCleared();

	testShmTag.setType(onh::TT_BYTE);

	try {

		procWriter->invertBit(testShmTag);

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessWriter::invertBit: ";
		s << "Tag: " << testShmTag.getName() << " has wrong type";

		ASSERT_STREQ(e.what(), s.str().c_str());
		ASSERT_EQ(onh::TagException::WRONG_TYPE, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

/**
 * Check process writer invert bit wrong byte address
 */
TEST_F(driverTests, processWriterInvertBitException2) {

	// Check all process data
	checkAllDataCleared();

	testShmTag.setAddress({onh::PDA_INPUT, maxShmBytes+10, 0});

	try {

		procWriter->invertBit(testShmTag);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::invertBit: (" << testShmTag.getName() << "): ";
		s << "ShmProcessWriter::modifyBit: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

TEST_F(driverTests, processWriterInvertBitException3) {

	// Check all process data
	checkAllDataCleared();

	testModbusTag.setAddress({onh::PDA_OUTPUT, maxModbusBytes+10, 0});

	try {

		procWriter->invertBit(testModbusTag);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::invertBit: (" << testModbusTag.getName() << "): ";
		s << "ModbusUtils::checkProcessAddress: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process writer invert bit wrong connection id
 */
TEST_F(driverTests, processWriterInvertBitException4) {

	// Check all process data
	checkAllDataCleared();

	onh::Tag tag1(
		15,
		45,
		"tag1",
		onh::TT_BIT,
		{onh::PDA_INPUT, 0, 2}
	);

	try {

		// Check test bit
		procWriter->invertBit(tag1);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::invertBit: (" << tag1.getName() << "): ";
		s << "Driver process writer with id: " << tag1.getConnId() << " does not exist";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process writer set bits
 */
TEST_F(driverTests, processWriterSetBits) {

	// Check all process data
	checkAllDataCleared();

	onh::Tag tag2(
		15,
		dcModbus.getId(),
		"tag2",
		onh::TT_BIT,
		{onh::PDA_OUTPUT, 8, 5}
	);

	onh::Tag tag3(
		16,
		dcSHM.getId(),
		"tag3",
		onh::TT_BIT,
		{onh::PDA_INPUT, 0, 6}
	);

	std::vector<onh::Tag> vTags;
	vTags.push_back(testShmTag);
	vTags.push_back(testModbusTag);
	vTags.push_back(tag2);
	vTags.push_back(tag3);

	procWriter->setBits(vTags);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<maxShmBytes; ++i) {
		if (i == 0) {
			ASSERT_EQ(64, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		} else if (i == 5) {
			ASSERT_EQ(1, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		} else {
			ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0}))) << " i: " << i;
		}

		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}))) << " i: " << i;
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0}))) << " i: " << i;
	}
	for (unsigned int i=0; i<maxModbusBytes; ++i) {
		if (i == 3) {
			ASSERT_EQ(4, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus)));
		} else if (i == 8) {
			ASSERT_EQ(32, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus)));
		} else {
			ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus))) << " i: " << i;
		}

		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0}, onh::DT_Modbus))) << " i: " << i;
	}
}

/**
 * Check process writer set bits empty tag vector
 */
TEST_F(driverTests, processWriterSetBitsException1) {

	// Check all process data
	checkAllDataCleared();

	std::vector<onh::Tag> vTags;

	try {

		procWriter->setBits(vTags);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "ProcessWriter::setBits: Tags array is empty");

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process writer set bits wrong tag type
 */
TEST_F(driverTests, processWriterSetBitsException2) {

	// Check all process data
	checkAllDataCleared();

	onh::Tag tag2(
		15,
		dcSHM.getId(),
		"TestTag2",
		onh::TT_BYTE,
		{onh::PDA_INPUT, 5, 0}
	);

	std::vector<onh::Tag> vTags;
	vTags.push_back(testModbusTag);
	vTags.push_back(tag2);

	try {

		procWriter->setBits(vTags);

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessWriter::setBits: ";
		s << "Tag: " << tag2.getName() << " has wrong type";

		ASSERT_STREQ(e.what(), s.str().c_str());
		ASSERT_EQ(onh::TagException::WRONG_TYPE, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

/**
 * Check process writer set bits wrong byte address
 */
TEST_F(driverTests, processWriterSetBitsException3) {

	// Check all process data
	checkAllDataCleared();

	onh::Tag tag2(
		15,
		dcSHM.getId(),
		"TestTag2",
		onh::TT_BIT,
		{onh::PDA_INPUT, maxShmBytes+10, 0}
	);

	std::vector<onh::Tag> vTags;
	vTags.push_back(testModbusTag);
	vTags.push_back(tag2);

	try {

		procWriter->setBits(vTags);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::setBits: ";
		s << "ShmProcessWriter::setBits: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process writer set BYTE
 */
TEST_F(driverTests, processWriterSetByte) {

	// Check all process data
	checkAllDataCleared();

	testShmTag.setType(onh::TagType::TT_BYTE);
	testModbusTag.setType(onh::TagType::TT_BYTE);

	// Change byte
	procWriter->writeByte(testShmTag, 154);

	// Wait on synchronization
	waitOnSyncBit();

	// Check test byte
	ASSERT_EQ(154, procReader->getByte(testShmTag));
	ASSERT_EQ(0, procReader->getByte(testModbusTag));

	// Change byte
	procWriter->writeByte(testModbusTag, 73);

	// Wait on synchronization
	waitOnSyncBit();

	// Check test byte
	ASSERT_EQ(154, procReader->getByte(testShmTag));
	ASSERT_EQ(73, procReader->getByte(testModbusTag));

	// Check all process data
	for (unsigned int i=0; i<maxShmBytes; ++i) {
		if (i == 5) {
			ASSERT_EQ(154, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		} else {
			ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		}

		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}))) << " i: " << i;
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0}))) << " i: " << i;
	}
	for (unsigned int i=0; i<maxModbusBytes; ++i) {
		if (i == 3) {
			ASSERT_EQ(73, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus)));
		} else {
			ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus))) << " i: " << i;
		}

		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0}, onh::DT_Modbus))) << " i: " << i;
	}
}

/**
 * Check process writer set BYTE wrong Tag type
 */
TEST_F(driverTests, processWriterSetByteException1) {

	// Check all process data
	checkAllDataCleared();

	try {

		// Check test byte
		procWriter->writeByte(testShmTag, 7);

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessWriter::writeByte: ";
		s << "Tag: " << testShmTag.getName() << " has wrong type";

		ASSERT_STREQ(e.what(), s.str().c_str());
		ASSERT_EQ(onh::TagException::WRONG_TYPE, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

/**
 * Check process writer set BYTE wrong byte address
 */
TEST_F(driverTests, processWriterSetByteException2) {

	// Check all process data
	checkAllDataCleared();

	testShmTag.setType(onh::TagType::TT_BYTE);
	testShmTag.setAddress({onh::PDA_INPUT, maxShmBytes, 0});

	try {

		// Check test byte
		procWriter->writeByte(testShmTag, 85);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::writeByte: (" << testShmTag.getName() << "): ";
		s << "ShmProcessWriter::writeByte: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

TEST_F(driverTests, processWriterSetByteException3) {

	// Check all process data
	checkAllDataCleared();

	testModbusTag.setType(onh::TagType::TT_BYTE);
	testModbusTag.setAddress({onh::PDA_OUTPUT, maxModbusBytes, 0});

	try {

		// Check test byte
		procWriter->writeByte(testModbusTag, 5);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::writeByte: (" << testModbusTag.getName() << "): ";
		s << "ModbusUtils::checkProcessAddress: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process writer write BYTE wrong byte address
 */
TEST_F(driverTests, processWriterSetByteException4) {

	// Check all process data
	checkAllDataCleared();

	onh::Tag tag1(
		15,
		45,
		"tag1",
		onh::TT_BYTE,
		{onh::PDA_INPUT, 0, 2}
	);

	try {

		// Check test bit
		procWriter->writeByte(tag1, 5);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::writeByte: (" << tag1.getName() << "): ";
		s << "Driver process writer with id: " << tag1.getConnId() << " does not exist";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process writer set WORD
 */
TEST_F(driverTests, processWriterSetWord) {

	// Check all process data
	checkAllDataCleared();

	testShmTag.setType(onh::TagType::TT_WORD);
	testModbusTag.setType(onh::TagType::TT_WORD);

	// Change word
	procWriter->writeWord(testShmTag, 45801);

	// Wait on synchronization
	waitOnSyncBit();

	// Check test word
	ASSERT_EQ(45801, procReader->getWord(testShmTag));
	ASSERT_EQ(0, procReader->getWord(testModbusTag));

	// Change word
	procWriter->writeWord(testModbusTag, 38455);

	// Wait on synchronization
	waitOnSyncBit();

	// Check test word
	ASSERT_EQ(45801, procReader->getWord(testShmTag));
	ASSERT_EQ(38455, procReader->getWord(testModbusTag));

	// Check all process data
	for (unsigned int i=0; i<maxShmBytes; ++i) {
		if (i == 5) {
			ASSERT_EQ(45801, procReader->getWord(createWordTag({onh::PDA_INPUT, i, 0})));
			ASSERT_EQ(233, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		} else if (i == 6) {
			ASSERT_EQ(178, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		} else {
			ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0}))) << " i: " << i;
		}

		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}))) << " i: " << i;
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0}))) << " i: " << i;
	}
	for (unsigned int i=0; i<maxModbusBytes; ++i) {
		if (i == 3) {
			ASSERT_EQ(38455, procReader->getWord(createWordTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus)));
			ASSERT_EQ(55, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus)));
		} else if (i == 4) {
			ASSERT_EQ(150, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus)));
		} else {
			ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus))) << " i: " << i;
		}

		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0}, onh::DT_Modbus))) << " i: " << i;
	}
}

/**
 * Check process writer set WORD wrong Tag type
 */
TEST_F(driverTests, processWriterSetWordException1) {

	// Check all process data
	checkAllDataCleared();

	try {

		procWriter->writeWord(testShmTag, 45801);

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessWriter::writeWord: ";
		s << "Tag: " << testShmTag.getName() << " has wrong type";

		ASSERT_STREQ(e.what(), s.str().c_str());
		ASSERT_EQ(onh::TagException::WRONG_TYPE, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

/**
 * Check process writer set WORD wrong byte address
 */
TEST_F(driverTests, processWriterSetWordException2) {

	// Check all process data
	checkAllDataCleared();

	testShmTag.setType(onh::TagType::TT_WORD);
	testShmTag.setAddress({onh::PDA_INPUT, maxShmBytes-1, 0});

	try {

		procWriter->writeWord(testShmTag, 45801);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::writeWord: (" << testShmTag.getName() << "): ";
		s << "ShmProcessWriter::writeWord: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

TEST_F(driverTests, processWriterSetWordException3) {

	// Check all process data
	checkAllDataCleared();

	testModbusTag.setType(onh::TagType::TT_WORD);
	testModbusTag.setAddress({onh::PDA_OUTPUT, maxModbusBytes, 0});

	try {

		// Check test byte
		procWriter->writeWord(testModbusTag, 5);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::writeWord: (" << testModbusTag.getName() << "): ";
		s << "ModbusUtils::checkProcessAddress: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process writer write WORD wrong byte address
 */
TEST_F(driverTests, processWriterSetWordException4) {

	// Check all process data
	checkAllDataCleared();

	onh::Tag tag1(
		15,
		45,
		"tag1",
		onh::TT_WORD,
		{onh::PDA_INPUT, 0, 2}
	);

	try {

		// Check test bit
		procWriter->writeWord(tag1, 5);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::writeWord: (" << tag1.getName() << "): ";
		s << "Driver process writer with id: " << tag1.getConnId() << " does not exist";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process writer set DWORD
 */
TEST_F(driverTests, processWriterSetDWord) {

	// Check all process data
	checkAllDataCleared();

	testShmTag.setType(onh::TagType::TT_DWORD);
	testModbusTag.setType(onh::TagType::TT_DWORD);

	// Change dword (1110 0010 1100 0110 0101 0001 1101 1100)
	procWriter->writeDWord(testShmTag, 3804647900);

	// Wait on synchronization
	waitOnSyncBit();

	// Check test dword
	ASSERT_EQ((DWORD)3804647900, procReader->getDWord(testShmTag));
	ASSERT_EQ((DWORD)0, procReader->getDWord(testModbusTag));

	// Change dword (1010 1011 0101 0110 0111 1110 1101 0100)
	procWriter->writeDWord(testModbusTag, 2874572500);

	// Wait on synchronization
	waitOnSyncBit();

	// Check test dword
	ASSERT_EQ((DWORD)3804647900, procReader->getDWord(testShmTag));
	ASSERT_EQ((DWORD)2874572500, procReader->getDWord(testModbusTag));

	// Check all process data
	for (unsigned int i=0; i<maxShmBytes; ++i) {
		switch (i) {
			case 5: {
					ASSERT_EQ((DWORD)3804647900, procReader->getDWord(createDWordTag({onh::PDA_INPUT, i, 0})));
					ASSERT_EQ(20956, procReader->getWord(createWordTag({onh::PDA_INPUT, i, 0})));
					ASSERT_EQ(220, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
				}; break;
			case 6: {
					ASSERT_EQ(50769, procReader->getWord(createWordTag({onh::PDA_INPUT, i, 0})));
					ASSERT_EQ(81, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
				}; break;
			case 7: {
					ASSERT_EQ(58054, procReader->getWord(createWordTag({onh::PDA_INPUT, i, 0})));
					ASSERT_EQ(198, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
				}; break;
			case 8: {
					ASSERT_EQ(226, procReader->getWord(createWordTag({onh::PDA_INPUT, i, 0})));
					ASSERT_EQ(226, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
				}; break;
			default: ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0}))) << " i: " << i; break;
		}

		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}))) << " i: " << i;
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0}))) << " i: " << i;
	}
	for (unsigned int i=0; i<maxModbusBytes; ++i) {
		switch (i) {
			case 3: {
					ASSERT_EQ((DWORD)2874572500, procReader->getDWord(createDWordTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus)));
					ASSERT_EQ(32468, procReader->getWord(createWordTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus)));
					ASSERT_EQ(212, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus)));
				}; break;
			case 4: {
					ASSERT_EQ(22142, procReader->getWord(createWordTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus)));
					ASSERT_EQ(126, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus)));
				}; break;
			case 5: {
					ASSERT_EQ(43862, procReader->getWord(createWordTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus)));
					ASSERT_EQ(86, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus)));
				}; break;
			case 6: {
					ASSERT_EQ(171, procReader->getWord(createWordTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus)));
					ASSERT_EQ(171, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus)));
				}; break;
			default: ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus))) << " i: " << i; break;
		}

		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0}, onh::DT_Modbus))) << " i: " << i;
	}
}

/**
 * Check process writer set DWORD wrong Tag type
 */
TEST_F(driverTests, processWriterSetDWordException1) {

	// Check all process data
	checkAllDataCleared();

	try {

		procWriter->writeDWord(testShmTag, 3804647900);

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessWriter::writeDWord: ";
		s << "Tag: " << testShmTag.getName() << " has wrong type";

		ASSERT_STREQ(e.what(), s.str().c_str());
		ASSERT_EQ(onh::TagException::WRONG_TYPE, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

/**
 * Check process writer set DWORD wrong byte address
 */
TEST_F(driverTests, processWriterSetDWordException2) {

	// Check all process data
	checkAllDataCleared();

	testShmTag.setType(onh::TagType::TT_DWORD);
	testShmTag.setAddress({onh::PDA_INPUT, maxShmBytes-1, 0});

	try {

		procWriter->writeDWord(testShmTag, 3804647900);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::writeDWord: (" << testShmTag.getName() << "): ";
		s << "ShmProcessWriter::writeDWord: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

TEST_F(driverTests, processWriterSetDWordException3) {

	// Check all process data
	checkAllDataCleared();

	testModbusTag.setType(onh::TagType::TT_DWORD);
	testModbusTag.setAddress({onh::PDA_OUTPUT, maxModbusBytes, 0});

	try {

		// Check test byte
		procWriter->writeDWord(testModbusTag, 5);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::writeDWord: (" << testModbusTag.getName() << "): ";
		s << "ModbusUtils::checkProcessAddress: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process writer write DWORD wrong byte address
 */
TEST_F(driverTests, processWriterSetDWordException4) {

	// Check all process data
	checkAllDataCleared();

	onh::Tag tag1(
		15,
		45,
		"tag1",
		onh::TT_DWORD,
		{onh::PDA_INPUT, 0, 2}
	);

	try {

		// Check test bit
		procWriter->writeDWord(tag1, 5);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::writeDWord: (" << tag1.getName() << "): ";
		s << "Driver process writer with id: " << tag1.getConnId() << " does not exist";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process writer set INT
 */
TEST_F(driverTests, processWriterSetInt) {

	// Check all process data
	checkAllDataCleared();

	testShmTag.setType(onh::TagType::TT_INT);
	testModbusTag.setType(onh::TagType::TT_INT);

	// Change int
	procWriter->writeInt(testShmTag, -548);

	// Wait on synchronization
	waitOnSyncBit();

	// Check test dword
	ASSERT_EQ(-548, procReader->getInt(testShmTag));
	ASSERT_EQ(0, procReader->getInt(testModbusTag));

	// Change int
	procWriter->writeInt(testModbusTag, -1789);

	// Wait on synchronization
	waitOnSyncBit();

	// Check test dword
	ASSERT_EQ(-548, procReader->getInt(testShmTag));
	ASSERT_EQ(-1789, procReader->getInt(testModbusTag));

	// Check all process data
	for (unsigned int i=0; i<maxShmBytes; ++i) {
		if (i == 5) {
			ASSERT_EQ(-548, procReader->getInt(createIntTag({onh::PDA_INPUT, i, 0})));
			// Skip checking bytes in int
			i += 3;
		} else {
			ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0}))) << " i: " << i;
		}

		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}
	for (unsigned int i=0; i<maxModbusBytes; ++i) {
		if (i == 3) {
			ASSERT_EQ(-1789, procReader->getInt(createIntTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus)));
			// Skip checking bytes in int
			i += 3;
		} else {
			ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus))) << " i: " << i;
		}

		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0}, onh::DT_Modbus))) << " i: " << i;
	}
}

/**
 * Check process writer set INT wrong Tag type
 */
TEST_F(driverTests, processWriterSetIntException1) {

	// Check all process data
	checkAllDataCleared();

	try {

		procWriter->writeInt(testShmTag, -548);

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessWriter::writeInt: ";
		s << "Tag: " << testShmTag.getName() << " has wrong type";

		ASSERT_STREQ(e.what(), s.str().c_str());
		ASSERT_EQ(onh::TagException::WRONG_TYPE, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

/**
 * Check process writer set INT wrong byte address
 */
TEST_F(driverTests, processWriterSetIntException2) {

	// Check all process data
	checkAllDataCleared();

	testShmTag.setType(onh::TagType::TT_INT);
	testShmTag.setAddress({onh::PDA_INPUT, maxShmBytes-1, 0});

	try {

		procWriter->writeInt(testShmTag, -548);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::writeInt: (" << testShmTag.getName() << "): ";
		s << "ShmProcessWriter::writeInt: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

TEST_F(driverTests, processWriterSetIntException3) {

	// Check all process data
	checkAllDataCleared();

	testModbusTag.setType(onh::TagType::TT_INT);
	testModbusTag.setAddress({onh::PDA_OUTPUT, maxModbusBytes, 0});

	try {

		// Check test byte
		procWriter->writeInt(testModbusTag, 5);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::writeInt: (" << testModbusTag.getName() << "): ";
		s << "ModbusUtils::checkProcessAddress: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process writer write INT wrong byte address
 */
TEST_F(driverTests, processWriterSetIntException4) {

	// Check all process data
	checkAllDataCleared();

	onh::Tag tag1(
		15,
		45,
		"tag1",
		onh::TT_INT,
		{onh::PDA_INPUT, 0, 2}
	);

	try {

		// Check test bit
		procWriter->writeInt(tag1, 5);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::writeInt: (" << tag1.getName() << "): ";
		s << "Driver process writer with id: " << tag1.getConnId() << " does not exist";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process writer set REAL
 */
TEST_F(driverTests, processWriterSetReal) {

	// Check all process data
	checkAllDataCleared();

	testShmTag.setType(onh::TagType::TT_REAL);
	testModbusTag.setType(onh::TagType::TT_REAL);

	// Change real
	procWriter->writeReal(testShmTag, -1589.74);

	// Wait on synchronization
	waitOnSyncBit();

	// Check test real
	ASSERT_EQ((float)-1589.74, procReader->getReal(testShmTag));
	ASSERT_EQ((float)0, procReader->getReal(testModbusTag));

	// Change real
	procWriter->writeReal(testModbusTag, -1410.07);

	// Wait on synchronization
	waitOnSyncBit();

	// Check test real
	ASSERT_EQ((float)-1589.74, procReader->getReal(testShmTag));
	ASSERT_EQ((float)-1410.07, procReader->getReal(testModbusTag));

	// Check all process data
	for (unsigned int i=0; i<maxShmBytes; ++i) {
		if (i == 5) {
			ASSERT_EQ((float)-1589.74, procReader->getReal(createRealTag({onh::PDA_INPUT, i, 0})));
			// Skip checking bytes in real
			i += 3;
		} else {
			ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		}

		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}
	for (unsigned int i=0; i<maxModbusBytes; ++i) {
		if (i == 3) {
			ASSERT_EQ((float)-1410.07, procReader->getReal(createRealTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus)));
			// Skip checking bytes in real
			i += 3;
		} else {
			ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus))) << " i: " << i;
		}

		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0}, onh::DT_Modbus))) << " i: " << i;
	}
}

/**
 * Check process writer set REAL wrong Tag type
 */
TEST_F(driverTests, processWriterSetRealException1) {

	// Check all process data
	checkAllDataCleared();

	try {

		procWriter->writeReal(testShmTag, -1589.74);

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessWriter::writeReal: ";
		s << "Tag: " << testShmTag.getName() << " has wrong type";

		ASSERT_STREQ(e.what(), s.str().c_str());
		ASSERT_EQ(onh::TagException::WRONG_TYPE, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

/**
 * Check process writer set REAL wrong byte address
 */
TEST_F(driverTests, processWriterSetRealException2) {

	// Check all process data
	checkAllDataCleared();

	testShmTag.setType(onh::TagType::TT_REAL);
	testShmTag.setAddress({onh::PDA_INPUT, maxShmBytes-1, 0});

	try {

		procWriter->writeReal(testShmTag, -1589.74);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::writeReal: (" << testShmTag.getName() << "): ";
		s << "ShmProcessWriter::writeReal: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

TEST_F(driverTests, processWriterSetRealException3) {

	// Check all process data
	checkAllDataCleared();

	testModbusTag.setType(onh::TagType::TT_REAL);
	testModbusTag.setAddress({onh::PDA_OUTPUT, maxModbusBytes, 0});

	try {

		// Check test byte
		procWriter->writeReal(testModbusTag, 5);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::writeReal: (" << testModbusTag.getName() << "): ";
		s << "ModbusUtils::checkProcessAddress: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process writer write REAL wrong byte address
 */
TEST_F(driverTests, processWriterSetRealException4) {

	// Check all process data
	checkAllDataCleared();

	onh::Tag tag1(
		15,
		45,
		"tag1",
		onh::TT_REAL,
		{onh::PDA_INPUT, 0, 2}
	);

	try {

		// Check test bit
		procWriter->writeReal(tag1, 5);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::writeReal: (" << tag1.getName() << "): ";
		s << "Driver process writer with id: " << tag1.getConnId() << " does not exist";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

#endif /* TESTS_DRIVER_PROCESSWRITERTESTS_H_ */
