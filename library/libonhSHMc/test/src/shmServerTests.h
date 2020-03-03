/**
 * Copyright (c) 2020 Mateusz Mirosławski
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of mosquitto nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SHMSERVERTESTS_H_
#define SHMSERVERTESTS_H_

#include <gtest/gtest.h>
#include "pdaTestGlobalData.h"
#include "fixtures/shmServerClearTest.h"

/**
 * Check client DRV_CMD_EXIT
 */
TEST_F(shmServerClearTest, TestClientExitCommand1) {

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_CMD_EXIT;
	ssdt.shm->cs.data.len = 0;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_ERROR_NONE, serverErr);

	ASSERT_EQ(1, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_EXIT, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_CMD_EXIT wrong command length
 */
TEST_F(shmServerClearTest, TestClientExitCommand2) {

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_CMD_EXIT;
	ssdt.shm->cs.data.len = 2;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_DATA_LENGTH_INVALID, serverErr);

	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_NOK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_CMD_EXIT command data too long
 */
TEST_F(shmServerClearTest, TestClientExitCommand3) {

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_CMD_EXIT;
	ssdt.shm->cs.data.len = CMD_DATA_SIZE+3;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_DATA_LENGTH_OUT_OF_RANGE, serverErr);

	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_NOK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client invalid command
 */
TEST_F(shmServerClearTest, TestClientInvalidCommand) {

	// Prepare client command
	ssdt.shm->cs.data.command = 1489;
	ssdt.shm->cs.data.len = 3;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_INVALID_COMMAND, serverErr);

	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_NOK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_CMD_PING
 */
TEST_F(shmServerClearTest, TestClientPingCommand1) {

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_CMD_PING;
	ssdt.shm->cs.data.len = 0;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_ERROR_NONE, serverErr);

	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_PONG, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_CMD_PING wrong command length
 */
TEST_F(shmServerClearTest, TestClientPingCommand2) {

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_CMD_PING;
	ssdt.shm->cs.data.len = 1;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_DATA_LENGTH_INVALID, serverErr);

	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_NOK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_SET_BIT
 */
TEST_F(shmServerClearTest, TestClientSetBitCommand1) {

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_SET_BIT;
	ssdt.shm->cs.data.len = 3;
	ssdt.shm->cs.data.value[0] = DRV_PROC_MEM;
	ssdt.shm->cs.data.value[1] = 45;
	ssdt.shm->cs.data.value[2] = 5;
	ssdt.shm->cs.requestIn = 1;

	// Check process value
	ASSERT_EQ(0, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_MEMORY, 45, 5}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_ERROR_NONE, serverErr);

	// Check process value
	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_MEMORY, 45, 5}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Check SHM state
	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_OK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_SET_BIT wrong command length
 */
TEST_F(shmServerClearTest, TestClientSetBitCommand2) {

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_SET_BIT;
	ssdt.shm->cs.data.len = 7;
	ssdt.shm->cs.data.value[0] = DRV_PROC_MEM;
	ssdt.shm->cs.data.value[1] = 45;
	ssdt.shm->cs.data.value[2] = 5;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_DATA_LENGTH_INVALID, serverErr);

	// Check SHM state
	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_NOK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_SET_BIT wrong driver area
 */
TEST_F(shmServerClearTest, TestClientSetBitCommand3) {

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_SET_BIT;
	ssdt.shm->cs.data.len = 3;
	ssdt.shm->cs.data.value[0] = 807;
	ssdt.shm->cs.data.value[1] = 45;
	ssdt.shm->cs.data.value[2] = 5;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_INVALID_DRIVER_AREA, serverErr);

	// Check SHM state
	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_NOK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_RESET_BIT
 */
TEST_F(shmServerClearTest, TestClientResetBitCommand1) {

	// Set test bit
	procErr = PROCESS_SET_BIT(&procDT, processDataAddress{PDA_MEMORY, 10, 1});
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Check process value
	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_MEMORY, 10, 1}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_RESET_BIT;
	ssdt.shm->cs.data.len = 3;
	ssdt.shm->cs.data.value[0] = DRV_PROC_MEM;
	ssdt.shm->cs.data.value[1] = 10;
	ssdt.shm->cs.data.value[2] = 1;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_ERROR_NONE, serverErr);

	// Check process value
	ASSERT_EQ(0, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_MEMORY, 10, 1}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Check SHM state
	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_OK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_RESET_BIT wrong command length
 */
