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

#ifndef LIBRARY_LIBONHSHMCPP_TEST_SRC_PDTAGBITTESTS_H_
#define LIBRARY_LIBONHSHMCPP_TEST_SRC_PDTAGBITTESTS_H_

#include <gtest/gtest.h>
#include "pdaTestGlobalData.h"
#include "fixtures/pdaClearTest.h"
#include <onhSHMcpp/PDTag.h>

using namespace onh;

/**
 * Check Tag BIT
 */
TEST_F(pdaClearTest, TestBitTagAssignment1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 0, 1};

	// Tag bool
	PDTag<bool> Tag1(addr1, *pda);
	PDTag<bool> Tag2(addr2, *pda);

	ASSERT_FALSE(pda->getBit(addr1));
	ASSERT_FALSE(pda->getBit(addr2));

	Tag1 = true;

	ASSERT_TRUE(pda->getBit(addr1));
	ASSERT_FALSE(pda->getBit(addr2));

	Tag2 = Tag1;

	ASSERT_TRUE(pda->getBit(addr1));
	ASSERT_TRUE(pda->getBit(addr2));

	// Check all process data
	ASSERT_EQ(3, pda->getByte(processDataAddress{PDA_MEMORY, 0, 0}));
	for (unsigned int i=1; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestBitTagAssignment2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<bool> Tag1(addr1, *pda);

	bool r1;

	r1 = Tag1;
	ASSERT_FALSE(pda->getBit(addr1));
	ASSERT_FALSE(r1);

	Tag1 = true;

	r1 = Tag1;
	ASSERT_TRUE(pda->getBit(addr1));
	ASSERT_TRUE(r1);

	// Check all process data
	ASSERT_EQ(1, pda->getByte(processDataAddress{PDA_MEMORY, 0, 0}));
	for (unsigned int i=1; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
	}
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
	}
}

TEST_F(pdaClearTest, TestBitTagSumException1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 0, 1};

	PDTag<bool> Tag1(addr1, *pda);
	PDTag<bool> Tag2(addr2, *pda);

	try {

		Tag1 = Tag2 + true;

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "PDTag<bool>::operator+ (bool): Can not sum binary values");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

TEST_F(pdaClearTest, TestBitTagSumException2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 0, 1};
	processDataAddress addr3 = {PDA_MEMORY, 0, 2};

	PDTag<bool> Tag1(addr1, *pda);
	PDTag<bool> Tag2(addr2, *pda);
	PDTag<bool> Tag3(addr3, *pda);

	try {

		Tag1 = Tag2 + Tag3;

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "PDTag<bool>::operator+ (PDTag<bool>): Can not sum binary values");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

TEST_F(pdaClearTest, TestBitTagSubException1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 0, 1};

	PDTag<bool> Tag1(addr1, *pda);
	PDTag<bool> Tag2(addr2, *pda);

	try {

		Tag1 = Tag2 - true;

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "PDTag<bool>::operator- (bool): Can not subtract binary values");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

TEST_F(pdaClearTest, TestBitTagSubException2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 0, 1};
	processDataAddress addr3 = {PDA_MEMORY, 0, 2};

	PDTag<bool> Tag1(addr1, *pda);
	PDTag<bool> Tag2(addr2, *pda);
	PDTag<bool> Tag3(addr3, *pda);

	try {

		Tag1 = Tag2 - Tag3;

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "PDTag<bool>::operator- (PDTag<bool>): Can not subtract binary values");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

TEST_F(pdaClearTest, TestBitTagMulException1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 0, 1};

	PDTag<bool> Tag1(addr1, *pda);
	PDTag<bool> Tag2(addr2, *pda);

	try {

		Tag1 = Tag2 * true;

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "PDTag<bool>::operator* (bool): Can not multiply binary values");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

