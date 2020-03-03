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
#include <onhSHMcpp/sCommands.h>
#include "pdaTestGlobalData.h"
#include "fixtures/shmServerClearTest.h"

using namespace onh;

/**
 * Check client DRV_CMD_EXIT
 */
TEST_F(shmServerClearTest, TestClientExitCommand1) {

	// Prepare client command
	shm->cs.data.command = DRV_CMD_EXIT;
	shm->cs.data.len = 0;
	shm->cs.requestIn = 1;

	// Parse command in server
	shmServer->parseClientCommand();

	ASSERT_TRUE(shmServer->isExitFlag());
	ASSERT_TRUE(shm->cs.replyIn);
	ASSERT_FALSE(shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_OK, shm->cs.data.command);
	ASSERT_EQ(0, shm->cs.data.len);
}

/**
 * Check client DRV_CMD_EXIT wrong command length
 */
TEST_F(shmServerClearTest, TestClientExitCommand2) {

	// Prepare client command
	shm->cs.data.command = DRV_CMD_EXIT;
	shm->cs.data.len = 4;
	shm->cs.requestIn = 1;

	try {
		// Parse command in server
		shmServer->parseClientCommand();

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "ShmServer::CMD_EXIT: Invalid command data length");

		ASSERT_FALSE(shmServer->isExitFlag());
		ASSERT_TRUE(shm->cs.replyIn);
		ASSERT_FALSE(shm->cs.requestIn);
		ASSERT_EQ(DRV_CMD_NOK, shm->cs.data.command);
		ASSERT_EQ(0, shm->cs.data.len);

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

/**
 * Check client DRV_CMD_EXIT command data too long
 */
TEST_F(shmServerClearTest, TestClientExitCommand3) {

	// Prepare client command
	shm->cs.data.command = DRV_CMD_EXIT;
	shm->cs.data.len = CMD_DATA_SIZE+3;
	shm->cs.requestIn = 1;

	try {
		// Parse command in server
		shmServer->parseClientCommand();

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "ShmServer::parseClientCommand: Command data length is out of range");

		ASSERT_FALSE(shmServer->isExitFlag());
		ASSERT_TRUE(shm->cs.replyIn);
		ASSERT_FALSE(shm->cs.requestIn);
		ASSERT_EQ(DRV_CMD_NOK, shm->cs.data.command);
		ASSERT_EQ(0, shm->cs.data.len);

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

/**
 * Check client invalid command
 */
TEST_F(shmServerClearTest, TestClientInvalidCommand) {

	// Prepare client command
	shm->cs.data.command = 1489;
	shm->cs.data.len = 3;
	shm->cs.requestIn = 1;

	try {
		// Parse command in server
		shmServer->parseClientCommand();

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "ShmServer::parseClientCommand: Invalid command");

		ASSERT_FALSE(shmServer->isExitFlag());
		ASSERT_TRUE(shm->cs.replyIn);
		ASSERT_FALSE(shm->cs.requestIn);
		ASSERT_EQ(DRV_CMD_NOK, shm->cs.data.command);
		ASSERT_EQ(0, shm->cs.data.len);

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

/**
 * Check client DRV_CMD_PING
 */
TEST_F(shmServerClearTest, TestClientPingCommand1) {

	// Prepare client command
	shm->cs.data.command = DRV_CMD_PING;
	shm->cs.data.len = 0;
	shm->cs.requestIn = 1;

	// Parse command in server
	shmServer->parseClientCommand();

	ASSERT_FALSE(shmServer->isExitFlag());
	ASSERT_TRUE(shm->cs.replyIn);
	ASSERT_FALSE(shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_PONG, shm->cs.data.command);
	ASSERT_EQ(0, shm->cs.data.len);
}

/**
 * Check client DRV_CMD_PING wrong command length
 */
TEST_F(shmServerClearTest, TestClientPingCommand2) {

	// Prepare client command
	shm->cs.data.command = DRV_CMD_PING;
	shm->cs.data.len = 1;
	shm->cs.requestIn = 1;

	try {
		// Parse command in server
		shmServer->parseClientCommand();

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "ShmServer::CMD_PING: Invalid command data length");

		ASSERT_FALSE(shmServer->isExitFlag());
		ASSERT_TRUE(shm->cs.replyIn);
		ASSERT_FALSE(shm->cs.requestIn);
		ASSERT_EQ(DRV_CMD_NOK, shm->cs.data.command);
		ASSERT_EQ(0, shm->cs.data.len);

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

/**
 * Check client DRV_SET_BIT
 */
TEST_F(shmServerClearTest, TestClientSetBitCommand1) {

	// Prepare client command
	shm->cs.data.command = DRV_SET_BIT;
	shm->cs.data.len = 3;
	shm->cs.data.value[0] = DRV_PROC_MEM;
	shm->cs.data.value[1] = 45;
	shm->cs.data.value[2] = 5;
	shm->cs.requestIn = 1;

	// Parse command in server
	shmServer->parseClientCommand();

	// Check process value
	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_MEMORY, 45, 5}));

	// Check SHM state
	ASSERT_FALSE(shmServer->isExitFlag());
	ASSERT_TRUE(shm->cs.replyIn);
	ASSERT_FALSE(shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_OK, shm->cs.data.command);
	ASSERT_EQ(0, shm->cs.data.len);
}

/**
 * Check client DRV_SET_BIT wrong command length
 */
TEST_F(shmServerClearTest, TestClientSetBitCommand2) {

	// Prepare client command
	shm->cs.data.command = DRV_SET_BIT;
	shm->cs.data.len = 7;
	shm->cs.data.value[0] = DRV_PROC_MEM;
	shm->cs.data.value[1] = 45;
	shm->cs.data.value[2] = 5;
	shm->cs.requestIn = 1;

	try {
		// Parse command in server
		shmServer->parseClientCommand();

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "ShmServer::CMD_SET_BIT: Invalid command data length");

		ASSERT_FALSE(shmServer->isExitFlag());
		ASSERT_TRUE(shm->cs.replyIn);
		ASSERT_FALSE(shm->cs.requestIn);
		ASSERT_EQ(DRV_CMD_NOK, shm->cs.data.command);
		ASSERT_EQ(0, shm->cs.data.len);

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

/**
 * Check client DRV_SET_BIT wrong driver area
 */
TEST_F(shmServerClearTest, TestClientSetBitCommand3) {

	// Prepare client command
	shm->cs.data.command = DRV_SET_BIT;
	shm->cs.data.len = 3;
	shm->cs.data.value[0] = 807;
	shm->cs.data.value[1] = 45;
	shm->cs.data.value[2] = 5;
	shm->cs.requestIn = 1;

	try {
		// Parse command in server
		shmServer->parseClientCommand();

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "ShmServer::CMD_SET_BIT: Invalid driver area");

		ASSERT_FALSE(shmServer->isExitFlag());
		ASSERT_TRUE(shm->cs.replyIn);
		ASSERT_FALSE(shm->cs.requestIn);
		ASSERT_EQ(DRV_CMD_NOK, shm->cs.data.command);
		ASSERT_EQ(0, shm->cs.data.len);

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

/**
 * Check client DRV_RESET_BIT
 */
TEST_F(shmServerClearTest, TestClientResetBitCommand1) {

	// Set test bit
	pda->setBit(processDataAddress{PDA_MEMORY, 10, 1});

	// Check process value
	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_MEMORY, 10, 1}));

	// Prepare client command
	shm->cs.data.command = DRV_RESET_BIT;
	shm->cs.data.len = 3;
	shm->cs.data.value[0] = DRV_PROC_MEM;
	shm->cs.data.value[1] = 10;
	shm->cs.data.value[2] = 1;
	shm->cs.requestIn = 1;

	// Parse command in server
	shmServer->parseClientCommand();

	// Check process value
	ASSERT_FALSE(pda->getBit(processDataAddress{PDA_MEMORY, 10, 1}));

	// Check SHM state
	ASSERT_FALSE(shmServer->isExitFlag());
	ASSERT_TRUE(shm->cs.replyIn);
	ASSERT_FALSE(shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_OK, shm->cs.data.command);
	ASSERT_EQ(0, shm->cs.data.len);
}

