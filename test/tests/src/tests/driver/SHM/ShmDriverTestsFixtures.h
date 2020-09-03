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

#ifndef TESTS_DRIVER_SHM_SHMDRIVERTESTSFIXTURES_H_
#define TESTS_DRIVER_SHM_SHMDRIVERTESTSFIXTURES_H_

#include <gtest/gtest.h>
#include <driver/SHM/ShmDriver.h>
#include <serverControlBits_test.h>
#include <unistd.h>
#include "../../testGlobalData.h"

class shmDriverTests: public ::testing::Test {
	protected:

		static void SetUpTestSuite() {

			// Create SHM driver instance
			shmDriver = new onh::ShmDriver(SHM_SEGMENT_NAME);

			// Create reader/writer/updater
			shmReader = shmDriver->getReader();
			shmWriter = shmDriver->getWriter();
			shmUpdater = shmDriver->getUpdater();
		}

		static void TearDownTestSuite() {

			if (shmReader)
				delete shmReader;

			if (shmWriter)
				delete shmWriter;

			if (shmUpdater)
				delete shmUpdater;

			if (shmDriver)
				delete shmDriver;
		}

		void SetUp() override {

			// Clear server process data
			clearServerProcessData();
		}

		void TearDown() override {

		}

		/**
		 * Clear server process data
		 */
		void clearServerProcessData() {

			// Set clear bit in server
			shmWriter->setBit(BIT_CLEAR_PROCESS);

			// Wait on synchronization
			waitOnSyncBit();
		}

		/**
		 * Wait on sync bit
		 */
		void waitOnSyncBit() {

			// Set sync bit server process data
			shmWriter->setBit(BIT_SYNC);
			// Wait until server copy modified process data to SHM
			usleep(1500);
			// Update local process data (copy from server)
			shmUpdater->updateProcessData();
			shmReader->updateProcessData();
			// Check sync bit to be 1
			while (!shmReader->getBitValue(BIT_SYNC)) {
				// Sleep 1.5ms
				usleep(1500);
				// Update local process data (copy from server)
				shmUpdater->updateProcessData();
				shmReader->updateProcessData();
			}

			// Reset sync bit server process data
			shmWriter->resetBit(BIT_SYNC);
			// Wait until server copy modified process data to SHM
			usleep(1500);
			// Update local process data (copy from server)
			shmUpdater->updateProcessData();
			shmReader->updateProcessData();
			// Check sync bit to be 0
			while (shmReader->getBitValue(BIT_SYNC)) {
				// Sleep 1.5ms
				usleep(1500);
				// Update local process data (copy from server)
				shmUpdater->updateProcessData();
				shmReader->updateProcessData();
			}
		}

		// SHM driver instance
		static onh::ShmDriver *shmDriver;

		// driver process reader
		static onh::DriverProcessReader *shmReader;
		// driver process writer
		static onh::DriverProcessWriter *shmWriter;
		// driver process updater
		static onh::DriverProcessUpdater *shmUpdater;
};

onh::ShmDriver* shmDriverTests::shmDriver = nullptr;
onh::DriverProcessReader* shmDriverTests::shmReader = nullptr;
onh::DriverProcessWriter* shmDriverTests::shmWriter = nullptr;
onh::DriverProcessUpdater* shmDriverTests::shmUpdater = nullptr;

#endif /* TESTS_DRIVER_SHM_SHMDRIVERTESTSFIXTURES_H_ */
