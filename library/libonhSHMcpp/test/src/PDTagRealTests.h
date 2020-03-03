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

#ifndef LIBRARY_LIBONHSHMCPP_TEST_SRC_PDTAGREALTESTS_H_
#define LIBRARY_LIBONHSHMCPP_TEST_SRC_PDTAGREALTESTS_H_

#include <gtest/gtest.h>
#include "pdaTestGlobalData.h"
#include "fixtures/pdaClearTest.h"
#include <onhSHMcpp/PDTag.h>

using namespace onh;

/**
 * Check Tag REAL
 */
TEST_F(pdaClearTest, TestRealTagAssignment1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};

	PDTag<float> Tag1(addr1, *pda);
	PDTag<float> Tag2(addr2, *pda);

	ASSERT_FLOAT_EQ(0, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(0, pda->getReal(addr2));

	Tag1 = -48.7;

	ASSERT_FLOAT_EQ(-48.7, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(0, pda->getReal(addr2));

	Tag2 = Tag1;

	ASSERT_FLOAT_EQ(-48.7, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(-48.7, pda->getReal(addr2));

	// Check all process data
	for (unsigned int i=8; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestRealTagAssignment2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<float> Tag1(addr1, *pda);

	float b1;

	b1 = Tag1;
	ASSERT_FLOAT_EQ(0, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(0, b1);

	Tag1 = -48.7;

	b1 = Tag1;
	ASSERT_FLOAT_EQ(-48.7, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(-48.7, b1);

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestRealTagSum1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};
	processDataAddress addr3 = {PDA_MEMORY, 8, 0};

	PDTag<float> Tag1(addr1, *pda);
	PDTag<float> Tag2(addr2, *pda);
	PDTag<float> Tag3(addr3, *pda);

	ASSERT_FLOAT_EQ(0, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(0, pda->getReal(addr2));
	ASSERT_FLOAT_EQ(0, pda->getReal(addr3));

	Tag1 = -48.7;
	Tag2 = 50.9;

	ASSERT_FLOAT_EQ(-48.7, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(50.9, pda->getReal(addr2));
	ASSERT_FLOAT_EQ(0, pda->getReal(addr3));

	Tag3 = Tag1 + Tag2;

	ASSERT_FLOAT_EQ(-48.7, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(50.9, pda->getReal(addr2));
	ASSERT_FLOAT_EQ(2.2, pda->getReal(addr3));

	// Check all process data
	for (unsigned int i=12; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestRealTagSum2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};

	PDTag<float> Tag1(addr1, *pda);
	PDTag<float> Tag2(addr2, *pda);

	ASSERT_FLOAT_EQ(0, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(0, pda->getReal(addr2));

	Tag1 = -45.7;

	ASSERT_FLOAT_EQ(-45.7, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(0, pda->getReal(addr2));

	Tag2 = Tag1 + (float)5.5;

	ASSERT_FLOAT_EQ(-45.7, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(-40.2, pda->getReal(addr2));

	// Check all process data
	for (unsigned int i=8; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestRealTagSub1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};
	processDataAddress addr3 = {PDA_MEMORY, 8, 0};

	PDTag<float> Tag1(addr1, *pda);
	PDTag<float> Tag2(addr2, *pda);
	PDTag<float> Tag3(addr3, *pda);

	ASSERT_FLOAT_EQ(0, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(0, pda->getReal(addr2));
	ASSERT_FLOAT_EQ(0, pda->getReal(addr3));

	Tag1 = -10.5;
	Tag2 = 5.2;

	ASSERT_FLOAT_EQ(-10.5, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(5.2, pda->getReal(addr2));
	ASSERT_FLOAT_EQ(0, pda->getReal(addr3));

	Tag3 = Tag2 - Tag1;

	ASSERT_FLOAT_EQ(-10.5, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(5.2, pda->getReal(addr2));
	ASSERT_FLOAT_EQ(15.7, pda->getReal(addr3));

	// Check all process data
	for (unsigned int i=12; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestRealTagSub2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};

	PDTag<float> Tag1(addr1, *pda);
	PDTag<float> Tag2(addr2, *pda);

	ASSERT_FLOAT_EQ(0, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(0, pda->getReal(addr2));

	Tag1 = -90.5;

	ASSERT_FLOAT_EQ(-90.5, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(0, pda->getReal(addr2));

	Tag2 = Tag1 - (float)10.4;

	ASSERT_FLOAT_EQ(-90.5, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(-100.9, pda->getReal(addr2));

	// Check all process data
	for (unsigned int i=8; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestRealTagMul1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};
	processDataAddress addr3 = {PDA_MEMORY, 8, 0};

	PDTag<float> Tag1(addr1, *pda);
	PDTag<float> Tag2(addr2, *pda);
	PDTag<float> Tag3(addr3, *pda);

	ASSERT_FLOAT_EQ(0, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(0, pda->getReal(addr2));
	ASSERT_FLOAT_EQ(0, pda->getReal(addr3));

	Tag1 = -2.4;
	Tag2 = 2.2;

	ASSERT_FLOAT_EQ(-2.4, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(2.2, pda->getReal(addr2));
	ASSERT_FLOAT_EQ(0, pda->getReal(addr3));

	Tag3 = Tag2 * Tag1;

	ASSERT_FLOAT_EQ(-2.4, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(2.2, pda->getReal(addr2));
	ASSERT_FLOAT_EQ(-5.28, pda->getReal(addr3));

	// Check all process data
	for (unsigned int i=12; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestRealTagMul2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};

	PDTag<float> Tag1(addr1, *pda);
	PDTag<float> Tag2(addr2, *pda);

	ASSERT_FLOAT_EQ(0, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(0, pda->getReal(addr2));

	Tag1 = -2.4;

	ASSERT_FLOAT_EQ(-2.4, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(0, pda->getReal(addr2));

	Tag2 = Tag1 * (float)2.2;

	ASSERT_FLOAT_EQ(-2.4, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(-5.28, pda->getReal(addr2));

	// Check all process data
	for (unsigned int i=8; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestRealTagDiv1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};
	processDataAddress addr3 = {PDA_MEMORY, 8, 0};

	PDTag<float> Tag1(addr1, *pda);
	PDTag<float> Tag2(addr2, *pda);
	PDTag<float> Tag3(addr3, *pda);

	ASSERT_FLOAT_EQ(0, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(0, pda->getReal(addr2));
	ASSERT_FLOAT_EQ(0, pda->getReal(addr3));

	Tag1 = 2.0;
	Tag2 = -2.6;

	ASSERT_FLOAT_EQ(2.0, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(-2.6, pda->getReal(addr2));
	ASSERT_FLOAT_EQ(0, pda->getReal(addr3));

	Tag3 = Tag2 / Tag1;

	ASSERT_FLOAT_EQ(2.0, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(-2.6, pda->getReal(addr2));
	ASSERT_FLOAT_EQ(-1.3, pda->getReal(addr3));

	// Check all process data
	for (unsigned int i=12; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestRealTagDiv2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};

	PDTag<float> Tag1(addr1, *pda);
	PDTag<float> Tag2(addr2, *pda);

	ASSERT_FLOAT_EQ(0, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(0, pda->getReal(addr2));

	Tag1 = -2.6;

	ASSERT_FLOAT_EQ(-2.6, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(0, pda->getReal(addr2));

	Tag2 = Tag1 / (float)2.0;

	ASSERT_FLOAT_EQ(-2.6, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(-1.3, pda->getReal(addr2));

	// Check all process data
	for (unsigned int i=8; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestRealTagSumEq1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};

	PDTag<float> Tag1(addr1, *pda);
	PDTag<float> Tag2(addr2, *pda);

	ASSERT_FLOAT_EQ(0, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(0, pda->getReal(addr2));

	Tag1 = -5.4;
	Tag2 = 2.1;

	ASSERT_FLOAT_EQ(-5.4, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(2.1, pda->getReal(addr2));

	Tag1 += Tag2;

	ASSERT_FLOAT_EQ(-3.3, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(2.1, pda->getReal(addr2));

	// Check all process data
	for (unsigned int i=8; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestRealTagSumEq2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<float> Tag1(addr1, *pda);

	ASSERT_FLOAT_EQ(0, pda->getReal(addr1));

	Tag1 = -5.4;

	ASSERT_FLOAT_EQ(-5.4, pda->getReal(addr1));

	Tag1 += (float)2.1;

	ASSERT_FLOAT_EQ(-3.3, pda->getReal(addr1));

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestRealTagSubEq1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};

	PDTag<float> Tag1(addr1, *pda);
	PDTag<float> Tag2(addr2, *pda);

	ASSERT_FLOAT_EQ(0, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(0, pda->getReal(addr2));

	Tag1 = 4.7;
	Tag2 = 10.6;

	ASSERT_FLOAT_EQ(4.7, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(10.6, pda->getReal(addr2));

	Tag1 -= Tag2;

	ASSERT_FLOAT_EQ(-5.9, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(10.6, pda->getReal(addr2));

	// Check all process data
	for (unsigned int i=8; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestRealTagSubEq2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<float> Tag1(addr1, *pda);

	ASSERT_FLOAT_EQ(0, pda->getReal(addr1));

	Tag1 = 4.7;

	ASSERT_FLOAT_EQ(4.7, pda->getReal(addr1));

	Tag1 -= (float)10.6;

	ASSERT_FLOAT_EQ(-5.9, pda->getReal(addr1));

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestRealTagMulEq1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};

	PDTag<float> Tag1(addr1, *pda);
	PDTag<float> Tag2(addr2, *pda);

	ASSERT_FLOAT_EQ(0, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(0, pda->getReal(addr2));

	Tag1 = -4.1;
	Tag2 = 2.0;

	ASSERT_FLOAT_EQ(-4.1, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(2.0, pda->getReal(addr2));

	Tag1 *= Tag2;

	ASSERT_FLOAT_EQ(-8.2, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(2.0, pda->getReal(addr2));

	// Check all process data
	for (unsigned int i=8; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestRealTagMulEq2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<float> Tag1(addr1, *pda);

	ASSERT_FLOAT_EQ(0, pda->getReal(addr1));

	Tag1 = -4.1;

	ASSERT_FLOAT_EQ(-4.1, pda->getReal(addr1));

	Tag1 *= (float)2.0;

	ASSERT_FLOAT_EQ(-8.2, pda->getReal(addr1));

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestRealTagDivEq1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 4, 0};

	PDTag<float> Tag1(addr1, *pda);
	PDTag<float> Tag2(addr2, *pda);

	ASSERT_FLOAT_EQ(0, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(0, pda->getReal(addr2));

	Tag1 = -4.2;
	Tag2 = 2.0;

	ASSERT_FLOAT_EQ(-4.2, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(2.0, pda->getReal(addr2));

	Tag1 /= Tag2;

	ASSERT_FLOAT_EQ(-2.1, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(2.0, pda->getReal(addr2));

	// Check all process data
	for (unsigned int i=8; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestRealTagDivEq2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<float> Tag1(addr1, *pda);

	ASSERT_FLOAT_EQ(0, pda->getReal(addr1));

	Tag1 = -4.2;

	ASSERT_FLOAT_EQ(-4.2, pda->getReal(addr1));

	Tag1 /= (float)2.0;

	ASSERT_FLOAT_EQ(-2.1, pda->getReal(addr1));

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestRealTagInc1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<float> Tag1(addr1, *pda);

	ASSERT_FLOAT_EQ(0, pda->getReal(addr1));

	Tag1 = -45.4;

	++Tag1;

	ASSERT_FLOAT_EQ(-44.4, pda->getReal(addr1));

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestRealTagInc2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<float> Tag1(addr1, *pda);

	ASSERT_FLOAT_EQ(0, pda->getReal(addr1));

	Tag1 = -45.4;

	float v = Tag1++;

	ASSERT_FLOAT_EQ(-44.4, pda->getReal(addr1));
	ASSERT_FLOAT_EQ(-45.4, v);

	// Check all process data
	for (unsigned int i=4; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_FLOAT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

#endif /* LIBRARY_LIBONHSHMCPP_TEST_SRC_PDTAGREALTESTS_H_ */
