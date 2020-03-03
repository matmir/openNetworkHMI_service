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

#ifndef LIBRARY_LIBONHSHMCPP_TEST_SRC_PDTAGINTTESTS_H_
#define LIBRARY_LIBONHSHMCPP_TEST_SRC_PDTAGINTTESTS_H_

#include <gtest/gtest.h>
#include "pdaTestGlobalData.h"
#include "fixtures/pdaClearTest.h"
#include <onhSHMcpp/PDTag.h>

using namespace onh;

/**
 * Check Tag INT
 */
TEST_F(pdaClearTest, TestIntTagAssignment1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};

	PDTag<int> Tag1(addr1, *pda);
	PDTag<int> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getInt(addr1));
	ASSERT_EQ(0, pda->getInt(addr2));

	Tag1 = -48;

	ASSERT_EQ(-48, pda->getInt(addr1));
	ASSERT_EQ(0, pda->getInt(addr2));

	Tag2 = Tag1;

	ASSERT_EQ(-48, pda->getInt(addr1));
	ASSERT_EQ(-48, pda->getInt(addr2));

	// Check all process data
	for (unsigned int i=8; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestIntTagAssignment2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<int> Tag1(addr1, *pda);

	int b1;

	b1 = Tag1;
	ASSERT_EQ(0, pda->getInt(addr1));
	ASSERT_EQ(0, b1);

	Tag1 = -48;

	b1 = Tag1;
	ASSERT_EQ(-48, pda->getInt(addr1));
	ASSERT_EQ(-48, b1);

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestIntTagSum1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};
	processDataAddress addr3 = {PDA_MEMORY, 8, 0};

	PDTag<int> Tag1(addr1, *pda);
	PDTag<int> Tag2(addr2, *pda);
	PDTag<int> Tag3(addr3, *pda);

	ASSERT_EQ(0, pda->getInt(addr1));
	ASSERT_EQ(0, pda->getInt(addr2));
	ASSERT_EQ(0, pda->getInt(addr3));

	Tag1 = -48;
	Tag2 = 50;

	ASSERT_EQ(-48, pda->getInt(addr1));
	ASSERT_EQ(50, pda->getInt(addr2));
	ASSERT_EQ(0, pda->getInt(addr3));

	Tag3 = Tag1 + Tag2;

	ASSERT_EQ(-48, pda->getInt(addr1));
	ASSERT_EQ(50, pda->getInt(addr2));
	ASSERT_EQ(2, pda->getInt(addr3));

	// Check all process data
	for (unsigned int i=12; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestIntTagSum2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};

	PDTag<int> Tag1(addr1, *pda);
	PDTag<int> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getInt(addr1));
	ASSERT_EQ(0, pda->getInt(addr2));

	Tag1 = -45;

	ASSERT_EQ(-45, pda->getInt(addr1));
	ASSERT_EQ(0, pda->getInt(addr2));

	Tag2 = Tag1 + (int)5;

	ASSERT_EQ(-45, pda->getInt(addr1));
	ASSERT_EQ(-40, pda->getInt(addr2));

	// Check all process data
	for (unsigned int i=8; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestIntTagSub1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};
	processDataAddress addr3 = {PDA_MEMORY, 8, 0};

	// Tag bool
	PDTag<int> Tag1(addr1, *pda);
	PDTag<int> Tag2(addr2, *pda);
	PDTag<int> Tag3(addr3, *pda);

	ASSERT_EQ(0, pda->getInt(addr1));
	ASSERT_EQ(0, pda->getInt(addr2));
	ASSERT_EQ(0, pda->getInt(addr3));

	Tag1 = -10;
	Tag2 = 5;

	ASSERT_EQ(-10, pda->getInt(addr1));
	ASSERT_EQ(5, pda->getInt(addr2));
	ASSERT_EQ(0, pda->getInt(addr3));

	Tag3 = Tag2 - Tag1;

	ASSERT_EQ(-10, pda->getInt(addr1));
	ASSERT_EQ(5, pda->getInt(addr2));
	ASSERT_EQ(15, pda->getInt(addr3));

	// Check all process data
	for (unsigned int i=12; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestIntTagSub2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};

	PDTag<int> Tag1(addr1, *pda);
	PDTag<int> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getInt(addr1));
	ASSERT_EQ(0, pda->getInt(addr2));

	Tag1 = -90;

	ASSERT_EQ(-90, pda->getInt(addr1));
	ASSERT_EQ(0, pda->getInt(addr2));

	Tag2 = Tag1 - (int)800;

	ASSERT_EQ(-90, pda->getInt(addr1));
	ASSERT_EQ(-890, pda->getInt(addr2));

	// Check all process data
	for (unsigned int i=8; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestIntTagMul1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};
	processDataAddress addr3 = {PDA_MEMORY, 8, 0};

	PDTag<int> Tag1(addr1, *pda);
	PDTag<int> Tag2(addr2, *pda);
	PDTag<int> Tag3(addr3, *pda);

	ASSERT_EQ(0, pda->getInt(addr1));
	ASSERT_EQ(0, pda->getInt(addr2));
	ASSERT_EQ(0, pda->getInt(addr3));

	Tag1 = -2;
	Tag2 = 40;

	ASSERT_EQ(-2, pda->getInt(addr1));
	ASSERT_EQ(40, pda->getInt(addr2));
	ASSERT_EQ(0, pda->getInt(addr3));

	Tag3 = Tag2 * Tag1;

	ASSERT_EQ(-2, pda->getInt(addr1));
	ASSERT_EQ(40, pda->getInt(addr2));
	ASSERT_EQ(-80, pda->getInt(addr3));

	// Check all process data
	for (unsigned int i=12; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestIntTagMul2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};

	PDTag<int> Tag1(addr1, *pda);
	PDTag<int> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getInt(addr1));
	ASSERT_EQ(0, pda->getInt(addr2));

	Tag1 = -9;

	ASSERT_EQ(-9, pda->getInt(addr1));
	ASSERT_EQ(0, pda->getInt(addr2));

	Tag2 = Tag1 * (int)2;

	ASSERT_EQ(-9, pda->getInt(addr1));
	ASSERT_EQ(-18, pda->getInt(addr2));

	// Check all process data
	for (unsigned int i=8; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestIntTagDiv1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};
	processDataAddress addr3 = {PDA_MEMORY, 8, 0};

	PDTag<int> Tag1(addr1, *pda);
	PDTag<int> Tag2(addr2, *pda);
	PDTag<int> Tag3(addr3, *pda);

	ASSERT_EQ(0, pda->getInt(addr1));
	ASSERT_EQ(0, pda->getInt(addr2));
	ASSERT_EQ(0, pda->getInt(addr3));

	Tag1 = 2;
	Tag2 = -4;

	ASSERT_EQ(2, pda->getInt(addr1));
	ASSERT_EQ(-4, pda->getInt(addr2));
	ASSERT_EQ(0, pda->getInt(addr3));

	Tag3 = Tag2 / Tag1;

	ASSERT_EQ(2, pda->getInt(addr1));
	ASSERT_EQ(-4, pda->getInt(addr2));
	ASSERT_EQ(-2, pda->getInt(addr3));

	// Check all process data
	for (unsigned int i=12; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestIntTagDiv2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};

	PDTag<int> Tag1(addr1, *pda);
	PDTag<int> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getInt(addr1));
	ASSERT_EQ(0, pda->getInt(addr2));

	Tag1 = -80;

	ASSERT_EQ(-80, pda->getInt(addr1));
	ASSERT_EQ(0, pda->getInt(addr2));

	Tag2 = Tag1 / (int)2;

	ASSERT_EQ(-80, pda->getInt(addr1));
	ASSERT_EQ(-40, pda->getInt(addr2));

	// Check all process data
	for (unsigned int i=8; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestIntTagSumEq1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};

	PDTag<int> Tag1(addr1, *pda);
	PDTag<int> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getInt(addr1));
	ASSERT_EQ(0, pda->getInt(addr2));

	Tag1 = -5;
	Tag2 = 2;

	ASSERT_EQ(-5, pda->getInt(addr1));
	ASSERT_EQ(2, pda->getInt(addr2));

	Tag1 += Tag2;

	ASSERT_EQ(-3, pda->getInt(addr1));
	ASSERT_EQ(2, pda->getInt(addr2));

	// Check all process data
	for (unsigned int i=8; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestIntTagSumEq2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<int> Tag1(addr1, *pda);

	ASSERT_EQ(0, pda->getInt(addr1));

	Tag1 = -5;

	ASSERT_EQ(-5, pda->getInt(addr1));

	Tag1 += (int)2;

	ASSERT_EQ(-3, pda->getInt(addr1));

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestIntTagSubEq1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};

	PDTag<int> Tag1(addr1, *pda);
	PDTag<int> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getInt(addr1));
	ASSERT_EQ(0, pda->getInt(addr2));

	Tag1 = 4;
	Tag2 = 10;

	ASSERT_EQ(4, pda->getInt(addr1));
	ASSERT_EQ(10, pda->getInt(addr2));

	Tag1 -= Tag2;

	ASSERT_EQ(-6, pda->getInt(addr1));
	ASSERT_EQ(10, pda->getInt(addr2));

	// Check all process data
	for (unsigned int i=8; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestIntTagSubEq2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<int> Tag1(addr1, *pda);

	ASSERT_EQ(0, pda->getInt(addr1));

	Tag1 = 4;

	ASSERT_EQ(4, pda->getInt(addr1));

	Tag1 -= (int)10;

	ASSERT_EQ(-6, pda->getInt(addr1));

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestIntTagMulEq1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};

	PDTag<int> Tag1(addr1, *pda);
	PDTag<int> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getInt(addr1));
	ASSERT_EQ(0, pda->getInt(addr2));

	Tag1 = -4;
	Tag2 = 20;

	ASSERT_EQ(-4, pda->getInt(addr1));
	ASSERT_EQ(20, pda->getInt(addr2));

	Tag1 *= Tag2;

	ASSERT_EQ(-80, pda->getInt(addr1));
	ASSERT_EQ(20, pda->getInt(addr2));

	// Check all process data
	for (unsigned int i=8; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestIntTagMulEq2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<int> Tag1(addr1, *pda);

	ASSERT_EQ(0, pda->getInt(addr1));

	Tag1 = -4;

	ASSERT_EQ(-4, pda->getInt(addr1));

	Tag1 *= (int)20;

	ASSERT_EQ(-80, pda->getInt(addr1));

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestIntTagDivEq1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};

	PDTag<int> Tag1(addr1, *pda);
	PDTag<int> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getInt(addr1));
	ASSERT_EQ(0, pda->getInt(addr2));

	Tag1 = -40;
	Tag2 = 2;

	ASSERT_EQ(-40, pda->getInt(addr1));
	ASSERT_EQ(2, pda->getInt(addr2));

	Tag1 /= Tag2;

	ASSERT_EQ(-20, pda->getInt(addr1));
	ASSERT_EQ(2, pda->getInt(addr2));

	// Check all process data
	for (unsigned int i=8; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestIntTagDivEq2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<int> Tag1(addr1, *pda);

	ASSERT_EQ(0, pda->getInt(addr1));

	Tag1 = -40;

	ASSERT_EQ(-40, pda->getInt(addr1));

	Tag1 /= (int)2;

	ASSERT_EQ(-20, pda->getInt(addr1));

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestIntTagInc1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<int> Tag1(addr1, *pda);

	ASSERT_EQ(0, pda->getInt(addr1));

	Tag1 = -45;

	++Tag1;

	ASSERT_EQ(-44, pda->getInt(addr1));

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestIntTagInc2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<int> Tag1(addr1, *pda);

	ASSERT_EQ(0, pda->getInt(addr1));

	Tag1 = -45;

	int v = Tag1++;

	ASSERT_EQ(-44, pda->getInt(addr1));
	ASSERT_EQ(-45, v);

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

#endif /* LIBRARY_LIBONHSHMCPP_TEST_SRC_PDTAGINTTESTS_H_ */
