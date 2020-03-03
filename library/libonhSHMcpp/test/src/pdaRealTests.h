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

#ifndef PDAREALTESTS_H_
#define PDAREALTESTS_H_

#include <gtest/gtest.h>
#include "pdaTestGlobalData.h"
#include "fixtures/pdaClearTest.h"

using namespace onh;

/**
 * Check single input real
 */
TEST_F(pdaClearTest, TestInputReal1) {

	pda->writeReal(processDataAddress{PDA_INPUT, 2, 0}, -49.709);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_FLOAT_EQ(-49.709, pda->getReal(processDataAddress{PDA_INPUT, i, 0}));
			// Skip checking bytes in float
			i += 3;
		} else {
			ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check if input real not overlapping itself
 */
TEST_F(pdaClearTest, TestInputReal2) {

	pda->writeReal(processDataAddress{PDA_INPUT, 0, 0}, -7.003);
	pda->writeReal(processDataAddress{PDA_INPUT, sizeof(float), 0}, 65489.14);
	pda->writeReal(processDataAddress{PDA_INPUT, sizeof(float)*2, 0}, -37489.1006);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 0: {
					ASSERT_FLOAT_EQ(-7.003, pda->getReal(processDataAddress{PDA_INPUT, i, 0}));
					// Skip checking bytes in float
					i += 3;
				}; break;
			case sizeof(float): {
					ASSERT_FLOAT_EQ(65489.14, pda->getReal(processDataAddress{PDA_INPUT, i, 0}));
					// Skip checking bytes in float
					i += 3;
				}; break;
			case sizeof(float)*2: {
					ASSERT_FLOAT_EQ(-37489.1006, pda->getReal(processDataAddress{PDA_INPUT, i, 0}));
					// Skip checking bytes in float
					i += 3;
				}; break;
			default: ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0})); break;
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check single output real
 */
TEST_F(pdaClearTest, TestOutputReal1) {

	pda->writeReal(processDataAddress{PDA_OUTPUT, 2, 0}, -49.709);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_FLOAT_EQ(-49.709, pda->getReal(processDataAddress{PDA_OUTPUT, i, 0}));
			// Skip checking bytes in float
			i += 3;
		} else {
			ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check if output real not overlapping itself
 */
TEST_F(pdaClearTest, TestOutputReal2) {

	pda->writeReal(processDataAddress{PDA_OUTPUT, 0, 0}, -7.003);
	pda->writeReal(processDataAddress{PDA_OUTPUT, sizeof(float), 0}, 65489.14);
	pda->writeReal(processDataAddress{PDA_OUTPUT, sizeof(float)*2, 0}, -37489.1006);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 0: {
					ASSERT_FLOAT_EQ(-7.003, pda->getReal(processDataAddress{PDA_OUTPUT, i, 0}));
					// Skip checking bytes in float
					i += 3;
				}; break;
			case sizeof(float): {
					ASSERT_FLOAT_EQ(65489.14, pda->getReal(processDataAddress{PDA_OUTPUT, i, 0}));
					// Skip checking bytes in float
					i += 3;
				}; break;
			case sizeof(float)*2: {
					ASSERT_FLOAT_EQ(-37489.1006, pda->getReal(processDataAddress{PDA_OUTPUT, i, 0}));
					// Skip checking bytes in float
					i += 3;
				}; break;
			default: ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0})); break;
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
}

/**
 * Check single memory real
 */
TEST_F(pdaClearTest, TestMemoryReal1) {

	pda->writeReal(processDataAddress{PDA_MEMORY, 2, 0}, -49.709);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_FLOAT_EQ(-49.709, pda->getReal(processDataAddress{PDA_MEMORY, i, 0}));
			// Skip checking bytes in float
			i += 3;
		} else {
			ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
	}
}

/**
 * Check if memory real not overlapping itself
 */
