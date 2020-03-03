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

#ifndef TESTS_DB_OBJS_TAGLOGGERITEMTESTS_H_
#define TESTS_DB_OBJS_TAGLOGGERITEMTESTS_H_

#include <gtest/gtest.h>
#include "TagLoggerItemTestsFixtures.h"

/**
 * Check tag logger item creation
 */
TEST_F(tagLoggerItemTests, Create1) {

	onh::TagLoggerItem tgLog(
			1,
			*tg,
			onh::TagLoggerItem::I_100MS,
			0,
			"2019-10-01 12:50:42.563",
			"1",
			true
	);

	ASSERT_EQ((unsigned int)1, tgLog.getId());

	ASSERT_EQ((unsigned int)5, tgLog.getTag().getId());
	ASSERT_STREQ("TestTag1", tgLog.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, tgLog.getTag().getType());
	ASSERT_EQ(onh::PDA_INPUT, tgLog.getTag().getArea());
	ASSERT_EQ((unsigned int)4, tgLog.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)6, tgLog.getTag().getBitAddress());

	ASSERT_EQ(onh::TagLoggerItem::I_100MS, tgLog.getInterval());
	ASSERT_EQ((unsigned int)0, tgLog.getIntervalSec());
	ASSERT_STREQ("2019-10-01 12:50:42.563", tgLog.getLastUpdate().c_str());
	ASSERT_STREQ("1", tgLog.getLastValue().c_str());
	ASSERT_TRUE(tgLog.isEnabled());
}

/**
 * Check tag logger item set id
 */
TEST_F(tagLoggerItemTests, CreateSetId) {

	onh::TagLoggerItem tgLog(
			1,
			*tg,
			onh::TagLoggerItem::I_100MS,
			0,
			"2019-10-01 12:50:42.563",
			"1",
			true
	);

	tgLog.setId(65);

	ASSERT_EQ((unsigned int)65, tgLog.getId());

	ASSERT_EQ((unsigned int)5, tgLog.getTag().getId());
	ASSERT_STREQ("TestTag1", tgLog.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, tgLog.getTag().getType());
	ASSERT_EQ(onh::PDA_INPUT, tgLog.getTag().getArea());
	ASSERT_EQ((unsigned int)4, tgLog.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)6, tgLog.getTag().getBitAddress());

	ASSERT_EQ(onh::TagLoggerItem::I_100MS, tgLog.getInterval());
	ASSERT_EQ((unsigned int)0, tgLog.getIntervalSec());
	ASSERT_STREQ("2019-10-01 12:50:42.563", tgLog.getLastUpdate().c_str());
	ASSERT_STREQ("1", tgLog.getLastValue().c_str());
	ASSERT_TRUE(tgLog.isEnabled());
}

/**
 * Check tag logger item set tag
 */
TEST_F(tagLoggerItemTests, CreateSetTag) {

	onh::TagLoggerItem tgLog(
			1,
			*tg,
			onh::TagLoggerItem::I_100MS,
			0,
			"2019-10-01 12:50:42.563",
			"1",
			true
	);

	onh::Tag tg2(
			500,
			"TestTag9",
			onh::TT_BYTE,
			{onh::PDA_MEMORY, 789, 0}
	);

	tgLog.setTag(tg2);

	ASSERT_EQ((unsigned int)1, tgLog.getId());

	ASSERT_EQ((unsigned int)500, tgLog.getTag().getId());
	ASSERT_STREQ("TestTag9", tgLog.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BYTE, tgLog.getTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, tgLog.getTag().getArea());
	ASSERT_EQ((unsigned int)789, tgLog.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)0, tgLog.getTag().getBitAddress());

	ASSERT_EQ(onh::TagLoggerItem::I_100MS, tgLog.getInterval());
	ASSERT_EQ((unsigned int)0, tgLog.getIntervalSec());
	ASSERT_STREQ("2019-10-01 12:50:42.563", tgLog.getLastUpdate().c_str());
	ASSERT_STREQ("1", tgLog.getLastValue().c_str());
	ASSERT_TRUE(tgLog.isEnabled());
}

/**
 * Check tag logger item set interval
 */
