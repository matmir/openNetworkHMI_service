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

#ifndef PDABYTETESTS_H_
#define PDABYTETESTS_H_

#include <gtest/gtest.h>
#include "pdaTestGlobalData.h"
#include "fixtures/pdaClearTest.h"

using namespace onh;

/**
 * Check single input byte
 */
TEST_F(pdaClearTest, TestInputByte1) {

	pda->writeByte(processDataAddress{PDA_INPUT, 2, 0}, 45);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_EQ(45, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check if input bytes not overlapping itself
 */
TEST_F(pdaClearTest, TestInputByte2) {

	pda->writeByte(processDataAddress{PDA_INPUT, 0, 0}, 7);
	pda->writeByte(processDataAddress{PDA_INPUT, 1, 0}, 45);
	pda->writeByte(processDataAddress{PDA_INPUT, 2, 0}, 252);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 0: ASSERT_EQ(7, pda->getByte(processDataAddress{PDA_INPUT, i, 0})); break;
			case 1: ASSERT_EQ(45, pda->getByte(processDataAddress{PDA_INPUT, i, 0})); break;
			case 2: ASSERT_EQ(252, pda->getByte(processDataAddress{PDA_INPUT, i, 0})); break;
			default: ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0})); break;
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check single output byte
 */
TEST_F(pdaClearTest, TestOutputByte1) {

	pda->writeByte(processDataAddress{PDA_OUTPUT, 203, 0}, 107);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 203) {
			ASSERT_EQ(107, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check if output bytes not overlapping itself
 */
TEST_F(pdaClearTest, TestOutputByte2) {

	pda->writeByte(processDataAddress{PDA_OUTPUT, 54, 0}, 44);
	pda->writeByte(processDataAddress{PDA_OUTPUT, 55, 0}, 1);
	pda->writeByte(processDataAddress{PDA_OUTPUT, 56, 0}, 109);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 54: ASSERT_EQ(44, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0})); break;
			case 55: ASSERT_EQ(1, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0})); break;
			case 56: ASSERT_EQ(109, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0})); break;
			default: ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0})); break;
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check single memory byte
 */
TEST_F(pdaClearTest, TestMemoryByte1) {

	pda->writeByte(processDataAddress{PDA_MEMORY, 1785, 0}, 6);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 1785) {
			ASSERT_EQ(6, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
	}
}

/**
 * Check if memory bytes not overlapping itself
 */
TEST_F(pdaClearTest, TestMemoryByte2) {

	pda->writeByte(processDataAddress{PDA_MEMORY, 82, 0}, 97);
	pda->writeByte(processDataAddress{PDA_MEMORY, 83, 0}, 2);
	pda->writeByte(processDataAddress{PDA_MEMORY, 84, 0}, 53);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 82: ASSERT_EQ(97, pda->getByte(processDataAddress{PDA_MEMORY, i, 0})); break;
			case 83: ASSERT_EQ(2, pda->getByte(processDataAddress{PDA_MEMORY, i, 0})); break;
			case 84: ASSERT_EQ(53, pda->getByte(processDataAddress{PDA_MEMORY, i, 0})); break;
			default: ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0})); break;
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
	}
}

/**
 * Check writing multiple bytes in multiple areas
 */
TEST_F(pdaClearTest, TestByte1) {

	pda->writeByte(processDataAddress{PDA_INPUT, 1150, 0}, 63);
	pda->writeByte(processDataAddress{PDA_MEMORY, 4850, 0}, 8);
	pda->writeByte(processDataAddress{PDA_OUTPUT, 4850, 0}, 70);
	pda->writeByte(processDataAddress{PDA_OUTPUT, 377, 0}, 114);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		if (i==377) {
			ASSERT_EQ(114, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		} else if (i==4850){
			ASSERT_EQ(70, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		}

		if (i==1150) {
			ASSERT_EQ(63, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		}

		if (i==4850) {
			ASSERT_EQ(8, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		}
	}
}

/**
 * Check exception on write byte (byte address wrong)
 */
TEST_F(pdaClearTest, TestExceptionWriteByte1) {

	try {

		pda->writeByte(processDataAddress{PDA_INPUT, PROCESS_DT_SIZE+100, 0}, 45);

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::writeByte: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on write byte (bit address wrong)
 */
TEST_F(pdaClearTest, TestExceptionWriteByte2) {

	try {

		pda->writeByte(processDataAddress{PDA_INPUT, 150, 9}, 45);

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkBitAddress: Bit value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on write byte (area wrong)
 */
TEST_F(pdaClearTest, TestExceptionWriteByte3) {

	try {

		pda->writeByte(processDataAddress{(processDataArea)5, 150, 2}, 45);

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkArea: Area value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on read byte (byte address wrong)
 */
TEST_F(pdaClearTest, TestExceptionReadByte1) {

	try {

		pda->getByte(processDataAddress{PDA_INPUT, PROCESS_DT_SIZE+10, 0});

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::getByte: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on read byte (bit address wrong)
 */
TEST_F(pdaClearTest, TestExceptionReadByte2) {

	try {

		pda->getByte(processDataAddress{PDA_INPUT, 150, 9});

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkBitAddress: Bit value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on read byte (area wrong)
 */
TEST_F(pdaClearTest, TestExceptionReadByte3) {

	try {

		pda->getByte(processDataAddress{(processDataArea)5, 150, 2});

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkArea: Area value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

#endif /* PDABYTETESTS_H_ */
