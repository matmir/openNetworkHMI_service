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

#ifndef TESTS_DRIVER_PROCESSUPDATERTESTS_H_
#define TESTS_DRIVER_PROCESSUPDATERTESTS_H_

#include <gtest/gtest.h>
#include "DriverTestsFixtures.h"

/**
 * Check process updater update
 */
TEST_F(driverTests, processUpdaterUpdate) {

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
		ASSERT_EQ(0, shmReader->getByte({onh::PDA_MEMORY, i, 0}));
	}

	// Change bit
	procWriter->setBit(*testTag);

	// Update local process data (copy from server)
	procUpdater->update();
	procReader->updateProcessData();
	shmReader->updateProcessData();
	// Check bit to be 1
	while (!procReader->getBitValue(*testTag)) {
		// Sleep 1.5ms
		usleep(1500);
		// Update local process data (copy from server)
		procUpdater->update();
		procReader->updateProcessData();
	}

	shmReader->updateProcessData();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		if (i == 0) {
			ASSERT_EQ(1, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		} else {
			ASSERT_EQ(0, shmReader->getByte({onh::PDA_INPUT, i, 0}));
		}

		ASSERT_EQ(0, shmReader->getByte({onh::PDA_OUTPUT, i, 0}));
	}
}

#endif /* TESTS_DRIVER_PROCESSUPDATERTESTS_H_ */