TEST_F(shmServerClearTest, TestClientResetBitCommand2) {

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_RESET_BIT;
	ssdt.shm->cs.data.len = 13;
	ssdt.shm->cs.data.value[0] = DRV_PROC_MEM;
	ssdt.shm->cs.data.value[1] = 10;
	ssdt.shm->cs.data.value[2] = 1;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_DATA_LENGTH_INVALID, serverErr);

	// Check SHM state
	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_NOK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_RESET_BIT wrong driver area
 */
TEST_F(shmServerClearTest, TestClientResetBitCommand3) {

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_RESET_BIT;
	ssdt.shm->cs.data.len = 3;
	ssdt.shm->cs.data.value[0] = 807;
	ssdt.shm->cs.data.value[1] = 10;
	ssdt.shm->cs.data.value[2] = 1;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_INVALID_DRIVER_AREA, serverErr);

	// Check SHM state
	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_NOK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_INVERT_BIT
 */
TEST_F(shmServerClearTest, TestClientInvertBitCommand1) {

	// Check process value
	ASSERT_EQ(0, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_MEMORY, 10, 1}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_INVERT_BIT;
	ssdt.shm->cs.data.len = 3;
	ssdt.shm->cs.data.value[0] = DRV_PROC_MEM;
	ssdt.shm->cs.data.value[1] = 10;
	ssdt.shm->cs.data.value[2] = 1;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_ERROR_NONE, serverErr);

	// Check process value
	ASSERT_EQ(1, PROCESS_GET_BIT(&procDT, processDataAddress{PDA_MEMORY, 10, 1}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Check SHM state
	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_OK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_INVERT_BIT wrong command length
 */
TEST_F(shmServerClearTest, TestClientInvertBitCommand2) {

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_INVERT_BIT;
	ssdt.shm->cs.data.len = 13;
	ssdt.shm->cs.data.value[0] = DRV_PROC_MEM;
	ssdt.shm->cs.data.value[1] = 10;
	ssdt.shm->cs.data.value[2] = 1;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_DATA_LENGTH_INVALID, serverErr);

	// Check SHM state
	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_NOK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_INVERT_BIT wrong driver area
 */
TEST_F(shmServerClearTest, TestClientInvertBitCommand3) {

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_INVERT_BIT;
	ssdt.shm->cs.data.len = 3;
	ssdt.shm->cs.data.value[0] = 807;
	ssdt.shm->cs.data.value[1] = 10;
	ssdt.shm->cs.data.value[2] = 1;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_INVALID_DRIVER_AREA, serverErr);

	// Check SHM state
	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_NOK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_SET_BITS
 */
TEST_F(shmServerClearTest, TestClientSetBitsCommand1) {

	// Return values
	char ret[] = {0, 0, 0};
	// Prepare addresses to get
	processDataAddress addr[] = {{PDA_INPUT, 1, 0},
									{PDA_MEMORY, 5, 2},
									{PDA_INPUT, 6, 3}};

	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_GET_BITS(&procDT, addr, ret, 3));

	ASSERT_EQ(0, ret[0]);
	ASSERT_EQ(0, ret[1]);
	ASSERT_EQ(0, ret[2]);

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_SET_BITS;
	ssdt.shm->cs.data.len = 9;
	ssdt.shm->cs.data.value[0] = DRV_PROC_IN;
	ssdt.shm->cs.data.value[1] = 1;
	ssdt.shm->cs.data.value[2] = 0;
	ssdt.shm->cs.data.value[3] = DRV_PROC_MEM;
	ssdt.shm->cs.data.value[4] = 5;
	ssdt.shm->cs.data.value[5] = 2;
	ssdt.shm->cs.data.value[6] = DRV_PROC_IN;
	ssdt.shm->cs.data.value[7] = 6;
	ssdt.shm->cs.data.value[8] = 3;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_ERROR_NONE, serverErr);

	// Check process value
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_GET_BITS(&procDT, addr, ret, 3));
	ASSERT_EQ(1, ret[0]);
	ASSERT_EQ(1, ret[1]);
	ASSERT_EQ(1, ret[2]);

	// Check SHM state
	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_OK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_SET_BITS wrong command length
 */