TEST_F(pdaClearTest, TestBitTagMulException2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 0, 1};
	processDataAddress addr3 = {PDA_MEMORY, 0, 2};

	PDTag<bool> Tag1(addr1, *pda);
	PDTag<bool> Tag2(addr2, *pda);
	PDTag<bool> Tag3(addr3, *pda);

	try {

		Tag1 = Tag2 * Tag3;

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "PDTag<bool>::operator* (PDTag<bool>): Can not multiply binary values");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

TEST_F(pdaClearTest, TestBitTagDivException1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 0, 1};

	PDTag<bool> Tag1(addr1, *pda);
	PDTag<bool> Tag2(addr2, *pda);

	try {

		Tag1 = Tag2 / true;

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "PDTag<bool>::operator/ (bool): Can not divide binary values");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

TEST_F(pdaClearTest, TestBitTagDivException2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 0, 1};
	processDataAddress addr3 = {PDA_MEMORY, 0, 2};

	PDTag<bool> Tag1(addr1, *pda);
	PDTag<bool> Tag2(addr2, *pda);
	PDTag<bool> Tag3(addr3, *pda);

	try {

		Tag1 = Tag2 / Tag3;

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "PDTag<bool>::operator/ (PDTag<bool>): Can not divide binary values");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

TEST_F(pdaClearTest, TestBitTagSumEqException1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<bool> Tag1(addr1, *pda);

	try {

		Tag1 += true;

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "PDTag<bool>::operator+= (bool): Can not sum binary values");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

TEST_F(pdaClearTest, TestBitTagSumEqException2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 0, 1};

	PDTag<bool> Tag1(addr1, *pda);
	PDTag<bool> Tag2(addr2, *pda);

	try {

		Tag1 += Tag2;

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "PDTag<bool>::operator+= (PDTag<bool>): Can not sum binary values");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

TEST_F(pdaClearTest, TestBitTagSubEqException1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<bool> Tag1(addr1, *pda);

	try {

		Tag1 -= true;

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "PDTag<bool>::operator-= (bool): Can not subtract binary values");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

TEST_F(pdaClearTest, TestBitTagSubEqException2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 0, 1};

	PDTag<bool> Tag1(addr1, *pda);
	PDTag<bool> Tag2(addr2, *pda);

	try {

		Tag1 -= Tag2;

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "PDTag<bool>::operator-= (PDTag<bool>): Can not subtract binary values");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

TEST_F(pdaClearTest, TestBitTagMulEqException1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<bool> Tag1(addr1, *pda);

	try {

		Tag1 *= true;

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "PDTag<bool>::operator*= (bool): Can not multiply binary values");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

TEST_F(pdaClearTest, TestBitTagMulEqException2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 0, 1};

	PDTag<bool> Tag1(addr1, *pda);
	PDTag<bool> Tag2(addr2, *pda);

	try {

		Tag1 *= Tag2;

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "PDTag<bool>::operator*= (PDTag<bool>): Can not multiply binary values");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

TEST_F(pdaClearTest, TestBitTagDivEqException1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<bool> Tag1(addr1, *pda);

	try {

		Tag1 /= true;

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "PDTag<bool>::operator/= (bool): Can not divide binary values");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

TEST_F(pdaClearTest, TestBitTagDivEqException2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};
	processDataAddress addr2 = {PDA_MEMORY, 0, 1};

	PDTag<bool> Tag1(addr1, *pda);
	PDTag<bool> Tag2(addr2, *pda);

	try {

		Tag1 /= Tag2;

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "PDTag<bool>::operator/= (PDTag<bool>): Can not divide binary values");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

TEST_F(pdaClearTest, TestBitTagIncException1) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<bool> Tag1(addr1, *pda);

	try {

		++Tag1;

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "PDTag<bool>::operator++: Can not increment binary values");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

TEST_F(pdaClearTest, TestBitTagIncException2) {

	processDataAddress addr1 = {PDA_MEMORY, 0, 0};

	PDTag<bool> Tag1(addr1, *pda);

	try {

		Tag1++;

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "PDTag<bool>::operator++ (f): Can not increment binary values");

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

#endif /* LIBRARY_LIBONHSHMCPP_TEST_SRC_PDTAGBITTESTS_H_ */
