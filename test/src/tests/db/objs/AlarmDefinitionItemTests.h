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

#ifndef TESTS_DB_OBJS_ALARMDEFINITIONITEMTESTS_H_
#define TESTS_DB_OBJS_ALARMDEFINITIONITEMTESTS_H_

#include <gtest/gtest.h>
#include "AlarmDefinitionItemTestsFixtures.h"

/**
 * Check alarm definition item creation
 */
TEST_F(alarmDefinitionItemTests, Create1) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_BIN,
			onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
			false,
			false,
			false,
			*tgFeedback,
			*tgHWAck,
			true
	);

	ASSERT_EQ((unsigned int)1, aItem.getId());

	ASSERT_EQ((unsigned int)5, aItem.getTag().getId());
	ASSERT_STREQ("TestTag1", aItem.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)6, aItem.getTag().getBitAddress());

	ASSERT_EQ((unsigned int)1, aItem.getPriority());
	ASSERT_STREQ("Alarm message", aItem.getMsg().c_str());
	ASSERT_EQ(onh::AlarmDefinitionItem::T_BIN, aItem.getTrigger());
	ASSERT_TRUE(aItem.getTriggerValues().binVal);
	ASSERT_EQ((DWORD)0, aItem.getTriggerValues().dwVal);
	ASSERT_EQ(0, aItem.getTriggerValues().intVal);
	ASSERT_EQ((float)0, aItem.getTriggerValues().realVal);
	ASSERT_FALSE(aItem.isAutoAck());
	ASSERT_FALSE(aItem.isActive());
	ASSERT_FALSE(aItem.isPending());

	ASSERT_EQ((unsigned int)6, aItem.getFeedbackNotAckTag().getId());
	ASSERT_STREQ("tagFeedback", aItem.getFeedbackNotAckTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getFeedbackNotAckTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getFeedbackNotAckTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getFeedbackNotAckTag().getByteAddress());
	ASSERT_EQ((unsigned int)0, aItem.getFeedbackNotAckTag().getBitAddress());

	ASSERT_EQ((unsigned int)7, aItem.getHWAckTag().getId());
	ASSERT_STREQ("tagHWAck", aItem.getHWAckTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getHWAckTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getHWAckTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getHWAckTag().getByteAddress());
	ASSERT_EQ((unsigned int)1, aItem.getHWAckTag().getBitAddress());

	ASSERT_TRUE(aItem.isEnabled());
}

/**
 * Check alarm definition item set id
 */
TEST_F(alarmDefinitionItemTests, CreateSetId) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_BIN,
			onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
			false,
			false,
			false,
			*tgFeedback,
			*tgHWAck,
			true
	);

	aItem.setId(45);

	ASSERT_EQ((unsigned int)45, aItem.getId());

	ASSERT_EQ((unsigned int)5, aItem.getTag().getId());
	ASSERT_STREQ("TestTag1", aItem.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)6, aItem.getTag().getBitAddress());

	ASSERT_EQ((unsigned int)1, aItem.getPriority());
	ASSERT_STREQ("Alarm message", aItem.getMsg().c_str());
	ASSERT_EQ(onh::AlarmDefinitionItem::T_BIN, aItem.getTrigger());
	ASSERT_TRUE(aItem.getTriggerValues().binVal);
	ASSERT_EQ((DWORD)0, aItem.getTriggerValues().dwVal);
	ASSERT_EQ(0, aItem.getTriggerValues().intVal);
	ASSERT_EQ((float)0, aItem.getTriggerValues().realVal);
	ASSERT_FALSE(aItem.isAutoAck());
	ASSERT_FALSE(aItem.isActive());
	ASSERT_FALSE(aItem.isPending());

	ASSERT_EQ((unsigned int)6, aItem.getFeedbackNotAckTag().getId());
	ASSERT_STREQ("tagFeedback", aItem.getFeedbackNotAckTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getFeedbackNotAckTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getFeedbackNotAckTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getFeedbackNotAckTag().getByteAddress());
	ASSERT_EQ((unsigned int)0, aItem.getFeedbackNotAckTag().getBitAddress());

	ASSERT_EQ((unsigned int)7, aItem.getHWAckTag().getId());
	ASSERT_STREQ("tagHWAck", aItem.getHWAckTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getHWAckTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getHWAckTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getHWAckTag().getByteAddress());
	ASSERT_EQ((unsigned int)1, aItem.getHWAckTag().getBitAddress());

	ASSERT_TRUE(aItem.isEnabled());
}

/**
 * Check alarm definition item set tag
 */
