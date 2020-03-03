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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	// Check test bit
	ASSERT_FALSE(procReader->getBitValue(*testTag));

	// Change bit
	driver->setBit(testTag->getAddress());

	// Wait on synchronization
	waitOnSyncBit();

	// Check test bit
	ASSERT_TRUE(procReader->getBitValue(*testTag));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 0) {
			ASSERT_EQ(1, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		}

		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}
}

/**
 * Check process reader get bit wrong Tag type
 */
TEST_F(driverTests, processReaderGetBitException1) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	testTag->setType(onh::TT_BYTE);

	try {

		// Check test bit
		ASSERT_FALSE(procReader->getBitValue(*testTag));

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessReader::getBitValue: ";
		s << "Tag: " << testTag->getName() << " has wrong type";

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	testTag->setAddress({onh::PDA_INPUT, PROCESS_DT_SIZE+10, 0});

	try {

		// Check test bit
		ASSERT_FALSE(procReader->getBitValue(*testTag));

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessReader::getBitValue: (" << testTag->getName() << "): ";
		s << "ShmProcessReader::getBitValue: Byte address is out of range";

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	onh::Tag tag2(
		15,
		"TestTag2",
		onh::TT_BIT,
		{onh::PDA_INPUT, 0, 2}
	);

	onh::Tag tag3(
		16,
		"TestTag3",
		onh::TT_BIT,
		{onh::PDA_INPUT, 0, 6}
	);

	std::vector<onh::Tag> vTags;
	vTags.push_back(*testTag);
	vTags.push_back(tag2);
	vTags.push_back(tag3);

	std::vector<bool> vRet;

	vRet = procReader->getBitsValue(vTags);

	ASSERT_EQ((unsigned int)3, vRet.size());
	// Check test bit
	ASSERT_FALSE(vRet[0]);
	ASSERT_FALSE(vRet[1]);
	ASSERT_FALSE(vRet[2]);

	// Change bit
	driver->setBit(testTag->getAddress());
	driver->setBit(tag2.getAddress());
	driver->setBit(tag3.getAddress());

	// Wait on synchronization
	waitOnSyncBit();

	vRet.clear();
	vRet = procReader->getBitsValue(vTags);

	ASSERT_EQ((unsigned int)3, vRet.size());
	// Check test bit
	ASSERT_TRUE(vRet[0]);
	ASSERT_TRUE(vRet[1]);
	ASSERT_TRUE(vRet[2]);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 0) {
			ASSERT_EQ(69, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		}

		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}
}

/**
 * Check process reader get bits empty tag vector
 */
TEST_F(driverTests, processReaderGetBitsException1) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	onh::Tag tag2(
		15,
		"TestTag2",
		onh::TT_BYTE,
		{onh::PDA_INPUT, 5, 0}
	);

	std::vector<onh::Tag> vTags;
	vTags.push_back(*testTag);
	vTags.push_back(tag2);

	std::vector<bool> vRet;

	try {

		vRet = procReader->getBitsValue(vTags);

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessReader::getBitsValue: ";
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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	onh::Tag tag2(
		15,
		"TestTag2",
		onh::TT_BIT,
		{onh::PDA_INPUT, PROCESS_DT_SIZE+10, 0}
	);

	std::vector<onh::Tag> vTags;
	vTags.push_back(*testTag);
	vTags.push_back(tag2);

	std::vector<bool> vRet;

	try {

		vRet = procReader->getBitsValue(vTags);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessReader::getBitsValue: ";
		s << "ShmProcessReader::getBitValue: Byte address is out of range";

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	testTag->setType(onh::TagType::TT_BYTE);

	// Check test byte
	ASSERT_EQ(0, procReader->getByte(*testTag));

	// Change byte
	driver->writeByte(testTag->getAddress(), 154);

	// Wait on synchronization
	waitOnSyncBit();

	// Check test byte
	ASSERT_EQ(154, procReader->getByte(*testTag));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 0) {
			ASSERT_EQ(154, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		}

		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}
}

/**
 * Check process reader get BYTE wrong Tag type
 */