TEST_F(shmServerClearTest, TestClientSetBitsCommand2) {

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_SET_BITS;
	ssdt.shm->cs.data.len = 8;
	ssdt.shm->cs.data.value[0] = DRV_PROC_IN;
	ssdt.shm->cs.data.value[1] = 1;
	ssdt.shm->cs.data.value[2] = 0;
	ssdt.shm->cs.data.value[3] = DRV_PROC_MEM;
	ssdt.shm->cs.data.value[4] = 5;
	ssdt.shm->cs.data.value[5] = 2;
	ssdt.shm->cs.data.value[6] = DRV_PROC_IN;
	ssdt.shm->cs.data.value[7] = 6;
	ssdt.shm->cs.data.value[8] = 3;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_DATA_LENGTH_INVALID, serverErr);

	// Check SHM state
	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_NOK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_SET_BITS wrong driver area
 */
TEST_F(shmServerClearTest, TestClientSetBitsCommand3) {

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_SET_BITS;
	ssdt.shm->cs.data.len = 9;
	ssdt.shm->cs.data.value[0] = DRV_PROC_IN;
	ssdt.shm->cs.data.value[1] = 1;
	ssdt.shm->cs.data.value[2] = 0;
	ssdt.shm->cs.data.value[3] = 555;
	ssdt.shm->cs.data.value[4] = 5;
	ssdt.shm->cs.data.value[5] = 2;
	ssdt.shm->cs.data.value[6] = DRV_PROC_IN;
	ssdt.shm->cs.data.value[7] = 6;
	ssdt.shm->cs.data.value[8] = 3;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_INVALID_DRIVER_AREA, serverErr);

	// Check SHM state
	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_NOK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_WRITE_BYTE
 */
TEST_F(shmServerClearTest, TestClientWriteByteCommand1) {

	// Check process value
	ASSERT_EQ(0, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, 10, 0}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_WRITE_BYTE;
	ssdt.shm->cs.data.len = 3;
	ssdt.shm->cs.data.value[0] = DRV_PROC_MEM;
	ssdt.shm->cs.data.value[1] = 10;
	ssdt.shm->cs.data.value[2] = 149;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_ERROR_NONE, serverErr);

	// Check process value
	ASSERT_EQ(149, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, 10, 0}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Check SHM state
	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_OK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_WRITE_BYTE wrong command length
 */
TEST_F(shmServerClearTest, TestClientWriteByteCommand2) {

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_WRITE_BYTE;
	ssdt.shm->cs.data.len = 4;
	ssdt.shm->cs.data.value[0] = DRV_PROC_MEM;
	ssdt.shm->cs.data.value[1] = 10;
	ssdt.shm->cs.data.value[2] = 149;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_DATA_LENGTH_INVALID, serverErr);

	// Check SHM state
	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_NOK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_WRITE_BYTE wrong driver area
 */
TEST_F(shmServerClearTest, TestClientWriteByteCommand3) {

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_WRITE_BYTE;
	ssdt.shm->cs.data.len = 3;
	ssdt.shm->cs.data.value[0] = 34;
	ssdt.shm->cs.data.value[1] = 10;
	ssdt.shm->cs.data.value[2] = 149;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_INVALID_DRIVER_AREA, serverErr);

	// Check SHM state
	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_NOK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_WRITE_WORD
 */
