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
#include <modbusControlBits_test.h>
#include <unistd.h>
#include "../testGlobalData.h"
#include <driver/DriverManager.h>

class driverTests: public ::testing::Test {

	public:
		driverTests(): testShmTag(), testModbusTag(),
						clearShmTag(15, dcSHM.getId(), "ClearShmTag1", onh::TT_BIT, BIT_CLEAR_PROCESS),
						syncShmTag(16, dcSHM.getId(), "SyncShmTag1", onh::TT_BIT, BIT_SYNC),
						clearModbusTag(15, dcModbus.getId(), "ClearModbusTag1", onh::TT_BIT, MB_BIT_CLEAR_PROCESS),
						syncModbusTag(16, dcModbus.getId(), "SyncModbusTag1", onh::TT_BIT, MB_BIT_SYNC)

		{
		}

	protected:

		static void SetUpTestSuite() {

			// Driver connection
			std::vector<onh::DriverConnection> dcv;

			// SHM driver
			dcSHM.setId(1);
			dcSHM.setName("TestConn1");
			dcSHM.setType(onh::DriverType::DT_SHM);
			dcSHM.setEnable(true);
			dcSHM.setShmCfg(SHM_SEGMENT_NAME);
			dcv.push_back(dcSHM);

			// Modbus driver
			dcModbus.setId(2);
			dcModbus.setName("TestConn2");
			dcModbus.setType(onh::DriverType::DT_Modbus);
			dcModbus.setEnable(true);
			// Modbus configuration
			modbusM::ModbusCfg mbc;
			mbc.mode = modbusM::MM_TCP;
			mbc.slaveID = 10;
			mbc.registerCount = MODBUS_REGS;
			mbc.TCP_addr = MODBUS_ADDR;
			mbc.TCP_port = MODBUS_PORT;
			dcModbus.setModbusCfg(mbc);
			dcv.push_back(dcModbus);

			// Driver Manager
			drvM = new onh::DriverManager(dcv);

			// Process Reader
			procReader = new onh::ProcessReader(drvM->getProcessReader());

			// Process Writer
			procWriter = new onh::ProcessWriter(drvM->getProcessWriter());

			// Process Updater
			std::vector<onh::ProcessUpdaterData> pu = drvM->getProcessUpdaters();
			procUpdaterSHM = new onh::ProcessUpdater(pu[0].procUpdater);
			procUpdaterModbus = new onh::ProcessUpdater(pu[1].procUpdater);

			// Driver buffers
			std::vector<onh::DriverBufferUpdaterData> buff = drvM->getDriverBufferUpdaters();
			buffUpdaterModbus = new onh::DriverBufferUpdater(buff[0].buffUpdater);
		}

		static void TearDownTestSuite() {

			if (buffUpdaterModbus)
				delete buffUpdaterModbus;

			if (procUpdaterSHM)
				delete procUpdaterSHM;
			if (procUpdaterModbus)
				delete procUpdaterModbus;


			if (procWriter)
				delete procWriter;

			if (procReader)
				delete procReader;

			if (drvM)
				delete drvM;
		}

		void SetUp() override {

			// Test SHM Tag
			testShmTag.setId(14);
			testShmTag.setConnId(dcSHM.getId());
			testShmTag.setName("TestShmTag1");
			testShmTag.setType(onh::TT_BIT);
			testShmTag.setAddress({onh::PDA_INPUT, 5, 0});

			// Test Modbus Tag
			testModbusTag.setId(12);
			testModbusTag.setConnId(dcModbus.getId());
			testModbusTag.setName("TestModbusTag1");
			testModbusTag.setType(onh::TT_BIT);
			testModbusTag.setAddress({onh::PDA_OUTPUT, 3, 2});

			// Clear server process data
			clearServerProcessData();
		}

		void TearDown() override {

		}

