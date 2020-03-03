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

/**
 * Check single input double word
 */
TEST_F(pdaClearTest, TestInputDWord1) {

	// 1110 0010 1100 0110 0101 0001 1101 1100
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_DWORD(&procDT, processDataAddress{PDA_INPUT, 7, 0}, 3804647900));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		switch (i) {
			case 7: {
					ASSERT_EQ((DWORD)3804647900, PROCESS_GET_DWORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(20956, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(220, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 8: {
					ASSERT_EQ(50769, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(81, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 9: {
					ASSERT_EQ(58054, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(198, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 10: {
					ASSERT_EQ(226, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(226, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
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
 * Check if input double words not overlapping itself
 */
TEST_F(pdaClearTest, TestInputDWord2) {

	// 1110 0010 1100 0110 0101 0001 1101 1100
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_DWORD(&procDT, processDataAddress{PDA_INPUT, 1, 0}, 3804647900));
	// 0001 0000 1000 0001 1011 0011 0111 1100
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_DWORD(&procDT, processDataAddress{PDA_INPUT, 5, 0}, 276935548));
	// 0100 0000 0000 0101 1110 0011 1011 0101
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_DWORD(&procDT, processDataAddress{PDA_INPUT, 9, 0}, 1074127797));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 1: { // First DWord
					ASSERT_EQ((DWORD)3804647900, PROCESS_GET_DWORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(20956, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(220, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 2: {
					ASSERT_EQ(50769, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(81, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 3: {
					ASSERT_EQ(58054, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(198, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 4: {
					ASSERT_EQ(31970, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(226, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 5: { // Second DWord
					ASSERT_EQ((DWORD)276935548, PROCESS_GET_DWORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(45948, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(124, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 6: {
					ASSERT_EQ(33203, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(179, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 7: {
					ASSERT_EQ(4225, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(129, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 8: {
					ASSERT_EQ(46352, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(16, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 9: { // Third DWord
					ASSERT_EQ((DWORD)1074127797, PROCESS_GET_DWORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(58293, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(181, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 10: {
					ASSERT_EQ(1507, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(227, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 11: {
					ASSERT_EQ(16389, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(5, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 12: {
					ASSERT_EQ(64, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(64, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
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
 * Check single output double word
 */
TEST_F(pdaClearTest, TestOutputDWord1) {

	// 1110 0010 1100 0110 0101 0001 1101 1100
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_DWORD(&procDT, processDataAddress{PDA_OUTPUT, 7, 0}, 3804647900));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		switch (i) {
			case 7: {
					ASSERT_EQ((DWORD)3804647900, PROCESS_GET_DWORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(20956, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(220, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 8: {
					ASSERT_EQ(50769, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(81, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 9: {
					ASSERT_EQ(58054, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(198, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 10: {
					ASSERT_EQ(226, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(226, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
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
 * Check if output double words not overlapping itself
 */
TEST_F(pdaClearTest, TestOutputDWord2) {

	// 1110 0010 1100 0110 0101 0001 1101 1100
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_DWORD(&procDT, processDataAddress{PDA_OUTPUT, 1, 0}, 3804647900));
	// 0001 0000 1000 0001 1011 0011 0111 1100
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_DWORD(&procDT, processDataAddress{PDA_OUTPUT, 5, 0}, 276935548));
	// 0100 0000 0000 0101 1110 0011 1011 0101
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_DWORD(&procDT, processDataAddress{PDA_OUTPUT, 9, 0}, 1074127797));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 1: { // First DWord
					ASSERT_EQ((DWORD)3804647900, PROCESS_GET_DWORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(20956, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(220, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 2: {
					ASSERT_EQ(50769, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(81, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 3: {
					ASSERT_EQ(58054, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(198, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 4: {
					ASSERT_EQ(31970, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(226, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 5: { // Second DWord
					ASSERT_EQ((DWORD)276935548, PROCESS_GET_DWORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(45948, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(124, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 6: {
					ASSERT_EQ(33203, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(179, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 7: {
					ASSERT_EQ(4225, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(129, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 8: {
					ASSERT_EQ(46352, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(16, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 9: { // Third DWord
					ASSERT_EQ((DWORD)1074127797, PROCESS_GET_DWORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(58293, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(181, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 10: {
					ASSERT_EQ(1507, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(227, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 11: {
					ASSERT_EQ(16389, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(5, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 12: {
					ASSERT_EQ(64, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(64, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
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
 * Check single memory double word
 */
TEST_F(pdaClearTest, TestMemoryDWord1) {

	// 1110 0010 1100 0110 0101 0001 1101 1100
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_DWORD(&procDT, processDataAddress{PDA_MEMORY, 7, 0}, 3804647900));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		switch (i) {
			case 7: {
					ASSERT_EQ((DWORD)3804647900, PROCESS_GET_DWORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(20956, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(220, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 8: {
					ASSERT_EQ(50769, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(81, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 9: {
					ASSERT_EQ(58054, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(198, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 10: {
					ASSERT_EQ(226, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(226, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
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
 * Check if memory double words not overlapping itself
 */
TEST_F(pdaClearTest, TestMemoryDWord2) {

	// 1110 0010 1100 0110 0101 0001 1101 1100
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_DWORD(&procDT, processDataAddress{PDA_MEMORY, 1, 0}, 3804647900));
	// 0001 0000 1000 0001 1011 0011 0111 1100
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_DWORD(&procDT, processDataAddress{PDA_MEMORY, 5, 0}, 276935548));
	// 0100 0000 0000 0101 1110 0011 1011 0101
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_DWORD(&procDT, processDataAddress{PDA_MEMORY, 9, 0}, 1074127797));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		switch (i) {
			case 1: { // First DWord
					ASSERT_EQ((DWORD)3804647900, PROCESS_GET_DWORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(20956, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(220, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 2: {
					ASSERT_EQ(50769, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(81, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 3: {
					ASSERT_EQ(58054, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(198, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 4: {
					ASSERT_EQ(31970, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(226, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 5: { // Second DWord
					ASSERT_EQ((DWORD)276935548, PROCESS_GET_DWORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(45948, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(124, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 6: {
					ASSERT_EQ(33203, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(179, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 7: {
					ASSERT_EQ(4225, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(129, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 8: {
					ASSERT_EQ(46352, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(16, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 9: { // Third DWord
					ASSERT_EQ((DWORD)1074127797, PROCESS_GET_DWORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(58293, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(181, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 10: {
					ASSERT_EQ(1507, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(227, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 11: {
					ASSERT_EQ(16389, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(5, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 12: {
					ASSERT_EQ(64, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(64, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
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
 * Check writing multiple double words in multiple areas
 */
TEST_F(pdaClearTest, TestDWord1) {

	// 1110 0010 1100 0110 0101 0001 1101 1100
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_DWORD(&procDT, processDataAddress{PDA_MEMORY, 1, 0}, 3804647900));
	// 0001 0000 1000 0001 1011 0011 0111 1100
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_DWORD(&procDT, processDataAddress{PDA_OUTPUT, 5, 0}, 276935548));
	// 0100 0000 0000 0101 1110 0011 1011 0101
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_DWORD(&procDT, processDataAddress{PDA_INPUT, 9, 0}, 1074127797));

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		// Memory
		switch (i) {
		case 1: { // First DWord
					ASSERT_EQ((DWORD)3804647900, PROCESS_GET_DWORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(20956, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(220, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 2: {
					ASSERT_EQ(50769, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(81, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 3: {
					ASSERT_EQ(58054, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(198, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 4: {
					ASSERT_EQ(226, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(226, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			default: {
					ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
		}
		// Output
		switch (i) {
		case 5: { // Second DWord
					ASSERT_EQ((DWORD)276935548, PROCESS_GET_DWORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(45948, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(124, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 6: {
					ASSERT_EQ(33203, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(179, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 7: {
					ASSERT_EQ(4225, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(129, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 8: {
					ASSERT_EQ(16, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(16, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			default: {
					ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
		}
		// Input
		switch (i) {
			case 9: { // Third DWord
					ASSERT_EQ((DWORD)1074127797, PROCESS_GET_DWORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(58293, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(181, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 10: {
					ASSERT_EQ(1507, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(227, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 11: {
					ASSERT_EQ(16389, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(5, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			case 12: {
					ASSERT_EQ(64, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
					ASSERT_EQ(64, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
			default: {
					ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
					ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
				}; break;
		}

	}
}

/**
 * Check error on write double word (byte address wrong)
 */
TEST_F(pdaClearTest, TestErrorWriteDWord1) {

	procErr = PROCESS_WRITE_DWORD(&procDT, processDataAddress{PDA_INPUT, PROCESS_DT_SIZE-3, 0}, 3804647900);

	ASSERT_EQ(PROCESS_ERROR_BYTE_OUT_OF_RANGE, procErr);
}

/**
 * Check error on write double word (bit address wrong)
 */
TEST_F(pdaClearTest, TestErrorWriteDWord2) {

	procErr = PROCESS_WRITE_DWORD(&procDT, processDataAddress{PDA_INPUT, 43, 9}, 3804647900);

	ASSERT_EQ(PROCESS_ERROR_BIT_OUT_OF_RANGE, procErr);
}

/**
 * Check error on write double word (area wrong)
 */
TEST_F(pdaClearTest, TestErrorWriteDWord3) {

	procErr = PROCESS_WRITE_DWORD(&procDT, processDataAddress{8, 43, 4}, 3804647900);

	ASSERT_EQ(PROCESS_ERROR_AREA_OUT_OF_RANGE, procErr);
}

/**
 * Check error on read double word (byte address wrong)
 */
TEST_F(pdaClearTest, TestErrorReadDWord1) {

	PROCESS_GET_DWORD(&procDT, processDataAddress{PDA_OUTPUT, PROCESS_DT_SIZE-3, 0}, &procErr);

	ASSERT_EQ(PROCESS_ERROR_BYTE_OUT_OF_RANGE, procErr);
}

/**
 * Check error on read double word (bit address wrong)
 */
TEST_F(pdaClearTest, TestErrorReadDWord2) {

	PROCESS_GET_DWORD(&procDT, processDataAddress{PDA_OUTPUT, 5, 9}, &procErr);

	ASSERT_EQ(PROCESS_ERROR_BIT_OUT_OF_RANGE, procErr);
}

/**
 * Check error on read double word (area wrong)
 */
TEST_F(pdaClearTest, TestErrorReadDWord3) {

	PROCESS_GET_DWORD(&procDT, processDataAddress{7, 5, 3}, &procErr);

	ASSERT_EQ(PROCESS_ERROR_AREA_OUT_OF_RANGE, procErr);
}

#endif /* PDADWORDTESTS_H_ */
