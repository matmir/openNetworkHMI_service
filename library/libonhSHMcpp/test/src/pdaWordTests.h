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

#ifndef PDAWORDTESTS_H_
#define PDAWORDTESTS_H_

#include <gtest/gtest.h>
#include "pdaTestGlobalData.h"
#include "fixtures/pdaClearTest.h"

using namespace onh;

/**
 * Check single input word
 */
TEST_F(pdaClearTest, TestInputWord1) {

	pda->writeWord(processDataAddress{PDA_INPUT, 2, 0}, 45801);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_EQ(45801, pda->getWord(processDataAddress{PDA_INPUT, i, 0}));
			ASSERT_EQ(233, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		} else if (i==3) {
			ASSERT_EQ(178, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check if input words not overlapping itself
 */
TEST_F(pdaClearTest, TestInputWord2) {

	pda->writeWord(processDataAddress{PDA_INPUT, 1, 0}, 45801);
	pda->writeWord(processDataAddress{PDA_INPUT, 3, 0}, 58007);
	pda->writeWord(processDataAddress{PDA_INPUT, 5, 0}, 14888);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 1: {
					ASSERT_EQ(45801, pda->getWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(233, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
				}; break;
			case 2: {
					ASSERT_EQ(178, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
				}; break;
			case 3: {
					ASSERT_EQ(58007, pda->getWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(151, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
				}; break;
			case 4: {
					ASSERT_EQ(226, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
				}; break;
			case 5: {
					ASSERT_EQ(14888, pda->getWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(40, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
				}; break;
			case 6: {
					ASSERT_EQ(58, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
				}; break;
			default: ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0})); break;
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check single output word
 */
TEST_F(pdaClearTest, TestOutputWord1) {

	pda->writeWord(processDataAddress{PDA_OUTPUT, 2, 0}, 45801);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_EQ(45801, pda->getWord(processDataAddress{PDA_OUTPUT, i, 0}));
			ASSERT_EQ(233, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		} else if (i==3) {
			ASSERT_EQ(178, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check if output words not overlapping itself
 */
TEST_F(pdaClearTest, TestOutputWord2) {

	pda->writeWord(processDataAddress{PDA_OUTPUT, 1, 0}, 45801);
	pda->writeWord(processDataAddress{PDA_OUTPUT, 3, 0}, 58007);
	pda->writeWord(processDataAddress{PDA_OUTPUT, 5, 0}, 14888);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 1: {
					ASSERT_EQ(45801, pda->getWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(233, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			case 2: {
					ASSERT_EQ(178, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			case 3: {
					ASSERT_EQ(58007, pda->getWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(151, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			case 4: {
					ASSERT_EQ(226, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			case 5: {
					ASSERT_EQ(14888, pda->getWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(40, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			case 6: {
					ASSERT_EQ(58, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			default: ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0})); break;
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check single memory word
 */
TEST_F(pdaClearTest, TestMemoryWord1) {

	pda->writeWord(processDataAddress{PDA_MEMORY, 2, 0}, 45801);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_EQ(45801, pda->getWord(processDataAddress{PDA_MEMORY, i, 0}));
			ASSERT_EQ(233, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		} else if (i==3) {
			ASSERT_EQ(178, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
	}
}

/**
 * Check if memory words not overlapping itself
 */
TEST_F(pdaClearTest, TestMemoryWord2) {

	pda->writeWord(processDataAddress{PDA_MEMORY, 1, 0}, 45801);
	pda->writeWord(processDataAddress{PDA_MEMORY, 3, 0}, 58007);
	pda->writeWord(processDataAddress{PDA_MEMORY, 5, 0}, 14888);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 1: {
					ASSERT_EQ(45801, pda->getWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(233, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
				}; break;
			case 2: {
					ASSERT_EQ(178, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
				}; break;
			case 3: {
					ASSERT_EQ(58007, pda->getWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(151, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
				}; break;
			case 4: {
					ASSERT_EQ(226, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
				}; break;
			case 5: {
					ASSERT_EQ(14888, pda->getWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(40, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
				}; break;
			case 6: {
					ASSERT_EQ(58, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
				}; break;
			default: ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0})); break;
		}

		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
	}
}

/**
 * Check writing multiple words in multiple areas
 */
TEST_F(pdaClearTest, TestWord1) {

	pda->writeWord(processDataAddress{PDA_INPUT, 1150, 0}, 45801);
	pda->writeWord(processDataAddress{PDA_MEMORY, 4850, 0}, 58007);
	pda->writeWord(processDataAddress{PDA_OUTPUT, 4850, 0}, 14888);
	pda->writeWord(processDataAddress{PDA_OUTPUT, 377, 0}, 14808);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		// Output
		switch (i) {
			case 377: {
					ASSERT_EQ(14808, pda->getWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(216, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			case 378: {
					ASSERT_EQ(57, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			case 4850: {
					ASSERT_EQ(14888, pda->getWord(processDataAddress{PDA_OUTPUT, i, 0}));
					ASSERT_EQ(40, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			case 4851: {
					ASSERT_EQ(58, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
				}; break;
			default: ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0})); break;
		}
		// Input
		switch (i) {
			case 1150: {
					ASSERT_EQ(45801, pda->getWord(processDataAddress{PDA_INPUT, i, 0}));
					ASSERT_EQ(233, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
				}; break;
			case 1151: {
					ASSERT_EQ(178, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
				}; break;
			default: ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0})); break;
		}
		// Memory
		switch (i) {
			case 4850: {
					ASSERT_EQ(58007, pda->getWord(processDataAddress{PDA_MEMORY, i, 0}));
					ASSERT_EQ(151, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
				}; break;
			case 4851: {
					ASSERT_EQ(226, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
				}; break;
			default: ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0})); break;
		}
	}
}

/**
 * Check exception on write word (byte address wrong)
 */
TEST_F(pdaClearTest, TestExceptionWriteWord1) {

	try {

		pda->writeWord(processDataAddress{PDA_INPUT, PROCESS_DT_SIZE-1, 0}, 63855);

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::writeWord: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on write word (bit address wrong)
 */
TEST_F(pdaClearTest, TestExceptionWriteWord2) {

	try {

		pda->writeWord(processDataAddress{PDA_INPUT, 150, 9}, 60400);

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkBitAddress: Bit value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on write word (area wrong)
 */
TEST_F(pdaClearTest, TestExceptionWriteWord3) {

	try {

		pda->writeWord(processDataAddress{(processDataArea)5, 150, 2}, 37546);

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkArea: Area value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on read word (byte address wrong)
 */
TEST_F(pdaClearTest, TestExceptionReadWord1) {

	try {

		pda->getWord(processDataAddress{PDA_INPUT, PROCESS_DT_SIZE-1, 0});

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::getWord: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on read word (bit address wrong)
 */
TEST_F(pdaClearTest, TestExceptionReadWord2) {

	try {

		pda->getWord(processDataAddress{PDA_INPUT, 150, 9});

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkBitAddress: Bit value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on read word (area wrong)
 */
TEST_F(pdaClearTest, TestExceptionReadWord3) {

	try {

		pda->getWord(processDataAddress{(processDataArea)5, 150, 2});

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkArea: Area value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

#endif /* PDAWORDTESTS_H_ */
