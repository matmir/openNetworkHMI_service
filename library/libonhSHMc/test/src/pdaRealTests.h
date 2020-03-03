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

/**
 * Check single input real
 */
TEST_F(pdaClearTest, TestInputReal1) {

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_REAL(&procDT, processDataAddress{PDA_INPUT, 2, 0}, -49.709));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_EQ((float)-49.709, PROCESS_GET_REAL(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
			// Skip checking bytes in float
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
 * Check if input real not overlapping itself
 */
TEST_F(pdaClearTest, TestInputReal2) {

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_REAL(&procDT, processDataAddress{PDA_INPUT, 0, 0}, -7.003));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_REAL(&procDT, processDataAddress{PDA_INPUT, sizeof(float), 0}, 65489.14));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_REAL(&procDT, processDataAddress{PDA_INPUT, sizeof(float)*2, 0}, -37489.1006));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 0: {
					ASSERT_EQ((float)-7.003, PROCESS_GET_REAL(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					// Skip checking bytes in float
					i += 3;
				}; break;
			case sizeof(float): {
					ASSERT_EQ((float)65489.14, PROCESS_GET_REAL(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					// Skip checking bytes in float
					i += 3;
				}; break;
			case sizeof(float)*2: {
					ASSERT_EQ((float)-37489.1006, PROCESS_GET_REAL(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					// Skip checking bytes in float
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
 * Check single output real
 */
TEST_F(pdaClearTest, TestOutputReal1) {

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_REAL(&procDT, processDataAddress{PDA_OUTPUT, 2, 0}, -49.709));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_EQ((float)-49.709, PROCESS_GET_REAL(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
			// Skip checking bytes in float
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
 * Check if output real not overlapping itself
 */
TEST_F(pdaClearTest, TestOutputReal2) {

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_REAL(&procDT, processDataAddress{PDA_OUTPUT, 0, 0}, -7.003));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_REAL(&procDT, processDataAddress{PDA_OUTPUT, sizeof(float), 0}, 65489.14));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_REAL(&procDT, processDataAddress{PDA_OUTPUT, sizeof(float)*2, 0}, -37489.1006));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 0: {
					ASSERT_EQ((float)-7.003, PROCESS_GET_REAL(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					// Skip checking bytes in float
					i += 3;
				}; break;
			case sizeof(float): {
					ASSERT_EQ((float)65489.14, PROCESS_GET_REAL(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					// Skip checking bytes in float
					i += 3;
				}; break;
			case sizeof(float)*2: {
					ASSERT_EQ((float)-37489.1006, PROCESS_GET_REAL(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					// Skip checking bytes in float
					i += 3;
				}; break;
			default: {
					ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
		}
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	}
}

/**
 * Check single memory real
 */
TEST_F(pdaClearTest, TestMemoryReal1) {

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_REAL(&procDT, processDataAddress{PDA_MEMORY, 2, 0}, -49.709));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_EQ((float)-49.709, PROCESS_GET_REAL(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
			// Skip checking bytes in float
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
 * Check if memory real not overlapping itself
 */
TEST_F(pdaClearTest, TestMemoryReal2) {

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_REAL(&procDT, processDataAddress{PDA_MEMORY, 0, 0}, -7.003));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_REAL(&procDT, processDataAddress{PDA_MEMORY, sizeof(float), 0}, 65489.14));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_REAL(&procDT, processDataAddress{PDA_MEMORY, sizeof(float)*2, 0}, -37489.1006));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 0: {
					ASSERT_EQ((float)-7.003, PROCESS_GET_REAL(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					// Skip checking bytes in float
					i += 3;
				}; break;
			case sizeof(float): {
					ASSERT_EQ((float)65489.14, PROCESS_GET_REAL(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					// Skip checking bytes in float
					i += 3;
				}; break;
			case sizeof(float)*2: {
					ASSERT_EQ((float)-37489.1006, PROCESS_GET_REAL(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					// Skip checking bytes in float
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
 * Check writing multiple real in multiple areas
 */
TEST_F(pdaClearTest, TestReal1) {

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_REAL(&procDT, processDataAddress{PDA_INPUT, 1150, 0}, -706.2356));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_REAL(&procDT, processDataAddress{PDA_MEMORY, 4850, 0}, 495321.04));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_REAL(&procDT, processDataAddress{PDA_OUTPUT, 4850, 0}, -1.006));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_REAL(&procDT, processDataAddress{PDA_OUTPUT, 377, 0}, 0.007));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		// Input
		switch (i) {
			case 1150: {
					ASSERT_EQ((float)-706.2356, PROCESS_GET_REAL(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					// Skip checking bytes in float
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
					ASSERT_EQ((float)495321.04, PROCESS_GET_REAL(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					// Skip checking bytes in float
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
					ASSERT_EQ((float)0.007, PROCESS_GET_REAL(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					// Skip checking bytes in float
					i += 3;
				}; break;
			case 4850: {
					ASSERT_EQ((float)-1.006, PROCESS_GET_REAL(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					// Skip checking bytes in float
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
 * Check error on write real (byte address wrong)
 */
TEST_F(pdaClearTest, TestErrorWriteReal1) {

	procErr = PROCESS_WRITE_REAL(&procDT, processDataAddress{PDA_INPUT, PROCESS_DT_SIZE-(sizeof(float)-1), 0}, -706);

	ASSERT_EQ(PROCESS_ERROR_BYTE_OUT_OF_RANGE, procErr);
}

/**
 * Check error on write real (bit address wrong)
 */
TEST_F(pdaClearTest, TestErrorWriteReal2) {

	procErr = PROCESS_WRITE_REAL(&procDT, processDataAddress{PDA_INPUT, 150, 9}, -706);

	ASSERT_EQ(PROCESS_ERROR_BIT_OUT_OF_RANGE, procErr);
}

/**
 * Check error on write real (area wrong)
 */
TEST_F(pdaClearTest, TestErrorWriteReal3) {

	procErr = PROCESS_WRITE_REAL(&procDT, processDataAddress{7, 150, 2}, -706);

	ASSERT_EQ(PROCESS_ERROR_AREA_OUT_OF_RANGE, procErr);
}

/**
 * Check error on read real (byte address wrong)
 */
TEST_F(pdaClearTest, TestErrorReadReal1) {

	PROCESS_GET_REAL(&procDT, processDataAddress{PDA_INPUT, PROCESS_DT_SIZE-(sizeof(float)-1), 0}, &procErr);

	ASSERT_EQ(PROCESS_ERROR_BYTE_OUT_OF_RANGE, procErr);
}

/**
 * Check error on read real (bit address wrong)
 */
TEST_F(pdaClearTest, TestErrorReadReal2) {

	PROCESS_GET_REAL(&procDT, processDataAddress{PDA_INPUT, 3, 8}, &procErr);

	ASSERT_EQ(PROCESS_ERROR_BIT_OUT_OF_RANGE, procErr);
}

/**
 * Check error on read real (area wrong)
 */
TEST_F(pdaClearTest, TestErrorReadReal3) {

	PROCESS_GET_REAL(&procDT, processDataAddress{8, 3, 3}, &procErr);

	ASSERT_EQ(PROCESS_ERROR_AREA_OUT_OF_RANGE, procErr);
}

#endif /* PDAREALTESTS_H_ */