TEST_F(alarmDefinitionItemTests, CreateSetTag) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_BIN,
			onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
			false,
			false,
			false,
			*tgFeedback,
			*tgHWAck,
			true
	);

	onh::Tag tg2(
			500,
			"TestTag9",
			onh::TT_BYTE,
			{onh::PDA_MEMORY, 789, 0}
	);

	aItem.setTag(tg2);

	ASSERT_EQ((unsigned int)1, aItem.getId());

	ASSERT_EQ((unsigned int)500, aItem.getTag().getId());
	ASSERT_STREQ("TestTag9", aItem.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BYTE, aItem.getTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getTag().getArea());
	ASSERT_EQ((unsigned int)789, aItem.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)0, aItem.getTag().getBitAddress());

	ASSERT_EQ((unsigned int)1, aItem.getPriority());
	ASSERT_STREQ("Alarm message", aItem.getMsg().c_str());
	ASSERT_EQ(onh::AlarmDefinitionItem::T_BIN, aItem.getTrigger());
	ASSERT_TRUE(aItem.getTriggerValues().binVal);
	ASSERT_EQ((DWORD)0, aItem.getTriggerValues().dwVal);
	ASSERT_EQ(0, aItem.getTriggerValues().intVal);
	ASSERT_EQ((float)0, aItem.getTriggerValues().realVal);
	ASSERT_FALSE(aItem.isAutoAck());
	ASSERT_FALSE(aItem.isActive());
	ASSERT_FALSE(aItem.isPending());

	ASSERT_EQ((unsigned int)6, aItem.getFeedbackNotAckTag().getId());
	ASSERT_STREQ("tagFeedback", aItem.getFeedbackNotAckTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getFeedbackNotAckTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getFeedbackNotAckTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getFeedbackNotAckTag().getByteAddress());
	ASSERT_EQ((unsigned int)0, aItem.getFeedbackNotAckTag().getBitAddress());

	ASSERT_EQ((unsigned int)7, aItem.getHWAckTag().getId());
	ASSERT_STREQ("tagHWAck", aItem.getHWAckTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getHWAckTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getHWAckTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getHWAckTag().getByteAddress());
	ASSERT_EQ((unsigned int)1, aItem.getHWAckTag().getBitAddress());

	ASSERT_TRUE(aItem.isEnabled());
}

/**
 * Check alarm definition item set priority
 */
TEST_F(alarmDefinitionItemTests, CreateSetPriority) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_BIN,
			onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
			false,
			false,
			false,
			*tgFeedback,
			*tgHWAck,
			true
	);

	aItem.setPriority(3);

	ASSERT_EQ((unsigned int)1, aItem.getId());

	ASSERT_EQ((unsigned int)5, aItem.getTag().getId());
	ASSERT_STREQ("TestTag1", aItem.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)6, aItem.getTag().getBitAddress());

	ASSERT_EQ((unsigned int)3, aItem.getPriority());
	ASSERT_STREQ("Alarm message", aItem.getMsg().c_str());
	ASSERT_EQ(onh::AlarmDefinitionItem::T_BIN, aItem.getTrigger());
	ASSERT_TRUE(aItem.getTriggerValues().binVal);
	ASSERT_EQ((DWORD)0, aItem.getTriggerValues().dwVal);
	ASSERT_EQ(0, aItem.getTriggerValues().intVal);
	ASSERT_EQ((float)0, aItem.getTriggerValues().realVal);
	ASSERT_FALSE(aItem.isAutoAck());
	ASSERT_FALSE(aItem.isActive());
	ASSERT_FALSE(aItem.isPending());

	ASSERT_EQ((unsigned int)6, aItem.getFeedbackNotAckTag().getId());
	ASSERT_STREQ("tagFeedback", aItem.getFeedbackNotAckTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getFeedbackNotAckTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getFeedbackNotAckTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getFeedbackNotAckTag().getByteAddress());
	ASSERT_EQ((unsigned int)0, aItem.getFeedbackNotAckTag().getBitAddress());

	ASSERT_EQ((unsigned int)7, aItem.getHWAckTag().getId());
	ASSERT_STREQ("tagHWAck", aItem.getHWAckTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getHWAckTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getHWAckTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getHWAckTag().getByteAddress());
	ASSERT_EQ((unsigned int)1, aItem.getHWAckTag().getBitAddress());

	ASSERT_TRUE(aItem.isEnabled());
}

/**
 * Check alarm definition item set message
 */
