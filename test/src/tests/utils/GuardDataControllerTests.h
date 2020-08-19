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

#ifndef TEST_SRC_TESTS_UTILS_GUARDDATACONTROLLERTESTS_H_
#define TEST_SRC_TESTS_UTILS_GUARDDATACONTROLLERTESTS_H_

#include <gtest/gtest.h>
#include <utils/GuardDataContainer.h>
#include <driver/SHM/ShmProcessData.h>

/**
 * Check guard data controller object
 */
TEST(GuardDataControllerTests, Guard1) {

	int d1, d2;
	onh::GuardDataContainer<int> data;
	onh::GuardDataController<int> c1(data.getController(false));
	onh::GuardDataController<int> c2(data.getController());

	c1.getData(d1);
	c2.getData(d2);

	ASSERT_EQ(d1, 0);
	ASSERT_EQ(d2, 0);

	c1.setData(65);
	c1.getData(d1);
	c2.getData(d2);

	ASSERT_EQ(d1, 65);
	ASSERT_EQ(d2, 65);
}

TEST(GuardDataControllerTests, Guard2) {

	int d1, d2;
	onh::GuardDataContainer<int> data(66);
	onh::GuardDataController<int> c1(data.getController(false));
	onh::GuardDataController<int> c2(data.getController());

	c1.getData(d1);
	c2.getData(d2);

	ASSERT_EQ(d1, 66);
	ASSERT_EQ(d2, 66);

	c1.setData(65);
	c1.getData(d1);
	c2.getData(d2);

	ASSERT_EQ(d1, 65);
	ASSERT_EQ(d2, 65);
}

TEST(GuardDataControllerTests, Guard3) {

	int d1, d2;
	onh::GuardDataContainer<int> data1(200);
	onh::GuardDataContainer<int> data2(100);
	onh::GuardDataController<int> c1(data1.getController(false));
	onh::GuardDataController<int> c2(data2.getController());

	c1.getData(d1);
	c2.getData(d2);

	ASSERT_EQ(d1, 200);
	ASSERT_EQ(d2, 100);

	c1.setData(c2);

	c1.getData(d1);
	c2.getData(d2);

	ASSERT_EQ(d1, 100);
	ASSERT_EQ(d2, 100);
}

TEST(GuardDataControllerTests, GuardSHM1) {

	onh::ShmProcessData pd, pd1, pd2;

	processData shmPD;
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		shmPD.in[i] = 0;
		shmPD.out[i] = 0;
		shmPD.mem[i] = 0;
	}
	shmPD.in[400] = 130;

	onh::GuardDataContainer<onh::ShmProcessData> data(pd);
	onh::GuardDataController<onh::ShmProcessData> c1(data.getController(false));
	onh::GuardDataController<onh::ShmProcessData> c2(data.getController());

	c1.getData(pd1);
	c2.getData(pd2);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		ASSERT_EQ(pd1.getByte({onh::PDA_INPUT, i, 0}), 0);
		ASSERT_EQ(pd2.getByte({onh::PDA_INPUT, i, 0}), 0);
		ASSERT_EQ(pd1.getByte({onh::PDA_OUTPUT, i, 0}), 0);
		ASSERT_EQ(pd2.getByte({onh::PDA_OUTPUT, i, 0}), 0);
		ASSERT_EQ(pd1.getByte({onh::PDA_MEMORY, i, 0}), 0);
		ASSERT_EQ(pd2.getByte({onh::PDA_MEMORY, i, 0}), 0);
	}

	pd = shmPD;
	c1.setData(pd);

	c1.getData(pd1);
	c2.getData(pd2);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {

		if (i == 400) {
			ASSERT_EQ(pd1.getByte({onh::PDA_INPUT, i, 0}), 130);
			ASSERT_EQ(pd2.getByte({onh::PDA_INPUT, i, 0}), 130);
		} else {
			ASSERT_EQ(pd1.getByte({onh::PDA_INPUT, i, 0}), 0);
			ASSERT_EQ(pd2.getByte({onh::PDA_INPUT, i, 0}), 0);
		}

		ASSERT_EQ(pd1.getByte({onh::PDA_OUTPUT, i, 0}), 0);
		ASSERT_EQ(pd2.getByte({onh::PDA_OUTPUT, i, 0}), 0);
		ASSERT_EQ(pd1.getByte({onh::PDA_MEMORY, i, 0}), 0);
		ASSERT_EQ(pd2.getByte({onh::PDA_MEMORY, i, 0}), 0);
	}
}

/**
 * Check guard data controller exception
 */
TEST(GuardDataControllerTests, GuardException1) {

	onh::GuardDataContainer<int> data;
	onh::GuardDataController<int> c1(data.getController(false));
	onh::GuardDataController<int> c2(data.getController());

	try {

		c2.setData(13);

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "GuardDataController::setData: Data controller is in read only state");

	} catch(...) {
		FAIL() << "Expected onh::Exception";
	}
}

#endif /* TEST_SRC_TESTS_UTILS_GUARDDATACONTROLLERTESTS_H_ */
