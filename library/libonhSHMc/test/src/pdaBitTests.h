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

#ifndef PDABITTESTS_H_
#define PDABITTESTS_H_

#include <gtest/gtest.h>
#include "pdaTestGlobalData.h"
#include "fixtures/pdaClearTest.h"

/**
 * Check single input bit
 */
TEST_F(pdaClearTest, TestInputBit1) {

	// 00000100
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_SET_BIT(&procDT, processDataAddress{PDA_INPUT, 1, 2}));

	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_INPUT, 1, 2}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	ASSERT_EQ(0, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_INPUT, 1, 0}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 1) {
			ASSERT_EQ(4, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
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
 * Check if input bits does not change other bits
 */
TEST_F(pdaClearTest, TestInputBit2) {

	// 00001000
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_SET_BIT(&procDT, processDataAddress{PDA_INPUT, 5, 3}));
	// 10001000
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_SET_BIT(&procDT, processDataAddress{PDA_INPUT, 5, 7}));
	// 11001000
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_SET_BIT(&procDT, processDataAddress{PDA_INPUT, 5, 6}));

	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_INPUT, 5, 3}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_INPUT, 5, 7}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_INPUT, 5, 6}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	ASSERT_EQ(0, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_INPUT, 5, 1}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 5) {
			ASSERT_EQ(200, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
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
 * Check single output bit
 */
TEST_F(pdaClearTest, TestOutputBit1) {

	// 00100000
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_SET_BIT(&procDT, processDataAddress{PDA_OUTPUT, 100, 5}));

	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_OUTPUT, 100, 5}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	ASSERT_EQ(0, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_OUTPUT, 100, 7}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 100) {
			ASSERT_EQ(32, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
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
 * Check if output bits does not change other bits
 */
TEST_F(pdaClearTest, TestOutputBit2) {

	// 00100000
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_SET_BIT(&procDT, processDataAddress{PDA_OUTPUT, 508, 5}));
	// 10100000
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_SET_BIT(&procDT, processDataAddress{PDA_OUTPUT, 508, 7}));
	// 11100000
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_SET_BIT(&procDT, processDataAddress{PDA_OUTPUT, 508, 6}));

	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_OUTPUT, 508, 5}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_OUTPUT, 508, 7}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_OUTPUT, 508, 6}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	ASSERT_EQ(0, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_OUTPUT, 508, 3}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 508) {
			ASSERT_EQ(224, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
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
 * Check single memory bit
 */
TEST_F(pdaClearTest, TestMemoryBit1) {

	// 00000001
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_SET_BIT(&procDT, processDataAddress{PDA_MEMORY, 1500, 0}));

	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_MEMORY, 1500, 0}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	ASSERT_EQ(0, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_MEMORY, 1500, 1}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 1500) {
			ASSERT_EQ(1, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
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
 * Check if memory bits does not change other bits
 */
TEST_F(pdaClearTest, TestMemoryBit2) {

	// 00100000
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_SET_BIT(&procDT, processDataAddress{PDA_MEMORY, 3784, 5}));
	// 10100000
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_SET_BIT(&procDT, processDataAddress{PDA_MEMORY, 3784, 7}));
	// 11100000
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_SET_BIT(&procDT, processDataAddress{PDA_MEMORY, 3784, 6}));

	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_MEMORY, 3784, 5}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_MEMORY, 3784, 7}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_MEMORY, 3784, 6}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	ASSERT_EQ(0, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_MEMORY, 3784, 3}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 3784) {
			ASSERT_EQ(224, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
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
 * Check writing multiple bits in multiple areas
 */
TEST_F(pdaClearTest, TestBit1) {

	// 00100000
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_SET_BIT(&procDT, processDataAddress{PDA_INPUT, 1150, 5}));
	// 00000010
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_SET_BIT(&procDT, processDataAddress{PDA_MEMORY, 4850, 1}));
	// 10000000
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_SET_BIT(&procDT, processDataAddress{PDA_OUTPUT, 4850, 7}));
	// 00001000
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_SET_BIT(&procDT, processDataAddress{PDA_OUTPUT, 377, 3}));

	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_INPUT, 1150, 5}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_MEMORY, 4850, 1}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_OUTPUT, 4850, 7}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_OUTPUT, 377, 3}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		if (i==377) {
			ASSERT_EQ(8, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		} else if (i==4850){
			ASSERT_EQ(128, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		} else {
			ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		}

		if (i==1150) {
			ASSERT_EQ(32, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		} else {
			ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		}

		if (i==4850) {
			ASSERT_EQ(2, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		} else {
			ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		}
	}
}

/**
 * Check error on set bit (byte address wrong)
 */
TEST_F(pdaClearTest, TestErrorSetBit1) {

	procErr = PROCESS_SET_BIT(&procDT, processDataAddress{PDA_INPUT, PROCESS_DT_SIZE+10, 0});

	ASSERT_EQ(PROCESS_ERROR_BYTE_OUT_OF_RANGE, procErr);
}

/**
 * Check error on set bit (bit address wrong)
 */
TEST_F(pdaClearTest, TestErrorSetBit2) {

	procErr = PROCESS_SET_BIT(&procDT, processDataAddress{PDA_INPUT, 9000, 70});

	ASSERT_EQ(PROCESS_ERROR_BIT_OUT_OF_RANGE, procErr);
}

/**
 * Check error on set bit (area wrong)
 */
TEST_F(pdaClearTest, TestErrorSetBit3) {

	procErr = PROCESS_SET_BIT(&procDT, processDataAddress{5, 150, 2});

	ASSERT_EQ(PROCESS_ERROR_AREA_OUT_OF_RANGE, procErr);
}

/**
 * Check error on get bit (byte address wrong)
 */
TEST_F(pdaClearTest, TestErrorGetBit1) {

	PROCESS_GET_BIT(&procDT, processDataAddress{PDA_INPUT, PROCESS_DT_SIZE+10, 0}, &procErr);

	ASSERT_EQ(PROCESS_ERROR_BYTE_OUT_OF_RANGE, procErr);
}

/**
 * Check error on get bit (bit address wrong)
 */
TEST_F(pdaClearTest, TestErrorGetBit2) {

	PROCESS_GET_BIT(&procDT, processDataAddress{PDA_INPUT, 9000, 70}, &procErr);

	ASSERT_EQ(PROCESS_ERROR_BIT_OUT_OF_RANGE, procErr);
}

/**
 * Check error on get bit (area wrong)
 */
TEST_F(pdaClearTest, TestErrorGetBit3) {

	PROCESS_GET_BIT(&procDT, processDataAddress{5, 150, 2}, &procErr);

	ASSERT_EQ(PROCESS_ERROR_AREA_OUT_OF_RANGE, procErr);
}

/**
 * Check single reset input bit
 */
TEST_F(pdaClearTest, TestResetInputBit1) {

	// 10110010
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_INPUT, 7, 0}, 178));
	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_INPUT, 7, 4}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// 10100010
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_RESET_BIT(&procDT, processDataAddress{PDA_INPUT, 7, 4}));
	ASSERT_EQ(0, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_INPUT, 7, 4}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 7) {
			ASSERT_EQ(162, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
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
 * Check if reset input bits does not change other bits
 */
TEST_F(pdaClearTest, TestResetInputBit2) {

	// 10110010
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_INPUT, 7, 0}, 178));
	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_INPUT, 7, 4}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_INPUT, 7, 5}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// 10100010
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_RESET_BIT(&procDT, processDataAddress{PDA_INPUT, 7, 4}));
	// 10000010
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_RESET_BIT(&procDT, processDataAddress{PDA_INPUT, 7, 5}));
	ASSERT_EQ(0, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_INPUT, 7, 4}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	ASSERT_EQ(0, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_INPUT, 7, 5}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 7) {
			ASSERT_EQ(130, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
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
 * Check single reset output bit
 */
TEST_F(pdaClearTest, TestResetOutputBit1) {

	// 10110010
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_OUTPUT, 7, 0}, 178));
	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_OUTPUT, 7, 4}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// 10100010
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_RESET_BIT(&procDT, processDataAddress{PDA_OUTPUT, 7, 4}));
	ASSERT_EQ(0, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_OUTPUT, 7, 4}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 7) {
			ASSERT_EQ(162, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
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
 * Check if reset output bits does not change other bits
 */
TEST_F(pdaClearTest, TestResetOutputBit2) {

	// 10110010
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_OUTPUT, 7, 0}, 178));
	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_OUTPUT, 7, 4}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_OUTPUT, 7, 5}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// 10100010
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_RESET_BIT(&procDT, processDataAddress{PDA_OUTPUT, 7, 4}));
	// 10000010
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_RESET_BIT(&procDT, processDataAddress{PDA_OUTPUT, 7, 5}));
	ASSERT_EQ(0, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_OUTPUT, 7, 4}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	ASSERT_EQ(0, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_OUTPUT, 7, 5}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 7) {
			ASSERT_EQ(130, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
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
 * Check single reset memory bit
 */
TEST_F(pdaClearTest, TestResetMemoryBit1) {

	// 10110010
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_MEMORY, 7, 0}, 178));
	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_MEMORY, 7, 4}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// 10100010
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_RESET_BIT(&procDT, processDataAddress{PDA_MEMORY, 7, 4}));
	ASSERT_EQ(0, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_MEMORY, 7, 4}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 7) {
			ASSERT_EQ(162, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
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
 * Check if reset memory bits does not change other bits
 */
TEST_F(pdaClearTest, TestResetMemoryBit2) {

	// 10110010
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_MEMORY, 7, 0}, 178));
	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_MEMORY, 7, 4}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_MEMORY, 7, 5}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// 10100010
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_RESET_BIT(&procDT, processDataAddress{PDA_MEMORY, 7, 4}));
	// 10000010
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_RESET_BIT(&procDT, processDataAddress{PDA_MEMORY, 7, 5}));
	ASSERT_EQ(0, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_MEMORY, 7, 4}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	ASSERT_EQ(0, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_MEMORY, 7, 5}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 7) {
			ASSERT_EQ(130, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
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
 * Check reset multiple bits in multiple areas
 */
TEST_F(pdaClearTest, TestResetBit1) {

	// 10110010
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_MEMORY, 7, 0}, 178));
	// 00000100
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_INPUT, 230, 0}, 4));
	// 00000101
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_OUTPUT, 231, 0}, 5));

	// 10110000
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_RESET_BIT(&procDT, processDataAddress{PDA_MEMORY, 7, 1}));
	// 00000000
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_RESET_BIT(&procDT, processDataAddress{PDA_INPUT, 230, 2}));
	// 00000100
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_RESET_BIT(&procDT, processDataAddress{PDA_OUTPUT, 231, 0}));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		if (i==7) {
			ASSERT_EQ(176, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		} else {
			ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		}

		if (i==231) {
			ASSERT_EQ(4, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		} else {
			ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		}

		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	}
}

