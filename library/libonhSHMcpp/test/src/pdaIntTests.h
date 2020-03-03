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

#ifndef PDAINTTESTS_H_
#define PDAINTTESTS_H_

#include <gtest/gtest.h>
#include "pdaTestGlobalData.h"
#include "fixtures/pdaClearTest.h"

using namespace onh;

/**
 * Check single input Int
 */
TEST_F(pdaClearTest, TestInputInt1) {

	pda->writeInt(processDataAddress{PDA_INPUT, 2, 0}, -37489);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_EQ(-37489, pda->getInt(processDataAddress{PDA_INPUT, i, 0}));
			// Skip checking bytes in int
			i += 3;
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check if input int not overlapping itself
 */
TEST_F(pdaClearTest, TestInputInt2) {

	pda->writeInt(processDataAddress{PDA_INPUT, 0, 0}, -7);
	pda->writeInt(processDataAddress{PDA_INPUT, sizeof(int), 0}, 65489);
	pda->writeInt(processDataAddress{PDA_INPUT, sizeof(int)*2, 0}, -37489);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 0: {
					ASSERT_EQ(-7, pda->getInt(processDataAddress{PDA_INPUT, i, 0}));
					// Skip checking bytes in int
					i += 3;
				}; break;
			case sizeof(int): {
					ASSERT_EQ(65489, pda->getInt(processDataAddress{PDA_INPUT, i, 0}));
					// Skip checking bytes in int
					i += 3;
				}; break;
			case sizeof(int)*2: {
					ASSERT_EQ(-37489, pda->getInt(processDataAddress{PDA_INPUT, i, 0}));
					// Skip checking bytes in int
					i += 3;
				}; break;
			default: ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0})); break;
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check single output Int
 */
TEST_F(pdaClearTest, TestOutputInt1) {

	pda->writeInt(processDataAddress{PDA_OUTPUT, 2, 0}, -37489);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_EQ(-37489, pda->getInt(processDataAddress{PDA_OUTPUT, i, 0}));
			// Skip checking bytes in int
			i += 3;
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check if output int not overlapping itself
 */
TEST_F(pdaClearTest, TestOutputInt2) {

	pda->writeInt(processDataAddress{PDA_OUTPUT, 0, 0}, -7);
	pda->writeInt(processDataAddress{PDA_OUTPUT, sizeof(int), 0}, 65489);
	pda->writeInt(processDataAddress{PDA_OUTPUT, sizeof(int)*2, 0}, -37489);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 0: {
					ASSERT_EQ(-7, pda->getInt(processDataAddress{PDA_OUTPUT, i, 0}));
					// Skip checking bytes in int
					i += 3;
				}; break;
			case sizeof(int): {
					ASSERT_EQ(65489, pda->getInt(processDataAddress{PDA_OUTPUT, i, 0}));
					// Skip checking bytes in int
					i += 3;
				}; break;
			case sizeof(int)*2: {
					ASSERT_EQ(-37489, pda->getInt(processDataAddress{PDA_OUTPUT, i, 0}));
					// Skip checking bytes in int
					i += 3;
				}; break;
			default: ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0})); break;
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check single memory Int
 */
TEST_F(pdaClearTest, TestMemoryInt1) {

	pda->writeInt(processDataAddress{PDA_MEMORY, 2, 0}, -37489);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_EQ(-37489, pda->getInt(processDataAddress{PDA_MEMORY, i, 0}));
			// Skip checking bytes in int
			i += 3;
		} else {
			ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
	}
}

/**
 * Check if memory int not overlapping itself
 */
TEST_F(pdaClearTest, TestMemoryInt2) {

	pda->writeInt(processDataAddress{PDA_MEMORY, 0, 0}, -7);
	pda->writeInt(processDataAddress{PDA_MEMORY, sizeof(int), 0}, 65489);
	pda->writeInt(processDataAddress{PDA_MEMORY, sizeof(int)*2, 0}, -37489);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 0: {
					ASSERT_EQ(-7, pda->getInt(processDataAddress{PDA_MEMORY, i, 0}));
					// Skip checking bytes in int
					i += 3;
				}; break;
			case sizeof(int): {
					ASSERT_EQ(65489, pda->getInt(processDataAddress{PDA_MEMORY, i, 0}));
					// Skip checking bytes in int
					i += 3;
				}; break;
			case sizeof(int)*2: {
					ASSERT_EQ(-37489, pda->getInt(processDataAddress{PDA_MEMORY, i, 0}));
					// Skip checking bytes in int
					i += 3;
				}; break;
			default: ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0})); break;
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
	}
}

/**
 * Check writing multiple int in multiple areas
 */
TEST_F(pdaClearTest, TestInt1) {

	pda->writeInt(processDataAddress{PDA_INPUT, 1150, 0}, -706);
	pda->writeInt(processDataAddress{PDA_MEMORY, 4850, 0}, 495321);
	pda->writeInt(processDataAddress{PDA_OUTPUT, 4850, 0}, -1);
	pda->writeInt(processDataAddress{PDA_OUTPUT, 377, 0}, 6487994);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		// Input
		switch (i) {
			case 1150: {
					ASSERT_EQ(-706, pda->getInt(processDataAddress{PDA_INPUT, i, 0}));
					// Skip checking bytes in int
					i += 3;
				}; break;
			default: ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0})); break;
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		// Memory
		switch (i) {
			case 4850: {
					ASSERT_EQ(495321, pda->getInt(processDataAddress{PDA_MEMORY, i, 0}));
					// Skip checking bytes in int
					i += 3;
				}; break;
			default: ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0})); break;
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		// Output
		switch (i) {
			case 377: {
					ASSERT_EQ(6487994, pda->getInt(processDataAddress{PDA_OUTPUT, i, 0}));
					// Skip checking bytes in int
					i += 3;
				}; break;
			case 4850: {
					ASSERT_EQ(-1, pda->getInt(processDataAddress{PDA_OUTPUT, i, 0}));
					// Skip checking bytes in int
					i += 3;
				}; break;
			default: ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0})); break;
		}
	}
}

/**
 * Check exception on write int (byte address wrong)
 */
TEST_F(pdaClearTest, TestExceptionWriteInt1) {

	try {

		pda->writeInt(processDataAddress{PDA_INPUT, PROCESS_DT_SIZE-(sizeof(int)-1), 0}, -45);

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::writeInt: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on write int (bit address wrong)
 */
TEST_F(pdaClearTest, TestExceptionWriteInt2) {

	try {

		pda->writeInt(processDataAddress{PDA_INPUT, 150, 9}, -45);

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkBitAddress: Bit value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on write int (area wrong)
 */
TEST_F(pdaClearTest, TestExceptionWriteInt3) {

	try {

		pda->writeInt(processDataAddress{(processDataArea)5, 150, 2}, -45);

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkArea: Area value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on read int (byte address wrong)
 */
TEST_F(pdaClearTest, TestExceptionReadInt1) {

	try {

		pda->getInt(processDataAddress{PDA_INPUT, PROCESS_DT_SIZE-(sizeof(int)-1), 0});

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::getInt: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on read int (bit address wrong)
 */
TEST_F(pdaClearTest, TestExceptionReadInt2) {

	try {

		pda->getInt(processDataAddress{PDA_INPUT, 150, 9});

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkBitAddress: Bit value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on read int (area wrong)
 */
TEST_F(pdaClearTest, TestExceptionReadInt3) {

	try {

		pda->getInt(processDataAddress{(processDataArea)5, 150, 2});

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkArea: Area value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

#endif /* PDAINTTESTS_H_ */
