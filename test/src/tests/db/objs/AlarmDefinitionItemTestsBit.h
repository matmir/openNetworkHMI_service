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

#ifndef TESTS_DB_OBJS_ALARMDEFINITIONITEMTESTSBIT_H_
#define TESTS_DB_OBJS_ALARMDEFINITIONITEMTESTSBIT_H_

#include <gtest/gtest.h>
#include "AlarmDefinitionItemTestsFixtures.h"

/**
 * Check alarm definition item trigger BIN
 */
TEST_F(alarmDefinitionItemTests, TriggerBIN1) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_BIN,
			onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger(false);

	ASSERT_FALSE(retTrig.active);
	ASSERT_FALSE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger BIN
 */
TEST_F(alarmDefinitionItemTests, TriggerBIN2) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_BIN,
			onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger(true);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger BIN
 */
TEST_F(alarmDefinitionItemTests, TriggerBIN3) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_BIN,
			onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
			false, // Auto ACK
			true, // Active
			true, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger(true);

	ASSERT_TRUE(retTrig.active);
	ASSERT_FALSE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger BIN
 */
TEST_F(alarmDefinitionItemTests, TriggerBIN4) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_BIN,
			onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
			false, // Auto ACK
			true, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger(true);

	ASSERT_TRUE(retTrig.active);
	ASSERT_FALSE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger BIN
 */
TEST_F(alarmDefinitionItemTests, TriggerBIN5) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_BIN,
			onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
			false, // Auto ACK
			false, // Active
			true, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger(true);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger BIN
 */
TEST_F(alarmDefinitionItemTests, TriggerBIN6) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_BIN,
			onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
			false, // Auto ACK
			true, // Active
			true, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger(false);

	ASSERT_FALSE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger BIN
 */
TEST_F(alarmDefinitionItemTests, TriggerBIN7) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_BIN,
			onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
			false, // Auto ACK
			true, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger(false);

	ASSERT_FALSE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger BIN
 */
TEST_F(alarmDefinitionItemTests, TriggerBIN8) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_BIN,
			onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
			false, // Auto ACK
			false, // Active
			true, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger(false);

	ASSERT_FALSE(retTrig.active);
	ASSERT_FALSE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger BIN wrong trigger
 */
TEST_F(alarmDefinitionItemTests, TriggerBINException1) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_EQ_value,
			onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	try {

		aItem.checkTrigger(true);

		FAIL() << "Expected onh::AlarmException";

	} catch (onh::AlarmException &e) {

		ASSERT_STREQ(e.what(), "AlarmDefinitionItem::checkTrigger (BIN): Wrong trigger type");
		ASSERT_EQ(onh::AlarmException::WRONG_TRIGGER, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::AlarmException";
	}
}

/**
 * Check alarm definition item trigger BIN wrong tag type
 */
TEST_F(alarmDefinitionItemTestsByte, TriggerBINException2) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_BIN,
			onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	try {

		aItem.checkTrigger(true);

		FAIL() << "Expected onh::AlarmException";

	} catch (onh::AlarmException &e) {

		ASSERT_STREQ(e.what(), "AlarmDefinitionItem::checkTrigger (BIN): Wrong tag type");
		ASSERT_EQ(onh::AlarmException::WRONG_TAG_TYPE, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::AlarmException";
	}
}

#endif /* TESTS_DB_OBJS_ALARMDEFINITIONITEMTESTSBIT_H_ */