/**
 * Check error on reset bit (byte address wrong)
 */
TEST_F(pdaClearTest, TestErrorResetBit1) {

	procErr = PROCESS_RESET_BIT(&procDT, processDataAddress{PDA_INPUT, PROCESS_DT_SIZE+100, 0});

	ASSERT_EQ(PROCESS_ERROR_BYTE_OUT_OF_RANGE, procErr);
}

/**
 * Check error on reset bit (bit address wrong)
 */
TEST_F(pdaClearTest, TestErrorResetBit2) {

	procErr = PROCESS_RESET_BIT(&procDT, processDataAddress{PDA_INPUT, 9000, 70});

	ASSERT_EQ(PROCESS_ERROR_BIT_OUT_OF_RANGE, procErr);
}

/**
 * Check error on reset bit (area wrong)
 */
TEST_F(pdaClearTest, TestErrorResetBit3) {

	procErr = PROCESS_RESET_BIT(&procDT, processDataAddress{5, 150, 2});

	ASSERT_EQ(PROCESS_ERROR_AREA_OUT_OF_RANGE, procErr);
}

/**
 * Check invert input bit
 */
TEST_F(pdaClearTest, TestInvertInputBit1) {

	// 10110010
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_INPUT, 7, 0}, 178));
	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_INPUT, 7, 4}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// 10100010
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_INVERT_BIT(&procDT, processDataAddress{PDA_INPUT, 7, 4}));
	ASSERT_EQ(0, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_INPUT, 7, 4}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// 10110010
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_INVERT_BIT(&procDT, processDataAddress{PDA_INPUT, 7, 4}));
	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_INPUT, 7, 4}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 7) {
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
 * Check invert output bit
 */
TEST_F(pdaClearTest, TestInvertOutputBit1) {

	// 10110010
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_OUTPUT, 7, 0}, 178));
	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_OUTPUT, 7, 4}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// 10100010
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_INVERT_BIT(&procDT, processDataAddress{PDA_OUTPUT, 7, 4}));
	ASSERT_EQ(0, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_OUTPUT, 7, 4}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// 10110010
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_INVERT_BIT(&procDT, processDataAddress{PDA_OUTPUT, 7, 4}));
	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_OUTPUT, 7, 4}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 7) {
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
 * Check invert memory bit
 */
TEST_F(pdaClearTest, TestInvertMemoryBit1) {

	// 10110010
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_MEMORY, 7, 0}, 178));
	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_MEMORY, 7, 4}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// 10100010
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_INVERT_BIT(&procDT, processDataAddress{PDA_MEMORY, 7, 4}));
	ASSERT_EQ(0, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_MEMORY, 7, 4}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// 10110010
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_INVERT_BIT(&procDT, processDataAddress{PDA_MEMORY, 7, 4}));
	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_MEMORY, 7, 4}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 7) {
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
 * Check error on invert bit (byte address wrong)
 */
TEST_F(pdaClearTest, TestErrorInvertBit1) {

	procErr = PROCESS_INVERT_BIT(&procDT, processDataAddress{PDA_INPUT, PROCESS_DT_SIZE+100, 0});

	ASSERT_EQ(PROCESS_ERROR_BYTE_OUT_OF_RANGE, procErr);
}

/**
 * Check error on invert bit (bit address wrong)
 */
TEST_F(pdaClearTest, TestErrorInvertBit2) {

	procErr = PROCESS_INVERT_BIT(&procDT, processDataAddress{PDA_INPUT, 9000, 70});

	ASSERT_EQ(PROCESS_ERROR_BIT_OUT_OF_RANGE, procErr);
}

/**
 * Check error on invert bit (area wrong)
 */
TEST_F(pdaClearTest, TestErrorInvertBit3) {

	procErr = PROCESS_INVERT_BIT(&procDT, processDataAddress{5, 150, 2});

	ASSERT_EQ(PROCESS_ERROR_AREA_OUT_OF_RANGE, procErr);
}

/**
 * Check set input bits
 */
TEST_F(pdaClearTest, TestSetInputBits1) {

	// Prepare addresses to set
	processDataAddress addr[3] = {{PDA_INPUT, 1, 0},
									{PDA_INPUT, 1, 2},
									{PDA_INPUT, 1, 3}};

	// 00001101
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_SET_BITS(&procDT, addr, 3));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 1) {
			ASSERT_EQ(13, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		} else {
			ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		}

		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	}
}

