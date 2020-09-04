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

#ifndef TESTS_DRIVER_PROCESSREADERTESTS_H_
#define TESTS_DRIVER_PROCESSREADERTESTS_H_

#include <gtest/gtest.h>
#include "DriverTestsFixtures.h"

/**
 * Check process reader get bit
 */
TEST_F(driverTests, processReaderGetBit) {

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
 * Check process reader get bit wrong Tag type
 */
TEST_F(driverTests, processReaderGetBitException1) {

	// Check all process data
	checkAllDataCleared();

	testShmTag.setType(onh::TT_BYTE);

	try {

		// Check test bit
		ASSERT_FALSE(procReader->getBitValue(testShmTag));

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessReader::getBitValue: ";
		s << "Tag: " << testShmTag.getName() << " has wrong type";

		ASSERT_STREQ(e.what(), s.str().c_str());
		ASSERT_EQ(onh::TagException::WRONG_TYPE, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

/**
 * Check process reader get bit wrong byte address
 */
TEST_F(driverTests, processReaderGetBitException2) {

	// Check all process data
	checkAllDataCleared();

	testShmTag.setAddress({onh::PDA_INPUT, maxShmBytes+10, 0});

	try {

		// Check test bit
		ASSERT_FALSE(procReader->getBitValue(testShmTag));

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessReader::getBitValue: (" << testShmTag.getName() << "): ";
		s << "ShmProcessData::getBitValue: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

TEST_F(driverTests, processReaderGetBitException3) {

	// Check all process data
	checkAllDataCleared();

	testModbusTag.setAddress({onh::PDA_OUTPUT, maxModbusBytes+10, 0});

	try {

		// Check test bit
		ASSERT_FALSE(procReader->getBitValue(testModbusTag));

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessReader::getBitValue: (" << testModbusTag.getName() << "): ";
		s << "ModbusUtils::checkProcessAddress: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process reader get bit wrong connection id
 */
TEST_F(driverTests, processReaderGetBitException4) {

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
		ASSERT_FALSE(procReader->getBitValue(tag1));

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessReader::getBitValue: (" << tag1.getName() << "): ";
		s << "Driver process reader with id: " << tag1.getConnId() << " does not exist";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process reader get bits
 */
TEST_F(driverTests, processReaderGetBits) {

	// Check all process data
	checkAllDataCleared();

	onh::Tag tag1(
		15,
		dcModbus.getId(),
		"tag1",
		onh::TT_BIT,
		{onh::PDA_OUTPUT, 7, 3}
	);

	onh::Tag tag2(
		16,
		dcSHM.getId(),
		"tag2",
		onh::TT_BIT,
		{onh::PDA_INPUT, 3, 6}
	);

	std::vector<onh::Tag> vTags;
	vTags.push_back(testShmTag);
	vTags.push_back(testModbusTag);
	vTags.push_back(tag1);
	vTags.push_back(tag2);

	std::vector<bool> vRet;

	vRet = procReader->getBitsValue(vTags);

	ASSERT_EQ((unsigned int)vTags.size(), vRet.size());
	// Check test bit
	for (unsigned int i=0; i<vRet.size(); ++i) {
		ASSERT_FALSE(vRet[i]) << " i: " << i;
	}

	// Change bit
	procWriter->setBit(testShmTag);
	procWriter->setBit(testModbusTag);
	procWriter->setBit(tag1);
	procWriter->setBit(tag2);

	// Wait on synchronization
	waitOnSyncBit();

	vRet.clear();
	vRet = procReader->getBitsValue(vTags);

	ASSERT_EQ((unsigned int)vTags.size(), vRet.size());
	// Check test bit
	for (unsigned int i=0; i<vRet.size(); ++i) {
		ASSERT_TRUE(vRet[i]) << " i: " << i;
	}

	// Check all process data
	for (unsigned int i=0; i<maxShmBytes; ++i) {
		if (i == 3) {
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
		} else if (i == 7) {
			ASSERT_EQ(8, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus)));
		} else {
			ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus))) << " i: " << i;
		}

		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0}, onh::DT_Modbus))) << " i: " << i;
	}
}

/**
 * Check process reader get bits empty tag vector
 */
