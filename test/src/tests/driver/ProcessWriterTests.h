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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

	// Change bit
	procWriter->setBit(*testTag);

	// Wait on synchronization
	waitOnSyncBit();

	// Check test bit
	ASSERT_TRUE(procReader->getBitValue(*testTag));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 0) {
			ASSERT_EQ(1, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		} else {
			ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		}

		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}
}

/**
 * Check process writer set bit wrong Tag type
 */
TEST_F(driverTests, processWriterSetBitException1) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

	testTag->setType(onh::TT_BYTE);

	try {

		procWriter->setBit(*testTag);

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessWriter::setBit: ";
		s << "Tag: " << testTag->getName() << " has wrong type";

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

	testTag->setAddress({onh::PDA_INPUT, PROCESS_DT_SIZE+10, 0});

	try {

		procWriter->setBit(*testTag);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::setBit: (" << testTag->getName() << "): ";
		s << "ShmProcessWriter::modifyBit: Byte address is out of range";

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

	// Change bit
	procWriter->setBit(*testTag);

	// Wait on synchronization
	waitOnSyncBit();

	// Check test bit
	ASSERT_TRUE(procReader->getBitValue(*testTag));

	procWriter->resetBit(*testTag);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}
}

/**
 * Check process writer reset bit wrong Tag type
 */
TEST_F(driverTests, processWriterResetBitException1) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

	testTag->setType(onh::TT_BYTE);

	try {

		procWriter->resetBit(*testTag);

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessWriter::resetBit: ";
		s << "Tag: " << testTag->getName() << " has wrong type";

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

	testTag->setAddress({onh::PDA_INPUT, PROCESS_DT_SIZE+10, 0});

	try {

		procWriter->resetBit(*testTag);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::resetBit: (" << testTag->getName() << "): ";
		s << "ShmProcessWriter::modifyBit: Byte address is out of range";

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

	// Change bit
	procWriter->invertBit(*testTag);

	// Wait on synchronization
	waitOnSyncBit();

	// Check test bit
	ASSERT_TRUE(procReader->getBitValue(*testTag));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 0) {
			ASSERT_EQ(1, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		} else {
			ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		}

		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

	procWriter->invertBit(*testTag);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}
}

/**
 * Check process writer invert bit wrong Tag type
 */
TEST_F(driverTests, processWriterInvertBitException1) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

	testTag->setType(onh::TT_BYTE);

	try {

		procWriter->invertBit(*testTag);

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessWriter::invertBit: ";
		s << "Tag: " << testTag->getName() << " has wrong type";

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

	testTag->setAddress({onh::PDA_INPUT, PROCESS_DT_SIZE+10, 0});

	try {

		procWriter->invertBit(*testTag);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::invertBit: (" << testTag->getName() << "): ";
		s << "ShmProcessWriter::modifyBit: Byte address is out of range";

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

	onh::Tag tag2(
		15,
		dc.getId(),
		"TestTag2",
		onh::TT_BIT,
		{onh::PDA_INPUT, 0, 2}
	);

	onh::Tag tag3(
		16,
		dc.getId(),
		"TestTag3",
		onh::TT_BIT,
		{onh::PDA_INPUT, 0, 6}
	);

	std::vector<onh::Tag> vTags;
	vTags.push_back(*testTag);
	vTags.push_back(tag2);
	vTags.push_back(tag3);

	procWriter->setBits(vTags);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 0) {
			ASSERT_EQ(69, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		} else {
			ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		}

		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}
}

/**
 * Check process writer set bits empty tag vector
 */
TEST_F(driverTests, processWriterSetBitsException1) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

	onh::Tag tag2(
		15,
		dc.getId(),
		"TestTag2",
		onh::TT_BYTE,
		{onh::PDA_INPUT, 5, 0}
	);

	std::vector<onh::Tag> vTags;
	vTags.push_back(*testTag);
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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

	onh::Tag tag2(
		15,
		dc.getId(),
		"TestTag2",
		onh::TT_BIT,
		{onh::PDA_INPUT, PROCESS_DT_SIZE+10, 0}
	);

	std::vector<onh::Tag> vTags;
	vTags.push_back(*testTag);
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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

	testTag->setType(onh::TagType::TT_BYTE);

	procWriter->writeByte(*testTag, 154);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 0) {
			ASSERT_EQ(154, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		} else {
			ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		}

		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}
}

/**
 * Check process writer set BYTE wrong Tag type
 */
