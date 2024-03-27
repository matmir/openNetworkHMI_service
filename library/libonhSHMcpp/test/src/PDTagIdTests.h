/**
 * Copyright (c) 2022 Mateusz Mirosławski
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

#ifndef LIBRARY_LIBONHSHMCPP_TEST_SRC_PDTAGIDTESTS_H_
#define LIBRARY_LIBONHSHMCPP_TEST_SRC_PDTAGIDTESTS_H_

#include <gtest/gtest.h>
#include "pdaTestGlobalData.h"
#include "fixtures/pdaClearTest.h"
#include <onhSHMcpp/PDTag.h>

using namespace onh;

/**
 * Check Tag ID
 */
TEST_F(pdaClearTest, TestTagId1) {

	PDTag<bool> Tag1({PDA_MEMORY, 0, 4}, *pda);
	PDTag<bool> Tag2({PDA_MEMORY, 14, 1}, *pda);
	PDTag<bool> Tag3({PDA_INPUT, 14, 1}, *pda);
	PDTag<bool> Tag4({PDA_OUTPUT, 14, 1}, *pda);
	PDTag<bool> Tag5({PDA_OUTPUT, 0, 0}, *pda);
	PDTag<bool> Tag6({PDA_INPUT, 1060, 0}, *pda);
	PDTag<BYTE> Tag7({PDA_MEMORY, 1060, 5}, *pda);
	PDTag<BYTE> Tag8({PDA_MEMORY, 1060, 3}, *pda);
	PDTag<float> Tag9({PDA_MEMORY, 1060, 3}, *pda);
	PDTag<int> Tag10({PDA_MEMORY, 1060, 3}, *pda);
	PDTag<WORD> Tag11({PDA_MEMORY, 1060, 3}, *pda);
	PDTag<DWORD> Tag12({PDA_MEMORY, 1060, 3}, *pda);

	ASSERT_EQ(431, Tag1.getId());
	ASSERT_EQ(14131, Tag2.getId());
	ASSERT_EQ(14111, Tag3.getId());
	ASSERT_EQ(14121, Tag4.getId());
	ASSERT_EQ(21, Tag5.getId());
	ASSERT_EQ(1060011, Tag6.getId());
	ASSERT_EQ(1060032, Tag7.getId());
	ASSERT_EQ(1060032, Tag8.getId());
	ASSERT_EQ(1060036, Tag9.getId());
	ASSERT_EQ(1060035, Tag10.getId());
	ASSERT_EQ(1060033, Tag11.getId());
	ASSERT_EQ(1060034, Tag12.getId());
}

TEST_F(pdaClearTest, TestTagId2) {

	PDTag<BYTE> Tag8({PDA_MEMORY, 1060, 3}, *pda);
	PDTag<bool> Tag9({PDA_MEMORY, 1060, 0}, *pda);
	PDTag<bool> Tag10({PDA_MEMORY, 1060, 3}, *pda);

	ASSERT_FALSE(Tag8.getId()==Tag9.getId());
	ASSERT_FALSE(Tag8.getId()==Tag10.getId());
}

#endif /* LIBRARY_LIBONHSHMCPP_TEST_SRC_PDTAGIDTESTS_H_ */
