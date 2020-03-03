/**
 * Copyright (c) 2020 Mateusz Mirosławski
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of mosquitto nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef PDADWORDTESTS_H_
#define PDADWORDTESTS_H_

#include <gtest/gtest.h>
#include "pdaTestGlobalData.h"
#include "fixtures/pdaClearTest.h"

using namespace onh;

/**
 * Check single input double word
 */
TEST_F(pdaClearTest, TestInputDWord1) {

	// 1110 0010 1100 0110 0101 0001 1101 1100
	pda->writeDWord(processDataAddress{PDA_INPUT, 7, 0}, 3804647900);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		switch (i) {
			case 7: {
					ASSERT_EQ((DWORD)3804647900, pda->getDWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(20956, pda->getWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(220, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
				}; break;
			case 8: {
					ASSERT_EQ(50769, pda->getWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(81, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
				}; break;
			case 9: {
					ASSERT_EQ(58054, pda->getWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(198, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
				}; break;
			case 10: {
					ASSERT_EQ(226, pda->getWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(226, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
				}; break;
			default: ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0})); break;
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check if input double words not overlapping itself
 */
TEST_F(pdaClearTest, TestInputDWord2) {

	// 1110 0010 1100 0110 0101 0001 1101 1100
	pda->writeDWord(processDataAddress{PDA_INPUT, 1, 0}, 3804647900);
	// 0001 0000 1000 0001 1011 0011 0111 1100
	pda->writeDWord(processDataAddress{PDA_INPUT, 5, 0}, 276935548);
	// 0100 0000 0000 0101 1110 0011 1011 0101
	pda->writeDWord(processDataAddress{PDA_INPUT, 9, 0}, 1074127797);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 1: { // First DWord
					ASSERT_EQ((DWORD)3804647900, pda->getDWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(20956, pda->getWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(220, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
				}; break;
			case 2: {
					ASSERT_EQ(50769, pda->getWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(81, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
				}; break;
			case 3: {
					ASSERT_EQ(58054, pda->getWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(198, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
				}; break;
			case 4: {
					ASSERT_EQ(31970, pda->getWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(226, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
				}; break;
			case 5: { // Second DWord
					ASSERT_EQ((DWORD)276935548, pda->getDWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(45948, pda->getWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(124, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
				}; break;
			case 6: {
					ASSERT_EQ(33203, pda->getWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(179, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
				}; break;
			case 7: {
					ASSERT_EQ(4225, pda->getWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(129, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
				}; break;
			case 8: {
					ASSERT_EQ(46352, pda->getWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(16, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
				}; break;
			case 9: { // Third DWord
					ASSERT_EQ((DWORD)1074127797, pda->getDWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(58293, pda->getWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(181, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
				}; break;
			case 10: {
					ASSERT_EQ(1507, pda->getWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(227, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
				}; break;
			case 11: {
					ASSERT_EQ(16389, pda->getWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(5, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
				}; break;
			case 12: {
					ASSERT_EQ(64, pda->getWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(64, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
				}; break;
			default: ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0})); break;
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check single output double word
 */
TEST_F(pdaClearTest, TestOutputDWord1) {

	// 1110 0010 1100 0110 0101 0001 1101 1100
	pda->writeDWord(processDataAddress{PDA_OUTPUT, 7, 0}, 3804647900);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		switch (i) {
			case 7: {
					ASSERT_EQ((DWORD)3804647900, pda->getDWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(20956, pda->getWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(220, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			case 8: {
					ASSERT_EQ(50769, pda->getWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(81, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			case 9: {
					ASSERT_EQ(58054, pda->getWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(198, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			case 10: {
					ASSERT_EQ(226, pda->getWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(226, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			default: ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0})); break;
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check if output double words not overlapping itself
 */
TEST_F(pdaClearTest, TestOutputDWord2) {

	// 1110 0010 1100 0110 0101 0001 1101 1100
	pda->writeDWord(processDataAddress{PDA_OUTPUT, 1, 0}, 3804647900);
	// 0001 0000 1000 0001 1011 0011 0111 1100
	pda->writeDWord(processDataAddress{PDA_OUTPUT, 5, 0}, 276935548);
	// 0100 0000 0000 0101 1110 0011 1011 0101
	pda->writeDWord(processDataAddress{PDA_OUTPUT, 9, 0}, 1074127797);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 1: { // First DWord
					ASSERT_EQ((DWORD)3804647900, pda->getDWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(20956, pda->getWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(220, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			case 2: {
					ASSERT_EQ(50769, pda->getWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(81, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			case 3: {
					ASSERT_EQ(58054, pda->getWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(198, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			case 4: {
					ASSERT_EQ(31970, pda->getWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(226, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			case 5: { // Second DWord
					ASSERT_EQ((DWORD)276935548, pda->getDWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(45948, pda->getWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(124, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			case 6: {
					ASSERT_EQ(33203, pda->getWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(179, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			case 7: {
					ASSERT_EQ(4225, pda->getWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(129, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			case 8: {
					ASSERT_EQ(46352, pda->getWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(16, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			case 9: { // Third DWord
					ASSERT_EQ((DWORD)1074127797, pda->getDWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(58293, pda->getWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(181, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			case 10: {
					ASSERT_EQ(1507, pda->getWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(227, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			case 11: {
					ASSERT_EQ(16389, pda->getWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(5, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			case 12: {
					ASSERT_EQ(64, pda->getWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(64, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			default: ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0})); break;
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check single memory double word
 */
TEST_F(pdaClearTest, TestMemoryDWord1) {

	// 1110 0010 1100 0110 0101 0001 1101 1100
	pda->writeDWord(processDataAddress{PDA_MEMORY, 7, 0}, 3804647900);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		switch (i) {
			case 7: {
					ASSERT_EQ((DWORD)3804647900, pda->getDWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(20956, pda->getWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(220, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
				}; break;
			case 8: {
					ASSERT_EQ(50769, pda->getWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(81, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
				}; break;
			case 9: {
					ASSERT_EQ(58054, pda->getWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(198, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
				}; break;
			case 10: {
					ASSERT_EQ(226, pda->getWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(226, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
				}; break;
			default: ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0})); break;
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
	}
}

/**
 * Check if memory double words not overlapping itself
 */
TEST_F(pdaClearTest, TestMemoryDWord2) {

	// 1110 0010 1100 0110 0101 0001 1101 1100
	pda->writeDWord(processDataAddress{PDA_MEMORY, 1, 0}, 3804647900);
	// 0001 0000 1000 0001 1011 0011 0111 1100
	pda->writeDWord(processDataAddress{PDA_MEMORY, 5, 0}, 276935548);
	// 0100 0000 0000 0101 1110 0011 1011 0101
	pda->writeDWord(processDataAddress{PDA_MEMORY, 9, 0}, 1074127797);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 1: { // First DWord
					ASSERT_EQ((DWORD)3804647900, pda->getDWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(20956, pda->getWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(220, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
				}; break;
			case 2: {
					ASSERT_EQ(50769, pda->getWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(81, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
				}; break;
			case 3: {
					ASSERT_EQ(58054, pda->getWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(198, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
				}; break;
			case 4: {
					ASSERT_EQ(31970, pda->getWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(226, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
				}; break;
			case 5: { // Second DWord
					ASSERT_EQ((DWORD)276935548, pda->getDWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(45948, pda->getWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(124, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
				}; break;
			case 6: {
					ASSERT_EQ(33203, pda->getWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(179, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
				}; break;
			case 7: {
					ASSERT_EQ(4225, pda->getWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(129, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
				}; break;
			case 8: {
					ASSERT_EQ(46352, pda->getWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(16, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
				}; break;
			case 9: { // Third DWord
					ASSERT_EQ((DWORD)1074127797, pda->getDWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(58293, pda->getWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(181, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
				}; break;
			case 10: {
					ASSERT_EQ(1507, pda->getWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(227, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
				}; break;
			case 11: {
					ASSERT_EQ(16389, pda->getWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(5, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
				}; break;
			case 12: {
					ASSERT_EQ(64, pda->getWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(64, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
				}; break;
			default: ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0})); break;
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
	}
}

/**
 * Check writing multiple double words in multiple areas
 */
TEST_F(pdaClearTest, TestDWord1) {

	// 1110 0010 1100 0110 0101 0001 1101 1100
	pda->writeDWord(processDataAddress{PDA_MEMORY, 1, 0}, 3804647900);
	// 0001 0000 1000 0001 1011 0011 0111 1100
	pda->writeDWord(processDataAddress{PDA_OUTPUT, 5, 0}, 276935548);
	// 0100 0000 0000 0101 1110 0011 1011 0101
	pda->writeDWord(processDataAddress{PDA_INPUT, 9, 0}, 1074127797);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		// Memory
		switch (i) {
			case 1: {
					ASSERT_EQ((DWORD)3804647900, pda->getDWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(20956, pda->getWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(220, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
				}; break;
			case 2: {
					ASSERT_EQ(50769, pda->getWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(81, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
				}; break;
			case 3: {
					ASSERT_EQ(58054, pda->getWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(198, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
				}; break;
			case 4: {
					ASSERT_EQ(226, pda->getWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(226, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
				}; break;
			default: ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0})); break;
		}
		// Output
		switch (i) {
			case 5: {
					ASSERT_EQ((DWORD)276935548, pda->getDWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(45948, pda->getWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(124, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			case 6: {
					ASSERT_EQ(33203, pda->getWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(179, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			case 7: {
					ASSERT_EQ(4225, pda->getWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(129, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			case 8: {
					ASSERT_EQ(16, pda->getWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(16, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			default: ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0})); break;
		}
		// Input
		switch (i) {
			case 9: { // Third DWord
					ASSERT_EQ((DWORD)1074127797, pda->getDWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(58293, pda->getWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(181, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
				}; break;
			case 10: {
					ASSERT_EQ(1507, pda->getWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(227, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
				}; break;
			case 11: {
					ASSERT_EQ(16389, pda->getWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(5, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
				}; break;
			case 12: {
					ASSERT_EQ(64, pda->getWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(64, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
				}; break;
			default: ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0})); break;
		}

	}
}

/**
 * Check exception on write double word (byte address wrong)
 */
TEST_F(pdaClearTest, TestExceptionWriteDWord1) {

	try {

		pda->writeDWord(processDataAddress{PDA_INPUT, PROCESS_DT_SIZE-3, 0}, 63855);

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::writeDWord: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on write double word (bit address wrong)
 */
TEST_F(pdaClearTest, TestExceptionWriteDWord2) {

	try {

		pda->writeDWord(processDataAddress{PDA_INPUT, 150, 9}, 3460400);

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkBitAddress: Bit value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on write double word (area wrong)
 */
TEST_F(pdaClearTest, TestExceptionWriteDWord3) {

	try {

		pda->writeDWord(processDataAddress{(processDataArea)5, 150, 2}, 66637546);

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkArea: Area value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on read double word (byte address wrong)
 */
TEST_F(pdaClearTest, TestExceptionReadDWord1) {

	try {

		pda->getDWord(processDataAddress{PDA_INPUT, PROCESS_DT_SIZE-3, 0});

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::getDWord: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on read double word (bit address wrong)
 */
TEST_F(pdaClearTest, TestExceptionReadDWord2) {

	try {

		pda->getDWord(processDataAddress{PDA_INPUT, 150, 9});

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkBitAddress: Bit value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on read double word (area wrong)
 */
TEST_F(pdaClearTest, TestExceptionReadDWord3) {

	try {

		pda->getDWord(processDataAddress{(processDataArea)5, 150, 2});

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkArea: Area value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

#endif /* PDADWORDTESTS_H_ */
