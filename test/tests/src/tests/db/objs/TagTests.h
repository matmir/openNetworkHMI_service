/**
 * This file is part of openNetworkHMI.
 * Copyright (c) 2020 Mateusz Mirosławski.
 *
 * openNetworkHMI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * openNetworkHMI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with openNetworkHMI.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TESTS_DB_OBJS_TAGTESTS_H_
#define TESTS_DB_OBJS_TAGTESTS_H_

#include <gtest/gtest.h>
#include <db/objs/Tag.h>

/**
 * Check tag creation
 */
TEST(TagTests, Create1) {

	onh::Tag tg(
			1,
			2,
			"TestTag1",
			onh::TT_BIT,
			{onh::PDA_INPUT, 4, 6}
	);

	onh::processDataAddress pda = tg.getAddress();

	ASSERT_EQ((unsigned int)1, tg.getId());
	ASSERT_EQ((unsigned int)2, tg.getConnId());
	ASSERT_STREQ("TestTag1", tg.getName().c_str());
	ASSERT_EQ(onh::TT_BIT, tg.getType());
	ASSERT_EQ(onh::PDA_INPUT, tg.getArea());
	ASSERT_EQ((unsigned int)4, tg.getByteAddress());
	ASSERT_EQ((unsigned int)6, tg.getBitAddress());
	ASSERT_EQ(onh::PDA_INPUT, pda.area);
	ASSERT_EQ((unsigned int)4, pda.byteAddr);
	ASSERT_EQ((unsigned int)6, pda.bitAddr);
}

/**
 * Check tag creation set id
 */
TEST(TagTests, CreateSetId) {

	onh::Tag tg(
			1,
			2,
			"TestTag1",
			onh::TT_BIT,
			{onh::PDA_INPUT, 4, 6}
	);

	tg.setId(666);

	onh::processDataAddress pda = tg.getAddress();

	ASSERT_EQ((unsigned int)666, tg.getId());
	ASSERT_EQ((unsigned int)2, tg.getConnId());
	ASSERT_STREQ("TestTag1", tg.getName().c_str());
	ASSERT_EQ(onh::TT_BIT, tg.getType());
	ASSERT_EQ(onh::PDA_INPUT, tg.getArea());
	ASSERT_EQ((unsigned int)4, tg.getByteAddress());
	ASSERT_EQ((unsigned int)6, tg.getBitAddress());
	ASSERT_EQ(onh::PDA_INPUT, pda.area);
	ASSERT_EQ((unsigned int)4, pda.byteAddr);
	ASSERT_EQ((unsigned int)6, pda.bitAddr);
}

/**
 * Check tag creation set conn id
 */
TEST(TagTests, CreateSetConnId) {

	onh::Tag tg(
			1,
			2,
			"TestTag1",
			onh::TT_BIT,
			{onh::PDA_INPUT, 4, 6}
	);

	tg.setConnId(45);

	onh::processDataAddress pda = tg.getAddress();

	ASSERT_EQ((unsigned int)1, tg.getId());
	ASSERT_EQ((unsigned int)45, tg.getConnId());
	ASSERT_STREQ("TestTag1", tg.getName().c_str());
	ASSERT_EQ(onh::TT_BIT, tg.getType());
	ASSERT_EQ(onh::PDA_INPUT, tg.getArea());
	ASSERT_EQ((unsigned int)4, tg.getByteAddress());
	ASSERT_EQ((unsigned int)6, tg.getBitAddress());
	ASSERT_EQ(onh::PDA_INPUT, pda.area);
	ASSERT_EQ((unsigned int)4, pda.byteAddr);
	ASSERT_EQ((unsigned int)6, pda.bitAddr);
}

/**
 * Check tag creation set name
 */
TEST(TagTests, CreateSetName) {

	onh::Tag tg(
			1,
			2,
			"TestTag1",
			onh::TT_BIT,
			{onh::PDA_INPUT, 4, 6}
	);

	tg.setName("Tag67");

	onh::processDataAddress pda = tg.getAddress();

	ASSERT_EQ((unsigned int)1, tg.getId());
	ASSERT_EQ((unsigned int)2, tg.getConnId());
	ASSERT_STREQ("Tag67", tg.getName().c_str());
	ASSERT_EQ(onh::TT_BIT, tg.getType());
	ASSERT_EQ(onh::PDA_INPUT, tg.getArea());
	ASSERT_EQ((unsigned int)4, tg.getByteAddress());
	ASSERT_EQ((unsigned int)6, tg.getBitAddress());
	ASSERT_EQ(onh::PDA_INPUT, pda.area);
	ASSERT_EQ((unsigned int)4, pda.byteAddr);
	ASSERT_EQ((unsigned int)6, pda.bitAddr);
}

/**
 * Check tag creation set type
 */
