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

#include "Application.h"
#include "utils/Delay.h"
#include <iostream>
#include "controlBits/serverControlBits_test.h"

Application::Application(const std::string &smem, bool *exSignal):
	shmServer(smem), exitProg(false), exitSignal(exSignal)
{
	// Create process data access
	pda = new onh::processDataAccess(shmServer.getProcessAccess());
}

Application::~Application() {
	if (pda)
		delete pda;
}

void Application::run() {

	onh::Delay d(1);

	// Create file informs that SHM is ready
	system("touch shmInited");

	while (!exitProg && !(*exitSignal)) {

		try {

			// Parse client commands
			shmServer.parseClientCommand();

			// Check control bits
			checkControlBits();

			// Tag logger sim
			tagLoggerSim();

			// Copy process data to SHM
			shmServer.copyProcessData();

			// Check exit flag
			exitProg = shmServer.isExitFlag();

			d.wait();

		} catch(std::exception &e) {

			exitProg = true;
			std::cout << e.what() << std::endl;
		}
	}

	std::cout << "Server program is closing..." << std::endl;

	// Give client app time to close
	d.setDelay(1000);
	d.wait();

	// Remove init flag
	system("rm -f shmInited");
}

void Application::checkControlBits() {

	// Clear process data
	if (pda->getBit(BIT_CLEAR_PROCESS)) {
		shmServer.clearProcessData(true, false);
	}
}

void Application::tagLoggerSim() {

	// Read simulation flag
	if (pda->getBit(TEST_LOG_SIM1)) {

		// Read logger data flag
		if (pda->getBit(TEST_LOG_DATA1)) {

			// BIT
			pda->invertBit(TEST_LOG_BIT1);
			pda->setBit(TEST_LOG_BIT2);

			// BYTE
			pda->writeByte(TEST_LOG_BYTE1, 150);
			pda->writeByte(TEST_LOG_BYTE2, 250);

			// WORD
			pda->writeWord(TEST_LOG_WORD1, 35120);
			pda->writeWord(TEST_LOG_WORD2, 15120);

			// DWORD
			pda->writeDWord(TEST_LOG_DWORD1, 158654);
			pda->writeDWord(TEST_LOG_DWORD2, 258654);

			// INT
			pda->writeInt(TEST_LOG_INT1, -1200);
			pda->writeInt(TEST_LOG_INT2, -10);

			// REAL
			pda->writeReal(TEST_LOG_REAL1, 3.78);
			pda->writeReal(TEST_LOG_REAL2, 2.15);
		} else {

			// BIT
			pda->invertBit(TEST_LOG_BIT1);
			pda->resetBit(TEST_LOG_BIT2);

			// BYTE
			pda->writeByte(TEST_LOG_BYTE1, 55);
			pda->writeByte(TEST_LOG_BYTE2, 210);

			// WORD
			pda->writeWord(TEST_LOG_WORD1, 12120);
			pda->writeWord(TEST_LOG_WORD2, 35120);

			// DWORD
			pda->writeDWord(TEST_LOG_DWORD1, 558654);
			pda->writeDWord(TEST_LOG_DWORD2, 658654);

			// INT
			pda->writeInt(TEST_LOG_INT1, -1201);
			pda->writeInt(TEST_LOG_INT2, -12);

			// REAL
			pda->writeReal(TEST_LOG_REAL1, 3.79);
			pda->writeReal(TEST_LOG_REAL2, 2.16);
		}
	}
}