TEST_F(tagLoggerItemTests, CreateSetInterval) {

	onh::TagLoggerItem tgLog(
			1,
			*tg,
			onh::TagLoggerItem::I_100MS,
			0,
			"2019-10-01 12:50:42.563",
			"1",
			true
	);

	tgLog.setInterval(onh::TagLoggerItem::I_500MS);

	ASSERT_EQ((unsigned int)1, tgLog.getId());

	ASSERT_EQ((unsigned int)5, tgLog.getTag().getId());
	ASSERT_STREQ("TestTag1", tgLog.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, tgLog.getTag().getType());
	ASSERT_EQ(onh::PDA_INPUT, tgLog.getTag().getArea());
	ASSERT_EQ((unsigned int)4, tgLog.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)6, tgLog.getTag().getBitAddress());

	ASSERT_EQ(onh::TagLoggerItem::I_500MS, tgLog.getInterval());
	ASSERT_EQ((unsigned int)0, tgLog.getIntervalSec());
	ASSERT_STREQ("2019-10-01 12:50:42.563", tgLog.getLastUpdate().c_str());
	ASSERT_STREQ("1", tgLog.getLastValue().c_str());
	ASSERT_TRUE(tgLog.isEnabled());
}

/**
 * Check tag logger item set interval seconds
 */
TEST_F(tagLoggerItemTests, CreateSetIntervalSec) {

	onh::TagLoggerItem tgLog(
			1,
			*tg,
			onh::TagLoggerItem::I_100MS,
			0,
			"2019-10-01 12:50:42.563",
			"1",
			true
	);

	tgLog.setIntervalSec(5);

	ASSERT_EQ((unsigned int)1, tgLog.getId());

	ASSERT_EQ((unsigned int)5, tgLog.getTag().getId());
	ASSERT_STREQ("TestTag1", tgLog.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, tgLog.getTag().getType());
	ASSERT_EQ(onh::PDA_INPUT, tgLog.getTag().getArea());
	ASSERT_EQ((unsigned int)4, tgLog.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)6, tgLog.getTag().getBitAddress());

	ASSERT_EQ(onh::TagLoggerItem::I_100MS, tgLog.getInterval());
	ASSERT_EQ((unsigned int)5, tgLog.getIntervalSec());
	ASSERT_STREQ("2019-10-01 12:50:42.563", tgLog.getLastUpdate().c_str());
	ASSERT_STREQ("1", tgLog.getLastValue().c_str());
	ASSERT_TRUE(tgLog.isEnabled());
}

/**
 * Check tag logger item set last update
 */
TEST_F(tagLoggerItemTests, CreateSetLastUpdate) {

	onh::TagLoggerItem tgLog(
			1,
			*tg,
			onh::TagLoggerItem::I_100MS,
			0,
			"2019-10-01 12:50:42.563",
			"1",
			true
	);

	tgLog.setLastUpdate("2019-10-04 07:15:49.402");

	ASSERT_EQ((unsigned int)1, tgLog.getId());

	ASSERT_EQ((unsigned int)5, tgLog.getTag().getId());
	ASSERT_STREQ("TestTag1", tgLog.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, tgLog.getTag().getType());
	ASSERT_EQ(onh::PDA_INPUT, tgLog.getTag().getArea());
	ASSERT_EQ((unsigned int)4, tgLog.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)6, tgLog.getTag().getBitAddress());

	ASSERT_EQ(onh::TagLoggerItem::I_100MS, tgLog.getInterval());
	ASSERT_EQ((unsigned int)0, tgLog.getIntervalSec());
	ASSERT_STREQ("2019-10-04 07:15:49.402", tgLog.getLastUpdate().c_str());
	ASSERT_STREQ("1", tgLog.getLastValue().c_str());
	ASSERT_TRUE(tgLog.isEnabled());
}

/**
 * Check tag logger item set last value
 */
