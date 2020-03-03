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

#ifndef LIBRARY_LIBONHSHMCPP_TEST_SRC_PDTAGDWORDTESTS_H_
#define LIBRARY_LIBONHSHMCPP_TEST_SRC_PDTAGDWORDTESTS_H_

#include <gtest/gtest.h>
#include "pdaTestGlobalData.h"
#include "fixtures/pdaClearTest.h"
#include <onhSHMcpp/PDTag.h>

using namespace onh;

/**
 * Check Tag DWORD
 */
TEST_F(pdaClearTest, TestDWordTagAssignment1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};

	PDTag<DWORD> Tag1(addr1, *pda);
	PDTag<DWORD> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getDWord(addr1));
	ASSERT_EQ(0, pda->getDWord(addr2));

	Tag1 = 150000;

	ASSERT_EQ(150000, pda->getDWord(addr1));
	ASSERT_EQ(0, pda->getDWord(addr2));

	Tag2 = Tag1;

	ASSERT_EQ(150000, pda->getDWord(addr1));
	ASSERT_EQ(150000, pda->getDWord(addr2));

	// Check all process data
	for (unsigned int i=8; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestDWordTagAssignment2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<DWORD> Tag1(addr1, *pda);

	DWORD b1;

	b1 = Tag1;
	ASSERT_EQ(0, pda->getDWord(addr1));
	ASSERT_EQ(0, b1);

	Tag1 = 150000;

	b1 = Tag1;
	ASSERT_EQ(150000, pda->getDWord(addr1));
	ASSERT_EQ(150000, b1);

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestDWordTagSum1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};
	processDataAddress addr3 = {PDA_MEMORY, 8, 0};

	PDTag<DWORD> Tag1(addr1, *pda);
	PDTag<DWORD> Tag2(addr2, *pda);
	PDTag<DWORD> Tag3(addr3, *pda);

	ASSERT_EQ(0, pda->getDWord(addr1));
	ASSERT_EQ(0, pda->getDWord(addr2));
	ASSERT_EQ(0, pda->getDWord(addr3));

	Tag1 = 15000;
	Tag2 = 25000;

	ASSERT_EQ(15000, pda->getDWord(addr1));
	ASSERT_EQ(25000, pda->getDWord(addr2));
	ASSERT_EQ(0, pda->getDWord(addr3));

	Tag3 = Tag1 + Tag2;

	ASSERT_EQ(15000, pda->getDWord(addr1));
	ASSERT_EQ(25000, pda->getDWord(addr2));
	ASSERT_EQ(40000, pda->getDWord(addr3));

	// Check all process data
	for (unsigned int i=12; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestDWordTagSum2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};

	PDTag<DWORD> Tag1(addr1, *pda);
	PDTag<DWORD> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getDWord(addr1));
	ASSERT_EQ(0, pda->getDWord(addr2));

	Tag1 = 160000;

	ASSERT_EQ(160000, pda->getDWord(addr1));
	ASSERT_EQ(0, pda->getDWord(addr2));

	Tag2 = Tag1 + (DWORD)400;

	ASSERT_EQ(160000, pda->getDWord(addr1));
	ASSERT_EQ(160400, pda->getDWord(addr2));

	// Check all process data
	for (unsigned int i=8; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestDWordTagSub1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};
	processDataAddress addr3 = {PDA_MEMORY, 8, 0};

	// Tag bool
	PDTag<DWORD> Tag1(addr1, *pda);
	PDTag<DWORD> Tag2(addr2, *pda);
	PDTag<DWORD> Tag3(addr3, *pda);

	ASSERT_EQ(0, pda->getDWord(addr1));
	ASSERT_EQ(0, pda->getDWord(addr2));
	ASSERT_EQ(0, pda->getDWord(addr3));

	Tag1 = 400000;
	Tag2 = 500000;

	ASSERT_EQ(400000, pda->getDWord(addr1));
	ASSERT_EQ(500000, pda->getDWord(addr2));
	ASSERT_EQ(0, pda->getDWord(addr3));

	Tag3 = Tag2 - Tag1;

	ASSERT_EQ(400000, pda->getDWord(addr1));
	ASSERT_EQ(500000, pda->getDWord(addr2));
	ASSERT_EQ(100000, pda->getDWord(addr3));

	// Check all process data
	for (unsigned int i=12; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestDWordTagSub2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};

	PDTag<DWORD> Tag1(addr1, *pda);
	PDTag<DWORD> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getDWord(addr1));
	ASSERT_EQ(0, pda->getDWord(addr2));

	Tag1 = 150000;

	ASSERT_EQ(150000, pda->getDWord(addr1));
	ASSERT_EQ(0, pda->getDWord(addr2));

	Tag2 = Tag1 - (DWORD)800;

	ASSERT_EQ(150000, pda->getDWord(addr1));
	ASSERT_EQ(149200, pda->getDWord(addr2));

	// Check all process data
	for (unsigned int i=8; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestDWordTagMul1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};
	processDataAddress addr3 = {PDA_MEMORY, 8, 0};

	PDTag<DWORD> Tag1(addr1, *pda);
	PDTag<DWORD> Tag2(addr2, *pda);
	PDTag<DWORD> Tag3(addr3, *pda);

	ASSERT_EQ(0, pda->getDWord(addr1));
	ASSERT_EQ(0, pda->getDWord(addr2));
	ASSERT_EQ(0, pda->getDWord(addr3));

	Tag1 = 100000;
	Tag2 = 40;

	ASSERT_EQ(100000, pda->getDWord(addr1));
	ASSERT_EQ(40, pda->getDWord(addr2));
	ASSERT_EQ(0, pda->getDWord(addr3));

	Tag3 = Tag2 * Tag1;

	ASSERT_EQ(100000, pda->getDWord(addr1));
	ASSERT_EQ(40, pda->getDWord(addr2));
	ASSERT_EQ(4000000, pda->getDWord(addr3));

	// Check all process data
	for (unsigned int i=12; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestDWordTagMul2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};

	PDTag<DWORD> Tag1(addr1, *pda);
	PDTag<DWORD> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getDWord(addr1));
	ASSERT_EQ(0, pda->getDWord(addr2));

	Tag1 = 100000;

	ASSERT_EQ(100000, pda->getDWord(addr1));
	ASSERT_EQ(0, pda->getDWord(addr2));

	Tag2 = Tag1 * (DWORD)3;

	ASSERT_EQ(100000, pda->getDWord(addr1));
	ASSERT_EQ(300000, pda->getDWord(addr2));

	// Check all process data
	for (unsigned int i=8; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestDWordTagDiv1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};
	processDataAddress addr3 = {PDA_MEMORY, 8, 0};

	PDTag<DWORD> Tag1(addr1, *pda);
	PDTag<DWORD> Tag2(addr2, *pda);
	PDTag<DWORD> Tag3(addr3, *pda);

	ASSERT_EQ(0, pda->getDWord(addr1));
	ASSERT_EQ(0, pda->getDWord(addr2));
	ASSERT_EQ(0, pda->getDWord(addr3));

	Tag1 = 4;
	Tag2 = 400000;

	ASSERT_EQ(4, pda->getDWord(addr1));
	ASSERT_EQ(400000, pda->getDWord(addr2));
	ASSERT_EQ(0, pda->getDWord(addr3));

	Tag3 = Tag2 / Tag1;

	ASSERT_EQ(4, pda->getDWord(addr1));
	ASSERT_EQ(400000, pda->getDWord(addr2));
	ASSERT_EQ(100000, pda->getDWord(addr3));

	// Check all process data
	for (unsigned int i=12; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestDWordTagDiv2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};

	PDTag<DWORD> Tag1(addr1, *pda);
	PDTag<DWORD> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getDWord(addr1));
	ASSERT_EQ(0, pda->getDWord(addr2));

	Tag1 = 100000;

	ASSERT_EQ(100000, pda->getDWord(addr1));
	ASSERT_EQ(0, pda->getDWord(addr2));

	Tag2 = Tag1 / (DWORD)2;

	ASSERT_EQ(100000, pda->getDWord(addr1));
	ASSERT_EQ(50000, pda->getDWord(addr2));

	// Check all process data
	for (unsigned int i=8; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestDWordTagSumEq1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};

	PDTag<DWORD> Tag1(addr1, *pda);
	PDTag<DWORD> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getDWord(addr1));
	ASSERT_EQ(0, pda->getDWord(addr2));

	Tag1 = 100000;
	Tag2 = 800;

	ASSERT_EQ(100000, pda->getDWord(addr1));
	ASSERT_EQ(800, pda->getDWord(addr2));

	Tag1 += Tag2;

	ASSERT_EQ(100800, pda->getDWord(addr1));
	ASSERT_EQ(800, pda->getDWord(addr2));

	// Check all process data
	for (unsigned int i=8; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestDWordTagSumEq2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<DWORD> Tag1(addr1, *pda);

	ASSERT_EQ(0, pda->getDWord(addr1));

	Tag1 = 120000;

	ASSERT_EQ(120000, pda->getDWord(addr1));

	Tag1 += (DWORD)600;

	ASSERT_EQ(120600, pda->getDWord(addr1));

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestDWordTagSubEq1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};

	PDTag<DWORD> Tag1(addr1, *pda);
	PDTag<DWORD> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getDWord(addr1));
	ASSERT_EQ(0, pda->getDWord(addr2));

	Tag1 = 300000;
	Tag2 = 200000;

	ASSERT_EQ(300000, pda->getDWord(addr1));
	ASSERT_EQ(200000, pda->getDWord(addr2));

	Tag1 -= Tag2;

	ASSERT_EQ(100000, pda->getDWord(addr1));
	ASSERT_EQ(200000, pda->getDWord(addr2));

	// Check all process data
	for (unsigned int i=8; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestDWordTagSubEq2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<DWORD> Tag1(addr1, *pda);

	ASSERT_EQ(0, pda->getDWord(addr1));

	Tag1 = 300000;

	ASSERT_EQ(300000, pda->getDWord(addr1));

	Tag1 -= (DWORD)200000;

	ASSERT_EQ(100000, pda->getDWord(addr1));

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestDWordTagMulEq1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};

	PDTag<DWORD> Tag1(addr1, *pda);
	PDTag<DWORD> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getDWord(addr1));
	ASSERT_EQ(0, pda->getDWord(addr2));

	Tag1 = 100000;
	Tag2 = 20;

	ASSERT_EQ(100000, pda->getDWord(addr1));
	ASSERT_EQ(20, pda->getDWord(addr2));

	Tag1 *= Tag2;

	ASSERT_EQ(2000000, pda->getDWord(addr1));
	ASSERT_EQ(20, pda->getDWord(addr2));

	// Check all process data
	for (unsigned int i=8; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestDWordTagMulEq2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<DWORD> Tag1(addr1, *pda);

	ASSERT_EQ(0, pda->getDWord(addr1));

	Tag1 = 100000;

	ASSERT_EQ(100000, pda->getDWord(addr1));

	Tag1 *= (DWORD)20;

	ASSERT_EQ(2000000, pda->getDWord(addr1));

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestDWordTagDivEq1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};

	PDTag<DWORD> Tag1(addr1, *pda);
	PDTag<DWORD> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getDWord(addr1));
	ASSERT_EQ(0, pda->getDWord(addr2));

	Tag1 = 200000;
	Tag2 = 2;

	ASSERT_EQ(200000, pda->getDWord(addr1));
	ASSERT_EQ(2, pda->getDWord(addr2));

	Tag1 /= Tag2;

	ASSERT_EQ(100000, pda->getDWord(addr1));
	ASSERT_EQ(2, pda->getDWord(addr2));

	// Check all process data
	for (unsigned int i=8; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestDWordTagDivEq2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<DWORD> Tag1(addr1, *pda);

	ASSERT_EQ(0, pda->getDWord(addr1));

	Tag1 = 200000;

	ASSERT_EQ(200000, pda->getDWord(addr1));

	Tag1 /= (DWORD)2;

	ASSERT_EQ(100000, pda->getDWord(addr1));

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestDWordTagInc1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<DWORD> Tag1(addr1, *pda);

	ASSERT_EQ(0, pda->getDWord(addr1));

	Tag1 = 150000;

	++Tag1;

	ASSERT_EQ(150001, pda->getDWord(addr1));

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestDWordTagInc2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<DWORD> Tag1(addr1, *pda);

	ASSERT_EQ(0, pda->getDWord(addr1));

	Tag1 = 150000;

	DWORD v = Tag1++;

	ASSERT_EQ(150001, pda->getDWord(addr1));
	ASSERT_EQ(150000, v);

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

#endif /* LIBRARY_LIBONHSHMCPP_TEST_SRC_PDTAGDWORDTESTS_H_ */
