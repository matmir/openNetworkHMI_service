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

#ifndef SERVERCONTROLBITS_TEST_H_
#define SERVERCONTROLBITS_TEST_H_

// Client/server synchronization bit
#define BIT_SYNC {onh::PDA_MEMORY, 0, 0}

// Clear server process data
#define BIT_CLEAR_PROCESS {onh::PDA_MEMORY, 0, 1}

// Tag Logger
#define TEST_LOG_SIM1 {onh::PDA_INPUT, 99, 0}
#define TEST_LOG_DATA1 {onh::PDA_INPUT, 99, 1}
#define TEST_LOG_BIT1 {onh::PDA_INPUT, 100, 0}
#define TEST_LOG_BIT2 {onh::PDA_INPUT, 200, 0}
#define TEST_LOG_BYTE1 {onh::PDA_INPUT, 101, 0}
#define TEST_LOG_BYTE2 {onh::PDA_INPUT, 201, 0}
#define TEST_LOG_WORD1 {onh::PDA_INPUT, 102, 0}
#define TEST_LOG_WORD2 {onh::PDA_INPUT, 202, 0}
#define TEST_LOG_DWORD1 {onh::PDA_INPUT, 104, 0}
#define TEST_LOG_DWORD2 {onh::PDA_INPUT, 204, 0}
#define TEST_LOG_INT1 {onh::PDA_INPUT, 108, 0}
#define TEST_LOG_INT2 {onh::PDA_INPUT, 208, 0}
#define TEST_LOG_REAL1 {onh::PDA_INPUT, 120, 0}
#define TEST_LOG_REAL2 {onh::PDA_INPUT, 220, 0}

#endif /* SERVERCONTROLBITS_TEST_H_ */