TEST_F(tagLoggerItemTests, CreateSetLastValue) {

	onh::TagLoggerItem tgLog(
			1,
			*tg,
			onh::TagLoggerItem::I_100MS,
			0,
			"2019-10-04 07:15:49.402",
			"1",
			true
	);

	tgLog.setLastValue("0");

	ASSERT_EQ((unsigned int)1, tgLog.getId());

	ASSERT_EQ((unsigned int)5, tgLog.getTag().getId());
	ASSERT_STREQ("TestTag1", tgLog.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, tgLog.getTag().getType());
	ASSERT_EQ(onh::PDA_INPUT, tgLog.getTag().getArea());
	ASSERT_EQ((unsigned int)4, tgLog.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)6, tgLog.getTag().getBitAddress());

	ASSERT_EQ(onh::TagLoggerItem::I_100MS, tgLog.getInterval());
	ASSERT_EQ((unsigned int)0, tgLog.getIntervalSec());
	ASSERT_STREQ("2019-10-04 07:15:49.402", tgLog.getLastUpdate().c_str());
	ASSERT_STREQ("0", tgLog.getLastValue().c_str());
	ASSERT_TRUE(tgLog.isEnabled());
}

/**
 * Check tag logger item set enable
 */
TEST_F(tagLoggerItemTests, CreateSetEnable) {

	onh::TagLoggerItem tgLog(
			1,
			*tg,
			onh::TagLoggerItem::I_100MS,
			0,
			"2019-10-04 07:15:49.402",
			"0",
			true
	);

	tgLog.setEnable(false);

	ASSERT_EQ((unsigned int)1, tgLog.getId());

	ASSERT_EQ((unsigned int)5, tgLog.getTag().getId());
	ASSERT_STREQ("TestTag1", tgLog.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, tgLog.getTag().getType());
	ASSERT_EQ(onh::PDA_INPUT, tgLog.getTag().getArea());
	ASSERT_EQ((unsigned int)4, tgLog.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)6, tgLog.getTag().getBitAddress());

	ASSERT_EQ(onh::TagLoggerItem::I_100MS, tgLog.getInterval());
	ASSERT_EQ((unsigned int)0, tgLog.getIntervalSec());
	ASSERT_STREQ("2019-10-04 07:15:49.402", tgLog.getLastUpdate().c_str());
	ASSERT_STREQ("0", tgLog.getLastValue().c_str());
	ASSERT_FALSE(tgLog.isEnabled());
}

/**
 * Check tag logger item creation wrong id
 */
