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
		void SetUp() override {

			// Remove all log files
			system("rm -r -f logs");

			// Create SHM driver instance
			shmDriver = new onh::ShmDriver(SHM_SEGMENT_NAME);

			// Create reader
			shmReader = shmDriver->getReader();

			// Clear server process data
			clearServerProcessData();
		}

		void TearDown() override {
			if (shmReader)
				delete shmReader;

			if (shmDriver)
				delete shmDriver;

			// Remove all logger files
			system("rm -r logs");
		}

		/**
		 * Clear server process data
		 */
		void clearServerProcessData() {

			// Set clear bit in server
			shmDriver->setBit(BIT_CLEAR_PROCESS);

			// Wait on synchronization
			waitOnSyncBit();
		}

		/**
		 * Wait on sync bit
		 */
		void waitOnSyncBit() {

			// Set sync bit server process data
			shmDriver->setBit(BIT_SYNC);
			// Wait until server copy modified process data to SHM
			usleep(1500);
			// Update local process data (copy from server)
			shmDriver->updateProcessData();
			shmReader->updateProcessData();
			// Check sync bit to be 1
			while (!shmReader->getBitValue(BIT_SYNC)) {
				// Sleep 1.5ms
				usleep(1500);
				// Update local process data (copy from server)
				shmDriver->updateProcessData();
				shmReader->updateProcessData();
			}

			// Reset sync bit server process data
			shmDriver->resetBit(BIT_SYNC);
			// Wait until server copy modified process data to SHM
			usleep(1500);
			// Update local process data (copy from server)
			shmDriver->updateProcessData();
			shmReader->updateProcessData();
			// Check sync bit to be 0
			while (shmReader->getBitValue(BIT_SYNC)) {
				// Sleep 1.5ms
				usleep(1500);
				// Update local process data (copy from server)
				shmDriver->updateProcessData();
				shmReader->updateProcessData();
			}
		}

		// SHM driver instance
		onh::ShmDriver *shmDriver;

		// driver process reader
		onh::DriverProcessReader * shmReader;
};

#endif /* TESTS_DRIVER_SHM_SHMDRIVERTESTSFIXTURES_H_ */
