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

#ifndef TESTS_DB_OBJS_SCRIPTITEMTESTS_H_
#define TESTS_DB_OBJS_SCRIPTITEMTESTS_H_

#include <gtest/gtest.h>
#include "ScriptItemTestsFixtures.h"

/**
 * Check script item creation
 */
TEST_F(scriptItemTests, Create1) {

	onh::ScriptItem scItem(
			1,
			*tg,
			"test1.sh",
			false,
			false,
			*fbTg,
			true
	);

	ASSERT_EQ((unsigned int)1, scItem.getId());

	ASSERT_EQ((unsigned int)5, scItem.getTag().getId());
	ASSERT_STREQ("TestTag1", scItem.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, scItem.getTag().getType());
	ASSERT_EQ(onh::PDA_INPUT, scItem.getTag().getArea());
	ASSERT_EQ((unsigned int)4, scItem.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)6, scItem.getTag().getBitAddress());

	ASSERT_EQ((unsigned int)9, scItem.getFeedbackRunTag().getId());
	ASSERT_STREQ("TestTag2", scItem.getFeedbackRunTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, scItem.getFeedbackRunTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, scItem.getFeedbackRunTag().getArea());
	ASSERT_EQ((unsigned int)70, scItem.getFeedbackRunTag().getByteAddress());
	ASSERT_EQ((unsigned int)0, scItem.getFeedbackRunTag().getBitAddress());

	ASSERT_STREQ("test1.sh", scItem.getName().c_str());
	ASSERT_FALSE(scItem.isRunning());
	ASSERT_FALSE(scItem.isLocked());
	ASSERT_TRUE(scItem.isEnabled());
}

/**
 * Check script item set id
 */
TEST_F(scriptItemTests, CreateSetId) {

	onh::ScriptItem scItem(
			1,
			*tg,
			"test1.sh",
			false,
			false,
			*fbTg,
			true
	);

	scItem.setId(87);

	ASSERT_EQ((unsigned int)87, scItem.getId());

	ASSERT_EQ((unsigned int)5, scItem.getTag().getId());
	ASSERT_STREQ("TestTag1", scItem.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, scItem.getTag().getType());
	ASSERT_EQ(onh::PDA_INPUT, scItem.getTag().getArea());
	ASSERT_EQ((unsigned int)4, scItem.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)6, scItem.getTag().getBitAddress());

	ASSERT_EQ((unsigned int)9, scItem.getFeedbackRunTag().getId());
	ASSERT_STREQ("TestTag2", scItem.getFeedbackRunTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, scItem.getFeedbackRunTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, scItem.getFeedbackRunTag().getArea());
	ASSERT_EQ((unsigned int)70, scItem.getFeedbackRunTag().getByteAddress());
	ASSERT_EQ((unsigned int)0, scItem.getFeedbackRunTag().getBitAddress());

	ASSERT_STREQ("test1.sh", scItem.getName().c_str());
	ASSERT_FALSE(scItem.isRunning());
	ASSERT_FALSE(scItem.isLocked());
	ASSERT_TRUE(scItem.isEnabled());
}

/**
 * Check script item set tag
 */
TEST_F(scriptItemTests, CreateSetTag) {

	onh::ScriptItem scItem(
			1,
			*tg,
			"test1.sh",
			false,
			false,
			*fbTg,
			true
	);

	onh::Tag tg2(
			500,
			"TestTag9",
			onh::TT_BIT,
			{onh::PDA_MEMORY, 789, 0}
	);

	scItem.setTag(tg2);

	ASSERT_EQ((unsigned int)1, scItem.getId());

	ASSERT_EQ((unsigned int)500, scItem.getTag().getId());
	ASSERT_STREQ("TestTag9", scItem.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, scItem.getTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, scItem.getTag().getArea());
	ASSERT_EQ((unsigned int)789, scItem.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)0, scItem.getTag().getBitAddress());

	ASSERT_EQ((unsigned int)9, scItem.getFeedbackRunTag().getId());
	ASSERT_STREQ("TestTag2", scItem.getFeedbackRunTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, scItem.getFeedbackRunTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, scItem.getFeedbackRunTag().getArea());
	ASSERT_EQ((unsigned int)70, scItem.getFeedbackRunTag().getByteAddress());
	ASSERT_EQ((unsigned int)0, scItem.getFeedbackRunTag().getBitAddress());

	ASSERT_STREQ("test1.sh", scItem.getName().c_str());
	ASSERT_FALSE(scItem.isRunning());
	ASSERT_FALSE(scItem.isLocked());
	ASSERT_TRUE(scItem.isEnabled());
}