TEST(TagTests, CreateSetType) {

	onh::Tag tg(
			1,
			2,
			"TestTag1",
			onh::TT_BIT,
			{onh::PDA_INPUT, 4, 6}
	);

	tg.setType(onh::TT_DWORD);

	onh::processDataAddress pda = tg.getAddress();

	ASSERT_EQ((unsigned int)1, tg.getId());
	ASSERT_EQ((unsigned int)2, tg.getConnId());
	ASSERT_STREQ("TestTag1", tg.getName().c_str());
	ASSERT_EQ(onh::TT_DWORD, tg.getType());
	ASSERT_EQ(onh::PDA_INPUT, tg.getArea());
	ASSERT_EQ((unsigned int)4, tg.getByteAddress());
	ASSERT_EQ((unsigned int)6, tg.getBitAddress());
	ASSERT_EQ(onh::PDA_INPUT, pda.area);
	ASSERT_EQ((unsigned int)4, pda.byteAddr);
	ASSERT_EQ((unsigned int)6, pda.bitAddr);
}

/**
 * Check tag creation set address
 */
TEST(TagTests, CreateSetAddress) {

	onh::Tag tg(
			1,
			2,
			"TestTag1",
			onh::TT_BIT,
			{onh::PDA_INPUT, 4, 6}
	);

	tg.setAddress({onh::PDA_MEMORY, 8, 2});

	onh::processDataAddress pda = tg.getAddress();

	ASSERT_EQ((unsigned int)1, tg.getId());
	ASSERT_EQ((unsigned int)2, tg.getConnId());
	ASSERT_STREQ("TestTag1", tg.getName().c_str());
	ASSERT_EQ(onh::TT_BIT, tg.getType());
	ASSERT_EQ(onh::PDA_MEMORY, tg.getArea());
	ASSERT_EQ((unsigned int)8, tg.getByteAddress());
	ASSERT_EQ((unsigned int)2, tg.getBitAddress());
	ASSERT_EQ(onh::PDA_MEMORY, pda.area);
	ASSERT_EQ((unsigned int)8, pda.byteAddr);
	ASSERT_EQ((unsigned int)2, pda.bitAddr);
}

/**
 * Check tag creation set area
 */
TEST(TagTests, CreateSetArea) {

	onh::Tag tg(
			1,
			2,
			"TestTag1",
			onh::TT_BIT,
			{onh::PDA_INPUT, 8, 2}
	);

	tg.setArea(onh::PDA_OUTPUT);

	onh::processDataAddress pda = tg.getAddress();

	ASSERT_EQ((unsigned int)1, tg.getId());
	ASSERT_EQ((unsigned int)2, tg.getConnId());
	ASSERT_STREQ("TestTag1", tg.getName().c_str());
	ASSERT_EQ(onh::TT_BIT, tg.getType());
	ASSERT_EQ(onh::PDA_OUTPUT, tg.getArea());
	ASSERT_EQ((unsigned int)8, tg.getByteAddress());
	ASSERT_EQ((unsigned int)2, tg.getBitAddress());
	ASSERT_EQ(onh::PDA_OUTPUT, pda.area);
	ASSERT_EQ((unsigned int)8, pda.byteAddr);
	ASSERT_EQ((unsigned int)2, pda.bitAddr);
}

/**
 * Check tag creation set byte address
 */
TEST(TagTests, CreateSetByteAddr) {

	onh::Tag tg(
			1,
			2,
			"TestTag1",
			onh::TT_BIT,
			{onh::PDA_INPUT, 8, 2}
	);

	tg.setByteAddress(700);

	onh::processDataAddress pda = tg.getAddress();

	ASSERT_EQ((unsigned int)1, tg.getId());
	ASSERT_EQ((unsigned int)2, tg.getConnId());
	ASSERT_STREQ("TestTag1", tg.getName().c_str());
	ASSERT_EQ(onh::TT_BIT, tg.getType());
	ASSERT_EQ(onh::PDA_INPUT, tg.getArea());
	ASSERT_EQ((unsigned int)700, tg.getByteAddress());
	ASSERT_EQ((unsigned int)2, tg.getBitAddress());
	ASSERT_EQ(onh::PDA_INPUT, pda.area);
	ASSERT_EQ((unsigned int)700, pda.byteAddr);
	ASSERT_EQ((unsigned int)2, pda.bitAddr);
}

/**
 * Check tag creation set bit address
 */
TEST(TagTests, CreateSetBitAddr) {

	onh::Tag tg(
			1,
			2,
			"TestTag1",
			onh::TT_BIT,
			{onh::PDA_INPUT, 8, 2}
	);

	tg.setBitAddress(5);

	onh::processDataAddress pda = tg.getAddress();

	ASSERT_EQ((unsigned int)1, tg.getId());
	ASSERT_EQ((unsigned int)2, tg.getConnId());
	ASSERT_STREQ("TestTag1", tg.getName().c_str());
	ASSERT_EQ(onh::TT_BIT, tg.getType());
	ASSERT_EQ(onh::PDA_INPUT, tg.getArea());
	ASSERT_EQ((unsigned int)8, tg.getByteAddress());
	ASSERT_EQ((unsigned int)5, tg.getBitAddress());
	ASSERT_EQ(onh::PDA_INPUT, pda.area);
	ASSERT_EQ((unsigned int)8, pda.byteAddr);
	ASSERT_EQ((unsigned int)5, pda.bitAddr);
}

