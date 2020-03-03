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

#ifndef TESTS_DRIVER_DRIVERTESTSFIXTURES_H_
#define TESTS_DRIVER_DRIVERTESTSFIXTURES_H_

#include <driver/ProcessManager.h>
#include "SHM/ShmDriverTestsFixtures.h"

class driverTests: public shmDriverTests {
	protected:

		void SetUp() override {

			shmDriverTests::SetUp();

			// Driver
			driver = shmDriver;

			// Process Manager
			procM = new onh::ProcessManager(driver, 0);

			// Process Reader
			procReader = new onh::ProcessReader(procM->getReader());

			// Process Writer
			procWriter = new onh::ProcessWriter(procM->getWriter());

			// Process Updater
			procUpdater = new onh::ProcessUpdater(procM->getUpdater());

			// Test Tag
			testTag = new onh::Tag(
					14,
					"TestTag1",
					onh::TT_BIT,
					{onh::PDA_INPUT, 0, 0}
			);
		}

		void TearDown() override {
			if (testTag)
				delete testTag;

			if (procUpdater)
				delete procUpdater;

			if (procWriter)
				delete procWriter;

			if (procReader)
				delete procReader;

			if (procM)
				delete procM;

			shmDriverTests::TearDown();
		}

		void waitOnSyncBit() {

			// Call base method
			shmDriverTests::waitOnSyncBit();

			// Update reader object
			procReader->updateProcessData();
		}

		// Driver handle
		onh::Driver *driver;

		// Process manager instance
		onh::ProcessManager *procM;

		// Process reader instance
		onh::ProcessReader *procReader;

		// Process writer instance
		onh::ProcessWriter *procWriter;

		// Process updater instance
		onh::ProcessUpdater *procUpdater;

		// Test tag
		onh::Tag *testTag;
};

#endif /* TESTS_DRIVER_DRIVERTESTSFIXTURES_H_ */
