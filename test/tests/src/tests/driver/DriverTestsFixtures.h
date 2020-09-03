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

#include <gtest/gtest.h>
#include <serverControlBits_test.h>
#include <unistd.h>
#include "../testGlobalData.h"
#include <driver/DriverManager.h>

class driverTests: public ::testing::Test {
	protected:

		static void SetUpTestSuite() {

			// Driver connection
			dcv.clear();
			dc.setId(1);
			dc.setName("TestConn");
			dc.setType(onh::DriverType::DT_SHM);
			dc.setEnable(true);
			dc.setShmCfg(SHM_SEGMENT_NAME);
			dcv.push_back(dc);

			// Driver Manager
			drvM = new onh::DriverManager(dcv);

			// Process Reader
			procReader = new onh::ProcessReader(drvM->getProcessReader());

			// Process Writer
			procWriter = new onh::ProcessWriter(drvM->getProcessWriter());

			// Process Updater
			procUpdater = new onh::ProcessUpdater(drvM->getProcessUpdaters()[0].procUpdater);
		}

		static void TearDownTestSuite() {

			if (procUpdater)
				delete procUpdater;

			if (procWriter)
				delete procWriter;

			if (procReader)
				delete procReader;

			if (drvM)
				delete drvM;
		}

		void SetUp() override {

			// Test Tag
			testTag = new onh::Tag(
					14,
					dc.getId(),
					"TestTag1",
					onh::TT_BIT,
					{onh::PDA_INPUT, 0, 0}
			);

			// Clear Tag
			clearTag = new onh::Tag(
					15,
					dc.getId(),
					"ClearTag1",
					onh::TT_BIT,
					BIT_CLEAR_PROCESS
			);
			// Sync Tag
			syncTag = new onh::Tag(
					16,
					dc.getId(),
					"SyncTag1",
					onh::TT_BIT,
					BIT_SYNC
			);

			// Clear server process data
			clearServerProcessData();
		}

		void TearDown() override {
			if (testTag)
				delete testTag;
			if (clearTag)
				delete clearTag;
			if (syncTag)
				delete syncTag;
		}

		/**
		 * Create test Byte tag
		 *
		 * @param addr Process data address
		 *
		 * @return Test Byte Tag
		 */
		onh::Tag createByteTag(const onh::processDataAddress& addr) {

			return onh::Tag(
					1,
					dc.getId(),
					"TestTag1",
					onh::TT_BYTE,
					addr
			);
		}

		/**
		 * Create test Word tag
		 *
		 * @param addr Process data address
		 *
		 * @return Test Word Tag
		 */
		onh::Tag createWordTag(const onh::processDataAddress& addr) {

			return onh::Tag(
					1,
					dc.getId(),
					"TestTag1",
					onh::TT_WORD,
					addr
			);
		}

		/**
		 * Create test DWord tag
		 *
		 * @param addr Process data address
		 *
		 * @return Test DWord Tag
		 */
		onh::Tag createDWordTag(const onh::processDataAddress& addr) {

			return onh::Tag(
					1,
					dc.getId(),
					"TestTag1",
					onh::TT_DWORD,
					addr
			);
		}

		/**
		 * Create test Int tag
		 *
		 * @param addr Process data address
		 *
		 * @return Test Int Tag
		 */
		onh::Tag createIntTag(const onh::processDataAddress& addr) {

			return onh::Tag(
					1,
					dc.getId(),
					"TestTag1",
					onh::TT_INT,
					addr
			);
		}

		/**
		 * Create test Real tag
		 *
		 * @param addr Process data address
		 *
		 * @return Test Real Tag
		 */
		onh::Tag createRealTag(const onh::processDataAddress& addr) {

			return onh::Tag(
					1,
					dc.getId(),
					"TestTag1",
					onh::TT_REAL,
					addr
			);
		}

		/**
		 * Clear server process data
		 */
		void clearServerProcessData() {

			// Set clear bit in server
			procWriter->setBit(*clearTag);

			// Wait on synchronization
			waitOnSyncBit();
		}

		/**
		 * Wait on sync bit
		 */
		void waitOnSyncBit() {

			// Set sync bit server process data
			procWriter->setBit(*syncTag);
			// Wait until server copy modified process data to SHM
			usleep(1500);
			// Update local process data (copy from server)
			procUpdater->update();
			procReader->updateProcessData();
			// Check sync bit to be 1
			while (!procReader->getBitValue(*syncTag)) {
				// Sleep 1.5ms
				usleep(1500);
				// Update local process data (copy from server)
				procUpdater->update();
				procReader->updateProcessData();
			}

			// Reset sync bit server process data
			procWriter->resetBit(*syncTag);
			// Wait until server copy modified process data to SHM
			usleep(1500);
			// Update local process data (copy from server)
			procUpdater->update();
			procReader->updateProcessData();
			// Check sync bit to be 0
			while (procReader->getBitValue(*syncTag)) {
				// Sleep 1.5ms
				usleep(1500);
				// Update local process data (copy from server)
				procUpdater->update();
				procReader->updateProcessData();
			}
		}

		// Driver connection
		static std::vector<onh::DriverConnection> dcv;
		static onh::DriverConnection dc;

		// Driver manager instance
		static onh::DriverManager *drvM;

		// Process reader instance
		static onh::ProcessReader *procReader;

		// Process writer instance
		static onh::ProcessWriter *procWriter;

		// Process updater instance
		static onh::ProcessUpdater *procUpdater;

		// Test tag
		onh::Tag *testTag;
		onh::Tag *clearTag;
		onh::Tag *syncTag;
};

std::vector<onh::DriverConnection> driverTests::dcv = {};
onh::DriverConnection driverTests::dc = onh::DriverConnection();
onh::DriverManager* driverTests::drvM = nullptr;
onh::ProcessReader* driverTests::procReader = nullptr;
onh::ProcessWriter* driverTests::procWriter = nullptr;
onh::ProcessUpdater* driverTests::procUpdater = nullptr;

#endif /* TESTS_DRIVER_DRIVERTESTSFIXTURES_H_ */
