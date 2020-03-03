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

#include "onhSHMc/sMemoryServer.h"

int shm_initMemory(shm_serverData *ssdt) {

	int err = SHM_ERROR_NONE;

	// Mutex settings
	pthread_mutexattr_t mutex_attr;

	// Condition variable settings
	pthread_condattr_t cond_attr;

	// Create the shared memory segment
	ssdt->sfd = shm_open(ssdt->smName, O_CREAT | O_RDWR, 0666);
	if (ssdt->sfd == -1) {
		err = SHM_ERROR_OPEN;
	}

	// Configure the size of the shared memory segment
	if (err == SHM_ERROR_NONE) {
		if (ftruncate(ssdt->sfd, sizeof(sMemory)) == -1) {
			err = SHM_ERROR_FTRUNCATE;
		}
	}

	// Map the shared memory segment in the address space of the process
	if (err == SHM_ERROR_NONE) {
		ssdt->shm = (sMemory*)mmap(NULL, sizeof(sMemory), PROT_READ | PROT_WRITE, MAP_SHARED, ssdt->sfd, 0);
		if (ssdt->shm == MAP_FAILED) {
			err = SHM_MAP_FAILED;
		}
	}

	if (err == SHM_ERROR_NONE) {
		if (pthread_mutexattr_init(&mutex_attr) != 0) {
			err = SHM_ERROR_MUTEX_ATTR_INIT;
		}
	}

	if (err == SHM_ERROR_NONE) {
		if (pthread_mutexattr_setpshared(&mutex_attr, PTHREAD_PROCESS_SHARED) != 0) {
			err = SHM_ERROR_MUTEX_ATTR_SHARED;
		}
	}

	// Init request mutex
	if (err == SHM_ERROR_NONE) {
		if (pthread_mutex_init(&ssdt->shm->cs.requestMutex, &mutex_attr) != 0) {
			err = SHM_ERROR_MUTEX_INIT;
		}
	}

	// Init reply mutex
	if (err == SHM_ERROR_NONE) {
		if (pthread_mutex_init(&ssdt->shm->cs.replyMutex, &mutex_attr) != 0) {
			err = SHM_ERROR_MUTEX_INIT;
		}
	}

	// Init process mutex
	if (err == SHM_ERROR_NONE) {
		if (pthread_mutex_init(&ssdt->shm->process.processMutex, &mutex_attr) != 0) {
			err = SHM_ERROR_MUTEX_INIT;
		}
	}

	// Condition variable
	if (err == SHM_ERROR_NONE) {
		if (pthread_condattr_init(&cond_attr) != 0) {
			err = SHM_ERROR_CONDVAR_ATTR_INIT;
		}
	}

	if (err == SHM_ERROR_NONE) {
		if (pthread_condattr_setpshared(&cond_attr, PTHREAD_PROCESS_SHARED) != 0) {
			err = SHM_ERROR_CONDVAR_ATTR_SHARED;
		}
	}

	// Init condition variable
	if (err == SHM_ERROR_NONE) {
		if (pthread_cond_init(&ssdt->shm->cs.replyCondvar, &cond_attr) != 0) {
			err = SHM_ERROR_CONDVAR_INIT;
		}
	}

	if (err == SHM_ERROR_NONE) {
		err = shm_clearCSCommandData(ssdt->shm);
	}

	if (err == SHM_ERROR_NONE) {
		err = shm_clearCSSyncData(ssdt->shm);
	}

	if (err == SHM_ERROR_NONE) {
		err = shm_clearProcessData(ssdt->shm);
	}

	return err;
}

void shm_closeMemory(shm_serverData *ssdt) {

	// Unmap shared memory
	munmap(ssdt->shm, sizeof(sMemory));

	// Close shared memory object
	close(ssdt->sfd);

	// Delete shared memory object
	shm_unlink(ssdt->smName);
}

int shm_clearCSCommandData(sMemory *shm) {

	int err = SHM_ERROR_NONE;

	if (shm != MAP_FAILED) {

		// Lock request mutex
		if (pthread_mutex_lock(&shm->cs.requestMutex) == 0) {

			shm->cs.data.command = 0;
			shm->cs.data.len = 0;

			for (int i=0; i<CMD_DATA_SIZE; ++i) {
				shm->cs.data.value[i] = 0;
			}

			// Unlock request mutex
			if (pthread_mutex_unlock(&shm->cs.requestMutex) != 0) {
				err = SHM_ERROR_MUTEX_UNLOCK;
			}
		} else {
			err = SHM_ERROR_MUTEX_LOCK;
		}
	} else {
		err = SHM_MAP_FAILED;
	}

	return err;
}

int shm_clearCSSyncData(sMemory *shm) {

	int err = SHM_ERROR_NONE;

	if (shm != MAP_FAILED) {

		// Lock request mutex
		if (pthread_mutex_lock(&shm->cs.requestMutex) == 0) {

			shm->cs.requestIn = 0;
			shm->cs.replyIn = 0;

			// Unlock request mutex
			if (pthread_mutex_unlock(&shm->cs.requestMutex) != 0) {
				err = SHM_ERROR_MUTEX_UNLOCK;
			}
		} else {
			err = SHM_ERROR_MUTEX_LOCK;
		}
	} else {
		err = SHM_MAP_FAILED;
	}

	return err;
}