/**
 * Check script item set script name
 */
TEST_F(scriptItemTests, CreateSetName) {

	onh::ScriptItem scItem(
			1,
			*tg,
			"test1.sh",
			false,
			false,
			*fbTg,
			true
	);

	scItem.setName("test66.sh");

	ASSERT_EQ((unsigned int)1, scItem.getId());

	ASSERT_EQ((unsigned int)5, scItem.getTag().getId());
	ASSERT_STREQ("TestTag1", scItem.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, scItem.getTag().getType());
	ASSERT_EQ(onh::PDA_INPUT, scItem.getTag().getArea());
	ASSERT_EQ((unsigned int)4, scItem.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)6, scItem.getTag().getBitAddress());

	ASSERT_EQ((unsigned int)9, scItem.getFeedbackRunTag().getId());
	ASSERT_STREQ("TestTag2", scItem.getFeedbackRunTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, scItem.getFeedbackRunTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, scItem.getFeedbackRunTag().getArea());
	ASSERT_EQ((unsigned int)70, scItem.getFeedbackRunTag().getByteAddress());
	ASSERT_EQ((unsigned int)0, scItem.getFeedbackRunTag().getBitAddress());

	ASSERT_STREQ("test66.sh", scItem.getName().c_str());
	ASSERT_FALSE(scItem.isRunning());
	ASSERT_FALSE(scItem.isLocked());
	ASSERT_TRUE(scItem.isEnabled());
}

/**
 * Check script item set run flag
 */
TEST_F(scriptItemTests, CreateSetRun) {

	onh::ScriptItem scItem(
			1,
			*tg,
			"test1.sh",
			false,
			false,
			*fbTg,
			true
	);

	scItem.setRun(true);

	ASSERT_EQ((unsigned int)1, scItem.getId());

	ASSERT_EQ((unsigned int)5, scItem.getTag().getId());
	ASSERT_STREQ("TestTag1", scItem.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, scItem.getTag().getType());
	ASSERT_EQ(onh::PDA_INPUT, scItem.getTag().getArea());
	ASSERT_EQ((unsigned int)4, scItem.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)6, scItem.getTag().getBitAddress());

	ASSERT_EQ((unsigned int)9, scItem.getFeedbackRunTag().getId());
	ASSERT_STREQ("TestTag2", scItem.getFeedbackRunTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, scItem.getFeedbackRunTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, scItem.getFeedbackRunTag().getArea());
	ASSERT_EQ((unsigned int)70, scItem.getFeedbackRunTag().getByteAddress());
	ASSERT_EQ((unsigned int)0, scItem.getFeedbackRunTag().getBitAddress());

	ASSERT_STREQ("test1.sh", scItem.getName().c_str());
	ASSERT_TRUE(scItem.isRunning());
	ASSERT_FALSE(scItem.isLocked());
	ASSERT_TRUE(scItem.isEnabled());
}

/**
 * Check script item set lock flag
 */
