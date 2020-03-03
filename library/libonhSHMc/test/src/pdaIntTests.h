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

/**
 * Check single input Int
 */
TEST_F(pdaClearTest, TestInputInt1) {

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_INT(&procDT, processDataAddress{PDA_INPUT, 2, 0}, -37489));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_EQ(-37489, PROCESS_GET_INT(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
			// Skip checking bytes in int
			i += 3;
		} else {
			ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	}
}

/**
 * Check if input int not overlapping itself
 */
TEST_F(pdaClearTest, TestInputInt2) {

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_INT(&procDT, processDataAddress{PDA_INPUT, 0, 0}, -7));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_INT(&procDT, processDataAddress{PDA_INPUT, sizeof(int), 0}, 65489));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_INT(&procDT, processDataAddress{PDA_INPUT, sizeof(int)*2, 0}, -37489));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 0: {
					ASSERT_EQ(-7, PROCESS_GET_INT(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					// Skip checking bytes in int
					i += 3;
				}; break;
			case sizeof(int): {
					ASSERT_EQ(65489, PROCESS_GET_INT(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					// Skip checking bytes in int
					i += 3;
				}; break;
			case sizeof(int)*2: {
					ASSERT_EQ(-37489, PROCESS_GET_INT(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					// Skip checking bytes in int
					i += 3;
				}; break;
			default: {
					ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	}
}

/**
 * Check single output Int
 */
TEST_F(pdaClearTest, TestOutputInt1) {

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_INT(&procDT, processDataAddress{PDA_OUTPUT, 2, 0}, -37489));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_EQ(-37489, PROCESS_GET_INT(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
			// Skip checking bytes in int
			i += 3;
		} else {
			ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	}
}

/**
 * Check if output int not overlapping itself
 */
TEST_F(pdaClearTest, TestOutputInt2) {

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_INT(&procDT, processDataAddress{PDA_OUTPUT, 0, 0}, -7));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_INT(&procDT, processDataAddress{PDA_OUTPUT, sizeof(int), 0}, 65489));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_INT(&procDT, processDataAddress{PDA_OUTPUT, sizeof(int)*2, 0}, -37489));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 0: {
					ASSERT_EQ(-7, PROCESS_GET_INT(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					// Skip checking bytes in int
					i += 3;
				}; break;
			case sizeof(int): {
					ASSERT_EQ(65489, PROCESS_GET_INT(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					// Skip checking bytes in int
					i += 3;
				}; break;
			case sizeof(int)*2: {
					ASSERT_EQ(-37489, PROCESS_GET_INT(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					// Skip checking bytes in int
					i += 3;
				}; break;
			default: {
					ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	}
}

/**
 * Check single memory Int
 */
TEST_F(pdaClearTest, TestMemoryInt1) {

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_INT(&procDT, processDataAddress{PDA_MEMORY, 2, 0}, -37489));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_EQ(-37489, PROCESS_GET_INT(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
			// Skip checking bytes in int
			i += 3;
		} else {
			ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	}
}

/**
 * Check if memory int not overlapping itself
 */
TEST_F(pdaClearTest, TestMemoryInt2) {

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_INT(&procDT, processDataAddress{PDA_MEMORY, 0, 0}, -7));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_INT(&procDT, processDataAddress{PDA_MEMORY, sizeof(int), 0}, 65489));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_INT(&procDT, processDataAddress{PDA_MEMORY, sizeof(int)*2, 0}, -37489));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 0: {
					ASSERT_EQ(-7, PROCESS_GET_INT(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					// Skip checking bytes in int
					i += 3;
				}; break;
			case sizeof(int): {
					ASSERT_EQ(65489, PROCESS_GET_INT(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					// Skip checking bytes in int
					i += 3;
				}; break;
			case sizeof(int)*2: {
					ASSERT_EQ(-37489, PROCESS_GET_INT(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					// Skip checking bytes in int
					i += 3;
				}; break;
			default: {
					ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	}
}

/**
 * Check writing multiple int in multiple areas
 */
TEST_F(pdaClearTest, TestInt1) {

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_INT(&procDT, processDataAddress{PDA_INPUT, 1150, 0}, -706));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_INT(&procDT, processDataAddress{PDA_MEMORY, 4850, 0}, 495321));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_INT(&procDT, processDataAddress{PDA_OUTPUT, 4850, 0}, -1));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_INT(&procDT, processDataAddress{PDA_OUTPUT, 377, 0}, 6487994));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		// Input
		switch (i) {
			case 1150: {
					ASSERT_EQ(-706, PROCESS_GET_INT(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					// Skip checking bytes in int
					i += 3;
				}; break;
			default: {
					ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		// Memory
		switch (i) {
			case 4850: {
					ASSERT_EQ(495321, PROCESS_GET_INT(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					// Skip checking bytes in int
					i += 3;
				}; break;
			default: {
					ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
		}
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		// Output
		switch (i) {
			case 377: {
					ASSERT_EQ(6487994, PROCESS_GET_INT(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					// Skip checking bytes in int
					i += 3;
				}; break;
			case 4850: {
					ASSERT_EQ(-1, PROCESS_GET_INT(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					// Skip checking bytes in int
					i += 3;
				}; break;
			default: {
					ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
		}
	}
}

/**
 * Check error on write int (byte address wrong)
 */
TEST_F(pdaClearTest, TestErrorWriteInt1) {

	procErr = PROCESS_WRITE_INT(&procDT, processDataAddress{PDA_INPUT, PROCESS_DT_SIZE-(sizeof(int)-1), 0}, -706);

	ASSERT_EQ(PROCESS_ERROR_BYTE_OUT_OF_RANGE, procErr);
}

/**
 * Check error on write int (bit address wrong)
 */
TEST_F(pdaClearTest, TestErrorWriteInt2) {

	procErr = PROCESS_WRITE_INT(&procDT, processDataAddress{PDA_INPUT, 6, 8}, -706);

	ASSERT_EQ(PROCESS_ERROR_BIT_OUT_OF_RANGE, procErr);
}

/**
 * Check error on write int (area wrong)
 */
TEST_F(pdaClearTest, TestErrorWriteInt3) {

	procErr = PROCESS_WRITE_INT(&procDT, processDataAddress{8, 6, 4}, -706);

	ASSERT_EQ(PROCESS_ERROR_AREA_OUT_OF_RANGE, procErr);
}

/**
 * Check error on read int (byte address wrong)
 */
TEST_F(pdaClearTest, TestErrorReadInt1) {

	PROCESS_GET_INT(&procDT, processDataAddress{PDA_INPUT, PROCESS_DT_SIZE-(sizeof(int)-1), 0}, &procErr);

	ASSERT_EQ(PROCESS_ERROR_BYTE_OUT_OF_RANGE, procErr);
}

/**
 * Check error on read int (bit address wrong)
 */
TEST_F(pdaClearTest, TestErrorReadInt2) {

	PROCESS_GET_INT(&procDT, processDataAddress{PDA_INPUT, 6, 9}, &procErr);

	ASSERT_EQ(PROCESS_ERROR_BIT_OUT_OF_RANGE, procErr);
}

/**
 * Check error on read int (area wrong)
 */
TEST_F(pdaClearTest, TestErrorReadInt3) {

	PROCESS_GET_INT(&procDT, processDataAddress{8, 6, 3}, &procErr);

	ASSERT_EQ(PROCESS_ERROR_AREA_OUT_OF_RANGE, procErr);
}

#endif /* PDAINTTESTS_H_ */