TEST_F(alarmDefinitionItemTests, CreateSetMessage) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_BIN,
			onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
			false,
			false,
			false,
			*tgFeedback,
			*tgHWAck,
			true
	);

	aItem.setMsg("Test msg");

	ASSERT_EQ((unsigned int)1, aItem.getId());

	ASSERT_EQ((unsigned int)5, aItem.getTag().getId());
	ASSERT_STREQ("TestTag1", aItem.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)6, aItem.getTag().getBitAddress());

	ASSERT_EQ((unsigned int)1, aItem.getPriority());
	ASSERT_STREQ("Test msg", aItem.getMsg().c_str());
	ASSERT_EQ(onh::AlarmDefinitionItem::T_BIN, aItem.getTrigger());
	ASSERT_TRUE(aItem.getTriggerValues().binVal);
	ASSERT_EQ((DWORD)0, aItem.getTriggerValues().dwVal);
	ASSERT_EQ(0, aItem.getTriggerValues().intVal);
	ASSERT_EQ((float)0, aItem.getTriggerValues().realVal);
	ASSERT_FALSE(aItem.isAutoAck());
	ASSERT_FALSE(aItem.isActive());
	ASSERT_FALSE(aItem.isPending());

	ASSERT_EQ((unsigned int)6, aItem.getFeedbackNotAckTag().getId());
	ASSERT_STREQ("tagFeedback", aItem.getFeedbackNotAckTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getFeedbackNotAckTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getFeedbackNotAckTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getFeedbackNotAckTag().getByteAddress());
	ASSERT_EQ((unsigned int)0, aItem.getFeedbackNotAckTag().getBitAddress());

	ASSERT_EQ((unsigned int)7, aItem.getHWAckTag().getId());
	ASSERT_STREQ("tagHWAck", aItem.getHWAckTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getHWAckTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getHWAckTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getHWAckTag().getByteAddress());
	ASSERT_EQ((unsigned int)1, aItem.getHWAckTag().getBitAddress());

	ASSERT_TRUE(aItem.isEnabled());
}

/**
 * Check alarm definition item set trigger
 */
TEST_F(alarmDefinitionItemTests, CreateSetTrigger) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_BIN,
			onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
			false,
			false,
			false,
			*tgFeedback,
			*tgHWAck,
			true
	);

	aItem.setTrigger(onh::AlarmDefinitionItem::T_Tag_GT_value);

	ASSERT_EQ((unsigned int)1, aItem.getId());

	ASSERT_EQ((unsigned int)5, aItem.getTag().getId());
	ASSERT_STREQ("TestTag1", aItem.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)6, aItem.getTag().getBitAddress());

	ASSERT_EQ((unsigned int)1, aItem.getPriority());
	ASSERT_STREQ("Alarm message", aItem.getMsg().c_str());
	ASSERT_EQ(onh::AlarmDefinitionItem::T_Tag_GT_value, aItem.getTrigger());
	ASSERT_TRUE(aItem.getTriggerValues().binVal);
	ASSERT_EQ((DWORD)0, aItem.getTriggerValues().dwVal);
	ASSERT_EQ(0, aItem.getTriggerValues().intVal);
	ASSERT_EQ((float)0, aItem.getTriggerValues().realVal);
	ASSERT_FALSE(aItem.isAutoAck());
	ASSERT_FALSE(aItem.isActive());
	ASSERT_FALSE(aItem.isPending());

	ASSERT_EQ((unsigned int)6, aItem.getFeedbackNotAckTag().getId());
	ASSERT_STREQ("tagFeedback", aItem.getFeedbackNotAckTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getFeedbackNotAckTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getFeedbackNotAckTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getFeedbackNotAckTag().getByteAddress());
	ASSERT_EQ((unsigned int)0, aItem.getFeedbackNotAckTag().getBitAddress());

	ASSERT_EQ((unsigned int)7, aItem.getHWAckTag().getId());
	ASSERT_STREQ("tagHWAck", aItem.getHWAckTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getHWAckTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getHWAckTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getHWAckTag().getByteAddress());
	ASSERT_EQ((unsigned int)1, aItem.getHWAckTag().getBitAddress());

	ASSERT_TRUE(aItem.isEnabled());
}

/**
 * Check alarm definition item set trigger values
 */