TEST_F(scriptItemTests, CreateSetLock) {

	onh::ScriptItem scItem(
			1,
			*tg,
			"test1.sh",
			false,
			false,
			*fbTg,
			true
	);

	scItem.setLock(true);

	ASSERT_EQ((unsigned int)1, scItem.getId());

	ASSERT_EQ((unsigned int)5, scItem.getTag().getId());
	ASSERT_STREQ("TestTag1", scItem.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, scItem.getTag().getType());
	ASSERT_EQ(onh::PDA_INPUT, scItem.getTag().getArea());
	ASSERT_EQ((unsigned int)4, scItem.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)6, scItem.getTag().getBitAddress());

	ASSERT_EQ((unsigned int)9, scItem.getFeedbackRunTag().getId());
	ASSERT_STREQ("TestTag2", scItem.getFeedbackRunTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, scItem.getFeedbackRunTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, scItem.getFeedbackRunTag().getArea());
	ASSERT_EQ((unsigned int)70, scItem.getFeedbackRunTag().getByteAddress());
	ASSERT_EQ((unsigned int)0, scItem.getFeedbackRunTag().getBitAddress());

	ASSERT_STREQ("test1.sh", scItem.getName().c_str());
	ASSERT_FALSE(scItem.isRunning());
	ASSERT_TRUE(scItem.isLocked());
	ASSERT_TRUE(scItem.isEnabled());
}

/**
 * Check script item set feedback tag
 */
TEST_F(scriptItemTests, CreateSetFeedbackTag) {

	onh::ScriptItem scItem(
			1,
			*tg,
			"test1.sh",
			false,
			false,
			*fbTg,
			true
	);

	onh::Tag fbTg2(
			500,
			"TestFB1",
			onh::TT_BIT,
			{onh::PDA_MEMORY, 40, 0}
	);

	scItem.setFeedbackRunTag(fbTg2);

	ASSERT_EQ((unsigned int)1, scItem.getId());

	ASSERT_EQ((unsigned int)5, scItem.getTag().getId());
	ASSERT_STREQ("TestTag1", scItem.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, scItem.getTag().getType());
	ASSERT_EQ(onh::PDA_INPUT, scItem.getTag().getArea());
	ASSERT_EQ((unsigned int)4, scItem.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)6, scItem.getTag().getBitAddress());

	ASSERT_EQ((unsigned int)500, scItem.getFeedbackRunTag().getId());
	ASSERT_STREQ("TestFB1", scItem.getFeedbackRunTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, scItem.getFeedbackRunTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, scItem.getFeedbackRunTag().getArea());
	ASSERT_EQ((unsigned int)40, scItem.getFeedbackRunTag().getByteAddress());
	ASSERT_EQ((unsigned int)0, scItem.getFeedbackRunTag().getBitAddress());

	ASSERT_STREQ("test1.sh", scItem.getName().c_str());
	ASSERT_FALSE(scItem.isRunning());
	ASSERT_FALSE(scItem.isLocked());
	ASSERT_TRUE(scItem.isEnabled());
}

/**
 * Check script item set enable flag
 */
TEST_F(scriptItemTests, CreateSetEnable) {

	onh::ScriptItem scItem(
			1,
			*tg,
			"test1.sh",
			false,
			false,
			*fbTg,
			true
	);

	scItem.setEnable(false);

	ASSERT_EQ((unsigned int)1, scItem.getId());

	ASSERT_EQ((unsigned int)5, scItem.getTag().getId());
	ASSERT_STREQ("TestTag1", scItem.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, scItem.getTag().getType());
	ASSERT_EQ(onh::PDA_INPUT, scItem.getTag().getArea());
	ASSERT_EQ((unsigned int)4, scItem.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)6, scItem.getTag().getBitAddress());

	ASSERT_EQ((unsigned int)9, scItem.getFeedbackRunTag().getId());
	ASSERT_STREQ("TestTag2", scItem.getFeedbackRunTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, scItem.getFeedbackRunTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, scItem.getFeedbackRunTag().getArea());
	ASSERT_EQ((unsigned int)70, scItem.getFeedbackRunTag().getByteAddress());
	ASSERT_EQ((unsigned int)0, scItem.getFeedbackRunTag().getBitAddress());

	ASSERT_STREQ("test1.sh", scItem.getName().c_str());
	ASSERT_FALSE(scItem.isRunning());
	ASSERT_FALSE(scItem.isLocked());
	ASSERT_FALSE(scItem.isEnabled());
}