TEST_F(driverTests, processWriterSetByteException1) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

	try {

		procWriter->writeByte(*testTag, 154);

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessWriter::writeByte: ";
		s << "Tag: " << testTag->getName() << " has wrong type";

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

	testTag->setType(onh::TagType::TT_BYTE);
	testTag->setAddress({onh::PDA_INPUT, PROCESS_DT_SIZE, 0});

	try {

		procWriter->writeByte(*testTag, 154);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::writeByte: (" << testTag->getName() << "): ";
		s << "ShmProcessWriter::writeByte: Byte address is out of range";

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

	testTag->setType(onh::TagType::TT_WORD);

	// Change word
	procWriter->writeWord(*testTag, 45801);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 0) {
			ASSERT_EQ(45801, procReader->getWord(createWordTag({onh::PDA_INPUT, i, 0})));
			ASSERT_EQ(233, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		} else if (i == 1) {
			ASSERT_EQ(178, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		} else {
			ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		}

		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}
}

/**
 * Check process writer set WORD wrong Tag type
 */
TEST_F(driverTests, processWriterSetWordException1) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

	try {

		procWriter->writeWord(*testTag, 45801);

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessWriter::writeWord: ";
		s << "Tag: " << testTag->getName() << " has wrong type";

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

	testTag->setType(onh::TagType::TT_WORD);
	testTag->setAddress({onh::PDA_INPUT, PROCESS_DT_SIZE-1, 0});

	try {

		procWriter->writeWord(*testTag, 45801);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::writeWord: (" << testTag->getName() << "): ";
		s << "ShmProcessWriter::writeWord: Byte address is out of range";

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

	testTag->setType(onh::TagType::TT_DWORD);

	// Change dword (1110 0010 1100 0110 0101 0001 1101 1100)
	procWriter->writeDWord(*testTag, 3804647900);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		switch (i) {
			case 0: {
					ASSERT_EQ((DWORD)3804647900, procReader->getDWord(createDWordTag({onh::PDA_INPUT, i, 0})));
					ASSERT_EQ(20956, procReader->getWord(createWordTag({onh::PDA_INPUT, i, 0})));
					ASSERT_EQ(220, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
				}; break;
			case 1: {
					ASSERT_EQ(50769, procReader->getWord(createWordTag({onh::PDA_INPUT, i, 0})));
					ASSERT_EQ(81, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
				}; break;
			case 2: {
					ASSERT_EQ(58054, procReader->getWord(createWordTag({onh::PDA_INPUT, i, 0})));
					ASSERT_EQ(198, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
				}; break;
			case 3: {
					ASSERT_EQ(226, procReader->getWord(createWordTag({onh::PDA_INPUT, i, 0})));
					ASSERT_EQ(226, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
				}; break;
			default: ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0}))); break;
		}

		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}
}

/**
 * Check process writer set DWORD wrong Tag type
 */
TEST_F(driverTests, processWriterSetDWordException1) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

	try {

		procWriter->writeDWord(*testTag, 3804647900);

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessWriter::writeDWord: ";
		s << "Tag: " << testTag->getName() << " has wrong type";

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

	testTag->setType(onh::TagType::TT_DWORD);
	testTag->setAddress({onh::PDA_INPUT, PROCESS_DT_SIZE-1, 0});

	try {

		procWriter->writeDWord(*testTag, 3804647900);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::writeDWord: (" << testTag->getName() << "): ";
		s << "ShmProcessWriter::writeDWord: Byte address is out of range";

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

	testTag->setType(onh::TagType::TT_INT);

	// Change int
	procWriter->writeInt(*testTag, -548);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 0) {
			ASSERT_EQ(-548, procReader->getInt(createIntTag({onh::PDA_INPUT, i, 0})));
			// Skip checking bytes in int
			i += 3;
		} else {
			ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}
}

/**
 * Check process writer set INT wrong Tag type
 */
TEST_F(driverTests, processWriterSetIntException1) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

	try {

		procWriter->writeInt(*testTag, -548);

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessWriter::writeInt: ";
		s << "Tag: " << testTag->getName() << " has wrong type";

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

	testTag->setType(onh::TagType::TT_INT);
	testTag->setAddress({onh::PDA_INPUT, PROCESS_DT_SIZE-1, 0});

	try {

		procWriter->writeInt(*testTag, -548);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::writeInt: (" << testTag->getName() << "): ";
		s << "ShmProcessWriter::writeInt: Byte address is out of range";

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

	testTag->setType(onh::TagType::TT_REAL);

	// Change real
	procWriter->writeReal(*testTag, -1589.74);

	// Wait on synchronization
	waitOnSyncBit();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 0) {
			ASSERT_EQ((float)-1589.74, procReader->getReal(createRealTag({onh::PDA_INPUT, i, 0})));
			// Skip checking bytes in real
			i += 3;
		} else {
			ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}
}

/**
 * Check process writer set REAL wrong Tag type
 */
TEST_F(driverTests, processWriterSetRealException1) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

	try {

		procWriter->writeReal(*testTag, -1589.74);

		FAIL() << "Expected onh::TagException";
	} catch (onh::TagException &e) {

		std::stringstream s;
		s << "ProcessWriter::writeReal: ";
		s << "Tag: " << testTag->getName() << " has wrong type";

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
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0})));
		ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0})));
	}

	testTag->setType(onh::TagType::TT_REAL);
	testTag->setAddress({onh::PDA_INPUT, PROCESS_DT_SIZE-1, 0});

	try {

		procWriter->writeReal(*testTag, -1589.74);

		FAIL() << "Expected onh::Exception";
	} catch (onh::Exception &e) {

		std::stringstream s;
		s << "ProcessWriter::writeReal: (" << testTag->getName() << "): ";
		s << "ShmProcessWriter::writeReal: Byte address is out of range";

		ASSERT_STREQ(e.what(), s.str().c_str());

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

#endif /* TESTS_DRIVER_PROCESSWRITERTESTS_H_ */