TEST_F(alarmDefinitionItemTests, CreateSetTriggerValues) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_Tag_GT_value,
			onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
			false,
			false,
			false,
			*tgFeedback,
			*tgHWAck,
			true
	);

	aItem.setTriggerValues(onh::AlarmDefinitionItem::triggerValues(false, 45, 0, 0));

	ASSERT_EQ((unsigned int)1, aItem.getId());

	ASSERT_EQ((unsigned int)5, aItem.getTag().getId());
	ASSERT_STREQ("TestTag1", aItem.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)6, aItem.getTag().getBitAddress());

	ASSERT_EQ((unsigned int)1, aItem.getPriority());
	ASSERT_STREQ("Alarm message", aItem.getMsg().c_str());
	ASSERT_EQ(onh::AlarmDefinitionItem::T_Tag_GT_value, aItem.getTrigger());
	ASSERT_FALSE(aItem.getTriggerValues().binVal);
	ASSERT_EQ((DWORD)45, aItem.getTriggerValues().dwVal);
	ASSERT_EQ(0, aItem.getTriggerValues().intVal);
	ASSERT_EQ((float)0, aItem.getTriggerValues().realVal);
	ASSERT_FALSE(aItem.isAutoAck());
	ASSERT_FALSE(aItem.isActive());
	ASSERT_FALSE(aItem.isPending());

	ASSERT_EQ((unsigned int)6, aItem.getFeedbackNotAckTag().getId());
	ASSERT_STREQ("tagFeedback", aItem.getFeedbackNotAckTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getFeedbackNotAckTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getFeedbackNotAckTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getFeedbackNotAckTag().getByteAddress());
	ASSERT_EQ((unsigned int)0, aItem.getFeedbackNotAckTag().getBitAddress());

	ASSERT_EQ((unsigned int)7, aItem.getHWAckTag().getId());
	ASSERT_STREQ("tagHWAck", aItem.getHWAckTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getHWAckTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getHWAckTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getHWAckTag().getByteAddress());
	ASSERT_EQ((unsigned int)1, aItem.getHWAckTag().getBitAddress());

	ASSERT_TRUE(aItem.isEnabled());
}

/**
 * Check alarm definition item set auto ack
 */
TEST_F(alarmDefinitionItemTests, CreateSetAutoAck) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_BIN,
			onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
			false,
			false,
			false,
			*tgFeedback,
			*tgHWAck,
			true
	);

	aItem.setAutoAck(true);

	ASSERT_EQ((unsigned int)1, aItem.getId());

	ASSERT_EQ((unsigned int)5, aItem.getTag().getId());
	ASSERT_STREQ("TestTag1", aItem.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)6, aItem.getTag().getBitAddress());

	ASSERT_EQ((unsigned int)1, aItem.getPriority());
	ASSERT_STREQ("Alarm message", aItem.getMsg().c_str());
	ASSERT_EQ(onh::AlarmDefinitionItem::T_BIN, aItem.getTrigger());
	ASSERT_TRUE(aItem.getTriggerValues().binVal);
	ASSERT_EQ((DWORD)0, aItem.getTriggerValues().dwVal);
	ASSERT_EQ(0, aItem.getTriggerValues().intVal);
	ASSERT_EQ((float)0, aItem.getTriggerValues().realVal);
	ASSERT_TRUE(aItem.isAutoAck());
	ASSERT_FALSE(aItem.isActive());
	ASSERT_FALSE(aItem.isPending());

	ASSERT_EQ((unsigned int)6, aItem.getFeedbackNotAckTag().getId());
	ASSERT_STREQ("tagFeedback", aItem.getFeedbackNotAckTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getFeedbackNotAckTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getFeedbackNotAckTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getFeedbackNotAckTag().getByteAddress());
	ASSERT_EQ((unsigned int)0, aItem.getFeedbackNotAckTag().getBitAddress());

	ASSERT_EQ((unsigned int)7, aItem.getHWAckTag().getId());
	ASSERT_STREQ("tagHWAck", aItem.getHWAckTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getHWAckTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getHWAckTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getHWAckTag().getByteAddress());
	ASSERT_EQ((unsigned int)1, aItem.getHWAckTag().getBitAddress());

	ASSERT_TRUE(aItem.isEnabled());
}

/**
 * Check alarm definition item set active
 */