TEST_F(shmServerClearTest, TestClientWriteWordCommand1) {

	// Check process value
	ASSERT_EQ(0, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_MEMORY, 10, 0}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_WRITE_WORD;
	ssdt.shm->cs.data.len = 3;
	ssdt.shm->cs.data.value[0] = DRV_PROC_MEM;
	ssdt.shm->cs.data.value[1] = 10;
	ssdt.shm->cs.data.value[2] = 51789;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_ERROR_NONE, serverErr);

	// Check process value
	ASSERT_EQ(51789, PROCESS_GET_WORD(&procDT, processDataAddress{PDA_MEMORY, 10, 0}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Check SHM state
	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_OK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_WRITE_WORD wrong command length
 */
TEST_F(shmServerClearTest, TestClientWriteWordCommand2) {

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_WRITE_WORD;
	ssdt.shm->cs.data.len = 1;
	ssdt.shm->cs.data.value[0] = DRV_PROC_MEM;
	ssdt.shm->cs.data.value[1] = 10;
	ssdt.shm->cs.data.value[2] = 51789;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_DATA_LENGTH_INVALID, serverErr);

	// Check SHM state
	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_NOK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_WRITE_WORD wrong driver area
 */
TEST_F(shmServerClearTest, TestClientWriteWordCommand3) {

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_WRITE_WORD;
	ssdt.shm->cs.data.len = 3;
	ssdt.shm->cs.data.value[0] = 965;
	ssdt.shm->cs.data.value[1] = 10;
	ssdt.shm->cs.data.value[2] = 51789;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_INVALID_DRIVER_AREA, serverErr);

	// Check SHM state
	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_NOK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_WRITE_DWORD
 */
TEST_F(shmServerClearTest, TestClientWriteDWordCommand1) {

	// Check process value
	ASSERT_EQ((DWORD)0, PROCESS_GET_DWORD(&procDT, processDataAddress{PDA_MEMORY, 10, 0}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_WRITE_DWORD;
	ssdt.shm->cs.data.len = 3;
	ssdt.shm->cs.data.value[0] = DRV_PROC_MEM;
	ssdt.shm->cs.data.value[1] = 10;
	ssdt.shm->cs.data.value[2] = 259347;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_ERROR_NONE, serverErr);

	// Check process value
	ASSERT_EQ((DWORD)259347, PROCESS_GET_DWORD(&procDT, processDataAddress{PDA_MEMORY, 10, 0}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Check SHM state
	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_OK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_WRITE_DWORD wrong command length
 */
TEST_F(shmServerClearTest, TestClientWriteDWordCommand2) {

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_WRITE_DWORD;
	ssdt.shm->cs.data.len = 1;
	ssdt.shm->cs.data.value[0] = DRV_PROC_MEM;
	ssdt.shm->cs.data.value[1] = 10;
	ssdt.shm->cs.data.value[2] = 259347;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_DATA_LENGTH_INVALID, serverErr);

	// Check SHM state
	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_NOK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_WRITE_DWORD wrong driver area
 */
TEST_F(shmServerClearTest, TestClientWriteDWordCommand3) {

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_WRITE_DWORD;
	ssdt.shm->cs.data.len = 3;
	ssdt.shm->cs.data.value[0] = 965;
	ssdt.shm->cs.data.value[1] = 10;
	ssdt.shm->cs.data.value[2] = 259347;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_INVALID_DRIVER_AREA, serverErr);

	// Check SHM state
	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_NOK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_WRITE_INT
 */
TEST_F(shmServerClearTest, TestClientWriteIntCommand1) {

	// Check process value
	ASSERT_EQ(0, PROCESS_GET_INT(&procDT, processDataAddress{PDA_MEMORY, 10, 0}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_WRITE_INT;
	ssdt.shm->cs.data.len = 3;
	ssdt.shm->cs.data.value[0] = DRV_PROC_MEM;
	ssdt.shm->cs.data.value[1] = 10;
	ssdt.shm->cs.data.value[2] = -384;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_ERROR_NONE, serverErr);

	// Check process value
	ASSERT_EQ(-384, PROCESS_GET_INT(&procDT, processDataAddress{PDA_MEMORY, 10, 0}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Check SHM state
	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_OK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_WRITE_INT wrong command length
 */
TEST_F(shmServerClearTest, TestClientWriteIntCommand2) {

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_WRITE_INT;
	ssdt.shm->cs.data.len = 1;
	ssdt.shm->cs.data.value[0] = DRV_PROC_MEM;
	ssdt.shm->cs.data.value[1] = 10;
	ssdt.shm->cs.data.value[2] = -384;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_DATA_LENGTH_INVALID, serverErr);

	// Check SHM state
	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_NOK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_WRITE_INT wrong driver area
 */
TEST_F(shmServerClearTest, TestClientWriteIntCommand3) {

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_WRITE_INT;
	ssdt.shm->cs.data.len = 3;
	ssdt.shm->cs.data.value[0] = 965;
	ssdt.shm->cs.data.value[1] = 10;
	ssdt.shm->cs.data.value[2] = -384;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_INVALID_DRIVER_AREA, serverErr);

	// Check SHM state
	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_NOK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_WRITE_REAL
 */
TEST_F(shmServerClearTest, TestClientWriteRealCommand1) {

	// Check process value
	ASSERT_EQ((float)0, PROCESS_GET_REAL(&procDT, processDataAddress{PDA_MEMORY, 10, 0}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_WRITE_REAL;
	ssdt.shm->cs.data.len = 3;
	ssdt.shm->cs.data.value[0] = DRV_PROC_MEM;
	ssdt.shm->cs.data.value[1] = 10;
	// Pointer to Real in shm command data
	float *pReal = (float*)&ssdt.shm->cs.data.value[2];
	*pReal = -304.178;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_ERROR_NONE, serverErr);

	// Check process value
	ASSERT_EQ((float)-304.178, PROCESS_GET_REAL(&procDT, processDataAddress{PDA_MEMORY, 10, 0}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Check SHM state
	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_OK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_WRITE_REAL wrong command length
 */
TEST_F(shmServerClearTest, TestClientWriteRealCommand2) {

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_WRITE_REAL;
	ssdt.shm->cs.data.len = 1;
	ssdt.shm->cs.data.value[0] = DRV_PROC_MEM;
	ssdt.shm->cs.data.value[1] = 10;
	// Pointer to Real in shm command data
	float *pReal = (float*)&ssdt.shm->cs.data.value[2];
	*pReal = -304.178;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_DATA_LENGTH_INVALID, serverErr);

	// Check SHM state
	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_NOK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check client DRV_WRITE_REAL wrong driver area
 */
TEST_F(shmServerClearTest, TestClientWriteRealCommand3) {

	// Prepare client command
	ssdt.shm->cs.data.command = DRV_WRITE_REAL;
	ssdt.shm->cs.data.len = 3;
	ssdt.shm->cs.data.value[0] = 666;
	ssdt.shm->cs.data.value[1] = 10;
	// Pointer to Real in shm command data
	float *pReal = (float*)&ssdt.shm->cs.data.value[2];
	*pReal = -304.178;
	ssdt.shm->cs.requestIn = 1;

	// Parse command in server
	serverErr = parseClientCommand(&ssdt, &exitFlag, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_INVALID_DRIVER_AREA, serverErr);

	// Check SHM state
	ASSERT_EQ(0, exitFlag);
	ASSERT_TRUE(ssdt.shm->cs.replyIn);
	ASSERT_FALSE(ssdt.shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_NOK, ssdt.shm->cs.data.command);
	ASSERT_EQ(0, ssdt.shm->cs.data.len);
}

/**
 * Check copy process data
 */
TEST_F(shmServerClearTest, TestCopyProcessData1) {

	// Modify local process data
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_INT(&procDT, processDataAddress{PDA_MEMORY, 10, 0}, -987));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_REAL(&procDT, processDataAddress{PDA_INPUT, 10, 0}, -13.78));
	ASSERT_EQ(PROCESS_ERROR_NONE, PROCESS_WRITE_BYTE(&procDT, processDataAddress{PDA_OUTPUT, 10, 0}, 45));

	// Check process value
	ASSERT_EQ(-987, PROCESS_GET_INT(&procDT, processDataAddress{PDA_MEMORY, 10, 0}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	ASSERT_EQ((float)-13.78, PROCESS_GET_REAL(&procDT, processDataAddress{PDA_INPUT, 10, 0}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	ASSERT_EQ(45, PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, 10, 0}, &procErr));
	ASSERT_EQ(PROCESS_ERROR_NONE, procErr);

	// Copy local process data to the SHM process
	serverErr = copyProcessData(&ssdt, &procDT, &shmErr);
	ASSERT_EQ(SHM_ERROR_NONE, shmErr);
	ASSERT_EQ(SERVER_ERROR_NONE, serverErr);

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(ssdt.shm->process.procDT.mem[i], PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_MEMORY, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		ASSERT_EQ(ssdt.shm->process.procDT.in[i], PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_INPUT, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
		ASSERT_EQ(ssdt.shm->process.procDT.out[i], PROCESS_GET_BYTE(&procDT, processDataAddress{PDA_OUTPUT, i, 0}, &procErr));
		ASSERT_EQ(PROCESS_ERROR_NONE, procErr);
	}
}

#endif /* SHMSERVERTESTS_H_ */
