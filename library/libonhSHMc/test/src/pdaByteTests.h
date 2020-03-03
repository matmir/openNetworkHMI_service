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

/**
 * Check single input byte
 */
TEST_F(pdaClearTest, TestInputByte1) {

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_INPUT, 2, 0}, 45));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 2) {
			ASSERT_EQ(45, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
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
 * Check if input bytes not overlapping itself
 */
TEST_F(pdaClearTest, TestInputByte2) {

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_INPUT, 0, 0}, 7));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_INPUT, 1, 0}, 45));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_INPUT, 2, 0}, 252));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 0: {
				ASSERT_EQ(7, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
				ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
			} break;
			case 1: {
				ASSERT_EQ(45, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
				ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
			} break;
			case 2: {
				ASSERT_EQ(252, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
				ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
			} break;
			default: {
				ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
				ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
			} break;
		}

		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	}
}

/**
 * Check single output byte
 */
TEST_F(pdaClearTest, TestOutputByte1) {

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_OUTPUT, 203, 0}, 207));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 203) {
			ASSERT_EQ(207, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
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
 * Check if output bytes not overlapping itself
 */
TEST_F(pdaClearTest, TestOutputByte2) {

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_OUTPUT, 54, 0}, 44));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_OUTPUT, 55, 0}, 1));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_OUTPUT, 56, 0}, 109));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 54: {
				ASSERT_EQ(44, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
				ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
			} break;
			case 55: {
				ASSERT_EQ(1, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
				ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
			} break;
			case 56: {
				ASSERT_EQ(109, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
				ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
			} break;
			default: {
				ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
				ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
			} break;
		}

		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	}
}

/**
 * Check single memory byte
 */
TEST_F(pdaClearTest, TestMemoryByte1) {

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_MEMORY, 1785, 0}, 6));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 1785) {
			ASSERT_EQ(6, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
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
 * Check if memory bytes not overlapping itself
 */
TEST_F(pdaClearTest, TestMemoryByte2) {

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_MEMORY, 82, 0}, 97));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_MEMORY, 83, 0}, 2));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_MEMORY, 84, 0}, 53));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 82: {
				ASSERT_EQ(97, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
				ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
			} break;
			case 83: {
				ASSERT_EQ(2, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
				ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
			} break;
			case 84: {
				ASSERT_EQ(53, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
				ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
			} break;
			default: {
				ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
				ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
			} break;
		}

		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	}
}

/**
 * Check writing multiple bytes in multiple areas
 */
TEST_F(pdaClearTest, TestByte1) {

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_INPUT, 1150, 0}, 63));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_MEMORY, 4850, 0}, 8));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_OUTPUT, 4850, 0}, 70));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_OUTPUT, 377, 0}, 114));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		if (i==377) {
			ASSERT_EQ(114, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		} else if (i==4850){
			ASSERT_EQ(70, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		} else {
			ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		}

		if (i==1150) {
			ASSERT_EQ(63, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		} else {
			ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		}

		if (i==4850) {
			ASSERT_EQ(8, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		} else {
			ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
			ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		}
	}
}

/**
 * Check error on write byte (byte address wrong)
 */
TEST_F(pdaClearTest, TestErrorWriteByte1) {

	procErr = PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_INPUT, PROCESS_DT_SIZE+100, 0}, 63);

	ASSERT_EQ(PROCESS_ERROR_BYTE_OUT_OF_RANGE, procErr);
}

/**
 * Check error on write byte (bit address wrong)
 */
TEST_F(pdaClearTest, TestErrorWriteByte2) {

	procErr = PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_INPUT, 150, 9}, 63);

	ASSERT_EQ(PROCESS_ERROR_BIT_OUT_OF_RANGE, procErr);
}

/**
 * Check error on write byte (area wrong)
 */
TEST_F(pdaClearTest, TestErrorWriteByte3) {

	procErr = PROCESS_WRITE_BYTE(&procDT, processDataAddress{7, 150, 1}, 63);

	ASSERT_EQ(PROCESS_ERROR_AREA_OUT_OF_RANGE, procErr);
}

/**
 * Check error on read byte (byte address wrong)
 */
TEST_F(pdaClearTest, TestErrorReadByte1) {

	PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, PROCESS_DT_SIZE+100, 0}, &procErr);

	ASSERT_EQ(PROCESS_ERROR_BYTE_OUT_OF_RANGE, procErr);
}

/**
 * Check error on read byte (bit address wrong)
 */
TEST_F(pdaClearTest, TestErrorReadByte2) {

	PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, 150, 9}, &procErr);

	ASSERT_EQ(PROCESS_ERROR_BIT_OUT_OF_RANGE, procErr);
}

/**
 * Check error on read byte (area wrong)
 */
TEST_F(pdaClearTest, TestErrorReadByte3) {

	PROCESS_GET_BYTE(&procDT, processDataAddress{7, 150, 1}, &procErr);

	ASSERT_EQ(PROCESS_ERROR_AREA_OUT_OF_RANGE, procErr);
}

#endif /* PDABYTETESTS_H_ */
