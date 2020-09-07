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

#ifndef MODBUSCONTROLBITS_TEST_H_
#define MODBUSCONTROLBITS_TEST_H_

// Client/server synchronization bit
#define MB_BIT_SYNC {onh::PDA_OUTPUT, 0, 0}

// Clear server process data
#define MB_BIT_CLEAR_PROCESS {onh::PDA_OUTPUT, 0, 1}

// Exit server
#define MB_BIT_EXIT {onh::PDA_OUTPUT, 0, 2}

// Tag Logger
#define MB_TEST_LOG_SIM1 {onh::PDA_OUTPUT, 0, 3}
#define MB_TEST_LOG_DATA1 {onh::PDA_OUTPUT, 0, 4}

#define MB_TEST_LOG_BIT1 {onh::PDA_INPUT, 2, 0}

#define MB_TEST_LOG_BYTE1 {onh::PDA_INPUT, 4, 0}
#define MB_TEST_LOG_BYTE2 {onh::PDA_INPUT, 5, 0}
#define MB_TEST_LOG_WORD1 {onh::PDA_INPUT, 6, 0}
#define MB_TEST_LOG_WORD2 {onh::PDA_INPUT, 8, 0}
#define MB_TEST_LOG_DWORD1 {onh::PDA_INPUT, 10, 0}
#define MB_TEST_LOG_DWORD2 {onh::PDA_INPUT, 14, 0}
#define MB_TEST_LOG_INT1 {onh::PDA_INPUT, 18, 0}
#define MB_TEST_LOG_INT2 {onh::PDA_INPUT, 22, 0}
#define MB_TEST_LOG_REAL1 {onh::PDA_INPUT, 26, 0}
#define MB_TEST_LOG_REAL2 {onh::PDA_INPUT, 30, 0}

#endif /* MODBUSCONTROLBITS_TEST_H_ */
