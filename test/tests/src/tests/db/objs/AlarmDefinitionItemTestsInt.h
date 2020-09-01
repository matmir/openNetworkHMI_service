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

#ifndef TESTS_DB_OBJS_ALARMDEFINITIONITEMTESTSINT_H_
#define TESTS_DB_OBJS_ALARMDEFINITIONITEMTESTSINT_H_

#include <gtest/gtest.h>
#include "AlarmDefinitionItemTestsFixtures.h"

/**
 * Check alarm definition item trigger INT (tag>value)
 */
TEST_F(alarmDefinitionItemTestsInt, TriggerINT1) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_GT_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, -450, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((int)-450);

	ASSERT_FALSE(retTrig.active);
	ASSERT_FALSE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger INT (tag>value)
 */
TEST_F(alarmDefinitionItemTestsInt, TriggerINT2) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_GT_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, -450, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((int)-449);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger INT (tag<value)
 */
TEST_F(alarmDefinitionItemTestsInt, TriggerINT3) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_LT_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, -450, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((int)-450);

	ASSERT_FALSE(retTrig.active);
	ASSERT_FALSE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger INT (tag<value)
 */
TEST_F(alarmDefinitionItemTestsInt, TriggerINT4) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_LT_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, -450, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((int)-451);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger INT (tag>=value)
 */
TEST_F(alarmDefinitionItemTestsInt, TriggerINT5) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_GE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, -450, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((int)-451);

	ASSERT_FALSE(retTrig.active);
	ASSERT_FALSE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger INT (tag>=value)
 */
TEST_F(alarmDefinitionItemTestsInt, TriggerINT6) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_GE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, -450, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((int)-450);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger INT (tag>=value)
 */
TEST_F(alarmDefinitionItemTestsInt, TriggerINT7) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_GE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, -450, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((int)-449);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger INT (tag<=value)
 */
TEST_F(alarmDefinitionItemTestsInt, TriggerINT8) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_LE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, -450, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((int)-449);

	ASSERT_FALSE(retTrig.active);
	ASSERT_FALSE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger INT (tag<=value)
 */
TEST_F(alarmDefinitionItemTestsInt, TriggerINT9) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_LE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, -450, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((int)-450);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger INT (tag<=value)
 */
TEST_F(alarmDefinitionItemTestsInt, TriggerINT10) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_LE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, -450, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((int)-451);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger INT (tag==value)
 */
TEST_F(alarmDefinitionItemTestsInt, TriggerINT11) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_EQ_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, -450, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((int)-449);

	ASSERT_FALSE(retTrig.active);
	ASSERT_FALSE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger INT (tag==value)
 */
TEST_F(alarmDefinitionItemTestsInt, TriggerINT12) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_EQ_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, -450, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((int)-450);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger INT (tag!=value)
 */
TEST_F(alarmDefinitionItemTestsInt, TriggerINT13) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_NE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, -450, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((int)-450);

	ASSERT_FALSE(retTrig.active);
	ASSERT_FALSE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger INT (tag!=value)
 */
TEST_F(alarmDefinitionItemTestsInt, TriggerINT14) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_NE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 0, -450, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((int)-449);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger INT wrong trigger
 */
TEST_F(alarmDefinitionItemTestsInt, TriggerINTException1) {

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

		aItem.checkTrigger((int)-450);

		FAIL() << "Expected onh::AlarmException";

	} catch (onh::AlarmException &e) {

		ASSERT_STREQ(e.what(), "AlarmDefinitionItem::checkTrigger (INT): Wrong trigger type");
		ASSERT_EQ(onh::AlarmException::WRONG_TRIGGER, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::AlarmException";
	}
}

/**
 * Check alarm definition item trigger INT wrong tag type
 */
TEST_F(alarmDefinitionItemTestsByte, TriggerINTException2) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_NE_value,
			onh::AlarmDefinitionItem::triggerValues(true, 0, -450, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	try {

		aItem.checkTrigger((int)-450);

		FAIL() << "Expected onh::AlarmException";

	} catch (onh::AlarmException &e) {

		ASSERT_STREQ(e.what(), "AlarmDefinitionItem::checkTrigger (INT): Wrong tag type");
		ASSERT_EQ(onh::AlarmException::WRONG_TAG_TYPE, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::AlarmException";
	}
}

#endif /* TESTS_DB_OBJS_ALARMDEFINITIONITEMTESTSINT_H_ */