/**
 * Check tag creation wrong id
 */
TEST(TagTests, CreateException1) {

	try {

		onh::Tag tg(
				0,
				2,
				"TestTag1",
				onh::TT_BIT,
				{onh::PDA_INPUT, 4, 6}
		);

		FAIL() << "Expected onh::TagException";

	} catch (onh::TagException &e) {

		ASSERT_STREQ(e.what(), "Tag::checkId: Invalid tag identifier");
		ASSERT_EQ(onh::TagException::WRONG_ID, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

/**
 * Check tag creation wrong conn id
 */
TEST(TagTests, CreateException1c) {

	try {

		onh::Tag tg(
				1,
				0,
				"TestTag1",
				onh::TT_BIT,
				{onh::PDA_INPUT, 4, 6}
		);

		FAIL() << "Expected onh::TagException";

	} catch (onh::TagException &e) {

		ASSERT_STREQ(e.what(), "Tag::checkConnId: Invalid driver connection identifier");
		ASSERT_EQ(onh::TagException::WRONG_ID, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

/**
 * Check tag creation wrong name
 */
TEST(TagTests, CreateException2) {

	try {

		onh::Tag tg(
				45,
				2,
				"",
				onh::TT_BIT,
				{onh::PDA_INPUT, 4, 6}
		);

		FAIL() << "Expected onh::TagException";

	} catch (onh::TagException &e) {

		ASSERT_STREQ(e.what(), "Tag::checkName: Tag name is empty");
		ASSERT_EQ(onh::TagException::WRONG_NAME, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

/**
 * Check tag creation wrong name
 */
TEST(TagTests, CreateException3) {

	try {

		onh::Tag tg(
				45,
				2,
				"Test-Tag5",
				onh::TT_BIT,
				{onh::PDA_INPUT, 4, 6}
		);

		FAIL() << "Expected onh::TagException";

	} catch (onh::TagException &e) {

		ASSERT_STREQ(e.what(), "Tag::checkName: Tag contains invalid characters");
		ASSERT_EQ(onh::TagException::WRONG_NAME, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

/**
 * Check tag creation wrong type
 */
TEST(TagTests, CreateException4) {

	try {

		onh::Tag tg(
				45,
				2,
				"TestTag5",
				(onh::TagType)70,
				{onh::PDA_INPUT, 4, 6}
		);

		FAIL() << "Expected onh::TagException";

	} catch (onh::TagException &e) {

		ASSERT_STREQ(e.what(), "Tag::checkType: Tag has wrong type");
		ASSERT_EQ(onh::TagException::WRONG_TYPE, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

/**
 * Check tag creation wrong area
 */
TEST(TagTests, CreateException5) {

	try {

		onh::Tag tg(
				45,
				2,
				"TestTag5",
				onh::TT_BIT,
				{(onh::processDataArea)80, 4, 6}
		);

		FAIL() << "Expected onh::TagException";

	} catch (onh::TagException &e) {

		ASSERT_STREQ(e.what(), "Tag::checkArea: Tag has wrong area");
		ASSERT_EQ(onh::TagException::WRONG_AREA, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

/**
 * Check tag creation wrong bit address
 */
TEST(TagTests, CreateException6) {

	try {

		onh::Tag tg(
				45,
				2,
				"TestTag5",
				onh::TT_BIT,
				{onh::PDA_INPUT, 4, 9}
		);

		FAIL() << "Expected onh::TagException";

	} catch (onh::TagException &e) {

		ASSERT_STREQ(e.what(), "Tag::checkBitAddress: Bit address is out of range");
		ASSERT_EQ(onh::TagException::BIT_ADDRESS_OUT_OF_RANGE, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

/**
 * Check tag default creation
 */
TEST(TagTests, CreateDefException1) {

	try {

		onh::Tag tg;

		tg.getId();

		FAIL() << "Expected onh::TagException";

	} catch (onh::TagException &e) {

		ASSERT_STREQ(e.what(), "Tag::checkId: Invalid tag identifier");
		ASSERT_EQ(onh::TagException::WRONG_ID, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

/**
 * Check tag default creation
 */
TEST(TagTests, CreateDefException2) {

	try {

		onh::Tag tg;

		tg.getName();

		FAIL() << "Expected onh::TagException";

	} catch (onh::TagException &e) {

		ASSERT_STREQ(e.what(), "Tag::checkName: Tag name is empty");
		ASSERT_EQ(onh::TagException::WRONG_NAME, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

/**
 * Check tag default creation
 */
TEST(TagTests, CreateDef1) {

	onh::Tag tg;

	ASSERT_EQ(onh::TT_BIT, tg.getType());
	ASSERT_EQ(onh::PDA_INPUT, tg.getArea());
	ASSERT_EQ((unsigned int)0, tg.getByteAddress());
	ASSERT_EQ((unsigned int)0, tg.getBitAddress());
}

#endif /* TESTS_DB_OBJS_TAGTESTS_H_ */
