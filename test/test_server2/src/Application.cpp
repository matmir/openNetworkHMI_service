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
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <sstream>
#include <string.h>
#include "controlBits/modbusControlBits_test.h"
#include "utils/Exception.h"

//#define debugMSG

Application::Application(const std::string &addr, const unsigned int& port, const unsigned int& regCount, bool *exSignal):
	ctx(nullptr), mb_mapping(nullptr), exitProg(false), exitSignal(exSignal), clearProcess(false), exit(false), simData(false), simData1(false)
{
	// Create modbus
	ctx = modbus_new_tcp(addr.c_str(), port);

	// Init registers
	mb_mapping = modbus_mapping_new(0, 0, regCount, regCount);
	if (mb_mapping == NULL) {

		modbus_free(ctx);

		std::stringstream s;
		s << "Failed to allocate the mapping: " << modbus_strerror(errno);

		throw onh::Exception(s.str(), "Application::Application");
	}
}

Application::~Application() {
	if (mb_mapping != nullptr)
		modbus_mapping_free(mb_mapping);

	if (ctx != nullptr) {
		modbus_close(ctx);
		modbus_free(ctx);
	}
}

void Application::run() {

	int s = -1;
	int rc;

	bool down = true;
	bool firstLoop = true;

	#ifdef debugMSG
		std::cout << "before listen\n";
	#endif
	s = modbus_tcp_listen(ctx, 1);
	#ifdef debugMSG
		std::cout << "after listen\n";
	#endif
	if (firstLoop) {
		// Create file informs that Modbus is ready
		system("touch modbusInited");
		firstLoop = false;
	}

	while (!exitProg && !(*exitSignal)) {

		try {

			if (down) {

				#ifdef debugMSG
					std::cout << "before accept\n";
				#endif
				modbus_tcp_accept(ctx, &s);
				#ifdef debugMSG
					std::cout << "after accept\n";
				#endif
				down = false;
			}

			#ifdef debugMSG
				std::cout << "before receive\n";
			#endif
			rc = modbus_receive(ctx, query);
			if (rc > 0) {
				#ifdef debugMSG
					std::cout << "receive ok\n";
				#endif
				/* rc is the query size */
				modbus_reply(ctx, query, rc, mb_mapping);
			#ifdef debugMSG
				std::cout << "reply\n";
			#endif

				clearQuery();
			} else { // client disconnected or error

				down = true;
			#ifdef debugMSG
				std::cout << "client down\n";
			#endif
			}

			// Update control flags
			updateControlFlags();

			// Check control bits
			checkControlBits();

			// Tag logger sim
			tagLoggerSim();

			// Wait
			std::this_thread::sleep_for(std::chrono::milliseconds(1));

			#ifdef debugMSG
				std::cout << "-----------------\n";
			#endif

		} catch(std::exception &e) {

			exitProg = true;
			std::cout << e.what() << std::endl;
		}
	}

	if (s != -1) {
		close(s);
	}

	std::cout << "Server program is closing..." << std::endl;

	// Give client app time to close
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	// Remove init flag
	system("rm -f modbusInited");
}

void Application::updateControlFlags() {

	// Control register
	uint16_t reg = mb_mapping->tab_registers[0];

	// Read control bits
	clearProcess = (reg >> 1 & 0x01);
	exit = (reg >> 2 & 0x01);
	simData = (reg >> 3 & 0x01);
	simData1 = (reg >> 4 & 0x01);
}

void Application::checkControlBits() {

	// Clear process data
	if (clearProcess) {
		for (int i=0; i<mb_mapping->nb_input_registers; ++i) {
			mb_mapping->tab_input_registers[i] = 0;
			mb_mapping->tab_registers[i] = 0;
		}
	}

	// Exit server
	if (exit) {
		exitProg = true;
	}
}

void Application::tagLoggerSim() {

	uint16_t reg = 0;
	uint16_t regTmp = 0;
	uint8_t b = 0;

	int *pInt = nullptr;
	float *pReal = nullptr;
	float rVal = 0;

	// Read simulation flag
	if (simData) {

		// Read logger data flag
		if (simData1) {

			// BIT
			mb_mapping->tab_input_registers[1] = 0;

			// BYTE 78 and 37 in one register
			b = 78;
			reg = b << 8;
			regTmp = 37;
			reg = (reg | regTmp);
			mb_mapping->tab_input_registers[2] = reg;

			// WORD
			mb_mapping->tab_input_registers[3] = 42001;
			mb_mapping->tab_input_registers[4] = 15120;

			// DWORD
			// 158653
			mb_mapping->tab_input_registers[5] = 27581;
			mb_mapping->tab_input_registers[6] = 2;
			// 258654
			mb_mapping->tab_input_registers[7] = 62046;
			mb_mapping->tab_input_registers[8] = 3;

			// INT
			pInt = (int*)&mb_mapping->tab_input_registers[9];
			*pInt = -1300;
			pInt = (int*)&mb_mapping->tab_input_registers[11];
			*pInt = -10;

			// REAL
			pReal = (float*)&mb_mapping->tab_input_registers[13];
			rVal = 9.78;
			memcpy(pReal, &rVal, sizeof rVal);
			pReal = (float*)&mb_mapping->tab_input_registers[15];
			rVal = 2.15;
			memcpy(pReal, &rVal, sizeof rVal);
		} else {

			// BIT
			mb_mapping->tab_input_registers[1] = 1;

			// BYTE 55 and 210 in one register
			b = 55;
			reg = b << 8;
			regTmp = 210;
			reg = (reg | regTmp);
			mb_mapping->tab_input_registers[2] = reg;

			// WORD
			mb_mapping->tab_input_registers[3] = 20478;
			mb_mapping->tab_input_registers[4] = 35120;

			// DWORD
			// 784566
			mb_mapping->tab_input_registers[5] = 63670;
			mb_mapping->tab_input_registers[6] = 11;
			// 658654
			mb_mapping->tab_input_registers[7] = 3294;
			mb_mapping->tab_input_registers[8] = 10;

			// INT
			pInt = (int*)&mb_mapping->tab_input_registers[9];
			*pInt = -410;
			pInt = (int*)&mb_mapping->tab_input_registers[11];
			*pInt = -12;

			// REAL
			pReal = (float*)&mb_mapping->tab_input_registers[13];
			rVal = 3.07;
			memcpy(pReal, &rVal, sizeof rVal);
			pReal = (float*)&mb_mapping->tab_input_registers[15];
			rVal = 2.16;
			memcpy(pReal, &rVal, sizeof rVal);
		}
	}
}

void Application::clearQuery() {

	for (unsigned int i=0; i<MODBUS_TCP_MAX_ADU_LENGTH; ++i) {
		query[i] = 0;
	}
}
