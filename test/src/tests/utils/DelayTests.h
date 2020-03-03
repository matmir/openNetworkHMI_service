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

#ifndef DELAYTESTS_H_
#define DELAYTESTS_H_

#include <gtest/gtest.h>
#include <utils/Delay.h>
#include <utils/CycleTime.h>
#include <unistd.h>

/**
 * Check wait
 */
TEST(DelayTests, Wait1) {

	onh::Delay d(30);
	onh::CycleTime ct;
	onh::CycleTimeData cdt;

	ct.start();
	d.wait();
	ct.stop();

	cdt = ct.getCycle();

	ASSERT_TRUE((cdt.current>=30)?(true):(false));
}

/**
 * Check wait
 */
TEST(DelayTests, Wait2) {

	onh::Delay d(50);
	onh::CycleTime ct;
	onh::CycleTimeData cdt;

	d.startDelay();
	// Sleep 10ms
	usleep(10000);

	ct.start();
	d.waitAfterStart();
	ct.stop();

	cdt = ct.getCycle();

	ASSERT_TRUE((cdt.current<50)?(true):(false)) << "Current cycle is: " << cdt.current;
}

#endif /* DELAYTESTS_H_ */
