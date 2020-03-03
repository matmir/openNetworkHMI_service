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

#ifndef LIBRARY_LIBONHSHMCPP_TEST_SRC_PDTAGWORDTESTS_H_
#define LIBRARY_LIBONHSHMCPP_TEST_SRC_PDTAGWORDTESTS_H_

#include <gtest/gtest.h>
#include "pdaTestGlobalData.h"
#include "fixtures/pdaClearTest.h"
#include <onhSHMcpp/PDTag.h>

using namespace onh;

/**
 * Check Tag WORD
 */
TEST_F(pdaClearTest, TestWordTagAssignment1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 2, 0};

	PDTag<WORD> Tag1(addr1, *pda);
	PDTag<WORD> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getWord(addr1));
	ASSERT_EQ(0, pda->getWord(addr2));

	Tag1 = 42789;

	ASSERT_EQ(42789, pda->getWord(addr1));
	ASSERT_EQ(0, pda->getWord(addr2));

	Tag2 = Tag1;

	ASSERT_EQ(42789, pda->getWord(addr1));
	ASSERT_EQ(42789, pda->getWord(addr2));

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestWordTagAssignment2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<WORD> Tag1(addr1, *pda);

	WORD b1;

	b1 = Tag1;
	ASSERT_EQ(0, pda->getWord(addr1));
	ASSERT_EQ(0, b1);

	Tag1 = 42789;

	b1 = Tag1;
	ASSERT_EQ(42789, pda->getWord(addr1));
	ASSERT_EQ(42789, b1);

	// Check all process data
	for (unsigned int i=2; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestWordTagSum1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 2, 0};
	processDataAddress addr3 = {PDA_MEMORY, 4, 0};

	PDTag<WORD> Tag1(addr1, *pda);
	PDTag<WORD> Tag2(addr2, *pda);
	PDTag<WORD> Tag3(addr3, *pda);

	ASSERT_EQ(0, pda->getWord(addr1));
	ASSERT_EQ(0, pda->getWord(addr2));
	ASSERT_EQ(0, pda->getWord(addr3));

	Tag1 = 1500;
	Tag2 = 2500;

	ASSERT_EQ(1500, pda->getWord(addr1));
	ASSERT_EQ(2500, pda->getWord(addr2));
	ASSERT_EQ(0, pda->getWord(addr3));

	Tag3 = Tag1 + Tag2;

	ASSERT_EQ(1500, pda->getWord(addr1));
	ASSERT_EQ(2500, pda->getWord(addr2));
	ASSERT_EQ(4000, pda->getWord(addr3));

	// Check all process data
	for (unsigned int i=6; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestWordTagSum2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 2, 0};

	PDTag<WORD> Tag1(addr1, *pda);
	PDTag<WORD> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getWord(addr1));
	ASSERT_EQ(0, pda->getWord(addr2));

	Tag1 = 1600;

	ASSERT_EQ(1600, pda->getWord(addr1));
	ASSERT_EQ(0, pda->getWord(addr2));

	Tag2 = Tag1 + (WORD)400;

	ASSERT_EQ(1600, pda->getWord(addr1));
	ASSERT_EQ(2000, pda->getWord(addr2));

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestWordTagSub1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 2, 0};
	processDataAddress addr3 = {PDA_MEMORY, 4, 0};

	// Tag bool
	PDTag<WORD> Tag1(addr1, *pda);
	PDTag<WORD> Tag2(addr2, *pda);
	PDTag<WORD> Tag3(addr3, *pda);

	ASSERT_EQ(0, pda->getWord(addr1));
	ASSERT_EQ(0, pda->getWord(addr2));
	ASSERT_EQ(0, pda->getWord(addr3));

	Tag1 = 40000;
	Tag2 = 50000;

	ASSERT_EQ(40000, pda->getWord(addr1));
	ASSERT_EQ(50000, pda->getWord(addr2));
	ASSERT_EQ(0, pda->getWord(addr3));

	Tag3 = Tag2 - Tag1;

	ASSERT_EQ(40000, pda->getWord(addr1));
	ASSERT_EQ(50000, pda->getWord(addr2));
	ASSERT_EQ(10000, pda->getWord(addr3));

	// Check all process data
	for (unsigned int i=6; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestWordTagSub2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 2, 0};

	PDTag<WORD> Tag1(addr1, *pda);
	PDTag<WORD> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getWord(addr1));
	ASSERT_EQ(0, pda->getWord(addr2));

	Tag1 = 1500;

	ASSERT_EQ(1500, pda->getWord(addr1));
	ASSERT_EQ(0, pda->getWord(addr2));

	Tag2 = Tag1 - (WORD)800;

	ASSERT_EQ(1500, pda->getWord(addr1));
	ASSERT_EQ(700, pda->getWord(addr2));

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestWordTagMul1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 2, 0};
	processDataAddress addr3 = {PDA_MEMORY, 4, 0};

	PDTag<WORD> Tag1(addr1, *pda);
	PDTag<WORD> Tag2(addr2, *pda);
	PDTag<WORD> Tag3(addr3, *pda);

	ASSERT_EQ(0, pda->getWord(addr1));
	ASSERT_EQ(0, pda->getWord(addr2));
	ASSERT_EQ(0, pda->getWord(addr3));

	Tag1 = 300;
	Tag2 = 40;

	ASSERT_EQ(300, pda->getWord(addr1));
	ASSERT_EQ(40, pda->getWord(addr2));
	ASSERT_EQ(0, pda->getWord(addr3));

	Tag3 = Tag2 * Tag1;

	ASSERT_EQ(300, pda->getWord(addr1));
	ASSERT_EQ(40, pda->getWord(addr2));
	ASSERT_EQ(12000, pda->getWord(addr3));

	// Check all process data
	for (unsigned int i=6; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestWordTagMul2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 2, 0};

	PDTag<WORD> Tag1(addr1, *pda);
	PDTag<WORD> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getWord(addr1));
	ASSERT_EQ(0, pda->getWord(addr2));

	Tag1 = 2000;

	ASSERT_EQ(2000, pda->getWord(addr1));
	ASSERT_EQ(0, pda->getWord(addr2));

	Tag2 = Tag1 * (WORD)3;

	ASSERT_EQ(2000, pda->getWord(addr1));
	ASSERT_EQ(6000, pda->getWord(addr2));

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestWordTagDiv1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 2, 0};
	processDataAddress addr3 = {PDA_MEMORY, 4, 0};

	// Tag bool
	PDTag<WORD> Tag1(addr1, *pda);
	PDTag<WORD> Tag2(addr2, *pda);
	PDTag<WORD> Tag3(addr3, *pda);

	ASSERT_EQ(0, pda->getWord(addr1));
	ASSERT_EQ(0, pda->getWord(addr2));
	ASSERT_EQ(0, pda->getWord(addr3));

	Tag1 = 4;
	Tag2 = 8000;

	ASSERT_EQ(4, pda->getWord(addr1));
	ASSERT_EQ(8000, pda->getWord(addr2));
	ASSERT_EQ(0, pda->getWord(addr3));

	Tag3 = Tag2 / Tag1;

	ASSERT_EQ(4, pda->getWord(addr1));
	ASSERT_EQ(8000, pda->getWord(addr2));
	ASSERT_EQ(2000, pda->getWord(addr3));

	// Check all process data
	for (unsigned int i=6; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestWordTagDiv2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 2, 0};

	PDTag<WORD> Tag1(addr1, *pda);
	PDTag<WORD> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getWord(addr1));
	ASSERT_EQ(0, pda->getWord(addr2));

	Tag1 = 1000;

	ASSERT_EQ(1000, pda->getWord(addr1));
	ASSERT_EQ(0, pda->getWord(addr2));

	Tag2 = Tag1 / (WORD)2;

	ASSERT_EQ(1000, pda->getWord(addr1));
	ASSERT_EQ(500, pda->getWord(addr2));

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestWordTagSumEq1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 2, 0};

	PDTag<WORD> Tag1(addr1, *pda);
	PDTag<WORD> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getWord(addr1));
	ASSERT_EQ(0, pda->getWord(addr2));

	Tag1 = 1200;
	Tag2 = 800;

	ASSERT_EQ(1200, pda->getWord(addr1));
	ASSERT_EQ(800, pda->getWord(addr2));

	Tag1 += Tag2;

	ASSERT_EQ(2000, pda->getWord(addr1));
	ASSERT_EQ(800, pda->getWord(addr2));

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestWordTagSumEq2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<WORD> Tag1(addr1, *pda);

	ASSERT_EQ(0, pda->getWord(addr1));

	Tag1 = 1200;

	ASSERT_EQ(1200, pda->getWord(addr1));

	Tag1 += (WORD)600;

	ASSERT_EQ(1800, pda->getWord(addr1));

	// Check all process data
	for (unsigned int i=2; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestWordTagSubEq1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 2, 0};

	PDTag<WORD> Tag1(addr1, *pda);
	PDTag<WORD> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getWord(addr1));
	ASSERT_EQ(0, pda->getWord(addr2));

	Tag1 = 30;
	Tag2 = 20;

	ASSERT_EQ(30, pda->getWord(addr1));
	ASSERT_EQ(20, pda->getWord(addr2));

	Tag1 -= Tag2;

	ASSERT_EQ(10, pda->getWord(addr1));
	ASSERT_EQ(20, pda->getWord(addr2));

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestWordTagSubEq2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<WORD> Tag1(addr1, *pda);

	ASSERT_EQ(0, pda->getWord(addr1));

	Tag1 = 3000;

	ASSERT_EQ(3000, pda->getWord(addr1));

	Tag1 -= (WORD)2000;

	ASSERT_EQ(1000, pda->getWord(addr1));

	// Check all process data
	for (unsigned int i=2; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestWordTagMulEq1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 2, 0};

	PDTag<WORD> Tag1(addr1, *pda);
	PDTag<WORD> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getWord(addr1));
	ASSERT_EQ(0, pda->getWord(addr2));

	Tag1 = 1000;
	Tag2 = 20;

	ASSERT_EQ(1000, pda->getWord(addr1));
	ASSERT_EQ(20, pda->getWord(addr2));

	Tag1 *= Tag2;

	ASSERT_EQ(20000, pda->getWord(addr1));
	ASSERT_EQ(20, pda->getWord(addr2));

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestWordTagMulEq2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<WORD> Tag1(addr1, *pda);

	ASSERT_EQ(0, pda->getWord(addr1));

	Tag1 = 1000;

	ASSERT_EQ(1000, pda->getWord(addr1));

	Tag1 *= (WORD)20;

	ASSERT_EQ(20000, pda->getWord(addr1));

	// Check all process data
	for (unsigned int i=2; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestWordTagDivEq1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 2, 0};

	PDTag<WORD> Tag1(addr1, *pda);
	PDTag<WORD> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getWord(addr1));
	ASSERT_EQ(0, pda->getWord(addr2));

	Tag1 = 1000;
	Tag2 = 2;

	ASSERT_EQ(1000, pda->getWord(addr1));
	ASSERT_EQ(2, pda->getWord(addr2));

	Tag1 /= Tag2;

	ASSERT_EQ(500, pda->getWord(addr1));
	ASSERT_EQ(2, pda->getWord(addr2));

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestWordTagDivEq2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<WORD> Tag1(addr1, *pda);

	ASSERT_EQ(0, pda->getWord(addr1));

	Tag1 = 1000;

	ASSERT_EQ(1000, pda->getWord(addr1));

	Tag1 /= (WORD)2;

	ASSERT_EQ(500, pda->getWord(addr1));

	// Check all process data
	for (unsigned int i=2; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestWordTagInc1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<WORD> Tag1(addr1, *pda);

	ASSERT_EQ(0, pda->getWord(addr1));

	Tag1 = 1500;

	++Tag1;

	ASSERT_EQ(1501, pda->getWord(addr1));

	// Check all process data
	for (unsigned int i=2; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestWordTagInc2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<WORD> Tag1(addr1, *pda);

	ASSERT_EQ(0, pda->getWord(addr1));

	Tag1 = 1500;

	WORD v = Tag1++;

	ASSERT_EQ(1501, pda->getWord(addr1));
	ASSERT_EQ(1500, v);

	// Check all process data
	for (unsigned int i=2; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

#endif /* LIBRARY_LIBONHSHMCPP_TEST_SRC_PDTAGWORDTESTS_H_ */
