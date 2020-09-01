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

#ifndef TESTS_DB_OBJS_SCRIPTITEMTESTSFIXTURES_H_
#define TESTS_DB_OBJS_SCRIPTITEMTESTSFIXTURES_H_

#include <gtest/gtest.h>
#include <db/objs/ScriptItem.h>

class scriptItemTests: public ::testing::Test {
	protected:
		void SetUp() override {

			tg = new onh::Tag(
					5,
					1,
					"TestTag1",
					onh::TT_BIT,
					{onh::PDA_INPUT, 4, 6}
			);

			fbTg = new onh::Tag(
					9,
					1,
					"TestTag2",
					onh::TT_BIT,
					{onh::PDA_MEMORY, 70, 0}
			);
		}

		void TearDown() override {
			if (tg)
				delete tg;

			if (fbTg)
				delete fbTg;
		}

		// Script tag
		onh::Tag *tg;

		// Feedback tag
		onh::Tag *fbTg;
};

#endif /* TESTS_DB_OBJS_SCRIPTITEMTESTSFIXTURES_H_ */