/**
 * Check script item creation wrong id
 */
TEST_F(scriptItemTests, CreateException1) {

	try {

		onh::ScriptItem scItem(
				0,
				*tg,
				"test1.sh",
				false,
				false,
				*fbTg,
				true
		);

		FAIL() << "Expected onh::ScriptException";

	} catch (onh::ScriptException &e) {

		ASSERT_STREQ(e.what(), "ScriptItem::checkId: Invalid script identifier");
		ASSERT_EQ(onh::ScriptException::WRONG_ID, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::ScriptException";
	}
}

/**
 * Check script item creation wrong tag type
 */
TEST_F(scriptItemTests, CreateException2) {

	try {

		onh::ScriptItem scItem(
				1,
				*tg,
				"test1.sh",
				false,
				false,
				*fbTg,
				true
		);

		onh::Tag tg2(
				500,
				"Test1",
				onh::TT_BYTE,
				{onh::PDA_MEMORY, 40, 0}
		);

		scItem.setTag(tg2);

		FAIL() << "Expected onh::ScriptException";

	} catch (onh::ScriptException &e) {

		ASSERT_STREQ(e.what(), "ScriptItem::checkBitTagType: Wrong tag type - need BIT type");
		ASSERT_EQ(onh::ScriptException::WRONG_TAG_TYPE, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::ScriptException";
	}
}

/**
 * Check script item creation wrong script name
 */
TEST_F(scriptItemTests, CreateException3) {

	try {

		onh::ScriptItem scItem(
				5,
				*tg,
				"",
				false,
				false,
				*fbTg,
				true
		);

		FAIL() << "Expected onh::ScriptException";

	} catch (onh::ScriptException &e) {

		ASSERT_STREQ(e.what(), "ScriptItem::checkScriptName: Script name is empty");
		ASSERT_EQ(onh::ScriptException::WRONG_NAME, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::ScriptException";
	}
}

/**
 * Check script item creation wrong feedback tag type
 */
TEST_F(scriptItemTests, CreateException4) {

	try {

		onh::ScriptItem scItem(
				1,
				*tg,
				"test1.sh",
				false,
				false,
				*fbTg,
				true
		);

		onh::Tag tg2(
				500,
				"Test1",
				onh::TT_BYTE,
				{onh::PDA_MEMORY, 40, 0}
		);

		scItem.setFeedbackRunTag(tg2);

		FAIL() << "Expected onh::ScriptException";

	} catch (onh::ScriptException &e) {

		ASSERT_STREQ(e.what(), "ScriptItem::checkBitTagType: Wrong tag type - need BIT type");
		ASSERT_EQ(onh::ScriptException::WRONG_TAG_TYPE, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::ScriptException";
	}
}

/**
 * Check script item creation no Tag assigned
 */
TEST_F(scriptItemTests, CreateException5) {

	try {

		onh::ScriptItem scItem;

		scItem.getTag();

		FAIL() << "Expected onh::ScriptException";

	} catch (onh::ScriptException &e) {

		ASSERT_STREQ(e.what(), "ScriptItem::getTag: Missing tag object in script item");
		ASSERT_EQ(onh::ScriptException::NO_TAG, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::ScriptException";
	}
}

/**
 * Check script item creation no feedback Tag assigned
 */
TEST_F(scriptItemTests, CreateException6) {

	try {

		onh::ScriptItem scItem;

		scItem.getFeedbackRunTag();

		FAIL() << "Expected onh::ScriptException";

	} catch (onh::ScriptException &e) {

		ASSERT_STREQ(e.what(), "ScriptItem::getFeedbackRunTag: No feedback run tag");
		ASSERT_EQ(onh::ScriptException::NO_FEEDBACK_RUN_TAG, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::ScriptException";
	}
}

#endif /* TESTS_DB_OBJS_SCRIPTITEMTESTS_H_ */