TEST_F(driverTests, processReaderGetBitsException1) {

	// Check all process data
	checkAllDataCleared();

	std::vector<onh::Tag> vTags;
	std::vector<bool> vRet;

	try {

		vRet = procReader->getBitsValue(vTags);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "ProcessReader::getBitsValue: Tags array is empty");

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process reader get bits wrong tag type
 */
TEST_F(driverTests, processReaderGetBitsException2) {

	// Check all process data
	checkAllDataCleared();

	onh::Tag tag2(
		15,
		dcModbus.getId(),
		"TestTag2",
		onh::TT_BYTE,
		{onh::PDA_INPUT, 5, 0}
	);

	std::vector<onh::Tag> vTags;
	vTags.push_back(testShmTag);
	vTags.push_back(tag2);

	std::vector<bool> vRet;

	try {

		vRet = procReader->getBitsValue(vTags);

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessReader::getBitValue: ";
		s << "Tag: " << tag2.getName() << " has wrong type";

		ASSERT_STREQ(e.what(), s.str().c_str());
		ASSERT_EQ(onh::TagException::WRONG_TYPE, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

/**
 * Check process reader get bits wrong byte address
 */
TEST_F(driverTests, processReaderGetBitsException3) {

	// Check all process data
	checkAllDataCleared();

	onh::Tag tag2(
		15,
		dcModbus.getId(),
		"TestTag2",
		onh::TT_BIT,
		{onh::PDA_INPUT, maxModbusBytes+10, 0}
	);

	std::vector<onh::Tag> vTags;
	vTags.push_back(testShmTag);
	vTags.push_back(tag2);

	std::vector<bool> vRet;

	try {

		vRet = procReader->getBitsValue(vTags);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessReader::getBitValue: (" << tag2.getName() << "): ";
		s << "ModbusUtils::checkProcessAddress: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process reader get BYTE
 */
TEST_F(driverTests, processReaderGetByte) {

	// Check all process data
	checkAllDataCleared();

	testShmTag.setType(onh::TagType::TT_BYTE);
	testModbusTag.setType(onh::TagType::TT_BYTE);

	// Check test byte
	ASSERT_EQ(0, procReader->getByte(testShmTag));
	ASSERT_EQ(0, procReader->getByte(testModbusTag));

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
 * Check process reader get BYTE wrong Tag type
 */
TEST_F(driverTests, processReaderGetByteException1) {

	// Check all process data
	checkAllDataCleared();

	try {

		// Check test byte
		ASSERT_EQ(0, procReader->getByte(testShmTag));

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessReader::getByte: ";
		s << "Tag: " << testShmTag.getName() << " has wrong type";

		ASSERT_STREQ(e.what(), s.str().c_str());
		ASSERT_EQ(onh::TagException::WRONG_TYPE, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

/**
 * Check process reader get BYTE wrong byte address
 */
TEST_F(driverTests, processReaderGetByteException2) {

	// Check all process data
	checkAllDataCleared();

	testShmTag.setType(onh::TagType::TT_BYTE);
	testShmTag.setAddress({onh::PDA_INPUT, maxShmBytes, 0});

	try {

		// Check test byte
		ASSERT_EQ(0, procReader->getByte(testShmTag));

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessReader::getByte: (" << testShmTag.getName() << "): ";
		s << "ShmProcessData::getByte: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

TEST_F(driverTests, processReaderGetByteException3) {

	// Check all process data
	checkAllDataCleared();

	testModbusTag.setType(onh::TagType::TT_BYTE);
	testModbusTag.setAddress({onh::PDA_OUTPUT, maxModbusBytes, 0});

	try {

		// Check test byte
		ASSERT_EQ(0, procReader->getByte(testModbusTag));

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessReader::getByte: (" << testModbusTag.getName() << "): ";
		s << "ModbusUtils::checkProcessAddress: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process reader get BYTE wrong connection id
 */
TEST_F(driverTests, processReaderGetByteException4) {

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
		ASSERT_FALSE(procReader->getByte(tag1));

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessReader::getByte: (" << tag1.getName() << "): ";
		s << "Driver process reader with id: " << tag1.getConnId() << " does not exist";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process reader get WORD
 */
TEST_F(driverTests, processReaderGetWord) {

	// Check all process data
	checkAllDataCleared();

	testShmTag.setType(onh::TagType::TT_WORD);
	testModbusTag.setType(onh::TagType::TT_WORD);

	// Check test word
	ASSERT_EQ(0, procReader->getWord(testShmTag));
	ASSERT_EQ(0, procReader->getWord(testModbusTag));

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
 * Check process reader get WORD wrong Tag type
 */
TEST_F(driverTests, processReaderGetWordException1) {

	// Check all process data
	checkAllDataCleared();

	try {

		// Check test word
		ASSERT_EQ(0, procReader->getWord(testShmTag));

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessReader::getWord: ";
		s << "Tag: " << testShmTag.getName() << " has wrong type";

		ASSERT_STREQ(e.what(), s.str().c_str());
		ASSERT_EQ(onh::TagException::WRONG_TYPE, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

/**
 * Check process reader get WORD wrong byte address
 */
TEST_F(driverTests, processReaderGetWordException2) {

	// Check all process data
	checkAllDataCleared();

	testShmTag.setType(onh::TagType::TT_WORD);
	testShmTag.setAddress({onh::PDA_INPUT, maxShmBytes-1, 0});

	try {

		// Check test word
		ASSERT_EQ(0, procReader->getWord(testShmTag));

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessReader::getWord: (" << testShmTag.getName() << "): ";
		s << "ShmProcessData::getWord: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

TEST_F(driverTests, processReaderGetWordException3) {

	// Check all process data
	checkAllDataCleared();

	testModbusTag.setType(onh::TagType::TT_WORD);
	testModbusTag.setAddress({onh::PDA_OUTPUT, maxModbusBytes-1, 0});

	try {

		// Check test word
		ASSERT_EQ(0, procReader->getWord(testModbusTag));

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessReader::getWord: (" << testModbusTag.getName() << "): ";
		s << "ModbusUtils::checkProcessAddress: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process reader get WORD wrong connection id
 */
TEST_F(driverTests, processReaderGetWordException4) {

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
		ASSERT_FALSE(procReader->getWord(tag1));

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessReader::getWord: (" << tag1.getName() << "): ";
		s << "Driver process reader with id: " << tag1.getConnId() << " does not exist";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process reader get DWORD
 */
TEST_F(driverTests, processReaderGetDWord) {

	// Check all process data
	checkAllDataCleared();

	testShmTag.setType(onh::TagType::TT_DWORD);
	testModbusTag.setType(onh::TagType::TT_DWORD);

	// Check test dword
	ASSERT_EQ((DWORD)0, procReader->getDWord(testShmTag));
	ASSERT_EQ((DWORD)0, procReader->getDWord(testModbusTag));

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
 * Check process reader get DWORD wrong Tag type
 */
TEST_F(driverTests, processReaderGetDWordException1) {

	// Check all process data
	checkAllDataCleared();

	try {

		// Check test word
		ASSERT_EQ((DWORD)0, procReader->getDWord(testShmTag));

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessReader::getDWord: ";
		s << "Tag: " << testShmTag.getName() << " has wrong type";

		ASSERT_STREQ(e.what(), s.str().c_str());
		ASSERT_EQ(onh::TagException::WRONG_TYPE, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

/**
 * Check process reader get DWORD wrong byte address
 */
TEST_F(driverTests, processReaderGetDWordException2) {

	// Check all process data
	checkAllDataCleared();

	testShmTag.setType(onh::TagType::TT_DWORD);
	testShmTag.setAddress({onh::PDA_INPUT, maxShmBytes-1, 0});

	try {

		// Check test word
		ASSERT_EQ((DWORD)0, procReader->getDWord(testShmTag));

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessReader::getDWord: (" << testShmTag.getName() << "): ";
		s << "ShmProcessData::getDWord: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

TEST_F(driverTests, processReaderGetDWordException3) {

	// Check all process data
	checkAllDataCleared();

	testModbusTag.setType(onh::TagType::TT_DWORD);
	testModbusTag.setAddress({onh::PDA_INPUT, maxModbusBytes-1, 0});

	try {

		// Check test word
		ASSERT_EQ((DWORD)0, procReader->getDWord(testModbusTag));

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessReader::getDWord: (" << testModbusTag.getName() << "): ";
		s << "ModbusUtils::checkProcessAddress: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process reader get DWORD wrong connection id
 */
TEST_F(driverTests, processReaderGetDWordException4) {

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
		ASSERT_FALSE(procReader->getDWord(tag1));

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessReader::getDWord: (" << tag1.getName() << "): ";
		s << "Driver process reader with id: " << tag1.getConnId() << " does not exist";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process reader get INT
 */
TEST_F(driverTests, processReaderGetInt) {

	// Check all process data
	checkAllDataCleared();

	testShmTag.setType(onh::TagType::TT_INT);
	testModbusTag.setType(onh::TagType::TT_INT);

	// Check test int
	ASSERT_EQ(0, procReader->getInt(testShmTag));
	ASSERT_EQ(0, procReader->getInt(testModbusTag));

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
 * Check process reader get INT wrong Tag type
 */
TEST_F(driverTests, processReaderGetIntException1) {

	// Check all process data
	checkAllDataCleared();

	try {

		// Check test int
		ASSERT_EQ(0, procReader->getInt(testShmTag));

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessReader::getInt: ";
		s << "Tag: " << testShmTag.getName() << " has wrong type";

		ASSERT_STREQ(e.what(), s.str().c_str());
		ASSERT_EQ(onh::TagException::WRONG_TYPE, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

/**
 * Check process reader get INT wrong byte address
 */
TEST_F(driverTests, processReaderGetIntException2) {

	// Check all process data
	checkAllDataCleared();

	testShmTag.setType(onh::TagType::TT_INT);
	testShmTag.setAddress({onh::PDA_INPUT, maxShmBytes-1, 0});

	try {

		// Check test int
		ASSERT_EQ(0, procReader->getInt(testShmTag));

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessReader::getInt: (" << testShmTag.getName() << "): ";
		s << "ShmProcessData::getInt: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

TEST_F(driverTests, processReaderGetIntException3) {

	// Check all process data
	checkAllDataCleared();

	testModbusTag.setType(onh::TagType::TT_INT);
	testModbusTag.setAddress({onh::PDA_INPUT, maxModbusBytes-1, 0});

	try {

		// Check test word
		ASSERT_EQ((DWORD)0, procReader->getInt(testModbusTag));

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessReader::getInt: (" << testModbusTag.getName() << "): ";
		s << "ModbusUtils::checkProcessAddress: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process reader get INT wrong connection id
 */
TEST_F(driverTests, processReaderGetIntException4) {

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
		ASSERT_FALSE(procReader->getInt(tag1));

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessReader::getInt: (" << tag1.getName() << "): ";
		s << "Driver process reader with id: " << tag1.getConnId() << " does not exist";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process reader get REAL
 */
TEST_F(driverTests, processReaderGetReal) {

	// Check all process data
	checkAllDataCleared();

	testShmTag.setType(onh::TagType::TT_REAL);
	testModbusTag.setType(onh::TagType::TT_REAL);

	// Check test real
	ASSERT_EQ((float)0, procReader->getReal(testShmTag));
	ASSERT_EQ((float)0, procReader->getReal(testModbusTag));

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
 * Check process reader get REAL wrong Tag type
 */
TEST_F(driverTests, processReaderGetRealException1) {

	// Check all process data
	checkAllDataCleared();

	try {

		// Check test real
		ASSERT_EQ((float)0, procReader->getReal(testShmTag));

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessReader::getReal: ";
		s << "Tag: " << testShmTag.getName() << " has wrong type";

		ASSERT_STREQ(e.what(), s.str().c_str());
		ASSERT_EQ(onh::TagException::WRONG_TYPE, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

/**
 * Check process reader get REAL wrong byte address
 */

TEST_F(driverTests, processReaderGetRealException2) {

	// Check all process data
	checkAllDataCleared();

	testShmTag.setType(onh::TagType::TT_REAL);
	testShmTag.setAddress({onh::PDA_INPUT, maxShmBytes-1, 0});

	try {

		// Check test real
		ASSERT_EQ((float)0, procReader->getReal(testShmTag));

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessReader::getReal: (" << testShmTag.getName() << "): ";
		s << "ShmProcessData::getReal: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

TEST_F(driverTests, processReaderGetRealException3) {

	// Check all process data
	checkAllDataCleared();

	testModbusTag.setType(onh::TagType::TT_REAL);
	testModbusTag.setAddress({onh::PDA_INPUT, maxModbusBytes-1, 0});

	try {

		// Check test word
		ASSERT_EQ((DWORD)0, procReader->getReal(testModbusTag));

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessReader::getReal: (" << testModbusTag.getName() << "): ";
		s << "ModbusUtils::checkProcessAddress: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check process reader get REAL wrong connection id
 */
TEST_F(driverTests, processReaderGetRealException4) {

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
		ASSERT_FALSE(procReader->getReal(tag1));

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessReader::getReal: (" << tag1.getName() << "): ";
		s << "Driver process reader with id: " << tag1.getConnId() << " does not exist";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

#endif /* TESTS_DRIVER_PROCESSREADERTESTS_H_ */
