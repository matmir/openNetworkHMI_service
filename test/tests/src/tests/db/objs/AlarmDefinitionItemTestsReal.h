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

#ifndef TESTS_DB_OBJS_ALARMDEFINITIONITEMTESTSREAL_H_
#define TESTS_DB_OBJS_ALARMDEFINITIONITEMTESTSREAL_H_

#include <gtest/gtest.h>
#include "AlarmDefinitionItemTestsFixtures.h"

/**
 * Check alarm definition item trigger REAL (tag>value)
 */
TEST_F(alarmDefinitionItemTestsReal, TriggerREAL1) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_GT_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, 0, -8.74),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((float)-8.74);

	ASSERT_FALSE(retTrig.active);
	ASSERT_FALSE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger REAL (tag>value)
 */
TEST_F(alarmDefinitionItemTestsReal, TriggerREAL2) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_GT_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, 0, -8.74),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((float)-8.73);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger REAL (tag<value)
 */
TEST_F(alarmDefinitionItemTestsReal, TriggerREAL3) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_LT_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, 0, -8.74),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((float)-8.74);

	ASSERT_FALSE(retTrig.active);
	ASSERT_FALSE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger REAL (tag<value)
 */
TEST_F(alarmDefinitionItemTestsReal, TriggerREAL4) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_LT_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, 0, -8.74),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((float)-8.75);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger REAL (tag>=value)
 */
TEST_F(alarmDefinitionItemTestsReal, TriggerREAL5) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_GE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, 0, -8.74),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((float)-8.75);

	ASSERT_FALSE(retTrig.active);
	ASSERT_FALSE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger REAL (tag>=value)
 */
TEST_F(alarmDefinitionItemTestsReal, TriggerREAL6) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_GE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, 0, -8.74),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((float)-8.74);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger REAL (tag>=value)
 */
TEST_F(alarmDefinitionItemTestsReal, TriggerREAL7) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_GE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, 0, -8.74),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((float)-8.73);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger REAL (tag<=value)
 */
TEST_F(alarmDefinitionItemTestsReal, TriggerREAL8) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_LE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, 0, -8.74),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((float)-8.73);

	ASSERT_FALSE(retTrig.active);
	ASSERT_FALSE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger REAL (tag<=value)
 */
TEST_F(alarmDefinitionItemTestsReal, TriggerREAL9) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_LE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, 0, -8.74),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((float)-8.74);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger REAL (tag<=value)
 */
TEST_F(alarmDefinitionItemTestsReal, TriggerREAL10) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_LE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, 0, -8.74),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((float)-8.75);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger REAL (tag==value)
 */
TEST_F(alarmDefinitionItemTestsReal, TriggerREAL11) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_EQ_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, 0, -8.74),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((float)-8.73);

	ASSERT_FALSE(retTrig.active);
	ASSERT_FALSE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger REAL (tag==value)
 */
TEST_F(alarmDefinitionItemTestsReal, TriggerREAL12) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_EQ_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, 0, -8.74),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((float)-8.74);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger REAL (tag!=value)
 */
TEST_F(alarmDefinitionItemTestsReal, TriggerREAL13) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_NE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, 0, -8.74),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((float)-8.74);

	ASSERT_FALSE(retTrig.active);
	ASSERT_FALSE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger REAL (tag!=value)
 */
TEST_F(alarmDefinitionItemTestsReal, TriggerREAL14) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_NE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, 0, -8.74),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((float)-8.73);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger REAL wrong trigger
 */
TEST_F(alarmDefinitionItemTestsReal, TriggerREALException1) {

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

	try {

		aItem.checkTrigger((float)-8.74);

		FAIL() << "Expected onh::AlarmException";

	} catch (onh::AlarmException &e) {

		ASSERT_STREQ(e.what(), "AlarmDefinitionItem::checkTrigger (REAL): Wrong trigger type");
		ASSERT_EQ(onh::AlarmException::WRONG_TRIGGER, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::AlarmException";
	}
}

/**
 * Check alarm definition item trigger REAL wrong tag type
 */
TEST_F(alarmDefinitionItemTestsByte, TriggerREALException2) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_NE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, 0, -8.74),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	try {

		aItem.checkTrigger((float)-8.74);

		FAIL() << "Expected onh::AlarmException";

	} catch (onh::AlarmException &e) {

		ASSERT_STREQ(e.what(), "AlarmDefinitionItem::checkTrigger (REAL): Wrong tag type");
		ASSERT_EQ(onh::AlarmException::WRONG_TAG_TYPE, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::AlarmException";
	}
}

#endif /* TESTS_DB_OBJS_ALARMDEFINITIONITEMTESTSREAL_H_ */
