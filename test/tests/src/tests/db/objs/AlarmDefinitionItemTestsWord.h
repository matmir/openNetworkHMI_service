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

#ifndef TESTS_DB_OBJS_ALARMDEFINITIONITEMTESTSWORD_H_
#define TESTS_DB_OBJS_ALARMDEFINITIONITEMTESTSWORD_H_

#include <gtest/gtest.h>
#include "AlarmDefinitionItemTestsFixtures.h"

/**
 * Check alarm definition item trigger WORD (tag>value)
 */
TEST_F(alarmDefinitionItemTestsWord, TriggerWORD1) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_GT_value,
			onh::AlarmDefinitionItem::triggerValues(false, 1500, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((WORD)1500);

	ASSERT_FALSE(retTrig.active);
	ASSERT_FALSE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger WORD (tag>value)
 */
TEST_F(alarmDefinitionItemTestsWord, TriggerWORD2) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_GT_value,
			onh::AlarmDefinitionItem::triggerValues(false, 1500, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((WORD)1501);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger WORD (tag<value)
 */
TEST_F(alarmDefinitionItemTestsWord, TriggerWORD3) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_LT_value,
			onh::AlarmDefinitionItem::triggerValues(false, 1500, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((WORD)1500);

	ASSERT_FALSE(retTrig.active);
	ASSERT_FALSE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger WORD (tag<value)
 */
TEST_F(alarmDefinitionItemTestsWord, TriggerWORD4) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_LT_value,
			onh::AlarmDefinitionItem::triggerValues(false, 1500, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((WORD)1499);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger WORD (tag>=value)
 */
TEST_F(alarmDefinitionItemTestsWord, TriggerWORD5) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_GE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 1500, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((WORD)1499);

	ASSERT_FALSE(retTrig.active);
	ASSERT_FALSE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger WORD (tag>=value)
 */
TEST_F(alarmDefinitionItemTestsWord, TriggerWORD6) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_GE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 1500, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((WORD)1500);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger WORD (tag>=value)
 */
TEST_F(alarmDefinitionItemTestsWord, TriggerWORD7) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_GE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 1500, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((WORD)1501);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger WORD (tag<=value)
 */
TEST_F(alarmDefinitionItemTestsWord, TriggerWORD8) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_LE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 1500, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((WORD)1501);

	ASSERT_FALSE(retTrig.active);
	ASSERT_FALSE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger WORD (tag<=value)
 */
TEST_F(alarmDefinitionItemTestsWord, TriggerWORD9) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_LE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 1500, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((WORD)1500);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger WORD (tag<=value)
 */
TEST_F(alarmDefinitionItemTestsWord, TriggerWORD10) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_LE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 1500, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((WORD)1499);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger WORD (tag==value)
 */
TEST_F(alarmDefinitionItemTestsWord, TriggerWORD11) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_EQ_value,
			onh::AlarmDefinitionItem::triggerValues(false, 1500, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((WORD)1501);

	ASSERT_FALSE(retTrig.active);
	ASSERT_FALSE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger WORD (tag==value)
 */
TEST_F(alarmDefinitionItemTestsWord, TriggerWORD12) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_EQ_value,
			onh::AlarmDefinitionItem::triggerValues(false, 1500, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((WORD)1500);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger WORD (tag!=value)
 */
TEST_F(alarmDefinitionItemTestsWord, TriggerWORD13) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_NE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 1500, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((WORD)1500);

	ASSERT_FALSE(retTrig.active);
	ASSERT_FALSE(retTrig.activeUpdate);
	ASSERT_FALSE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger WORD (tag!=value)
 */
TEST_F(alarmDefinitionItemTestsWord, TriggerWORD14) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_NE_value,
			onh::AlarmDefinitionItem::triggerValues(false, 1500, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	// Return trigger value;
	onh::AlarmDefinitionItem::triggerRet retTrig;

	retTrig = aItem.checkTrigger((WORD)1501);

	ASSERT_TRUE(retTrig.active);
	ASSERT_TRUE(retTrig.activeUpdate);
	ASSERT_TRUE(retTrig.trigger);
}

/**
 * Check alarm definition item trigger WORD wrong trigger
 */
TEST_F(alarmDefinitionItemTestsWord, TriggerWORDException1) {

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

		aItem.checkTrigger((WORD)1500);

		FAIL() << "Expected onh::AlarmException";

	} catch (onh::AlarmException &e) {

		ASSERT_STREQ(e.what(), "AlarmDefinitionItem::checkTrigger (WORD): Wrong trigger type");
		ASSERT_EQ(onh::AlarmException::WRONG_TRIGGER, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::AlarmException";
	}
}

/**
 * Check alarm definition item trigger WORD wrong tag type
 */
TEST_F(alarmDefinitionItemTestsDWord, TriggerWORDException2) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_NE_value,
			onh::AlarmDefinitionItem::triggerValues(true, 1500, 0, 0),
			false, // Auto ACK
			false, // Active
			false, // Pending
			*tgFeedback,
			*tgHWAck,
			true
	);

	try {

		aItem.checkTrigger((WORD)1500);

		FAIL() << "Expected onh::AlarmException";

	} catch (onh::AlarmException &e) {

		ASSERT_STREQ(e.what(), "AlarmDefinitionItem::checkTrigger (WORD): Wrong tag type");
		ASSERT_EQ(onh::AlarmException::WRONG_TAG_TYPE, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::AlarmException";
	}
}

#endif /* TESTS_DB_OBJS_ALARMDEFINITIONITEMTESTSWORD_H_ */
