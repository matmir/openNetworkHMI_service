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

#ifndef LIBRARY_LIBONHSHMCPP_TEST_SRC_PDTAGBYTETESTS_H_
#define LIBRARY_LIBONHSHMCPP_TEST_SRC_PDTAGBYTETESTS_H_

#include <gtest/gtest.h>
#include "pdaTestGlobalData.h"
#include "fixtures/pdaClearTest.h"
#include <onhSHMcpp/PDTag.h>

using namespace onh;

/**
 * Check Tag BYTE
 */
TEST_F(pdaClearTest, TestByteTagAssignment1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 1, 0};

	PDTag<BYTE> Tag1(addr1, *pda);
	PDTag<BYTE> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getByte(addr1));
	ASSERT_EQ(0, pda->getByte(addr2));

	Tag1 = 75;

	ASSERT_EQ(75, pda->getByte(addr1));
	ASSERT_EQ(0, pda->getByte(addr2));

	Tag2 = Tag1;

	ASSERT_EQ(75, pda->getByte(addr1));
	ASSERT_EQ(75, pda->getByte(addr2));

	// Check all process data
	for (unsigned int i=2; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestByteTagAssignment2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<BYTE> Tag1(addr1, *pda);

	BYTE b1;

	b1 = Tag1;
	ASSERT_EQ(0, pda->getByte(addr1));
	ASSERT_EQ(0, b1);

	Tag1 = 75;

	b1 = Tag1;
	ASSERT_EQ(75, pda->getByte(addr1));
	ASSERT_EQ(75, b1);

	// Check all process data
	for (unsigned int i=1; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestByteTagSum1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 1, 0};
	processDataAddress addr3 = {PDA_MEMORY, 2, 0};

	PDTag<BYTE> Tag1(addr1, *pda);
	PDTag<BYTE> Tag2(addr2, *pda);
	PDTag<BYTE> Tag3(addr3, *pda);

	ASSERT_EQ(0, pda->getByte(addr1));
	ASSERT_EQ(0, pda->getByte(addr2));
	ASSERT_EQ(0, pda->getByte(addr3));

	Tag1 = 42;
	Tag2 = 100;

	ASSERT_EQ(42, pda->getByte(addr1));
	ASSERT_EQ(100, pda->getByte(addr2));
	ASSERT_EQ(0, pda->getByte(addr3));

	Tag3 = Tag1 + Tag2;

	ASSERT_EQ(42, pda->getByte(addr1));
	ASSERT_EQ(100, pda->getByte(addr2));
	ASSERT_EQ(142, pda->getByte(addr3));

	// Check all process data
	for (unsigned int i=3; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestByteTagSum2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 1, 0};

	PDTag<BYTE> Tag1(addr1, *pda);
	PDTag<BYTE> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getByte(addr1));
	ASSERT_EQ(0, pda->getByte(addr2));

	Tag1 = 42;

	ASSERT_EQ(42, pda->getByte(addr1));
	ASSERT_EQ(0, pda->getByte(addr2));

	Tag2 = Tag1 + (BYTE)8;

	ASSERT_EQ(42, pda->getByte(addr1));
	ASSERT_EQ(50, pda->getByte(addr2));

	// Check all process data
	for (unsigned int i=2; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestByteTagSub1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 1, 0};
	processDataAddress addr3 = {PDA_MEMORY, 2, 0};

	PDTag<BYTE> Tag1(addr1, *pda);
	PDTag<BYTE> Tag2(addr2, *pda);
	PDTag<BYTE> Tag3(addr3, *pda);

	ASSERT_EQ(0, pda->getByte(addr1));
	ASSERT_EQ(0, pda->getByte(addr2));
	ASSERT_EQ(0, pda->getByte(addr3));

	Tag1 = 42;
	Tag2 = 100;

	ASSERT_EQ(42, pda->getByte(addr1));
	ASSERT_EQ(100, pda->getByte(addr2));
	ASSERT_EQ(0, pda->getByte(addr3));

	Tag3 = Tag2 - Tag1;

	ASSERT_EQ(42, pda->getByte(addr1));
	ASSERT_EQ(100, pda->getByte(addr2));
	ASSERT_EQ(58, pda->getByte(addr3));

	// Check all process data
	for (unsigned int i=3; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestByteTagSub2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 1, 0};

	PDTag<BYTE> Tag1(addr1, *pda);
	PDTag<BYTE> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getByte(addr1));
	ASSERT_EQ(0, pda->getByte(addr2));

	Tag1 = 42;

	ASSERT_EQ(42, pda->getByte(addr1));
	ASSERT_EQ(0, pda->getByte(addr2));

	Tag2 = Tag1 - (BYTE)8;

	ASSERT_EQ(42, pda->getByte(addr1));
	ASSERT_EQ(34, pda->getByte(addr2));

	// Check all process data
	for (unsigned int i=2; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestByteTagMul1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 1, 0};
	processDataAddress addr3 = {PDA_MEMORY, 2, 0};

	PDTag<BYTE> Tag1(addr1, *pda);
	PDTag<BYTE> Tag2(addr2, *pda);
	PDTag<BYTE> Tag3(addr3, *pda);

	ASSERT_EQ(0, pda->getByte(addr1));
	ASSERT_EQ(0, pda->getByte(addr2));
	ASSERT_EQ(0, pda->getByte(addr3));

	Tag1 = 3;
	Tag2 = 20;

	ASSERT_EQ(3, pda->getByte(addr1));
	ASSERT_EQ(20, pda->getByte(addr2));
	ASSERT_EQ(0, pda->getByte(addr3));

	Tag3 = Tag2 * Tag1;

	ASSERT_EQ(3, pda->getByte(addr1));
	ASSERT_EQ(20, pda->getByte(addr2));
	ASSERT_EQ(60, pda->getByte(addr3));

	// Check all process data
	for (unsigned int i=3; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestByteTagMul2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 1, 0};

	PDTag<BYTE> Tag1(addr1, *pda);
	PDTag<BYTE> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getByte(addr1));
	ASSERT_EQ(0, pda->getByte(addr2));

	Tag1 = 42;

	ASSERT_EQ(42, pda->getByte(addr1));
	ASSERT_EQ(0, pda->getByte(addr2));

	Tag2 = Tag1 * (BYTE)3;

	ASSERT_EQ(42, pda->getByte(addr1));
	ASSERT_EQ(126, pda->getByte(addr2));

	// Check all process data
	for (unsigned int i=2; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestByteTagDiv1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 1, 0};
	processDataAddress addr3 = {PDA_MEMORY, 2, 0};

	PDTag<BYTE> Tag1(addr1, *pda);
	PDTag<BYTE> Tag2(addr2, *pda);
	PDTag<BYTE> Tag3(addr3, *pda);

	ASSERT_EQ(0, pda->getByte(addr1));
	ASSERT_EQ(0, pda->getByte(addr2));
	ASSERT_EQ(0, pda->getByte(addr3));

	Tag1 = 3;
	Tag2 = 20;

	ASSERT_EQ(3, pda->getByte(addr1));
	ASSERT_EQ(20, pda->getByte(addr2));
	ASSERT_EQ(0, pda->getByte(addr3));

	Tag3 = Tag2 / Tag1;

	ASSERT_EQ(3, pda->getByte(addr1));
	ASSERT_EQ(20, pda->getByte(addr2));
	ASSERT_EQ(6, pda->getByte(addr3));

	// Check all process data
	for (unsigned int i=3; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestByteTagDiv2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 1, 0};

	PDTag<BYTE> Tag1(addr1, *pda);
	PDTag<BYTE> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getByte(addr1));
	ASSERT_EQ(0, pda->getByte(addr2));

	Tag1 = 42;

	ASSERT_EQ(42, pda->getByte(addr1));
	ASSERT_EQ(0, pda->getByte(addr2));

	Tag2 = Tag1 / (BYTE)3;

	ASSERT_EQ(42, pda->getByte(addr1));
	ASSERT_EQ(14, pda->getByte(addr2));

	// Check all process data
	for (unsigned int i=2; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestByteTagSumEq1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 1, 0};

	PDTag<BYTE> Tag1(addr1, *pda);
	PDTag<BYTE> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getByte(addr1));
	ASSERT_EQ(0, pda->getByte(addr2));

	Tag1 = 3;
	Tag2 = 20;

	ASSERT_EQ(3, pda->getByte(addr1));
	ASSERT_EQ(20, pda->getByte(addr2));

	Tag1 += Tag2;

	ASSERT_EQ(23, pda->getByte(addr1));
	ASSERT_EQ(20, pda->getByte(addr2));

	// Check all process data
	for (unsigned int i=2; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestByteTagSumEq2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<BYTE> Tag1(addr1, *pda);

	ASSERT_EQ(0, pda->getByte(addr1));

	Tag1 = 3;

	ASSERT_EQ(3, pda->getByte(addr1));

	Tag1 += (BYTE)50;

	ASSERT_EQ(53, pda->getByte(addr1));

	// Check all process data
	for (unsigned int i=1; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestByteTagSubEq1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 1, 0};

	PDTag<BYTE> Tag1(addr1, *pda);
	PDTag<BYTE> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getByte(addr1));
	ASSERT_EQ(0, pda->getByte(addr2));

	Tag1 = 30;
	Tag2 = 20;

	ASSERT_EQ(30, pda->getByte(addr1));
	ASSERT_EQ(20, pda->getByte(addr2));

	Tag1 -= Tag2;

	ASSERT_EQ(10, pda->getByte(addr1));
	ASSERT_EQ(20, pda->getByte(addr2));

	// Check all process data
	for (unsigned int i=2; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestByteTagSubEq2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<BYTE> Tag1(addr1, *pda);

	ASSERT_EQ(0, pda->getByte(addr1));

	Tag1 = 3;

	ASSERT_EQ(3, pda->getByte(addr1));

	Tag1 -= (BYTE)2;

	ASSERT_EQ(1, pda->getByte(addr1));

	// Check all process data
	for (unsigned int i=1; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestByteTagMulEq1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 1, 0};

	PDTag<BYTE> Tag1(addr1, *pda);
	PDTag<BYTE> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getByte(addr1));
	ASSERT_EQ(0, pda->getByte(addr2));

	Tag1 = 3;
	Tag2 = 2;

	ASSERT_EQ(3, pda->getByte(addr1));
	ASSERT_EQ(2, pda->getByte(addr2));

	Tag1 *= Tag2;

	ASSERT_EQ(6, pda->getByte(addr1));
	ASSERT_EQ(2, pda->getByte(addr2));

	// Check all process data
	for (unsigned int i=2; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestByteTagMulEq2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<BYTE> Tag1(addr1, *pda);

	ASSERT_EQ(0, pda->getByte(addr1));

	Tag1 = 3;

	ASSERT_EQ(3, pda->getByte(addr1));

	Tag1 *= (BYTE)2;

	ASSERT_EQ(6, pda->getByte(addr1));

	// Check all process data
	for (unsigned int i=1; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestByteTagDivEq1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 1, 0};

	PDTag<BYTE> Tag1(addr1, *pda);
	PDTag<BYTE> Tag2(addr2, *pda);

	ASSERT_EQ(0, pda->getByte(addr1));
	ASSERT_EQ(0, pda->getByte(addr2));

	Tag1 = 8;
	Tag2 = 2;

	ASSERT_EQ(8, pda->getByte(addr1));
	ASSERT_EQ(2, pda->getByte(addr2));

	Tag1 /= Tag2;

	ASSERT_EQ(4, pda->getByte(addr1));
	ASSERT_EQ(2, pda->getByte(addr2));

	// Check all process data
	for (unsigned int i=2; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestByteTagDivEq2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<BYTE> Tag1(addr1, *pda);

	ASSERT_EQ(0, pda->getByte(addr1));

	Tag1 = 9;

	ASSERT_EQ(9, pda->getByte(addr1));

	Tag1 /= (BYTE)2;

	ASSERT_EQ(4, pda->getByte(addr1));

	// Check all process data
	for (unsigned int i=1; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestByteTagInc1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<BYTE> Tag1(addr1, *pda);

	ASSERT_EQ(0, pda->getByte(addr1));

	++Tag1;

	ASSERT_EQ(1, pda->getByte(addr1));

	// Check all process data
	for (unsigned int i=1; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestByteTagInc2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<BYTE> Tag1(addr1, *pda);

	ASSERT_EQ(0, pda->getByte(addr1));

	Tag1 = 45;

	BYTE v = Tag1++;

	ASSERT_EQ(46, pda->getByte(addr1));
	ASSERT_EQ(45, v);

	// Check all process data
	for (unsigned int i=1; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

#endif /* LIBRARY_LIBONHSHMCPP_TEST_SRC_PDTAGBYTETESTS_H_ */
