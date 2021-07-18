/**
 * This file is part of openNetworkHMI.
 * Copyright (c) 2021 Mateusz Mirosławski.
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

#ifndef ONH_THREAD_SOCKET_PARSER_COMMANDLIST_H_
#define ONH_THREAD_SOCKET_PARSER_COMMANDLIST_H_

#define CMD_SEPARATOR '|'
#define CMD_TAGS_SEPARATOR ','
#define CMD_TAG_VALUE_SEPARATOR ','

namespace onh {

/**
 * Query commands definition
 */
enum parserCMD {
	GET_BIT = 10,
	SET_BIT = 11,
	RESET_BIT = 12,
	INVERT_BIT = 13,

	GET_BITS = 20,
	SET_BITS = 21,

	GET_BYTE = 30,
	WRITE_BYTE = 31,

	GET_WORD = 32,
	WRITE_WORD = 33,

	GET_DWORD = 34,
	WRITE_DWORD = 35,

	GET_INT = 36,
	WRITE_INT = 37,

	GET_REAL = 38,
	WRITE_REAL = 39,

	MULTI_CMD = 50,

	ACK_ALARM = 90,

	GET_THREAD_CYCLE_TIME = 500,

	EXIT_APP = 600
};

/**
 * Reply commands definition
 */
enum parserReply {
	OK = 0,
	NOK = -1,

	NOT_EXIST = 5,
	WRONG_VALUE = 6,
	WRONG_TAG_TYPE = 7,
	WRONG_TAG_AREA = 8,
	WRONG_ADDR = 9,

	INTERNAL_ERR = 20,

	SQL_ERROR = 50,

	UNKNOWN_CMD = 99
};

}  // namespace onh

#endif  // ONH_THREAD_SOCKET_PARSER_COMMANDLIST_H_
