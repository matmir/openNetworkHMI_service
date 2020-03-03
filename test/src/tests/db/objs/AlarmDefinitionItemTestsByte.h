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

#ifndef TESTS_DB_OBJS_ALARMDEFINITIONITEMTESTSBYTE_H_
#define TESTS_DB_OBJS_ALARMDEFINITIONITEMTESTSBYTE_H_

#include <gtest/gtest.h>
#include "AlarmDefinitionItemTestsFixtures.h"

/**
 * Check alarm definition item trigger BYTE (tag>value)
 */
TEST_F(alarmDefinitionItemTestsByte, TriggerBYTE1) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_GT_value,
			onh::AlarmDefinitionItem::triggerValues(false, 10, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((BYTE)10);

	ASSERT_FALSE(retTrig.active);
	ASSERT_FALSE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger BYTE (tag>value)
 */
TEST_F(alarmDefinitionItemTestsByte, TriggerBYTE2) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_GT_value,
			onh::AlarmDefinitionItem::triggerValues(false, 10, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((BYTE)11);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger BYTE (tag<value)
 */
TEST_F(alarmDefinitionItemTestsByte, TriggerBYTE3) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_LT_value,
			onh::AlarmDefinitionItem::triggerValues(false, 10, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((BYTE)10);

	ASSERT_FALSE(retTrig.active);
	ASSERT_FALSE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger BYTE (tag<value)
 */
TEST_F(alarmDefinitionItemTestsByte, TriggerBYTE4) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_LT_value,
			onh::AlarmDefinitionItem::triggerValues(false, 10, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((BYTE)9);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger BYTE (tag>=value)
 */
TEST_F(alarmDefinitionItemTestsByte, TriggerBYTE5) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_GE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 10, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((BYTE)9);

	ASSERT_FALSE(retTrig.active);
	ASSERT_FALSE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger BYTE (tag>=value)
 */
TEST_F(alarmDefinitionItemTestsByte, TriggerBYTE6) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_GE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 10, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((BYTE)10);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger BYTE (tag>=value)
 */
TEST_F(alarmDefinitionItemTestsByte, TriggerBYTE7) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_GE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 10, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((BYTE)11);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger BYTE (tag<=value)
 */
TEST_F(alarmDefinitionItemTestsByte, TriggerBYTE8) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_LE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 10, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((BYTE)11);

	ASSERT_FALSE(retTrig.active);
	ASSERT_FALSE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger BYTE (tag<=value)
 */
TEST_F(alarmDefinitionItemTestsByte, TriggerBYTE9) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_LE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 10, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((BYTE)10);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger BYTE (tag<=value)
 */
TEST_F(alarmDefinitionItemTestsByte, TriggerBYTE10) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_LE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 10, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((BYTE)9);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger BYTE (tag==value)
 */
TEST_F(alarmDefinitionItemTestsByte, TriggerBYTE11) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_EQ_value,
			onh::AlarmDefinitionItem::triggerValues(false, 10, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((BYTE)11);

	ASSERT_FALSE(retTrig.active);
	ASSERT_FALSE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger BYTE (tag==value)
 */
TEST_F(alarmDefinitionItemTestsByte, TriggerBYTE12) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_EQ_value,
			onh::AlarmDefinitionItem::triggerValues(false, 10, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((BYTE)10);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger BYTE (tag!=value)
 */
TEST_F(alarmDefinitionItemTestsByte, TriggerBYTE13) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_NE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 10, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((BYTE)10);

	ASSERT_FALSE(retTrig.active);
	ASSERT_FALSE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger BYTE (tag!=value)
 */
TEST_F(alarmDefinitionItemTestsByte, TriggerBYTE14) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_NE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 10, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((BYTE)9);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger BYTE wrong trigger
 */
TEST_F(alarmDefinitionItemTestsByte, TriggerBYTEException1) {

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

		aItem.checkTrigger((BYTE)9);

		FAIL() << "Expected onh::AlarmException";

	} catch (onh::AlarmException &e) {

		ASSERT_STREQ(e.what(), "AlarmDefinitionItem::checkTrigger (BYTE): Wrong trigger type");
		ASSERT_EQ(onh::AlarmException::WRONG_TRIGGER, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::AlarmException";
	}
}

/**
 * Check alarm definition item trigger BYTE wrong tag type
 */
TEST_F(alarmDefinitionItemTests, TriggerBYTEException2) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_NE_value,
			onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	try {

		aItem.checkTrigger((BYTE)9);

		FAIL() << "Expected onh::AlarmException";

	} catch (onh::AlarmException &e) {

		ASSERT_STREQ(e.what(), "AlarmDefinitionItem::checkTrigger (BYTE): Wrong tag type");
		ASSERT_EQ(onh::AlarmException::WRONG_TAG_TYPE, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::AlarmException";
	}
}

#endif /* TESTS_DB_OBJS_ALARMDEFINITIONITEMTESTSBYTE_H_ */
