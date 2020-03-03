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

#ifndef TESTS_DB_OBJS_ALARMDEFINITIONITEMTESTSFIXTURES_H_
#define TESTS_DB_OBJS_ALARMDEFINITIONITEMTESTSFIXTURES_H_

#include <gtest/gtest.h>
#include <db/objs/AlarmDefinitionItem.h>

class alarmDefinitionItemTests: public ::testing::Test {
	protected:
		void SetUp() override {

			tg = new onh::Tag(
					5,
					"TestTag1",
					onh::TT_BIT,
					{onh::PDA_MEMORY, 4, 6}
			);

			initFeedbackAndHWTag();
		}

		void TearDown() override {

			if (tg)
				delete tg;

			if (tgFeedback)
				delete tgFeedback;

			if (tgHWAck)
				delete tgHWAck;
		}

		void initFeedbackAndHWTag() {

			tgFeedback = new onh::Tag(
					6,
					"tagFeedback",
					onh::TT_BIT,
					{onh::PDA_MEMORY, 4, 0}
			);

			tgHWAck = new onh::Tag(
					7,
					"tagHWAck",
					onh::TT_BIT,
					{onh::PDA_MEMORY, 4, 1}
			);
		}

		// Tag
		onh::Tag *tg;

		// Tag feedback
		onh::Tag *tgFeedback;

		// Tag hw ACK
		onh::Tag *tgHWAck;
};

class alarmDefinitionItemTestsByte: public alarmDefinitionItemTests {
	protected:
		void SetUp() override {

			tg = new onh::Tag(
					5,
					"TestTag1",
					onh::TT_BYTE,
					{onh::PDA_MEMORY, 4, 0}
			);

			initFeedbackAndHWTag();
		}

		void TearDown() override {
			alarmDefinitionItemTests::TearDown();
		}
};

class alarmDefinitionItemTestsWord: public alarmDefinitionItemTests {
	protected:
		void SetUp() override {

			tg = new onh::Tag(
					5,
					"TestTag1",
					onh::TT_WORD,
					{onh::PDA_MEMORY, 4, 0}
			);

			initFeedbackAndHWTag();
		}

		void TearDown() override {
			alarmDefinitionItemTests::TearDown();
		}
};

class alarmDefinitionItemTestsDWord: public alarmDefinitionItemTests {
	protected:
		void SetUp() override {

			tg = new onh::Tag(
					5,
					"TestTag1",
					onh::TT_DWORD,
					{onh::PDA_MEMORY, 4, 0}
			);

			initFeedbackAndHWTag();
		}

		void TearDown() override {
			alarmDefinitionItemTests::TearDown();
		}
};

class alarmDefinitionItemTestsInt: public alarmDefinitionItemTests {
	protected:
		void SetUp() override {

			tg = new onh::Tag(
					5,
					"TestTag1",
					onh::TT_INT,
					{onh::PDA_MEMORY, 4, 0}
			);

			initFeedbackAndHWTag();
		}

		void TearDown() override {
			alarmDefinitionItemTests::TearDown();
		}
};

class alarmDefinitionItemTestsReal: public alarmDefinitionItemTests {
	protected:
		void SetUp() override {

			tg = new onh::Tag(
					5,
					"TestTag1",
					onh::TT_REAL,
					{onh::PDA_MEMORY, 4, 0}
			);

			initFeedbackAndHWTag();
		}

		void TearDown() override {
			alarmDefinitionItemTests::TearDown();
		}
};

#endif /* TESTS_DB_OBJS_ALARMDEFINITIONITEMTESTSFIXTURES_H_ */