		/**
		 * Create test Byte tag
		 *
		 * @param addr Process data address
		 * @param shmT SHM tag creation flag
		 *
		 * @return Test Byte Tag
		 */
		onh::Tag createByteTag(const onh::processDataAddress& addr, onh::DriverType driverType = onh::DriverType::DT_SHM) {

			return onh::Tag(
					1,
					((driverType==onh::DriverType::DT_SHM)?(dcSHM.getId()):(dcModbus.getId())),
					"TestByteTag1",
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
		onh::Tag createWordTag(const onh::processDataAddress& addr, onh::DriverType driverType = onh::DriverType::DT_SHM) {

			return onh::Tag(
					1,
					((driverType==onh::DriverType::DT_SHM)?(dcSHM.getId()):(dcModbus.getId())),
					"TestWordTag1",
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
		onh::Tag createDWordTag(const onh::processDataAddress& addr, onh::DriverType driverType = onh::DriverType::DT_SHM) {

			return onh::Tag(
					1,
					((driverType==onh::DriverType::DT_SHM)?(dcSHM.getId()):(dcModbus.getId())),
					"TestDWordTag1",
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
		onh::Tag createIntTag(const onh::processDataAddress& addr, onh::DriverType driverType = onh::DriverType::DT_SHM) {

			return onh::Tag(
					1,
					((driverType==onh::DriverType::DT_SHM)?(dcSHM.getId()):(dcModbus.getId())),
					"TestIntTag1",
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
		onh::Tag createRealTag(const onh::processDataAddress& addr, onh::DriverType driverType = onh::DriverType::DT_SHM) {

			return onh::Tag(
					1,
					((driverType==onh::DriverType::DT_SHM)?(dcSHM.getId()):(dcModbus.getId())),
					"TestRealTag1",
					onh::TT_REAL,
					addr
			);
		}

		/**
		 * Clear server process data
		 */
		void clearServerProcessData() {

			// Set clear bit in server
			procWriter->setBit(clearShmTag);
			procWriter->setBit(clearModbusTag);

			// Wait on synchronization
			waitOnSyncBit();
		}

		/**
		 * Wait on sync bit in SHM
		 */
		void waitOnSyncBitShm() {

			// Set sync bit server process data
			procWriter->setBit(syncShmTag);
			// Wait until server copy modified process data to SHM
			usleep(1500);
			// Update local process data (copy from server)
			procUpdaterSHM->update();
			procReader->updateProcessData();
			// Check sync bit to be 1
			while (!procReader->getBitValue(syncShmTag)) {
				// Sleep 1.5ms
				usleep(1500);
				// Update local process data (copy from server)
				procUpdaterSHM->update();
				procReader->updateProcessData();
			}

			// Reset sync bit server process data
			procWriter->resetBit(syncShmTag);
			// Wait until server copy modified process data to SHM
			usleep(1500);
			// Update local process data (copy from server)
			procUpdaterSHM->update();
			procReader->updateProcessData();
			// Check sync bit to be 0
			while (procReader->getBitValue(syncShmTag)) {
				// Sleep 1.5ms
				usleep(1500);
				// Update local process data (copy from server)
				procUpdaterSHM->update();
				procReader->updateProcessData();
			}
		}

		/**
		 * Wait on sync bit in Modbus
		 */
		void waitOnSyncBitModbus() {

			// Set sync bit server process data
			procWriter->setBit(syncModbusTag);
			// Wait until server copy modified process data to SHM
			usleep(1500);
			// Update local process data (copy from server)
			buffUpdaterModbus->update();
			procUpdaterModbus->update();
			procReader->updateProcessData();
			// Check sync bit to be 1
			while (!procReader->getBitValue(syncModbusTag)) {
				// Sleep 1.5ms
				usleep(1500);
				// Update local process data (copy from server)
				buffUpdaterModbus->update();
				procUpdaterModbus->update();
				procReader->updateProcessData();
			}

			// Reset sync bit server process data
			procWriter->resetBit(syncModbusTag);
			// Wait until server copy modified process data to SHM
			usleep(1500);
			// Update local process data (copy from server)
			buffUpdaterModbus->update();
			procUpdaterModbus->update();
			procReader->updateProcessData();
			// Check sync bit to be 0
			while (procReader->getBitValue(syncModbusTag)) {
				// Sleep 1.5ms
				usleep(1500);
				// Update local process data (copy from server)
				buffUpdaterModbus->update();
				procUpdaterModbus->update();
				procReader->updateProcessData();
			}
		}

		/**
		 * Wait on sync bit
		 */
		void waitOnSyncBit() {

			waitOnSyncBitShm();
			waitOnSyncBitModbus();
		}

		/**
		 * Check all process data cleared
		 */
		void checkAllDataCleared() {
			// Check all process data
			for (unsigned int i=0; i<maxShmBytes; ++i) {
				ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0}))) << " i: " << i;
				ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}))) << " i: " << i;
				ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_MEMORY, i, 0}))) << " i: " << i;
			}
			for (unsigned int i=0; i<maxModbusBytes; ++i) {
				ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_INPUT, i, 0}, onh::DT_Modbus))) << " i: " << i;
				ASSERT_EQ(0, procReader->getByte(createByteTag({onh::PDA_OUTPUT, i, 0}, onh::DT_Modbus))) << " i: " << i;
			}
		}

		// Driver connection
		static onh::DriverConnection dcSHM, dcModbus;

		// Driver manager instance
		static onh::DriverManager *drvM;

		// Process reader instance
		static onh::ProcessReader *procReader;

		// Process writer instance
		static onh::ProcessWriter *procWriter;

		// Process updater instance
		static onh::ProcessUpdater *procUpdaterSHM;
		static onh::ProcessUpdater *procUpdaterModbus;

		// Driver buffers
		static onh::DriverBufferUpdater *buffUpdaterModbus;

		// Test tag
		onh::Tag testShmTag, testModbusTag;
		const onh::Tag clearShmTag;
		const onh::Tag syncShmTag;
		const onh::Tag clearModbusTag;
		const onh::Tag syncModbusTag;

		static const unsigned int maxModbusBytes = MODBUS_REGS*2;
		static const unsigned int maxShmBytes = PROCESS_DT_SIZE;
};

onh::DriverConnection driverTests::dcSHM = onh::DriverConnection();
onh::DriverConnection driverTests::dcModbus = onh::DriverConnection();
onh::DriverManager* driverTests::drvM = nullptr;
onh::ProcessReader* driverTests::procReader = nullptr;
onh::ProcessWriter* driverTests::procWriter = nullptr;
onh::ProcessUpdater* driverTests::procUpdaterSHM = nullptr;
onh::ProcessUpdater* driverTests::procUpdaterModbus = nullptr;
onh::DriverBufferUpdater* driverTests::buffUpdaterModbus = nullptr;

#endif /* TESTS_DRIVER_DRIVERTESTSFIXTURES_H_ */
