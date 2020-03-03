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

#ifndef S_MEMORY
#define S_MEMORY

#include "processData.h"
#include <pthread.h>

/// Default command data array size (int)
#define CMD_DATA_SIZE 100

/**
 * 			Client - Server communication description.
 *
 *				Communication is realized based on Client - Server concept: client sends request, server is responding.
 * 				There is only one server and one client!
 *
 * 				If client wants to send request to server he lock requestMutex, check that requestIn, replyIn are 0, write command data,
 * 				set requestIn=1, unlock requestMutex and wait on signal from replyCondvar variable.
 *
 *				Server is checking in loop requestIn flag (if requestMutex is locked, he skipped - pthread_mutex_trylock).
 *				If requestIn is set he read request data, writes reply data, set requestIn=0, replyIn=1 and send signal to replyCondvar variable.
 *
 *				When client receive signal from replyCondvar he read reply and clear replyIn flag.
 *
 *			Client - Server process data exchange description.
 *
 *				If client wants to read process data he lock processMutex, read data and unlock processMutex.
 *
 *				If server wants to write process data he try to lock processMutex - pthread_mutex_trylock, write data and unlock processMutex.
 */

/**
 * @brief	Command data structure
 */
typedef struct {

	/// Command number
	int command;

	/// Command data array
	int value[CMD_DATA_SIZE];

	/// Command data length
	int len;

} extCMD;

/**
 * @brief	Client - Server communication structure
 */
typedef struct {

	/// Command data structure.
	extCMD data;

	/// Request mutex
	pthread_mutex_t requestMutex;

	/// Reply condition variable
	pthread_mutex_t replyMutex;
	pthread_cond_t  replyCondvar;

	/// Client set this variable to 1 when he finished writing request data.
	int requestIn;

	/// Server set this variable to 1 when he finished writing reply data.
	int replyIn;

} smCS;

/**
 * @brief	Shared memory process data structure
 */
typedef struct {

	/// Process data
	processData procDT;

	/// Synchronization mutex
	pthread_mutex_t processMutex;

} smProcess;

/**
 * @brief	Shared memory structure.
 */
typedef struct {

	/// Client - Server communication structure.
	smCS cs;

	/// Process data exchange structure.
	smProcess process;

} sMemory;

#endif