TEST_F(driverTests, processReaderGetByteException1) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	try {

		// Check test byte
		ASSERT_EQ(0, procReader->getByte(*testTag));

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessReader::getByte: ";
		s << "Tag: " << testTag->getName() << " has wrong type";

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	testTag->setType(onh::TagType::TT_BYTE);
	testTag->setAddress({onh::PDA_INPUT, PROCESS_DT_SIZE, 0});

	try {

		// Check test byte
		ASSERT_EQ(0, procReader->getByte(*testTag));

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessReader::getByte: (" << testTag->getName() << "): ";
		s << "ShmProcessReader::getByte: Byte address is out of range";

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	testTag->setType(onh::TagType::TT_WORD);

	// Check test word
	ASSERT_EQ(0, procReader->getWord(*testTag));

	// Change word
	driver->writeWord(testTag->getAddress(), 45801);

	// Wait on synchronization
	waitOnSyncBit();

	// Check test word
	ASSERT_EQ(45801, procReader->getWord(*testTag));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 0) {
			ASSERT_EQ(45801, shmReader->getWord({onh::PDA_INPUT, i, 0}));
			ASSERT_EQ(233, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		} else if (i == 1) {
			ASSERT_EQ(178, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		}

		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}
}

/**
 * Check process reader get WORD wrong Tag type
 */
TEST_F(driverTests, processReaderGetWordException1) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	try {

		// Check test word
		ASSERT_EQ(0, procReader->getWord(*testTag));

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessReader::getWord: ";
		s << "Tag: " << testTag->getName() << " has wrong type";

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	testTag->setType(onh::TagType::TT_WORD);
	testTag->setAddress({onh::PDA_INPUT, PROCESS_DT_SIZE-1, 0});

	try {

		// Check test word
		ASSERT_EQ(0, procReader->getWord(*testTag));

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessReader::getWord: (" << testTag->getName() << "): ";
		s << "ShmProcessReader::getWord: Byte address is out of range";

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	testTag->setType(onh::TagType::TT_DWORD);

	// Check test dword
	ASSERT_EQ((DWORD)0, procReader->getDWord(*testTag));

	// Change dword (1110 0010 1100 0110 0101 0001 1101 1100)
	driver->writeDWord(testTag->getAddress(), 3804647900);

	// Wait on synchronization
	waitOnSyncBit();

	// Check test dword
	ASSERT_EQ((DWORD)3804647900, procReader->getDWord(*testTag));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		switch (i) {
			case 0: {
					ASSERT_EQ((DWORD)3804647900, shmReader->getDWord({onh::PDA_INPUT, i, 0}));
					ASSERT_EQ(20956, shmReader->getWord({onh::PDA_INPUT, i, 0}));
					ASSERT_EQ(220, shmReader->getByte({onh::PDA_INPUT, i, 0}));
				}; break;
			case 1: {
					ASSERT_EQ(50769, shmReader->getWord({onh::PDA_INPUT, i, 0}));
					ASSERT_EQ(81, shmReader->getByte({onh::PDA_INPUT, i, 0}));
				}; break;
			case 2: {
					ASSERT_EQ(58054, shmReader->getWord({onh::PDA_INPUT, i, 0}));
					ASSERT_EQ(198, shmReader->getByte({onh::PDA_INPUT, i, 0}));
				}; break;
			case 3: {
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
 * Check process reader get DWORD wrong Tag type
 */
TEST_F(driverTests, processReaderGetDWordException1) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	try {

		// Check test word
		ASSERT_EQ((DWORD)0, procReader->getDWord(*testTag));

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessReader::getDWord: ";
		s << "Tag: " << testTag->getName() << " has wrong type";

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	testTag->setType(onh::TagType::TT_DWORD);
	testTag->setAddress({onh::PDA_INPUT, PROCESS_DT_SIZE-1, 0});

	try {

		// Check test word
		ASSERT_EQ((DWORD)0, procReader->getDWord(*testTag));

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessReader::getDWord: (" << testTag->getName() << "): ";
		s << "ShmProcessReader::getDWord: Byte address is out of range";

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	testTag->setType(onh::TagType::TT_INT);

	// Check test int
	ASSERT_EQ(0, procReader->getInt(*testTag));

	// Change int
	driver->writeInt(testTag->getAddress(), -548);

	// Wait on synchronization
	waitOnSyncBit();

	// Check test dword
	ASSERT_EQ(-548, procReader->getInt(*testTag));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 0) {
			ASSERT_EQ(-548, shmReader->getInt({onh::PDA_INPUT, i, 0}));
			// Skip checking bytes in int
			i += 3;
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}
}

/**
 * Check process reader get INT wrong Tag type
 */
TEST_F(driverTests, processReaderGetIntException1) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	try {

		// Check test int
		ASSERT_EQ(0, procReader->getInt(*testTag));

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessReader::getInt: ";
		s << "Tag: " << testTag->getName() << " has wrong type";

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	testTag->setType(onh::TagType::TT_INT);
	testTag->setAddress({onh::PDA_INPUT, PROCESS_DT_SIZE-1, 0});

	try {

		// Check test int
		ASSERT_EQ(0, procReader->getInt(*testTag));

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessReader::getInt: (" << testTag->getName() << "): ";
		s << "ShmProcessReader::getInt: Byte address is out of range";

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	testTag->setType(onh::TagType::TT_REAL);

	// Check test real
	ASSERT_EQ((float)0, procReader->getReal(*testTag));

	// Change real
	driver->writeReal(testTag->getAddress(), -1589.74);

	// Wait on synchronization
	waitOnSyncBit();

	// Check test real
	ASSERT_EQ((float)-1589.74, procReader->getReal(*testTag));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 0) {
			ASSERT_EQ((float)-1589.74, shmReader->getReal({onh::PDA_INPUT, i, 0}));
			// Skip checking bytes in real
			i += 3;
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}
}

/**
 * Check process reader get REAL wrong Tag type
 */
TEST_F(driverTests, processReaderGetRealException1) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	try {

		// Check test real
		ASSERT_EQ((float)0, procReader->getReal(*testTag));

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessReader::getReal: ";
		s << "Tag: " << testTag->getName() << " has wrong type";

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	testTag->setType(onh::TagType::TT_REAL);
	testTag->setAddress({onh::PDA_INPUT, PROCESS_DT_SIZE-1, 0});

	try {

		// Check test real
		ASSERT_EQ((float)0, procReader->getReal(*testTag));

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessReader::getReal: (" << testTag->getName() << "): ";
		s << "ShmProcessReader::getReal: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

#endif /* TESTS_DRIVER_PROCESSREADERTESTS_H_ */