int shm_clearProcessData(sMemory *shm) {

	int err = SHM_ERROR_NONE;

	if (shm != MAP_FAILED) {

		// Lock process mutex
		if (pthread_mutex_lock(&shm->process.processMutex) == 0) {

			for (int i=0; i<PROCESS_DT_SIZE; ++i) {
				shm->process.procDT.in[i] = 0;
				shm->process.procDT.out[i] = 0;
				shm->process.procDT.mem[i] = 0;
			}

			// Unlock process mutex
			if (pthread_mutex_unlock(&shm->process.processMutex) != 0) {
				err = SHM_ERROR_MUTEX_UNLOCK;
			}
		} else {
			err = SHM_ERROR_MUTEX_LOCK;
		}
	} else {
		err = SHM_MAP_FAILED;
	}

	return err;
}

void shm_clearExtCommandData(extCMD *cdt) {

	cdt->command = 0;
	cdt->len = 0;

	for (int i=0; i<CMD_DATA_SIZE; ++i) {
		cdt->value[i] = 0;
	}
}

int shm_requestIn(sMemory *shm, extCMD *sdt) {

	int err = SHM_ERROR_NONE;

	if (shm != MAP_FAILED) {

		// Clear local command data structure
		shm_clearExtCommandData(sdt);

		// Try to lock request mutex
		if (pthread_mutex_trylock(&shm->cs.requestMutex) == 0) {

			if ((shm->cs.requestIn == 1) && (shm->cs.replyIn == 0)) {

				// Read data
				sdt->command = shm->cs.data.command;
				sdt->len = shm->cs.data.len;

				if (sdt->len<CMD_DATA_SIZE) {
					for (int i=0; i<sdt->len; ++i) {
						sdt->value[i] = shm->cs.data.value[i];
					}
				}

				err = SHM_REQUEST_IN;

			} else if ((shm->cs.requestIn == 1) && (shm->cs.replyIn == 1)) {
				// Wrong sync data - clear all command data
				shm_clearCSCommandData(shm);
				shm_clearCSSyncData(shm);
			}

			// Unlock request mutex
			if (pthread_mutex_unlock(&shm->cs.requestMutex) != 0) {
				err = SHM_ERROR_MUTEX_UNLOCK;
			}
		}
	} else {
		err = SHM_MAP_FAILED;
	}

	return err;
}

int shm_put_replyIn(sMemory *shm, extCMD *sdt) {

	int err = SHM_ERROR_NONE;

	// Check values length
	if (sdt->len < CMD_DATA_SIZE) {

		if (shm != MAP_FAILED) {

			// Lock request mutex
			if (pthread_mutex_lock(&shm->cs.requestMutex) == 0) {

				// Copy data
				shm->cs.data.command = sdt->command;
				shm->cs.data.len = sdt->len;

				for (int i=0; i<shm->cs.data.len; ++i) {
					shm->cs.data.value[i] = sdt->value[i];
				}

				shm->cs.requestIn = 0;
				shm->cs.replyIn = 1;

				// Unlock request mutex
				if (pthread_mutex_unlock(&shm->cs.requestMutex) != 0) {
					err = SHM_ERROR_MUTEX_UNLOCK;
				}

				// Condition variable signaling
				if (err == SHM_ERROR_NONE) {
					if (pthread_mutex_lock(&shm->cs.replyMutex) != 0) {
						err = SHM_ERROR_MUTEX_LOCK;
					}
				}
				if (err == SHM_ERROR_NONE) {
					if (pthread_cond_signal(&shm->cs.replyCondvar) != 0) {
						err = SHM_ERROR_CONDVAR_SIGNAL;
					}
				}
				if (err == SHM_ERROR_NONE) {
					if (pthread_mutex_unlock(&shm->cs.replyMutex) != 0) {
						err = SHM_ERROR_MUTEX_UNLOCK;
					}
				}
			} else {
				err = SHM_ERROR_MUTEX_LOCK;
			}
		} else {
			err = SHM_MAP_FAILED;
		}
	} else {
		err = SHM_DATA_LENGTH_OUT_OF_RANGE;
	}

	return err;
}

int shm_copy_process_data(sMemory *shm, processData *process) {

	int err = SHM_ERROR_NONE;

	if (shm != MAP_FAILED) {

		// Try to lock process mutex
		if (pthread_mutex_trylock(&shm->process.processMutex) == 0) {

			// Copy process data into shared memory
			shm->process.procDT = *process;

			// Unlock request mutex
			if (pthread_mutex_unlock(&shm->process.processMutex) != 0) {
				err = SHM_ERROR_MUTEX_UNLOCK;
			}
		}
	} else {
		err = SHM_MAP_FAILED;
	}

	return err;
}
