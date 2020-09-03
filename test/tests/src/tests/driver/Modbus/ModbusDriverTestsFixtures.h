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

#ifndef TESTS_DRIVER_MODBUS_MODBUSDRIVERTESTSFIXTURES_H_
#define TESTS_DRIVER_MODBUS_MODBUSDRIVERTESTSFIXTURES_H_

#include <gtest/gtest.h>
#include <driver/Modbus/ModbusDriver.h>
#include <modbusControlBits_test.h>
#include <unistd.h>
#include "../../testGlobalData.h"

class modbusDriverTests: public ::testing::Test {
	protected:

		static void SetUpTestSuite() {

			modbusM::ModbusCfg mbc;
			mbc.mode = modbusM::MM_TCP;
			mbc.slaveID = 10;
			mbc.registerCount = MODBUS_REGS;
			mbc.TCP_addr = MODBUS_ADDR;
			mbc.TCP_port = MODBUS_PORT;

			// Create Modbus driver instance
			mbDriver = new onh::ModbusDriver(mbc);

			// Buffer updater
			mbUpd = mbDriver->getBuffer();

			// Create reader/writer/updater
			mbReader = mbDriver->getReader();
			mbWriter = mbDriver->getWriter();
			mbUpdater = mbDriver->getUpdater();
		}

		static void TearDownTestSuite() {

			if (mbReader)
				delete mbReader;

			if (mbWriter)
				delete mbWriter;

			if (mbUpdater)
				delete mbUpdater;

			if (mbUpd)
				delete mbUpd;

			if (mbDriver)
				delete mbDriver;
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
			mbWriter->setBit(MB_BIT_CLEAR_PROCESS);

			// Wait on synchronization
			waitOnSyncBit();
		}

		/**
		 * Wait on sync bit
		 */
		void waitOnSyncBit() {

			// Set sync bit server process data
			mbWriter->setBit(MB_BIT_SYNC);
			// Wait until server copy modified process data to SHM
			usleep(1500);
			// Update local process data (copy from server)
			mbUpd->updateBuffer();
			mbUpdater->updateProcessData();
			mbReader->updateProcessData();
			// Check sync bit to be 1
			while (!mbReader->getBitValue(MB_BIT_SYNC)) {
				// Sleep 1.5ms
				usleep(1500);
				// Update local process data (copy from server)
				mbUpd->updateBuffer();
				mbUpdater->updateProcessData();
				mbReader->updateProcessData();
			}

			// Reset sync bit server process data
			mbWriter->resetBit(MB_BIT_SYNC);
			// Wait until server copy modified process data to SHM
			usleep(1500);
			// Update local process data (copy from server)
			mbUpd->updateBuffer();
			mbUpdater->updateProcessData();
			mbReader->updateProcessData();
			// Check sync bit to be 0
			while (mbReader->getBitValue(MB_BIT_SYNC)) {
				// Sleep 1.5ms
				usleep(1500);
				// Update local process data (copy from server)
				mbUpd->updateBuffer();
				mbUpdater->updateProcessData();
				mbReader->updateProcessData();
			}
		}

		// Modbus driver instance
		static onh::ModbusDriver *mbDriver;

		// Modbus buffer updater
		static onh::DriverBuffer *mbUpd;

		// driver process reader
		static onh::DriverProcessReader *mbReader;
		// driver process writer
		static onh::DriverProcessWriter *mbWriter;
		// driver process updater
		static onh::DriverProcessUpdater *mbUpdater;

		static const unsigned int maxBytes = MODBUS_REGS*2;
};

onh::ModbusDriver* modbusDriverTests::mbDriver = nullptr;
onh::DriverBuffer* modbusDriverTests::mbUpd = nullptr;
onh::DriverProcessReader* modbusDriverTests::mbReader = nullptr;
onh::DriverProcessWriter* modbusDriverTests::mbWriter = nullptr;
onh::DriverProcessUpdater* modbusDriverTests::mbUpdater = nullptr;

#endif /* TESTS_DRIVER_MODBUS_MODBUSDRIVERTESTSFIXTURES_H_ */