/**
 * Check client DRV_RESET_BIT wrong command length
 */
TEST_F(shmServerClearTest, TestClientResetBitCommand2) {

	// Prepare client command
	shm->cs.data.command = DRV_RESET_BIT;
	shm->cs.data.len = 13;
	shm->cs.data.value[0] = DRV_PROC_MEM;
	shm->cs.data.value[1] = 10;
	shm->cs.data.value[2] = 1;
	shm->cs.requestIn = 1;

	try {
		// Parse command in server
		shmServer->parseClientCommand();

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "ShmServer::CMD_RESET_BIT: Invalid command data length");

		ASSERT_FALSE(shmServer->isExitFlag());
		ASSERT_TRUE(shm->cs.replyIn);
		ASSERT_FALSE(shm->cs.requestIn);
		ASSERT_EQ(DRV_CMD_NOK, shm->cs.data.command);
		ASSERT_EQ(0, shm->cs.data.len);

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

/**
 * Check client DRV_RESET_BIT wrong driver area
 */
TEST_F(shmServerClearTest, TestClientResetBitCommand3) {

	// Prepare client command
	shm->cs.data.command = DRV_RESET_BIT;
	shm->cs.data.len = 3;
	shm->cs.data.value[0] = 807;
	shm->cs.data.value[1] = 10;
	shm->cs.data.value[2] = 1;
	shm->cs.requestIn = 1;

	try {
		// Parse command in server
		shmServer->parseClientCommand();

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "ShmServer::CMD_RESET_BIT: Invalid driver area");

		ASSERT_FALSE(shmServer->isExitFlag());
		ASSERT_TRUE(shm->cs.replyIn);
		ASSERT_FALSE(shm->cs.requestIn);
		ASSERT_EQ(DRV_CMD_NOK, shm->cs.data.command);
		ASSERT_EQ(0, shm->cs.data.len);

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

/**
 * Check client DRV_INVERT_BIT
 */
TEST_F(shmServerClearTest, TestClientInvertBitCommand1) {

	// Check process value
	ASSERT_FALSE(pda->getBit(processDataAddress{PDA_MEMORY, 10, 1}));

	// Prepare client command
	shm->cs.data.command = DRV_INVERT_BIT;
	shm->cs.data.len = 3;
	shm->cs.data.value[0] = DRV_PROC_MEM;
	shm->cs.data.value[1] = 10;
	shm->cs.data.value[2] = 1;
	shm->cs.requestIn = 1;

	// Parse command in server
	shmServer->parseClientCommand();

	// Check process value
	ASSERT_TRUE(pda->getBit(processDataAddress{PDA_MEMORY, 10, 1}));

	// Check SHM state
	ASSERT_FALSE(shmServer->isExitFlag());
	ASSERT_TRUE(shm->cs.replyIn);
	ASSERT_FALSE(shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_OK, shm->cs.data.command);
	ASSERT_EQ(0, shm->cs.data.len);
}

/**
 * Check client DRV_INVERT_BIT wrong command length
 */
TEST_F(shmServerClearTest, TestClientInvertBitCommand2) {

	// Prepare client command
	shm->cs.data.command = DRV_INVERT_BIT;
	shm->cs.data.len = 13;
	shm->cs.data.value[0] = DRV_PROC_MEM;
	shm->cs.data.value[1] = 10;
	shm->cs.data.value[2] = 1;
	shm->cs.requestIn = 1;

	try {
		// Parse command in server
		shmServer->parseClientCommand();

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "ShmServer::CMD_INVERT_BIT: Invalid command data length");

		ASSERT_FALSE(shmServer->isExitFlag());
		ASSERT_TRUE(shm->cs.replyIn);
		ASSERT_FALSE(shm->cs.requestIn);
		ASSERT_EQ(DRV_CMD_NOK, shm->cs.data.command);
		ASSERT_EQ(0, shm->cs.data.len);

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

/**
 * Check client DRV_INVERT_BIT wrong driver area
 */
TEST_F(shmServerClearTest, TestClientInvertBitCommand3) {

	// Prepare client command
	shm->cs.data.command = DRV_INVERT_BIT;
	shm->cs.data.len = 3;
	shm->cs.data.value[0] = 807;
	shm->cs.data.value[1] = 10;
	shm->cs.data.value[2] = 1;
	shm->cs.requestIn = 1;

	try {
		// Parse command in server
		shmServer->parseClientCommand();

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "ShmServer::CMD_INVERT_BIT: Invalid driver area");

		ASSERT_FALSE(shmServer->isExitFlag());
		ASSERT_TRUE(shm->cs.replyIn);
		ASSERT_FALSE(shm->cs.requestIn);
		ASSERT_EQ(DRV_CMD_NOK, shm->cs.data.command);
		ASSERT_EQ(0, shm->cs.data.len);

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

/**
 * Check client DRV_SET_BITS
 */
TEST_F(shmServerClearTest, TestClientSetBitsCommand1) {

	// Return values
	std::vector<bool> ret;
	// Prepare addresses to get
	std::vector<processDataAddress> addr;
	addr.push_back(processDataAddress{PDA_INPUT, 1, 0});
	addr.push_back(processDataAddress{PDA_MEMORY, 5, 2});
	addr.push_back(processDataAddress{PDA_INPUT, 6, 3});

	ret = pda->getBits(addr);

	ASSERT_FALSE(ret[0]);
	ASSERT_FALSE(ret[1]);
	ASSERT_FALSE(ret[2]);

	// Prepare client command
	shm->cs.data.command = DRV_SET_BITS;
	shm->cs.data.len = 9;
	shm->cs.data.value[0] = DRV_PROC_IN;
	shm->cs.data.value[1] = 1;
	shm->cs.data.value[2] = 0;
	shm->cs.data.value[3] = DRV_PROC_MEM;
	shm->cs.data.value[4] = 5;
	shm->cs.data.value[5] = 2;
	shm->cs.data.value[6] = DRV_PROC_IN;
	shm->cs.data.value[7] = 6;
	shm->cs.data.value[8] = 3;
	shm->cs.requestIn = 1;

	// Parse command in server
	shmServer->parseClientCommand();

	// Check process value
	ret = pda->getBits(addr);
	ASSERT_TRUE(ret[0]);
	ASSERT_TRUE(ret[1]);
	ASSERT_TRUE(ret[2]);

	// Check SHM state
	ASSERT_FALSE(shmServer->isExitFlag());
	ASSERT_TRUE(shm->cs.replyIn);
	ASSERT_FALSE(shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_OK, shm->cs.data.command);
	ASSERT_EQ(0, shm->cs.data.len);
}

/**
 * Check client DRV_SET_BITS wrong command length
 */
TEST_F(shmServerClearTest, TestClientSetBitsCommand2) {

	// Prepare client command
	shm->cs.data.command = DRV_SET_BITS;
	shm->cs.data.len = 8;
	shm->cs.data.value[0] = DRV_PROC_IN;
	shm->cs.data.value[1] = 1;
	shm->cs.data.value[2] = 0;
	shm->cs.data.value[3] = DRV_PROC_MEM;
	shm->cs.data.value[4] = 5;
	shm->cs.data.value[5] = 2;
	shm->cs.data.value[6] = DRV_PROC_IN;
	shm->cs.data.value[7] = 6;
	shm->cs.data.value[8] = 3;
	shm->cs.requestIn = 1;

	try {
		// Parse command in server
		shmServer->parseClientCommand();

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "ShmServer::CMD_SET_BITS: Invalid command data length");

		ASSERT_FALSE(shmServer->isExitFlag());
		ASSERT_TRUE(shm->cs.replyIn);
		ASSERT_FALSE(shm->cs.requestIn);
		ASSERT_EQ(DRV_CMD_NOK, shm->cs.data.command);
		ASSERT_EQ(0, shm->cs.data.len);

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

/**
 * Check client DRV_SET_BITS wrong driver area
 */
TEST_F(shmServerClearTest, TestClientSetBitsCommand3) {

	// Prepare client command
	shm->cs.data.command = DRV_SET_BITS;
	shm->cs.data.len = 9;
	shm->cs.data.value[0] = DRV_PROC_IN;
	shm->cs.data.value[1] = 1;
	shm->cs.data.value[2] = 0;
	shm->cs.data.value[3] = 555;
	shm->cs.data.value[4] = 5;
	shm->cs.data.value[5] = 2;
	shm->cs.data.value[6] = DRV_PROC_IN;
	shm->cs.data.value[7] = 6;
	shm->cs.data.value[8] = 3;
	shm->cs.requestIn = 1;

	try {
		// Parse command in server
		shmServer->parseClientCommand();

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "ShmServer::CMD_SET_BITS: Invalid driver area");

		ASSERT_FALSE(shmServer->isExitFlag());
		ASSERT_TRUE(shm->cs.replyIn);
		ASSERT_FALSE(shm->cs.requestIn);
		ASSERT_EQ(DRV_CMD_NOK, shm->cs.data.command);
		ASSERT_EQ(0, shm->cs.data.len);

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

/**
 * Check client DRV_WRITE_BYTE
 */
TEST_F(shmServerClearTest, TestClientWriteByteCommand1) {

	// Check process value
	ASSERT_EQ(0, pda->getByte(processDataAddress{PDA_MEMORY, 10, 0}));

	// Prepare client command
	shm->cs.data.command = DRV_WRITE_BYTE;
	shm->cs.data.len = 3;
	shm->cs.data.value[0] = DRV_PROC_MEM;
	shm->cs.data.value[1] = 10;
	shm->cs.data.value[2] = 149;
	shm->cs.requestIn = 1;

	// Parse command in server
	shmServer->parseClientCommand();

	// Check process value
	ASSERT_EQ(149, pda->getByte(processDataAddress{PDA_MEMORY, 10, 0}));

	// Check SHM state
	ASSERT_FALSE(shmServer->isExitFlag());
	ASSERT_TRUE(shm->cs.replyIn);
	ASSERT_FALSE(shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_OK, shm->cs.data.command);
	ASSERT_EQ(0, shm->cs.data.len);
}

/**
 * Check client DRV_WRITE_BYTE wrong command length
 */
TEST_F(shmServerClearTest, TestClientWriteByteCommand2) {

	// Prepare client command
	shm->cs.data.command = DRV_WRITE_BYTE;
	shm->cs.data.len = 4;
	shm->cs.data.value[0] = DRV_PROC_MEM;
	shm->cs.data.value[1] = 10;
	shm->cs.data.value[2] = 149;
	shm->cs.requestIn = 1;

	try {
		// Parse command in server
		shmServer->parseClientCommand();

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "ShmServer::CMD_WRITE_BYTE: Invalid command data length");

		ASSERT_FALSE(shmServer->isExitFlag());
		ASSERT_TRUE(shm->cs.replyIn);
		ASSERT_FALSE(shm->cs.requestIn);
		ASSERT_EQ(DRV_CMD_NOK, shm->cs.data.command);
		ASSERT_EQ(0, shm->cs.data.len);

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

/**
 * Check client DRV_WRITE_BYTE wrong driver area
 */
TEST_F(shmServerClearTest, TestClientWriteByteCommand3) {

	// Prepare client command
	shm->cs.data.command = DRV_WRITE_BYTE;
	shm->cs.data.len = 3;
	shm->cs.data.value[0] = 34;
	shm->cs.data.value[1] = 10;
	shm->cs.data.value[2] = 149;
	shm->cs.requestIn = 1;

	try {
		// Parse command in server
		shmServer->parseClientCommand();

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "ShmServer::CMD_WRITE_BYTE: Invalid driver area");

		ASSERT_FALSE(shmServer->isExitFlag());
		ASSERT_TRUE(shm->cs.replyIn);
		ASSERT_FALSE(shm->cs.requestIn);
		ASSERT_EQ(DRV_CMD_NOK, shm->cs.data.command);
		ASSERT_EQ(0, shm->cs.data.len);

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

/**
 * Check client DRV_WRITE_WORD
 */
TEST_F(shmServerClearTest, TestClientWriteWordCommand1) {

	// Check process value
	ASSERT_EQ(0, pda->getWord(processDataAddress{PDA_MEMORY, 10, 0}));

	// Prepare client command
	shm->cs.data.command = DRV_WRITE_WORD;
	shm->cs.data.len = 3;
	shm->cs.data.value[0] = DRV_PROC_MEM;
	shm->cs.data.value[1] = 10;
	shm->cs.data.value[2] = 51789;
	shm->cs.requestIn = 1;

	// Parse command in server
	shmServer->parseClientCommand();

	// Check process value
	ASSERT_EQ(51789, pda->getWord(processDataAddress{PDA_MEMORY, 10, 0}));

	// Check SHM state
	ASSERT_FALSE(shmServer->isExitFlag());
	ASSERT_TRUE(shm->cs.replyIn);
	ASSERT_FALSE(shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_OK, shm->cs.data.command);
	ASSERT_EQ(0, shm->cs.data.len);
}

/**
 * Check client DRV_WRITE_WORD wrong command length
 */
TEST_F(shmServerClearTest, TestClientWriteWordCommand2) {

	// Prepare client command
	shm->cs.data.command = DRV_WRITE_WORD;
	shm->cs.data.len = 1;
	shm->cs.data.value[0] = DRV_PROC_MEM;
	shm->cs.data.value[1] = 10;
	shm->cs.data.value[2] = 51789;
	shm->cs.requestIn = 1;

	try {
		// Parse command in server
		shmServer->parseClientCommand();

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "ShmServer::CMD_WRITE_WORD: Invalid command data length");

		ASSERT_FALSE(shmServer->isExitFlag());
		ASSERT_TRUE(shm->cs.replyIn);
		ASSERT_FALSE(shm->cs.requestIn);
		ASSERT_EQ(DRV_CMD_NOK, shm->cs.data.command);
		ASSERT_EQ(0, shm->cs.data.len);

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

/**
 * Check client DRV_WRITE_WORD wrong driver area
 */
TEST_F(shmServerClearTest, TestClientWriteWordCommand3) {

	// Prepare client command
	shm->cs.data.command = DRV_WRITE_WORD;
	shm->cs.data.len = 3;
	shm->cs.data.value[0] = 965;
	shm->cs.data.value[1] = 10;
	shm->cs.data.value[2] = 51789;
	shm->cs.requestIn = 1;

	try {
		// Parse command in server
		shmServer->parseClientCommand();

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "ShmServer::CMD_WRITE_WORD: Invalid driver area");

		ASSERT_FALSE(shmServer->isExitFlag());
		ASSERT_TRUE(shm->cs.replyIn);
		ASSERT_FALSE(shm->cs.requestIn);
		ASSERT_EQ(DRV_CMD_NOK, shm->cs.data.command);
		ASSERT_EQ(0, shm->cs.data.len);

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

/**
 * Check client DRV_WRITE_DWORD
 */
TEST_F(shmServerClearTest, TestClientWriteDWordCommand1) {

	// Check process value
	ASSERT_EQ((DWORD)0, pda->getDWord(processDataAddress{PDA_MEMORY, 10, 0}));

	// Prepare client command
	shm->cs.data.command = DRV_WRITE_DWORD;
	shm->cs.data.len = 3;
	shm->cs.data.value[0] = DRV_PROC_MEM;
	shm->cs.data.value[1] = 10;
	shm->cs.data.value[2] = 259347;
	shm->cs.requestIn = 1;

	// Parse command in server
	shmServer->parseClientCommand();

	// Check process value
	ASSERT_EQ((DWORD)259347, pda->getDWord(processDataAddress{PDA_MEMORY, 10, 0}));

	// Check SHM state
	ASSERT_FALSE(shmServer->isExitFlag());
	ASSERT_TRUE(shm->cs.replyIn);
	ASSERT_FALSE(shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_OK, shm->cs.data.command);
	ASSERT_EQ(0, shm->cs.data.len);
}

/**
 * Check client DRV_WRITE_DWORD wrong command length
 */
TEST_F(shmServerClearTest, TestClientWriteDWordCommand2) {

	// Prepare client command
	shm->cs.data.command = DRV_WRITE_DWORD;
	shm->cs.data.len = 1;
	shm->cs.data.value[0] = DRV_PROC_MEM;
	shm->cs.data.value[1] = 10;
	shm->cs.data.value[2] = 259347;
	shm->cs.requestIn = 1;

	try {
		// Parse command in server
		shmServer->parseClientCommand();

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "ShmServer::CMD_WRITE_DWORD: Invalid command data length");

		ASSERT_FALSE(shmServer->isExitFlag());
		ASSERT_TRUE(shm->cs.replyIn);
		ASSERT_FALSE(shm->cs.requestIn);
		ASSERT_EQ(DRV_CMD_NOK, shm->cs.data.command);
		ASSERT_EQ(0, shm->cs.data.len);

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

/**
 * Check client DRV_WRITE_DWORD wrong driver area
 */
TEST_F(shmServerClearTest, TestClientWriteDWordCommand3) {

	// Prepare client command
	shm->cs.data.command = DRV_WRITE_DWORD;
	shm->cs.data.len = 3;
	shm->cs.data.value[0] = 965;
	shm->cs.data.value[1] = 10;
	shm->cs.data.value[2] = 259347;
	shm->cs.requestIn = 1;

	try {
		// Parse command in server
		shmServer->parseClientCommand();

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "ShmServer::CMD_WRITE_DWORD: Invalid driver area");

		ASSERT_FALSE(shmServer->isExitFlag());
		ASSERT_TRUE(shm->cs.replyIn);
		ASSERT_FALSE(shm->cs.requestIn);
		ASSERT_EQ(DRV_CMD_NOK, shm->cs.data.command);
		ASSERT_EQ(0, shm->cs.data.len);

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

/**
 * Check client DRV_WRITE_INT
 */
TEST_F(shmServerClearTest, TestClientWriteIntCommand1) {

	// Check process value
	ASSERT_EQ(0, pda->getInt(processDataAddress{PDA_MEMORY, 10, 0}));

	// Prepare client command
	shm->cs.data.command = DRV_WRITE_INT;
	shm->cs.data.len = 3;
	shm->cs.data.value[0] = DRV_PROC_MEM;
	shm->cs.data.value[1] = 10;
	shm->cs.data.value[2] = -384;
	shm->cs.requestIn = 1;

	// Parse command in server
	shmServer->parseClientCommand();

	// Check process value
	ASSERT_EQ(-384,  pda->getInt(processDataAddress{PDA_MEMORY, 10, 0}));

	// Check SHM state
	ASSERT_FALSE(shmServer->isExitFlag());
	ASSERT_TRUE(shm->cs.replyIn);
	ASSERT_FALSE(shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_OK, shm->cs.data.command);
	ASSERT_EQ(0, shm->cs.data.len);
}

/**
 * Check client DRV_WRITE_INT wrong command length
 */
TEST_F(shmServerClearTest, TestClientWriteIntCommand2) {

	// Prepare client command
	shm->cs.data.command = DRV_WRITE_INT;
	shm->cs.data.len = 1;
	shm->cs.data.value[0] = DRV_PROC_MEM;
	shm->cs.data.value[1] = 10;
	shm->cs.data.value[2] = -384;
	shm->cs.requestIn = 1;

	try {
		// Parse command in server
		shmServer->parseClientCommand();

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "ShmServer::CMD_WRITE_INT: Invalid command data length");

		ASSERT_FALSE(shmServer->isExitFlag());
		ASSERT_TRUE(shm->cs.replyIn);
		ASSERT_FALSE(shm->cs.requestIn);
		ASSERT_EQ(DRV_CMD_NOK, shm->cs.data.command);
		ASSERT_EQ(0, shm->cs.data.len);

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

/**
 * Check client DRV_WRITE_INT wrong driver area
 */
TEST_F(shmServerClearTest, TestClientWriteIntCommand3) {

	// Prepare client command
	shm->cs.data.command = DRV_WRITE_INT;
	shm->cs.data.len = 3;
	shm->cs.data.value[0] = 965;
	shm->cs.data.value[1] = 10;
	shm->cs.data.value[2] = -384;
	shm->cs.requestIn = 1;

	try {
		// Parse command in server
		shmServer->parseClientCommand();

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "ShmServer::CMD_WRITE_INT: Invalid driver area");

		ASSERT_FALSE(shmServer->isExitFlag());
		ASSERT_TRUE(shm->cs.replyIn);
		ASSERT_FALSE(shm->cs.requestIn);
		ASSERT_EQ(DRV_CMD_NOK, shm->cs.data.command);
		ASSERT_EQ(0, shm->cs.data.len);

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

/**
 * Check client DRV_WRITE_REAL
 */
TEST_F(shmServerClearTest, TestClientWriteRealCommand1) {

	// Check process value
	ASSERT_EQ((float)0, pda->getReal(processDataAddress{PDA_MEMORY, 10, 0}));

	// Prepare client command
	shm->cs.data.command = DRV_WRITE_REAL;
	shm->cs.data.len = 3;
	shm->cs.data.value[0] = DRV_PROC_MEM;
	shm->cs.data.value[1] = 10;
	// Pointer to Real in shm command data
	float *pReal = (float*)&shm->cs.data.value[2];
	*pReal = -304.178;
	shm->cs.requestIn = 1;

	// Parse command in server
	shmServer->parseClientCommand();

	// Check process value
	ASSERT_EQ((float)-304.178,  pda->getReal(processDataAddress{PDA_MEMORY, 10, 0}));

	// Check SHM state
	ASSERT_FALSE(shmServer->isExitFlag());
	ASSERT_TRUE(shm->cs.replyIn);
	ASSERT_FALSE(shm->cs.requestIn);
	ASSERT_EQ(DRV_CMD_OK, shm->cs.data.command);
	ASSERT_EQ(0, shm->cs.data.len);
}

/**
 * Check client DRV_WRITE_REAL wrong command length
 */
TEST_F(shmServerClearTest, TestClientWriteRealCommand2) {

	// Prepare client command
	shm->cs.data.command = DRV_WRITE_REAL;
	shm->cs.data.len = 1;
	shm->cs.data.value[0] = DRV_PROC_MEM;
	shm->cs.data.value[1] = 10;
	// Pointer to Real in shm command data
	float *pReal = (float*)&shm->cs.data.value[2];
	*pReal = -304.178;
	shm->cs.requestIn = 1;

	try {
		// Parse command in server
		shmServer->parseClientCommand();

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "ShmServer::CMD_WRITE_REAL: Invalid command data length");

		ASSERT_FALSE(shmServer->isExitFlag());
		ASSERT_TRUE(shm->cs.replyIn);
		ASSERT_FALSE(shm->cs.requestIn);
		ASSERT_EQ(DRV_CMD_NOK, shm->cs.data.command);
		ASSERT_EQ(0, shm->cs.data.len);

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

/**
 * Check client DRV_WRITE_REAL wrong driver area
 */
TEST_F(shmServerClearTest, TestClientWriteRealCommand3) {

	// Prepare client command
	shm->cs.data.command = DRV_WRITE_REAL;
	shm->cs.data.len = 3;
	shm->cs.data.value[0] = 666;
	shm->cs.data.value[1] = 10;
	// Pointer to Real in shm command data
	float *pReal = (float*)&shm->cs.data.value[2];
	*pReal = -304.178;
	shm->cs.requestIn = 1;

	try {
		// Parse command in server
		shmServer->parseClientCommand();

		FAIL() << "Expected onh::ShmException";

	} catch (ShmException &e) {

		ASSERT_STREQ(e.what(), "ShmServer::CMD_WRITE_REAL: Invalid driver area");

		ASSERT_FALSE(shmServer->isExitFlag());
		ASSERT_TRUE(shm->cs.replyIn);
		ASSERT_FALSE(shm->cs.requestIn);
		ASSERT_EQ(DRV_CMD_NOK, shm->cs.data.command);
		ASSERT_EQ(0, shm->cs.data.len);

	} catch(...) {
		FAIL() << "Expected onh::ShmException";
	}
}

/**
 * Check copy process data
 */
TEST_F(shmServerClearTest, TestCopyProcessData1) {

	// Modify local process data
	pda->writeInt(processDataAddress{PDA_MEMORY, 10, 0}, -987);
	pda->writeReal(processDataAddress{PDA_INPUT, 10, 0}, (float)-13.78);
	pda->writeByte(processDataAddress{PDA_OUTPUT, 10, 0}, 45);

	// Check process value
	ASSERT_EQ(-987, pda->getInt(processDataAddress{PDA_MEMORY, 10, 0}));
	ASSERT_EQ((float)-13.78, pda->getReal(processDataAddress{PDA_INPUT, 10, 0}));
	ASSERT_EQ(45, pda->getByte(processDataAddress{PDA_OUTPUT, 10, 0}));

	// Copy local process data to the SHM process
	shmServer->copyProcessData();

	// Check all process data
	for (unsigned int i=0; i<PROCESS_DT_SIZE; ++i) {
		ASSERT_EQ(shm->process.procDT.mem[i], pda->getByte(processDataAddress{PDA_MEMORY, i, 0}));
		ASSERT_EQ(shm->process.procDT.in[i], pda->getByte(processDataAddress{PDA_INPUT, i, 0}));
		ASSERT_EQ(shm->process.procDT.out[i], pda->getByte(processDataAddress{PDA_OUTPUT, i, 0}));
	}
}

/**
 * Check process tag creation
 */
TEST_F(shmServerClearTest, TestPDTag1) {

	processDataAddress addr = {PDA_MEMORY, 10, 0};

	PDTag<bool> tag1(shmServer->getTag<bool>(addr));

	ASSERT_FALSE(pda->getBit(addr));

	tag1 = true;

	ASSERT_TRUE(pda->getBit(addr));
}

TEST_F(shmServerClearTest, TestPDTag2) {

	processDataAddress addr = {PDA_MEMORY, 10, 0};

	PDTag<BYTE> tag1(shmServer->getTag<BYTE>(addr));

	ASSERT_EQ(0, pda->getByte(addr));

	tag1 = 140;

	ASSERT_EQ(140, pda->getByte(addr));
}

TEST_F(shmServerClearTest, TestPDTag3) {

	processDataAddress addr = {PDA_MEMORY, 10, 0};

	PDTag<WORD> tag1(shmServer->getTag<WORD>(addr));

	ASSERT_EQ(0, pda->getWord(addr));

	tag1 = 14000;

	ASSERT_EQ(14000, pda->getWord(addr));
}

TEST_F(shmServerClearTest, TestPDTag4) {

	processDataAddress addr = {PDA_MEMORY, 10, 0};

	PDTag<DWORD> tag1(shmServer->getTag<DWORD>(addr));

	ASSERT_EQ(0, pda->getDWord(addr));

	tag1 = 140000;

	ASSERT_EQ(140000, pda->getDWord(addr));
}

TEST_F(shmServerClearTest, TestPDTag5) {

	processDataAddress addr = {PDA_MEMORY, 10, 0};

	PDTag<int> tag1(shmServer->getTag<int>(addr));

	ASSERT_EQ(0, pda->getInt(addr));

	tag1 = -65;

	ASSERT_EQ(-65, pda->getInt(addr));
}

TEST_F(shmServerClearTest, TestPDTag6) {

	processDataAddress addr = {PDA_MEMORY, 10, 0};

	PDTag<float> tag1(shmServer->getTag<float>(addr));

	ASSERT_FLOAT_EQ(0, pda->getReal(addr));

	tag1 = 6.78;

	ASSERT_FLOAT_EQ(6.78, pda->getReal(addr));
}

#endif /* SHMSERVERTESTS_H_ */
