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

/**
 * Check single input word
 */
TEST_F(pdaClearTest, TestInputWord1) {

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_WORD(&procDT, processDataAddress{PDA_INPUT, 2, 0}, 45801));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_EQ(45801, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
			ASSERT_EQ(233, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		} else if (i==3) {
			ASSERT_EQ(178, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		} else {
			ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		}

		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	}
}

/**
 * Check if input words not overlapping itself
 */
TEST_F(pdaClearTest, TestInputWord2) {

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_WORD(&procDT, processDataAddress{PDA_INPUT, 1, 0}, 45801));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_WORD(&procDT, processDataAddress{PDA_INPUT, 3, 0}, 58007));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_WORD(&procDT, processDataAddress{PDA_INPUT, 5, 0}, 14888));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 1: {
					ASSERT_EQ(45801, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(233, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 2: {
					ASSERT_EQ(178, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 3: {
					ASSERT_EQ(58007, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(151, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 4: {
					ASSERT_EQ(226, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 5: {
					ASSERT_EQ(14888, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(40, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 6: {
					ASSERT_EQ(58, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			default: {
					ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
		}

		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	}
}

/**
 * Check single output word
 */
TEST_F(pdaClearTest, TestOutputWord1) {

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_WORD(&procDT, processDataAddress{PDA_OUTPUT, 2, 0}, 45801));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_EQ(45801, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
			ASSERT_EQ(233, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		} else if (i==3) {
			ASSERT_EQ(178, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		} else {
			ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		}

		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	}
}

/**
 * Check if output words not overlapping itself
 */
TEST_F(pdaClearTest, TestOutputWord2) {

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_WORD(&procDT, processDataAddress{PDA_OUTPUT, 1, 0}, 45801));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_WORD(&procDT, processDataAddress{PDA_OUTPUT, 3, 0}, 58007));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_WORD(&procDT, processDataAddress{PDA_OUTPUT, 5, 0}, 14888));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 1: {
					ASSERT_EQ(45801, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(233, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 2: {
					ASSERT_EQ(178, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 3: {
					ASSERT_EQ(58007, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(151, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 4: {
					ASSERT_EQ(226, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 5: {
					ASSERT_EQ(14888, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(40, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 6: {
					ASSERT_EQ(58, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			default: {
				ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
				ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
			}; break;
		}

		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	}
}

/**
 * Check single memory word
 */
TEST_F(pdaClearTest, TestMemoryWord1) {

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_WORD(&procDT, processDataAddress{PDA_MEMORY, 2, 0}, 45801));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_EQ(45801, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
			ASSERT_EQ(233, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		} else if (i==3) {
			ASSERT_EQ(178, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		} else {
			ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		}

		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	}
}

/**
 * Check if memory words not overlapping itself
 */
TEST_F(pdaClearTest, TestMemoryWord2) {

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_WORD(&procDT, processDataAddress{PDA_MEMORY, 1, 0}, 45801));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_WORD(&procDT, processDataAddress{PDA_MEMORY, 3, 0}, 58007));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_WORD(&procDT, processDataAddress{PDA_MEMORY, 5, 0}, 14888));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 1: {
					ASSERT_EQ(45801, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(233, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 2: {
					ASSERT_EQ(178, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 3: {
					ASSERT_EQ(58007, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(151, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 4: {
					ASSERT_EQ(226, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 5: {
					ASSERT_EQ(14888, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(40, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 6: {
					ASSERT_EQ(58, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			default: {
				ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
				ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
			}; break;
		}

		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	}
}

/**
 * Check writing multiple words in multiple areas
 */
TEST_F(pdaClearTest, TestWord1) {

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_WORD(&procDT, processDataAddress{PDA_INPUT, 1150, 0}, 45801));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_WORD(&procDT, processDataAddress{PDA_MEMORY, 4850, 0}, 58007));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_WORD(&procDT, processDataAddress{PDA_OUTPUT, 4850, 0}, 14888));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_WORD(&procDT, processDataAddress{PDA_OUTPUT, 377, 0}, 14808));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		// Output
		switch (i) {
			case 377: {
					ASSERT_EQ(14808, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(216, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 378: {
					ASSERT_EQ(57, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 4850: {
					ASSERT_EQ(14888, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(40, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 4851: {
					ASSERT_EQ(58, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			default: {
					ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
		}
		// Input
		switch (i) {
			case 1150: {
					ASSERT_EQ(45801, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(233, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 1151: {
					ASSERT_EQ(178, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			default: {
					ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
		}
		// Memory
		switch (i) {
			case 4850: {
					ASSERT_EQ(58007, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(151, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 4851: {
					ASSERT_EQ(226, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			default: {
					ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
		}
	}
}

/**
 * Check error on write word (byte address wrong)
 */
TEST_F(pdaClearTest, TestErrorWriteWord1) {

	procErr = PROCESS_WRITE_WORD(&procDT, processDataAddress{PDA_INPUT, PROCESS_DT_SIZE-1, 0}, 63855);

	ASSERT_EQ(PROCESS_ERROR_BYTE_OUT_OF_RANGE, procErr);
}

/**
 * Check error on write word (bit address wrong)
 */
TEST_F(pdaClearTest, TestErrorWriteWord2) {

	procErr = PROCESS_WRITE_WORD(&procDT, processDataAddress{PDA_INPUT, 150, 9}, 63855);

	ASSERT_EQ(PROCESS_ERROR_BIT_OUT_OF_RANGE, procErr);
}

/**
 * Check error on write word (area wrong)
 */
TEST_F(pdaClearTest, TestErrorWriteWord3) {

	procErr = PROCESS_WRITE_WORD(&procDT, processDataAddress{6, 150, 2}, 63855);

	ASSERT_EQ(PROCESS_ERROR_AREA_OUT_OF_RANGE, procErr);
}

/**
 * Check error on read word (byte address wrong)
 */
TEST_F(pdaClearTest, TestErrorReadWord1) {

	PROCESS_GET_WORD(&procDT, processDataAddress{PDA_INPUT, PROCESS_DT_SIZE-1, 0}, &procErr);

	ASSERT_EQ(PROCESS_ERROR_BYTE_OUT_OF_RANGE, procErr);
}

/**
 * Check error on read word (bit address wrong)
 */
TEST_F(pdaClearTest, TestErrorReadWord2) {

	PROCESS_GET_WORD(&procDT, processDataAddress{PDA_INPUT, 150, 9}, &procErr);

	ASSERT_EQ(PROCESS_ERROR_BIT_OUT_OF_RANGE, procErr);
}

/**
 * Check error on read word (area wrong)
 */
TEST_F(pdaClearTest, TestErrorReadWord3) {

	PROCESS_GET_WORD(&procDT, processDataAddress{8, 150, 3}, &procErr);

	ASSERT_EQ(PROCESS_ERROR_AREA_OUT_OF_RANGE, procErr);
}

#endif /* PDAWORDTESTS_H_ */