TEST_F(pdaClearTest, TestMemoryReal2) {

	pda->writeReal(processDataAddress{PDA_MEMORY, 0, 0}, -7.003);
	pda->writeReal(processDataAddress{PDA_MEMORY, sizeof(float), 0}, 65489.14);
	pda->writeReal(processDataAddress{PDA_MEMORY, sizeof(float)*2, 0}, -37489.1006);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 0: {
					ASSERT_FLOAT_EQ(-7.003, pda->getReal(processDataAddress{PDA_MEMORY, i, 0}));
					// Skip checking bytes in float
					i += 3;
				}; break;
			case sizeof(float): {
					ASSERT_FLOAT_EQ(65489.14, pda->getReal(processDataAddress{PDA_MEMORY, i, 0}));
					// Skip checking bytes in float
					i += 3;
				}; break;
			case sizeof(float)*2: {
					ASSERT_FLOAT_EQ(-37489.1006, pda->getReal(processDataAddress{PDA_MEMORY, i, 0}));
					// Skip checking bytes in float
					i += 3;
				}; break;
			default: ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0})); break;
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
	}
}

/**
 * Check writing multiple real in multiple areas
 */
TEST_F(pdaClearTest, TestReal1) {

	pda->writeReal(processDataAddress{PDA_INPUT, 1150, 0}, -706.2356);
	pda->writeReal(processDataAddress{PDA_MEMORY, 4850, 0}, 495321.04);
	pda->writeReal(processDataAddress{PDA_OUTPUT, 4850, 0}, -1.006);
	pda->writeReal(processDataAddress{PDA_OUTPUT, 377, 0}, 0.007);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		// Input
		switch (i) {
			case 1150: {
					ASSERT_FLOAT_EQ(-706.2356, pda->getReal(processDataAddress{PDA_INPUT, i, 0}));
					// Skip checking bytes in float
					i += 3;
				}; break;
			default: ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0})); break;
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		// Memory
		switch (i) {
			case 4850: {
					ASSERT_FLOAT_EQ(495321.04, pda->getReal(processDataAddress{PDA_MEMORY, i, 0}));
					// Skip checking bytes in float
					i += 3;
				}; break;
			default: ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0})); break;
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		// Output
		switch (i) {
			case 377: {
					ASSERT_FLOAT_EQ(0.007, pda->getReal(processDataAddress{PDA_OUTPUT, i, 0}));
					// Skip checking bytes in float
					i += 3;
				}; break;
			case 4850: {
					ASSERT_FLOAT_EQ(-1.006, pda->getReal(processDataAddress{PDA_OUTPUT, i, 0}));
					// Skip checking bytes in float
					i += 3;
				}; break;
			default: ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0})); break;
		}
	}
}

/**
 * Check exception on write real (byte address wrong)
 */
TEST_F(pdaClearTest, TestExceptionWriteReal1) {

	try {

		pda->writeReal(processDataAddress{PDA_INPUT, PROCESS_DT_SIZE-(sizeof(float)-1), 0}, -45);

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::writeReal: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on write real (bit address wrong)
 */
TEST_F(pdaClearTest, TestExceptionWriteReal2) {

	try {

		pda->writeReal(processDataAddress{PDA_INPUT, 150, 9}, -45);

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkBitAddress: Bit value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on write real (area wrong)
 */
TEST_F(pdaClearTest, TestExceptionWriteReal3) {

	try {

		pda->writeReal(processDataAddress{(processDataArea)5, 150, 2}, -45);

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkArea: Area value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on read real (byte address wrong)
 */
TEST_F(pdaClearTest, TestExceptionReadReal1) {

	try {

		pda->getReal(processDataAddress{PDA_INPUT, PROCESS_DT_SIZE-(sizeof(float)-1), 0});

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::getReal: Byte address is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on read real (bit address wrong)
 */
TEST_F(pdaClearTest, TestExceptionReadReal2) {

	try {

		pda->getReal(processDataAddress{PDA_INPUT, 150, 9});

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkBitAddress: Bit value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

/**
 * Check exception on read real (area wrong)
 */
TEST_F(pdaClearTest, TestExceptionReadReal3) {

	try {

		pda->getReal(processDataAddress{(processDataArea)5, 150, 2});

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "processDataAccess::checkArea: Area value is out of range");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}

}

#endif /* PDAREALTESTS_H_ */