TEST_F(alarmDefinitionItemTests, CreateSetActive) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_BIN,
			onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
			false,
			false,
			false,
			*tgFeedback,
			*tgHWAck,
			true
	);

	aItem.setActive(true);

	ASSERT_EQ((unsigned int)1, aItem.getId());

	ASSERT_EQ((unsigned int)5, aItem.getTag().getId());
	ASSERT_STREQ("TestTag1", aItem.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)6, aItem.getTag().getBitAddress());

	ASSERT_EQ((unsigned int)1, aItem.getPriority());
	ASSERT_STREQ("Alarm message", aItem.getMsg().c_str());
	ASSERT_EQ(onh::AlarmDefinitionItem::T_BIN, aItem.getTrigger());
	ASSERT_TRUE(aItem.getTriggerValues().binVal);
	ASSERT_EQ((DWORD)0, aItem.getTriggerValues().dwVal);
	ASSERT_EQ(0, aItem.getTriggerValues().intVal);
	ASSERT_EQ((float)0, aItem.getTriggerValues().realVal);
	ASSERT_FALSE(aItem.isAutoAck());
	ASSERT_TRUE(aItem.isActive());
	ASSERT_FALSE(aItem.isPending());

	ASSERT_EQ((unsigned int)6, aItem.getFeedbackNotAckTag().getId());
	ASSERT_STREQ("tagFeedback", aItem.getFeedbackNotAckTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getFeedbackNotAckTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getFeedbackNotAckTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getFeedbackNotAckTag().getByteAddress());
	ASSERT_EQ((unsigned int)0, aItem.getFeedbackNotAckTag().getBitAddress());

	ASSERT_EQ((unsigned int)7, aItem.getHWAckTag().getId());
	ASSERT_STREQ("tagHWAck", aItem.getHWAckTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getHWAckTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getHWAckTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getHWAckTag().getByteAddress());
	ASSERT_EQ((unsigned int)1, aItem.getHWAckTag().getBitAddress());

	ASSERT_TRUE(aItem.isEnabled());
}

/**
 * Check alarm definition item set pending
 */
TEST_F(alarmDefinitionItemTests, CreateSetPending) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_BIN,
			onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
			false,
			false,
			false,
			*tgFeedback,
			*tgHWAck,
			true
	);

	aItem.setPending(true);

	ASSERT_EQ((unsigned int)1, aItem.getId());

	ASSERT_EQ((unsigned int)5, aItem.getTag().getId());
	ASSERT_STREQ("TestTag1", aItem.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)6, aItem.getTag().getBitAddress());

	ASSERT_EQ((unsigned int)1, aItem.getPriority());
	ASSERT_STREQ("Alarm message", aItem.getMsg().c_str());
	ASSERT_EQ(onh::AlarmDefinitionItem::T_BIN, aItem.getTrigger());
	ASSERT_TRUE(aItem.getTriggerValues().binVal);
	ASSERT_EQ((DWORD)0, aItem.getTriggerValues().dwVal);
	ASSERT_EQ(0, aItem.getTriggerValues().intVal);
	ASSERT_EQ((float)0, aItem.getTriggerValues().realVal);
	ASSERT_FALSE(aItem.isAutoAck());
	ASSERT_FALSE(aItem.isActive());
	ASSERT_TRUE(aItem.isPending());

	ASSERT_EQ((unsigned int)6, aItem.getFeedbackNotAckTag().getId());
	ASSERT_STREQ("tagFeedback", aItem.getFeedbackNotAckTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getFeedbackNotAckTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getFeedbackNotAckTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getFeedbackNotAckTag().getByteAddress());
	ASSERT_EQ((unsigned int)0, aItem.getFeedbackNotAckTag().getBitAddress());

	ASSERT_EQ((unsigned int)7, aItem.getHWAckTag().getId());
	ASSERT_STREQ("tagHWAck", aItem.getHWAckTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getHWAckTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getHWAckTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getHWAckTag().getByteAddress());
	ASSERT_EQ((unsigned int)1, aItem.getHWAckTag().getBitAddress());

	ASSERT_TRUE(aItem.isEnabled());
}

/**
 * Check alarm definition item set feedback not ack tag
 */