TEST_F(tagLoggerItemTests, CreateException1) {

	try {

		onh::TagLoggerItem tgLog(
				0,
				*tg,
				onh::TagLoggerItem::I_100MS,
				0,
				"2019-10-04 07:15:49.402",
				"0",
				true
		);

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "TagLoggerItem::checkId: Invalid tag logger identifier");

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check tag logger item creation wrong interval
 */
TEST_F(tagLoggerItemTests, CreateException2) {

	try {

		onh::TagLoggerItem tgLog(
				4,
				*tg,
				(onh::TagLoggerItem::intervals)63,
				0,
				"2019-10-04 07:15:49.402",
				"0",
				true
		);

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "TagLoggerItem::checkInterval: Interval wrong value");

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check tag logger item creation wrong last update timestamp
 */
TEST_F(tagLoggerItemTests, CreateTimestampException1) {

	try {

		onh::TagLoggerItem tgLog(
				6,
				*tg,
				onh::TagLoggerItem::I_100MS,
				0,
				"",
				"0",
				true
		);

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "TagLoggerItem::checkLastUpdate: Timestamp string is empty");

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check tag logger item creation wrong last update timestamp
 */
TEST_F(tagLoggerItemTests, CreateTimestampException2) {

	try {

		onh::TagLoggerItem tgLog(
				6,
				*tg,
				onh::TagLoggerItem::I_100MS,
				0,
				"2019-10-04 07:15:49.402r",
				"0",
				true
		);

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "TagLoggerItem::checkLastUpdate: Timestamp string wrong length");

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check tag logger item creation wrong last update timestamp
 */
TEST_F(tagLoggerItemTests, CreateTimestampException3) {

	try {

		onh::TagLoggerItem tgLog(
				6,
				*tg,
				onh::TagLoggerItem::I_100MS,
				0,
				"2019.10-04 07:15:49.402",
				"0",
				true
		);

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "TagLoggerItem::checkLastUpdate: Timestamp string wrong format. Pos 4 need to contain '-' character");

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check tag logger item creation wrong last update timestamp
 */
TEST_F(tagLoggerItemTests, CreateTimestampException4) {

	try {

		onh::TagLoggerItem tgLog(
				6,
				*tg,
				onh::TagLoggerItem::I_100MS,
				0,
				"2019-10,04 07:15:49.402",
				"0",
				true
		);

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "TagLoggerItem::checkLastUpdate: Timestamp string wrong format. Pos 7 need to contain '-' character");

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check tag logger item creation wrong last update timestamp
 */
TEST_F(tagLoggerItemTests, CreateTimestampException5) {

	try {

		onh::TagLoggerItem tgLog(
				6,
				*tg,
				onh::TagLoggerItem::I_100MS,
				0,
				"2019-10-04@07:15:49.402",
				"0",
				true
		);

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "TagLoggerItem::checkLastUpdate: Timestamp string wrong format. Pos 10 need to contain space");

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check tag logger item creation wrong last update timestamp
 */
TEST_F(tagLoggerItemTests, CreateTimestampException6) {

	try {

		onh::TagLoggerItem tgLog(
				6,
				*tg,
				onh::TagLoggerItem::I_100MS,
				0,
				"2019-10-04 07-15:49.402",
				"0",
				true
		);

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "TagLoggerItem::checkLastUpdate: Timestamp string wrong format. Pos 13 need to contain ':' character");

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check tag logger item creation wrong last update timestamp
 */
TEST_F(tagLoggerItemTests, CreateTimestampException7) {

	try {

		onh::TagLoggerItem tgLog(
				6,
				*tg,
				onh::TagLoggerItem::I_100MS,
				0,
				"2019-10-04 07:15.49.402",
				"0",
				true
		);

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "TagLoggerItem::checkLastUpdate: Timestamp string wrong format. Pos 16 need to contain ':' character");

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check tag logger item creation wrong last update timestamp
 */
TEST_F(tagLoggerItemTests, CreateTimestampException8) {

	try {

		onh::TagLoggerItem tgLog(
				6,
				*tg,
				onh::TagLoggerItem::I_100MS,
				0,
				"2019-10-04 07:15:49_402",
				"0",
				true
		);

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "TagLoggerItem::checkLastUpdate: Timestamp string wrong format. Pos 19 need to contain '.' character");

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check tag logger item creation wrong last update timestamp
 */
TEST_F(tagLoggerItemTests, CreateTimestampException9) {

	try {

		onh::TagLoggerItem tgLog(
				6,
				*tg,
				onh::TagLoggerItem::I_100MS,
				0,
				"20t9-10-04 07:15:49.402",
				"0",
				true
		);

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "TagLoggerItem::checkLastUpdate: Timestamp string wrong format. Pos 2 need to be number");

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check tag logger item creation wrong value
 */
TEST_F(tagLoggerItemTests, CreateException3) {

	try {

		onh::TagLoggerItem tgLog(
				4,
				*tg,
				onh::TagLoggerItem::I_100MS,
				0,
				"2019-10-04 07:15:49.402",
				"",
				true
		);

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "TagLoggerItem::checkLastValue: Value string is empty");

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check tag logger item default creation
 */
TEST_F(tagLoggerItemTests, CreateDefException1) {

	try {

		onh::TagLoggerItem tgLog;

		tgLog.getId();

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "TagLoggerItem::checkId: Invalid tag logger identifier");

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check tag logger item default creation
 */
TEST_F(tagLoggerItemTests, CreateDefException2) {

	try {

		onh::TagLoggerItem tgLog;

		tgLog.getTag().getId();

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "Tag::checkId: Invalid tag identifier");

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check tag logger item default creation
 */
TEST_F(tagLoggerItemTests, CreateDefException3) {

	try {

		onh::TagLoggerItem tgLog;

		tgLog.getLastUpdate();

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "TagLoggerItem::checkLastUpdate: Timestamp string is empty");

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check tag logger item default creation
 */
TEST_F(tagLoggerItemTests, CreateDefException4) {

	try {

		onh::TagLoggerItem tgLog;

		tgLog.getLastValue();

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "TagLoggerItem::checkLastValue: Value string is empty");

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check tag logger item default creation
 */
TEST_F(tagLoggerItemTests, CreateDefException5) {

	try {

		onh::TagLoggerItem tgLog;

		tgLog.getCurrentUpdate();

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "TagLoggerItem::getCurrentUpdate: Current update timestamp is empty");

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

/**
 * Check tag logger item update trigger
 */
TEST_F(tagLoggerItemTests, UpdateTest1) {

	onh::TagLoggerItem tgLog(
			1,
			*tg,
			onh::TagLoggerItem::I_100MS,
			0,
			createTimestamp(0, -50),
			"1",
			true
	);

	ASSERT_FALSE(tgLog.isNeededUpdate("0"));
}

/**
 * Check tag logger item update trigger
 */
TEST_F(tagLoggerItemTests, UpdateTest2) {

	onh::TagLoggerItem tgLog(
			1,
			*tg,
			onh::TagLoggerItem::I_100MS,
			0,
			createTimestamp(0, -100),
			"1",
			true
	);

	ASSERT_TRUE(tgLog.isNeededUpdate("0"));
	ASSERT_TRUE((tgLog.getCurrentUpdate()!="")?(true):(false));
}

/**
 * Check tag logger item update trigger
 */
TEST_F(tagLoggerItemTests, UpdateTest3) {

	onh::TagLoggerItem tgLog(
			1,
			*tg,
			onh::TagLoggerItem::I_200MS,
			0,
			createTimestamp(0, -120),
			"1",
			true
	);

	ASSERT_FALSE(tgLog.isNeededUpdate("0"));
}

/**
 * Check tag logger item update trigger
 */
TEST_F(tagLoggerItemTests, UpdateTest4) {

	onh::TagLoggerItem tgLog(
			1,
			*tg,
			onh::TagLoggerItem::I_200MS,
			0,
			createTimestamp(0, -200),
			"1",
			true
	);

	ASSERT_TRUE(tgLog.isNeededUpdate("0"));
}

/**
 * Check tag logger item update trigger
 */
TEST_F(tagLoggerItemTests, UpdateTest5) {

	onh::TagLoggerItem tgLog(
			1,
			*tg,
			onh::TagLoggerItem::I_500MS,
			0,
			createTimestamp(0, -410),
			"1",
			true
	);

	ASSERT_FALSE(tgLog.isNeededUpdate("0"));
}

/**
 * Check tag logger item update trigger
 */
TEST_F(tagLoggerItemTests, UpdateTest6) {

	onh::TagLoggerItem tgLog(
			1,
			*tg,
			onh::TagLoggerItem::I_500MS,
			0,
			createTimestamp(0, -500),
			"1",
			true
	);

	ASSERT_TRUE(tgLog.isNeededUpdate("0"));
}

/**
 * Check tag logger item update trigger
 */
TEST_F(tagLoggerItemTests, UpdateTest7) {

	onh::TagLoggerItem tgLog(
			1,
			*tg,
			onh::TagLoggerItem::I_XS,
			3,
			createTimestamp(-2, 0),
			"1",
			true
	);

	ASSERT_FALSE(tgLog.isNeededUpdate("0"));
}

/**
 * Check tag logger item update trigger
 */
TEST_F(tagLoggerItemTests, UpdateTest8) {

	onh::TagLoggerItem tgLog(
			1,
			*tg,
			onh::TagLoggerItem::I_XS,
			3,
			createTimestamp(-3, 0),
			"1",
			true
	);

	ASSERT_TRUE(tgLog.isNeededUpdate("0"));
}

/**
 * Check tag logger item update trigger
 */
TEST_F(tagLoggerItemTests, UpdateTest9) {

	onh::TagLoggerItem tgLog(
			1,
			*tg,
			onh::TagLoggerItem::I_ON_CHANGE,
			0,
			createTimestamp(0, 0),
			"1",
			true
	);

	ASSERT_FALSE(tgLog.isNeededUpdate("1"));
}

/**
 * Check tag logger item update trigger
 */
TEST_F(tagLoggerItemTests, UpdateTest10) {

	onh::TagLoggerItem tgLog(
			1,
			*tg,
			onh::TagLoggerItem::I_ON_CHANGE,
			0,
			createTimestamp(0, 0),
			"1",
			true
	);

	ASSERT_TRUE(tgLog.isNeededUpdate("0"));
}

#endif /* TESTS_DB_OBJS_TAGLOGGERITEMTESTS_H_ */