/**
 * Check set output bits
 */
TEST_F(pdaClearTest, TestSetOutputBits1) {

	// Prepare addresses to set
	processDataAddress addr[3] = {{PDA_OUTPUT, 1, 0},
									{PDA_OUTPUT, 1, 2},
									{PDA_OUTPUT, 1, 3}};

	// 00001101
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_SET_BITS(&procDT, addr, 3));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 1) {
			ASSERT_EQ(13, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		} else {
			ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		}

		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	}
}

/**
 * Check set memory bits
 */
TEST_F(pdaClearTest, TestSetMemoryBits1) {

	// Prepare addresses to set
	processDataAddress addr[3] = {{PDA_MEMORY, 1, 0},
									{PDA_MEMORY, 1, 2},
									{PDA_MEMORY, 1, 3}};

	// 00001101
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_SET_BITS(&procDT, addr, 3));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 1) {
			ASSERT_EQ(13, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		} else {
			ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		}

		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	}
}

/**
 * Check set bits
 */
TEST_F(pdaClearTest, TestSetBits1) {

	// Prepare addresses to set
	processDataAddress addr[] = {{PDA_MEMORY, 1, 0},
									{PDA_MEMORY, 1, 2},
									{PDA_INPUT, 100, 5},
									{PDA_OUTPUT, 4800, 7}};

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_SET_BITS(&procDT, addr, 4));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 1) {
			ASSERT_EQ(5, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		} else {
			ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		}

		if (i == 100) {
			ASSERT_EQ(32, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		} else {
			ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		}

		if (i == 4800) {
			ASSERT_EQ(128, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		} else {
			ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		}
	}
}

/**
 * Check error on set bits (byte address wrong)
 */
TEST_F(pdaClearTest, TestErrorSetBits1) {

	// Prepare addresses to set
	processDataAddress addr[] = {{PDA_MEMORY, 1, 0},
									{PDA_MEMORY, PROCESS_DT_SIZE+10, 2},
									{PDA_INPUT, 100, 5},
									{PDA_OUTPUT, 4800, 7}};

	ASSERT_EQ(PROCESS_ERROR_BYTE_OUT_OF_RANGE, PROCESS_SET_BITS(&procDT, addr, 4));
}

/**
 * Check error on set bits (bit address wrong)
 */
TEST_F(pdaClearTest, TestErrorSetBits2) {

	// Prepare addresses to set
	processDataAddress addr[] = {{PDA_MEMORY, 1, 0},
									{PDA_MEMORY, 8, 2},
									{PDA_INPUT, 100, 93},
									{PDA_OUTPUT, 4800, 7}};

	ASSERT_EQ(PROCESS_ERROR_BIT_OUT_OF_RANGE, PROCESS_SET_BITS(&procDT, addr, 4));
}

/**
 * Check error on set bits (area wrong)
 */
TEST_F(pdaClearTest, TestErrorSetBits3) {

	// Prepare addresses to set
	processDataAddress addr[] = {{PDA_MEMORY, 1, 0},
										{5, 1, 2},
										{PDA_INPUT, 100, 5},
										{PDA_OUTPUT, 4800, 7}};

	ASSERT_EQ(PROCESS_ERROR_AREA_OUT_OF_RANGE, PROCESS_SET_BITS(&procDT, addr, 4));
}

/**
 * Check get bits
 */
TEST_F(pdaClearTest, TestGetBits1) {

	// Return values
	char ret[7];

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_INPUT, 1, 0}, 13));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_OUTPUT, 10, 0}, 197));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_MEMORY, 78, 0}, 25));

	// Prepare addresses to get
	processDataAddress addr[] = {{PDA_INPUT, 1, 0},
									{PDA_INPUT, 1, 2},
									{PDA_INPUT, 1, 3},
									{PDA_OUTPUT, 10, 6},
									{PDA_OUTPUT, 10, 7},
									{PDA_MEMORY, 78, 4},
									{PDA_MEMORY, 78, 5}};

	ASSERT_EQ(PROCESS_ERROR_NONE,PROCESS_GET_BITS(&procDT, addr, ret, 7));

	ASSERT_EQ(1, ret[0]);
	ASSERT_EQ(1, ret[1]);
	ASSERT_EQ(1, ret[2]);
	ASSERT_EQ(1, ret[3]);
	ASSERT_EQ(1, ret[5]);
	ASSERT_EQ(0, ret[6]);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 1) {
			ASSERT_EQ(13, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		} else {
			ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		}

		if (i == 10) {
			ASSERT_EQ(197, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		} else {
			ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		}

		if (i == 78) {
			ASSERT_EQ(25, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		} else {
			ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		}
	}
}

/**
 * Check error on get bits (byte address wrong)
 */
TEST_F(pdaClearTest, TestErrorGetBits1) {

	// Return values
	char ret[7];

	// Prepare addresses to get
	processDataAddress addr[] = {{PDA_INPUT, 1, 0},
									{PDA_INPUT, PROCESS_DT_SIZE+100, 2},
									{PDA_INPUT, 1, 3},
									{PDA_OUTPUT, 10, 6},
									{PDA_OUTPUT, 10, 7},
									{PDA_MEMORY, 78, 4},
									{PDA_MEMORY, 78, 5}};

	ASSERT_EQ(PROCESS_ERROR_BYTE_OUT_OF_RANGE,PROCESS_GET_BITS(&procDT, addr, ret, 7));
}

/**
 * Check error on get bits (bit address wrong)
 */
TEST_F(pdaClearTest, TestErrorGetBits2) {

	// Return values
	char ret[7];

	// Prepare addresses to get
	processDataAddress addr[] = {{PDA_INPUT, 1, 0},
									{PDA_INPUT, 1, 2},
									{PDA_INPUT, 1, 3},
									{PDA_OUTPUT, 10, 65},
									{PDA_OUTPUT, 10, 7},
									{PDA_MEMORY, 78, 4},
									{PDA_MEMORY, 78, 5}};

	ASSERT_EQ(PROCESS_ERROR_BIT_OUT_OF_RANGE,PROCESS_GET_BITS(&procDT, addr, ret, 7));
}

/**
 * Check error on get bits (area wrong)
 */
TEST_F(pdaClearTest, TestErrorGetBits3) {

	// Return values
	char ret[7];

	// Prepare addresses to get
	processDataAddress addr[] = {{PDA_INPUT, 1, 0},
									{PDA_INPUT, 1, 2},
									{PDA_INPUT, 1, 3},
									{PDA_OUTPUT, 10, 5},
									{PDA_OUTPUT, 10, 7},
									{5, 78, 4},
									{PDA_MEMORY, 78, 5}};

	ASSERT_EQ(PROCESS_ERROR_AREA_OUT_OF_RANGE,PROCESS_GET_BITS(&procDT, addr, ret, 7));
}

#endif /* PDABITTESTS_H_ */
