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

#ifndef CYCLETIMETESTS_H_
#define CYCLETIMETESTS_H_

#include <gtest/gtest.h>
#include <unistd.h>
#include <utils/CycleTime.h>

/**
 * Check cycle time object
 */
TEST(CycleTimeTests, Cycle1) {

	onh::CycleTime ct;
	onh::CycleTimeData cdt1, cdt2, cdt3;

	// Start measure
	ct.start();
	// Sleep 2ms
	usleep(2000);
	// Stop measure
	ct.stop();

	cdt1 = ct.getCycle();

	ASSERT_EQ(cdt1.min, cdt1.current);
	ASSERT_EQ(cdt1.max, cdt1.current);

	// Start measure
	ct.start();
	// Sleep 50ms
	usleep(50000);
	// Stop measure
	ct.stop();

	cdt2 = ct.getCycle();

	ASSERT_EQ(cdt2.min, cdt1.min);
	ASSERT_EQ(cdt2.max, cdt2.current);

	// Start measure
	ct.start();
	// Sleep 15ms
	usleep(15000);
	// Stop measure
	ct.stop();

	cdt3 = ct.getCycle();

	ASSERT_EQ(cdt3.min, cdt1.min);
	ASSERT_EQ(cdt3.max, cdt2.max);
}

TEST(CycleTimeTests, Cycle2) {

	try {

		onh::CycleTime ct;

		ct.start();
		ct.start();

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "CycleTime::start: Cycle calculation already started");

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

TEST(CycleTimeTests, Cycle3) {

	try {

		onh::CycleTime ct;

		ct.stop();

		FAIL() << "Expected onh::Exception";

	} catch (onh::Exception &e) {

		ASSERT_STREQ(e.what(), "CycleTime::stop: Cycle calculation not started");

	} catch(...) {
		FAIL() << "Expected onh::TagException";
	}
}

#endif /* CYCLETIMETESTS_H_ */