TEST_F(alarmDefinitionItemTests, CreateSetFeedbackNotAck) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_BIN,
			onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
			false,
			false,
			false,
			*tgFeedback,
			*tgHWAck,
			true
	);

	onh::Tag tgFeedback2(
			68,
			"tagFeedback68",
			onh::TT_BIT,
			{onh::PDA_OUTPUT, 434, 4}
	);

	aItem.setFeedbackNotAckTag(tgFeedback2);

	ASSERT_EQ((unsigned int)1, aItem.getId());

	ASSERT_EQ((unsigned int)5, aItem.getTag().getId());
	ASSERT_STREQ("TestTag1", aItem.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)6, aItem.getTag().getBitAddress());

	ASSERT_EQ((unsigned int)1, aItem.getPriority());
	ASSERT_STREQ("Alarm message", aItem.getMsg().c_str());
	ASSERT_EQ(onh::AlarmDefinitionItem::T_BIN, aItem.getTrigger());
	ASSERT_TRUE(aItem.getTriggerValues().binVal);
	ASSERT_EQ((DWORD)0, aItem.getTriggerValues().dwVal);
	ASSERT_EQ(0, aItem.getTriggerValues().intVal);
	ASSERT_EQ((float)0, aItem.getTriggerValues().realVal);
	ASSERT_FALSE(aItem.isAutoAck());
	ASSERT_FALSE(aItem.isActive());
	ASSERT_FALSE(aItem.isPending());

	ASSERT_EQ((unsigned int)68, aItem.getFeedbackNotAckTag().getId());
	ASSERT_STREQ("tagFeedback68", aItem.getFeedbackNotAckTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getFeedbackNotAckTag().getType());
	ASSERT_EQ(onh::PDA_OUTPUT, aItem.getFeedbackNotAckTag().getArea());
	ASSERT_EQ((unsigned int)434, aItem.getFeedbackNotAckTag().getByteAddress());
	ASSERT_EQ((unsigned int)4, aItem.getFeedbackNotAckTag().getBitAddress());

	ASSERT_EQ((unsigned int)7, aItem.getHWAckTag().getId());
	ASSERT_STREQ("tagHWAck", aItem.getHWAckTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getHWAckTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getHWAckTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getHWAckTag().getByteAddress());
	ASSERT_EQ((unsigned int)1, aItem.getHWAckTag().getBitAddress());

	ASSERT_TRUE(aItem.isEnabled());
}

/**
 * Check alarm definition item set HW ack tag
 */
TEST_F(alarmDefinitionItemTests, CreateSetHWtag) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_BIN,
			onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
			false,
			false,
			false,
			*tgFeedback,
			*tgHWAck,
			true
	);

	onh::Tag tgHW2(
			666,
			"tagDevil",
			onh::TT_BIT,
			{onh::PDA_OUTPUT, 666, 2}
	);

	aItem.setHWAckTag(tgHW2);

	ASSERT_EQ((unsigned int)1, aItem.getId());

	ASSERT_EQ((unsigned int)5, aItem.getTag().getId());
	ASSERT_STREQ("TestTag1", aItem.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)6, aItem.getTag().getBitAddress());

	ASSERT_EQ((unsigned int)1, aItem.getPriority());
	ASSERT_STREQ("Alarm message", aItem.getMsg().c_str());
	ASSERT_EQ(onh::AlarmDefinitionItem::T_BIN, aItem.getTrigger());
	ASSERT_TRUE(aItem.getTriggerValues().binVal);
	ASSERT_EQ((DWORD)0, aItem.getTriggerValues().dwVal);
	ASSERT_EQ(0, aItem.getTriggerValues().intVal);
	ASSERT_EQ((float)0, aItem.getTriggerValues().realVal);
	ASSERT_FALSE(aItem.isAutoAck());
	ASSERT_FALSE(aItem.isActive());
	ASSERT_FALSE(aItem.isPending());

	ASSERT_EQ((unsigned int)6, aItem.getFeedbackNotAckTag().getId());
	ASSERT_STREQ("tagFeedback", aItem.getFeedbackNotAckTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getFeedbackNotAckTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getFeedbackNotAckTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getFeedbackNotAckTag().getByteAddress());
	ASSERT_EQ((unsigned int)0, aItem.getFeedbackNotAckTag().getBitAddress());

	ASSERT_EQ((unsigned int)666, aItem.getHWAckTag().getId());
	ASSERT_STREQ("tagDevil", aItem.getHWAckTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getHWAckTag().getType());
	ASSERT_EQ(onh::PDA_OUTPUT, aItem.getHWAckTag().getArea());
	ASSERT_EQ((unsigned int)666, aItem.getHWAckTag().getByteAddress());
	ASSERT_EQ((unsigned int)2, aItem.getHWAckTag().getBitAddress());

	ASSERT_TRUE(aItem.isEnabled());
}

/**
 * Check alarm definition item set enable
 */
