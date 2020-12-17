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

#ifndef S_MEMORY_SERVER
#define S_MEMORY_SERVER

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

#include "sMemory.h"

#define SHM_ERROR_NONE 0						// No error
#define SHM_MAP_FAILED 1						// SHM map failed
#define SHM_ERROR_MUTEX_ATTR_INIT 2				// Error on mutex atrr init
#define SHM_ERROR_MUTEX_ATTR_SHARED 3			// Error on set mutex atrr shared
#define SHM_ERROR_MUTEX_INIT 4					// Error on mutex init
#define SHM_ERROR_CONDVAR_ATTR_INIT 5			// Error on condition variable atrr init
#define SHM_ERROR_CONDVAR_ATTR_SHARED 6			// Error on condition variable atrr shared
#define SHM_ERROR_CONDVAR_INIT 7				// Error on condition variable init
#define SHM_ERROR_MUTEX_LOCK 8					// Error on mutex locking
#define SHM_ERROR_MUTEX_UNLOCK 9				// Error on mutex unlocking
#define SHM_REQUEST_IN 10						// SHM contains request
#define SHM_ERROR_CONDVAR_SIGNAL 11				// Error on condition variable signaling
#define SHM_DATA_LENGTH_OUT_OF_RANGE 12			// SHM command data length is out of range
#define SHM_ERROR_OPEN 13						// SHM open error
#define SHM_ERROR_FTRUNCATE 14					// SHM ftruncate error

/**
 * Server shared memory data structure
 */
typedef struct {

	/// Shared memory segment name
	const char *smName;

	/// Shared memory handle
	sMemory *shm;

	/// Shared memory id
	int sfd;

} shm_serverData;

/**
 * Initialize shared memory
 *
 * @param ssdt Server shared memory data structure
 *
 * @return Error number
 */
int shm_initMemory(shm_serverData *ssdt);

/**
 * Close shared memory
 *
 * @param ssdt Server shared memory data structure
 */
void shm_closeMemory(shm_serverData *ssdt);

/**
 * Clear Client-Server command data
 *
 * @param shm Shared memory structure
 *
 * @return Error number
 */
int shm_clearCSCommandData(sMemory *shm);

/**
 * Clear Client-Server synchronization data
 *
 * @param shm Shared memory structure
 *
 * @return Error number
 */
int shm_clearCSSyncData(sMemory *shm);

/**
 * Clear process data
 *
 * @param shm Shared memory structure
 *
 * @return Error number
 */
int shm_clearProcessData(sMemory *shm);

/**
 * Clear external command data
 *
 * @param cdt Command structure
 */
void shm_clearExtCommandData(extCMD *cdt);

/**
 * Check if there is request and read command
 *
 * @param shm Shared memory structure
 * @param sdt Shared memory command data
 *
 * @return Error number
 */
int shm_requestIn(sMemory *shm, extCMD *sdt);

/**
 * Put reply into the shared memory
 *
 * @param shm Shared memory structure
 * @param sdt Shared memory reply data
 *
 * @return Error number
 */
int shm_put_replyIn(sMemory *shm, extCMD *sdt);

/**
 * Copy local process data to the shared memory
 *
 * @param shm Shared memory structure
 * @param process Local process data
 *
 * @return Error number
 */
int shm_copy_process_data(sMemory *shm, processData *process);

#ifdef __cplusplus
}
#endif

#endif
