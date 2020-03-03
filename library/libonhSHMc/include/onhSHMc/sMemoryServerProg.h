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

#ifndef SMEMORY_SERVER_PROG
#define SMEMORY_SERVER_PROG

#include "sMemoryServer.h"

#define SERVER_ERROR_NONE 0						// No error
#define SERVER_SHM_ERROR 1						// SHM error
#define SERVER_PROCESS_ERROR 2					// Process data error
#define SERVER_INVALID_COMMAND 3				// Invalid command
#define SERVER_TAGS_COUNT_OUT_OF_RANGE 4		// Too much tags to read
#define SERVER_DATA_LENGTH_INVALID 5			// Command data length is invalid
#define SERVER_DATA_LENGTH_OUT_OF_RANGE 6		// Command data length is out of range
#define SERVER_INVALID_DRIVER_AREA 7			// Invalid driver area

/**
 * Parse client commands
 *
 * @param ssdt Server shared memory data structure
 * @param exitPrg Exit program flag
 * @param processData Process data
 * @param additionalError Error number from SHM or Process
 *
 * @return Error number
 */
int parseClientCommand(shm_serverData *ssdt, int *exitPrg, processData *process, int *additionalError);

/**
 * Parse DRV_CMD_EXIT
 *
 * @param requestCMD Request command structure
 * @param replyCMD Reply command structure
 * @param exitFlag Exit program flag
 *
 * @return Error number
 */
int CMD_EXIT(extCMD *requestCMD, extCMD *replyCMD, int *exitFlag);

/**
 * Parse DRV_CMD_PING
 *
 * @param requestCMD Request command structure
 * @param replyCMD Reply command structure
 *
 * @return Error number
 */
int CMD_PING(extCMD *requestCMD, extCMD *replyCMD);

/**
 * Parse DRV_SET_BIT
 *
 * @param requestCMD Request command structure
 * @param replyCMD Reply command structure
 * @param processData Process data
 * @param additionalError Error number from SHM or Process
 *
 * @return Error number
 */
int CMD_SET_BIT(extCMD *requestCMD, extCMD *replyCMD, processData *process, int *additionalError);

/**
 * Parse DRV_RESET_BIT
 *
 * @param requestCMD Request command structure
 * @param replyCMD Reply command structure
 * @param processData Process data
 * @param additionalError Error number from SHM or Process
 *
 * @return Error number
 */
int CMD_RESET_BIT(extCMD *requestCMD, extCMD *replyCMD, processData *process, int *additionalError);

/**
 * Parse DRV_INVERT_BIT
 *
 * @param requestCMD Request command structure
 * @param replyCMD Reply command structure
 * @param processData Process data
 * @param additionalError Error number from SHM or Process
 *
 * @return Error number
 */
int CMD_INVERT_BIT(extCMD *requestCMD, extCMD *replyCMD, processData *process, int *additionalError);

/**
 * Parse DRV_SET_BITS
 *
 * @param requestCMD Request command structure
 * @param replyCMD Reply command structure
 * @param processData Process data
 * @param additionalError Error number from SHM or Process
 *
 * @return Error number
 */
int CMD_SET_BITS(extCMD *requestCMD, extCMD *replyCMD, processData *process, int *additionalError);

/**
 * Parse DRV_WRITE_BYTE
 *
 * @param requestCMD Request command structure
 * @param replyCMD Reply command structure
 * @param processData Process data
 * @param additionalError Error number from SHM or Process
 *
 * @return Error number
 */
int CMD_WRITE_BYTE(extCMD *requestCMD, extCMD *replyCMD, processData *process, int *additionalError);

/**
 * Parse DRV_WRITE_WORD
 *
 * @param requestCMD Request command structure
 * @param replyCMD Reply command structure
 * @param processData Process data
 * @param additionalError Error number from SHM or Process
 *
 * @return Error number
 */
int CMD_WRITE_WORD(extCMD *requestCMD, extCMD *replyCMD, processData *process, int *additionalError);

/**
 * Parse DRV_WRITE_DWORD
 *
 * @param requestCMD Request command structure
 * @param replyCMD Reply command structure
 * @param processData Process data
 * @param additionalError Error number from SHM or Process
 *
 * @return Error number
 */
int CMD_WRITE_DWORD(extCMD *requestCMD, extCMD *replyCMD, processData *process, int *additionalError);

/**
 * Parse DRV_WRITE_INT
 *
 * @param requestCMD Request command structure
 * @param replyCMD Reply command structure
 * @param processData Process data
 * @param additionalError Error number from SHM or Process
 *
 * @return Error number
 */
int CMD_WRITE_INT(extCMD *requestCMD, extCMD *replyCMD, processData *process, int *additionalError);

/**
 * Parse DRV_WRITE_REAL
 *
 * @param requestCMD Request command structure
 * @param replyCMD Reply command structure
 * @param processData Process data
 * @param additionalError Error number from SHM or Process
 *
 * @return Error number
 */
int CMD_WRITE_REAL(extCMD *requestCMD, extCMD *replyCMD, processData *process, int *additionalError);

/**
 * Copy process data to the shared memory
 *
 * @param ssdt Server shared memory data structure
 * @param process Process data
 * @param additionalError Error number from SHM or Process
 *
 * @return Error number
 */
int copyProcessData(shm_serverData *ssdt, processData *process, int *additionalError);

#endif