TEST_F(alarmDefinitionItemTests, CreateSetEnable) {

	onh::AlarmDefinitionItem aItem(
			1,
			*tg,
			1,
			"Alarm message",
			onh::AlarmDefinitionItem::T_BIN,
			onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
			false,
			false,
			false,
			*tgFeedback,
			*tgHWAck,
			true
	);

	aItem.setEnable(false);

	ASSERT_EQ((unsigned int)1, aItem.getId());

	ASSERT_EQ((unsigned int)5, aItem.getTag().getId());
	ASSERT_STREQ("TestTag1", aItem.getTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getTag().getByteAddress());
	ASSERT_EQ((unsigned int)6, aItem.getTag().getBitAddress());

	ASSERT_EQ((unsigned int)1, aItem.getPriority());
	ASSERT_STREQ("Alarm message", aItem.getMsg().c_str());
	ASSERT_EQ(onh::AlarmDefinitionItem::T_BIN, aItem.getTrigger());
	ASSERT_TRUE(aItem.getTriggerValues().binVal);
	ASSERT_EQ((DWORD)0, aItem.getTriggerValues().dwVal);
	ASSERT_EQ(0, aItem.getTriggerValues().intVal);
	ASSERT_EQ((float)0, aItem.getTriggerValues().realVal);
	ASSERT_FALSE(aItem.isAutoAck());
	ASSERT_FALSE(aItem.isActive());
	ASSERT_FALSE(aItem.isPending());

	ASSERT_EQ((unsigned int)6, aItem.getFeedbackNotAckTag().getId());
	ASSERT_STREQ("tagFeedback", aItem.getFeedbackNotAckTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getFeedbackNotAckTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getFeedbackNotAckTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getFeedbackNotAckTag().getByteAddress());
	ASSERT_EQ((unsigned int)0, aItem.getFeedbackNotAckTag().getBitAddress());

	ASSERT_EQ((unsigned int)7, aItem.getHWAckTag().getId());
	ASSERT_STREQ("tagHWAck", aItem.getHWAckTag().getName().c_str());
	ASSERT_EQ(onh::TT_BIT, aItem.getHWAckTag().getType());
	ASSERT_EQ(onh::PDA_MEMORY, aItem.getHWAckTag().getArea());
	ASSERT_EQ((unsigned int)4, aItem.getHWAckTag().getByteAddress());
	ASSERT_EQ((unsigned int)1, aItem.getHWAckTag().getBitAddress());

	ASSERT_FALSE(aItem.isEnabled());
}

/**
 * Check alarm definition item creation wrong id
 */
TEST_F(alarmDefinitionItemTests, CreateException1) {

	try {

		onh::AlarmDefinitionItem aItem(
				0,
				*tg,
				1,
				"Alarm message",
				onh::AlarmDefinitionItem::T_BIN,
				onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
				false,
				false,
				false,
				*tgFeedback,
				*tgHWAck,
				true
		);

		FAIL() << "Expected onh::AlarmException";

	} catch (onh::AlarmException &e) {

		ASSERT_STREQ(e.what(), "AlarmDefinitionItem::checkId: Invalid alarm definition identifier");
		ASSERT_EQ(onh::AlarmException::WRONG_ID, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::AlarmException";
	}
}

/**
 * Check alarm definition item creation wrong message
 */
TEST_F(alarmDefinitionItemTests, CreateException2) {

	try {

		onh::AlarmDefinitionItem aItem(
				1,
				*tg,
				1,
				"",
				onh::AlarmDefinitionItem::T_BIN,
				onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
				false,
				false,
				false,
				*tgFeedback,
				*tgHWAck,
				true
		);

		FAIL() << "Expected onh::AlarmException";

	} catch (onh::AlarmException &e) {

		ASSERT_STREQ(e.what(), "AlarmDefinitionItem::getMsg: Message string is empty");
		ASSERT_EQ(onh::AlarmException::WRONG_MSG, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::AlarmException";
	}
}

/**
 * Check alarm definition item creation wrong trigger
 */
TEST_F(alarmDefinitionItemTests, CreateException3) {

	try {

		onh::AlarmDefinitionItem aItem(
				1,
				*tg,
				1,
				"Alarm message",
				(onh::AlarmDefinitionItem::triggers)56,
				onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
				false,
				false,
				false,
				*tgFeedback,
				*tgHWAck,
				true
		);

		FAIL() << "Expected onh::AlarmException";

	} catch (onh::AlarmException &e) {

		ASSERT_STREQ(e.what(), "AlarmDefinitionItem::checkTrigger: Wrong trigger value");
		ASSERT_EQ(onh::AlarmException::WRONG_TRIGGER, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::AlarmException";
	}
}

/**
 * Check alarm definition item creation wrong feedback tag type
 */
TEST_F(alarmDefinitionItemTests, CreateException4) {

	try {

		onh::AlarmDefinitionItem aItem(
				1,
				*tg,
				1,
				"Alarm message",
				onh::AlarmDefinitionItem::T_BIN,
				onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
				false,
				false,
				false,
				*tgFeedback,
				*tgHWAck,
				true
		);

		onh::Tag tgFeedback2(
				68,
				"tagFeedback68",
				onh::TT_WORD,
				{onh::PDA_OUTPUT, 434, 0}
		);

		aItem.setFeedbackNotAckTag(tgFeedback2);

		FAIL() << "Expected onh::AlarmException";

	} catch (onh::AlarmException &e) {

		ASSERT_STREQ(e.what(), "AlarmDefinitionItem::checkBitTagType: Wrong tag type - need BIT type");
		ASSERT_EQ(onh::AlarmException::WRONG_TAG_TYPE, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::AlarmException";
	}
}

/**
 * Check alarm definition item creation wrong HW tag type
 */
TEST_F(alarmDefinitionItemTests, CreateException5) {

	try {

		onh::AlarmDefinitionItem aItem(
				1,
				*tg,
				1,
				"Alarm message",
				onh::AlarmDefinitionItem::T_BIN,
				onh::AlarmDefinitionItem::triggerValues(true, 0, 0, 0),
				false,
				false,
				false,
				*tgFeedback,
				*tgHWAck,
				true
		);

		onh::Tag tgHW2(
				68,
				"tagHW68",
				onh::TT_WORD,
				{onh::PDA_MEMORY, 434, 0}
		);

		aItem.setHWAckTag(tgHW2);

		FAIL() << "Expected onh::AlarmException";

	} catch (onh::AlarmException &e) {

		ASSERT_STREQ(e.what(), "AlarmDefinitionItem::checkBitTagType: Wrong tag type - need BIT type");
		ASSERT_EQ(onh::AlarmException::WRONG_TAG_TYPE, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::AlarmException";
	}
}

/**
 * Check alarm definition item creation default
 */
TEST_F(alarmDefinitionItemTests, CreateDefException1) {

	try {

		onh::AlarmDefinitionItem aItem;

		aItem.getId();

		FAIL() << "Expected onh::AlarmException";

	} catch (onh::AlarmException &e) {

		ASSERT_STREQ(e.what(), "AlarmDefinitionItem::checkId: Invalid alarm definition identifier");
		ASSERT_EQ(onh::AlarmException::WRONG_ID, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::AlarmException";
	}
}

/**
 * Check alarm definition item creation default
 */
TEST_F(alarmDefinitionItemTests, CreateDefException2) {

	try {

		onh::AlarmDefinitionItem aItem;

		aItem.getTag().getId();

		FAIL() << "Expected onh::AlarmException";

	} catch (onh::TagException &e) {

		ASSERT_STREQ(e.what(), "Tag::checkId: Invalid tag identifier");
		ASSERT_EQ(onh::TagException::WRONG_ID, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::AlarmException";
	}
}

/**
 * Check alarm definition item creation default
 */
TEST_F(alarmDefinitionItemTests, CreateDefException3) {

	try {

		onh::AlarmDefinitionItem aItem;

		aItem.getMsg();

		FAIL() << "Expected onh::AlarmException";

	} catch (onh::AlarmException &e) {

		ASSERT_STREQ(e.what(), "AlarmDefinitionItem::getMsg: Message string is empty");
		ASSERT_EQ(onh::AlarmException::WRONG_MSG, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::AlarmException";
	}
}

/**
 * Check alarm definition item creation default
 */
TEST_F(alarmDefinitionItemTests, CreateDefException4) {

	try {

		onh::AlarmDefinitionItem aItem;

		aItem.getFeedbackNotAckTag();

		FAIL() << "Expected onh::AlarmException";

	} catch (onh::AlarmException &e) {

		ASSERT_STREQ(e.what(), "AlarmDefinitionItem::getFeedbackNotAckTag: No feedback not ack tag");
		ASSERT_EQ(onh::AlarmException::NO_FEEDBACK_NOT_ACK_TAG, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::AlarmException";
	}
}

/**
 * Check alarm definition item creation default
 */
TEST_F(alarmDefinitionItemTests, CreateDefException5) {

	try {

		onh::AlarmDefinitionItem aItem;

		aItem.getHWAckTag();

		FAIL() << "Expected onh::AlarmException";

	} catch (onh::AlarmException &e) {

		ASSERT_STREQ(e.what(), "AlarmDefinitionItem::getHWAckTag: No HW ack tag");
		ASSERT_EQ(onh::AlarmException::NO_HW_ACK_TAG, e.getType());

	} catch(...) {
		FAIL() << "Expected onh::AlarmException";
	}
}

#endif /* TESTS_DB_OBJS_ALARMDEFINITIONITEMTESTS_H_ */
