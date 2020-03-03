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

#include "onhSHMc/sMemoryServerProg.h"
#include "onhSHMc/sCommands.h"
#include "onhSHMc/processDataAccess.h"

int CMD_EXIT(extCMD *requestCMD, extCMD *replyCMD, int *exitFlag) {

	int ret = SERVER_ERROR_NONE;

	// Check command
	if (requestCMD->command == DRV_CMD_EXIT) {

		// Check data length
		if (requestCMD->len == 0) {

			// Prepare reply command
			replyCMD->command = DRV_CMD_EXIT;

			// Exit flag
			*exitFlag = 1;
		} else {
			ret = SERVER_DATA_LENGTH_INVALID;
		}
	} else {
		ret = SERVER_INVALID_COMMAND;
	}

	return ret;
}

int CMD_PING(extCMD *requestCMD, extCMD *replyCMD) {

	int ret = SERVER_ERROR_NONE;

	// Check command
	if (requestCMD->command == DRV_CMD_PING) {

		// Check data length
		if (requestCMD->len == 0) {

			// Prepare reply command
			replyCMD->command = DRV_CMD_PONG;
		} else {
			ret = SERVER_DATA_LENGTH_INVALID;
		}
	} else {
		ret = SERVER_INVALID_COMMAND;
	}

	return ret;
}

int CMD_SET_BIT(extCMD *requestCMD, extCMD *replyCMD, processData *process, int *additionalError) {

	int ret = SERVER_ERROR_NONE;

	// Check command
	if (requestCMD->command == DRV_SET_BIT) {

		// Check data length
		if (requestCMD->len == 3) {

			// Prepare address structure
			processDataAddress addr;
			// Area
			switch (requestCMD->value[0]) {
				case DRV_PROC_IN: addr.area = PDA_INPUT; break;
				case DRV_PROC_OUT: addr.area = PDA_OUTPUT; break;
				case DRV_PROC_MEM: addr.area = PDA_MEMORY; break;
				default: ret = SERVER_INVALID_DRIVER_AREA; break;
			}

			if (ret == SERVER_ERROR_NONE) {

				// Byte address
				addr.byteAddr = requestCMD->value[1];
				// Bit address
				addr.bitAddr = requestCMD->value[2];

				// Set bit
				int procErr = PROCESS_SET_BIT(process, addr);

				// Check error
				if (procErr == PROCESS_ERROR_NONE) {

					// Prepare reply command
					replyCMD->command = DRV_CMD_OK;

				} else {
					ret = SERVER_PROCESS_ERROR;
					*additionalError = procErr;
				}
			}
		} else {
			ret = SERVER_DATA_LENGTH_INVALID;
		}
	} else {
		ret = SERVER_INVALID_COMMAND;
	}

	return ret;
}

int CMD_RESET_BIT(extCMD *requestCMD, extCMD *replyCMD, processData *process, int *additionalError) {

	int ret = SERVER_ERROR_NONE;

	// Check command
	if (requestCMD->command == DRV_RESET_BIT) {

		// Check data length
		if (requestCMD->len == 3) {

			// Prepare address structure
			processDataAddress addr;
			// Area
			switch (requestCMD->value[0]) {
				case DRV_PROC_IN: addr.area = PDA_INPUT; break;
				case DRV_PROC_OUT: addr.area = PDA_OUTPUT; break;
				case DRV_PROC_MEM: addr.area = PDA_MEMORY; break;
				default: ret = SERVER_INVALID_DRIVER_AREA; break;
			}

			if (ret == SERVER_ERROR_NONE) {

				// Byte address
				addr.byteAddr = requestCMD->value[1];
				// Bit address
				addr.bitAddr = requestCMD->value[2];

				// Reset bit
				int procErr = PROCESS_RESET_BIT(process, addr);

				// Check error
				if (procErr == PROCESS_ERROR_NONE) {

					// Prepare reply command
					replyCMD->command = DRV_CMD_OK;

				} else {
					ret = SERVER_PROCESS_ERROR;
					*additionalError = procErr;
				}
			}
		} else {
			ret = SERVER_DATA_LENGTH_INVALID;
		}
	} else {
		ret = SERVER_INVALID_COMMAND;
	}

	return ret;
}

int CMD_INVERT_BIT(extCMD *requestCMD, extCMD *replyCMD, processData *process, int *additionalError) {

	int ret = SERVER_ERROR_NONE;

	// Check command
	if (requestCMD->command == DRV_INVERT_BIT) {

		// Check data length
		if (requestCMD->len == 3) {

			// Prepare address structure
			processDataAddress addr;
			// Area
			switch (requestCMD->value[0]) {
				case DRV_PROC_IN: addr.area = PDA_INPUT; break;
				case DRV_PROC_OUT: addr.area = PDA_OUTPUT; break;
				case DRV_PROC_MEM: addr.area = PDA_MEMORY; break;
				default: ret = SERVER_INVALID_DRIVER_AREA; break;
			}

			if (ret == SERVER_ERROR_NONE) {

				// Byte address
				addr.byteAddr = requestCMD->value[1];
				// Bit address
				addr.bitAddr = requestCMD->value[2];

				// Invert bit
				int procErr = PROCESS_INVERT_BIT(process, addr);

				// Check error
				if (procErr == PROCESS_ERROR_NONE) {

					// Prepare reply command
					replyCMD->command = DRV_CMD_OK;

				} else {
					ret = SERVER_PROCESS_ERROR;
					*additionalError = procErr;
				}
			}
		} else {
			ret = SERVER_DATA_LENGTH_INVALID;
		}
	} else {
		ret = SERVER_INVALID_COMMAND;
	}

	return ret;
}

int CMD_SET_BITS(extCMD *requestCMD, extCMD *replyCMD, processData *process, int *additionalError) {

	int ret = SERVER_ERROR_NONE;

	// Check command
	if (requestCMD->command == DRV_SET_BITS) {

		// Check data length
		if (!((requestCMD->len == 0) || ((requestCMD->len % 3) != 0))) {

			int tagsCount = requestCMD->len / 3;
			int dto = 0;

			// Check tags count
			if (tagsCount <= CMD_DATA_SIZE/3) {

				// Address table buff
				processDataAddress pAddr[CMD_DATA_SIZE/3];

				// Prepare address table
				for (int i=0; i<tagsCount; ++i) {

					// Area
					switch (requestCMD->value[dto+0]) {
						case DRV_PROC_IN: pAddr[i].area = PDA_INPUT; break;
						case DRV_PROC_OUT: pAddr[i].area = PDA_OUTPUT; break;
						case DRV_PROC_MEM: pAddr[i].area = PDA_MEMORY; break;
						default: ret = SERVER_INVALID_DRIVER_AREA; break;
					}

					if (ret != SERVER_ERROR_NONE) {
						// stop the loop
						break;
					}
					// Byte address
					pAddr[i].byteAddr = requestCMD->value[dto+1];
					// Bit address
					pAddr[i].bitAddr = requestCMD->value[dto+2];

					// Next tag
					dto += 3;
				}

				if (ret == SERVER_ERROR_NONE) {

					// Set bits
					int procErr = PROCESS_SET_BITS(process, pAddr, tagsCount);

					// Check error
					if (procErr == PROCESS_ERROR_NONE) {

						// Prepare reply command
						replyCMD->command = DRV_CMD_OK;

					} else {
						ret = SERVER_PROCESS_ERROR;
						*additionalError = procErr;
					}
				}
			} else {
				ret = SERVER_TAGS_COUNT_OUT_OF_RANGE;
			}
		} else {
			ret = SERVER_DATA_LENGTH_INVALID;
		}
	} else {
		ret = SERVER_INVALID_COMMAND;
	}

	return ret;
}

int CMD_WRITE_BYTE(extCMD *requestCMD, extCMD *replyCMD, processData *process, int *additionalError) {

	int ret = SERVER_ERROR_NONE;

	// Check command
	if (requestCMD->command == DRV_WRITE_BYTE) {

		// Check data length
		if (requestCMD->len == 3) {

			// Prepare address structure
			processDataAddress addr;
			// Area
			switch (requestCMD->value[0]) {
				case DRV_PROC_IN: addr.area = PDA_INPUT; break;
				case DRV_PROC_OUT: addr.area = PDA_OUTPUT; break;
				case DRV_PROC_MEM: addr.area = PDA_MEMORY; break;
				default: ret = SERVER_INVALID_DRIVER_AREA; break;
			}

			if (ret == SERVER_ERROR_NONE) {

				// Byte address
				addr.byteAddr = requestCMD->value[1];
				// Bit address
				addr.bitAddr = 0;

				// Value
				BYTE val = requestCMD->value[2];

				// Write BYTE
				int procErr = PROCESS_WRITE_BYTE(process, addr, val);

				// Check error
				if (procErr == PROCESS_ERROR_NONE) {

					// Prepare reply command
					replyCMD->command = DRV_CMD_OK;

				} else {
					ret = SERVER_PROCESS_ERROR;
					*additionalError = procErr;
				}
			}
		} else {
			ret = SERVER_DATA_LENGTH_INVALID;
		}
	} else {
		ret = SERVER_INVALID_COMMAND;
	}

	return ret;
}

int CMD_WRITE_WORD(extCMD *requestCMD, extCMD *replyCMD, processData *process, int *additionalError) {

	int ret = SERVER_ERROR_NONE;

	// Check command
	if (requestCMD->command == DRV_WRITE_WORD) {

		// Check data length
		if (requestCMD->len == 3) {

			// Prepare address structure
			processDataAddress addr;
			// Area
			switch (requestCMD->value[0]) {
				case DRV_PROC_IN: addr.area = PDA_INPUT; break;
				case DRV_PROC_OUT: addr.area = PDA_OUTPUT; break;
				case DRV_PROC_MEM: addr.area = PDA_MEMORY; break;
				default: ret = SERVER_INVALID_DRIVER_AREA; break;
			}

			if (ret == SERVER_ERROR_NONE) {

				// Byte address
				addr.byteAddr = requestCMD->value[1];
				// Bit address
				addr.bitAddr = 0;

				// Value
				WORD val = requestCMD->value[2];

				// Write WORD
				int procErr = PROCESS_WRITE_WORD(process, addr, val);

				// Check error
				if (procErr == PROCESS_ERROR_NONE) {

					// Prepare reply command
					replyCMD->command = DRV_CMD_OK;

				} else {
					ret = SERVER_PROCESS_ERROR;
					*additionalError = procErr;
				}
			}
		} else {
			ret = SERVER_DATA_LENGTH_INVALID;
		}
	} else {
		ret = SERVER_INVALID_COMMAND;
	}

	return ret;
}

int CMD_WRITE_DWORD(extCMD *requestCMD, extCMD *replyCMD, processData *process, int *additionalError) {

	int ret = SERVER_ERROR_NONE;

	// Check command
	if (requestCMD->command == DRV_WRITE_DWORD) {

		// Check data length
		if (requestCMD->len == 3) {

			// Prepare address structure
			processDataAddress addr;
			// Area
			switch (requestCMD->value[0]) {
				case DRV_PROC_IN: addr.area = PDA_INPUT; break;
				case DRV_PROC_OUT: addr.area = PDA_OUTPUT; break;
				case DRV_PROC_MEM: addr.area = PDA_MEMORY; break;
				default: ret = SERVER_INVALID_DRIVER_AREA; break;
			}

			if (ret == SERVER_ERROR_NONE) {

				// Byte address
				addr.byteAddr = requestCMD->value[1];
				// Bit address
				addr.bitAddr = 0;

				// Pointer to double word in command data
				DWORD *val = (DWORD*)&requestCMD->value[2];

				// Write DWORD
				int procErr = PROCESS_WRITE_DWORD(process, addr, *val);

				// Check error
				if (procErr == PROCESS_ERROR_NONE) {

					// Prepare reply command
					replyCMD->command = DRV_CMD_OK;

				} else {
					ret = SERVER_PROCESS_ERROR;
					*additionalError = procErr;
				}
			}
		} else {
			ret = SERVER_DATA_LENGTH_INVALID;
		}
	} else {
		ret = SERVER_INVALID_COMMAND;
	}

	return ret;
}

int CMD_WRITE_INT(extCMD *requestCMD, extCMD *replyCMD, processData *process, int *additionalError) {

	int ret = SERVER_ERROR_NONE;

	// Check command
	if (requestCMD->command == DRV_WRITE_INT) {

		// Check data length
		if (requestCMD->len == 3) {

			// Prepare address structure
			processDataAddress addr;
			// Area
			switch (requestCMD->value[0]) {
				case DRV_PROC_IN: addr.area = PDA_INPUT; break;
				case DRV_PROC_OUT: addr.area = PDA_OUTPUT; break;
				case DRV_PROC_MEM: addr.area = PDA_MEMORY; break;
				default: ret = SERVER_INVALID_DRIVER_AREA; break;
			}

			if (ret == SERVER_ERROR_NONE) {

				// Byte address
				addr.byteAddr = requestCMD->value[1];
				// Bit address
				addr.bitAddr = 0;

				// Value
				int val = requestCMD->value[2];

				// Write INT
				int procErr = PROCESS_WRITE_INT(process, addr, val);

				// Check error
				if (procErr == PROCESS_ERROR_NONE) {

					// Prepare reply command
					replyCMD->command = DRV_CMD_OK;

				} else {
					ret = SERVER_PROCESS_ERROR;
					*additionalError = procErr;
				}
			}
		} else {
			ret = SERVER_DATA_LENGTH_INVALID;
		}
	} else {
		ret = SERVER_INVALID_COMMAND;
	}

	return ret;
}

int CMD_WRITE_REAL(extCMD *requestCMD, extCMD *replyCMD, processData *process, int *additionalError) {

	int ret = SERVER_ERROR_NONE;

	// Check command
	if (requestCMD->command == DRV_WRITE_REAL) {

		// Check data length
		if (requestCMD->len == 3) {

			// Prepare address structure
			processDataAddress addr;
			// Area
			switch (requestCMD->value[0]) {
				case DRV_PROC_IN: addr.area = PDA_INPUT; break;
				case DRV_PROC_OUT: addr.area = PDA_OUTPUT; break;
				case DRV_PROC_MEM: addr.area = PDA_MEMORY; break;
				default: ret = SERVER_INVALID_DRIVER_AREA; break;
			}

			if (ret == SERVER_ERROR_NONE) {

				// Byte address
				addr.byteAddr = requestCMD->value[1];
				// Bit address
				addr.bitAddr = 0;

				// Pointer to Real in command data
				float *val = (float*)&requestCMD->value[2];

				// Write INT
				int procErr = PROCESS_WRITE_REAL(process, addr, *val);

				// Check error
				if (procErr == PROCESS_ERROR_NONE) {

					// Prepare reply command
					replyCMD->command = DRV_CMD_OK;

				} else {
					ret = SERVER_PROCESS_ERROR;
					*additionalError = procErr;
				}
			}
		} else {
			ret = SERVER_DATA_LENGTH_INVALID;
		}
	} else {
		ret = SERVER_INVALID_COMMAND;
	}

	return ret;
}

int parseClientCommand(shm_serverData *ssdt, int *exitPrg, processData *process, int *additionalError) {

	int ret = SERVER_ERROR_NONE;
	*additionalError = SERVER_ERROR_NONE;

	// Request command data
	extCMD requestDT;
	// Reply command data
	extCMD replyDT;

	// Clear command data structure
	shm_clearExtCommandData(&replyDT);

	// Check request
	int reqResult = shm_requestIn(ssdt->shm, &requestDT);

	// Request from client
	if (reqResult == SHM_REQUEST_IN) {

		// Check values length
		if (requestDT.len < CMD_DATA_SIZE) {

			// Check command number
			switch (requestDT.command) {
				case DRV_CMD_EXIT: ret = CMD_EXIT(&requestDT, &replyDT, exitPrg); break;
				case DRV_CMD_PING: ret = CMD_PING(&requestDT, &replyDT); break;
				case DRV_SET_BIT: ret = CMD_SET_BIT(&requestDT, &replyDT, process, additionalError); break;
				case DRV_RESET_BIT: ret = CMD_RESET_BIT(&requestDT, &replyDT, process, additionalError); break;
				case DRV_INVERT_BIT: ret = CMD_INVERT_BIT(&requestDT, &replyDT, process, additionalError); break;
				case DRV_SET_BITS: ret = CMD_SET_BITS(&requestDT, &replyDT, process, additionalError); break;
				case DRV_WRITE_BYTE: ret = CMD_WRITE_BYTE(&requestDT, &replyDT, process, additionalError); break;
				case DRV_WRITE_WORD: ret = CMD_WRITE_WORD(&requestDT, &replyDT, process, additionalError); break;
				case DRV_WRITE_DWORD: ret = CMD_WRITE_DWORD(&requestDT, &replyDT, process, additionalError); break;
				case DRV_WRITE_INT: ret = CMD_WRITE_INT(&requestDT, &replyDT, process, additionalError); break;
				case DRV_WRITE_REAL: ret = CMD_WRITE_REAL(&requestDT, &replyDT, process, additionalError); break;
				default: ret = SERVER_INVALID_COMMAND; break;
			}
		} else {
			ret = SERVER_DATA_LENGTH_OUT_OF_RANGE;
		}

		// Check error
		if (ret != SERVER_ERROR_NONE) {

			replyDT.command = DRV_CMD_NOK;
		}

		// Put reply
		int replyResult = shm_put_replyIn(ssdt->shm, &replyDT);
		if (replyResult != SHM_ERROR_NONE) {
			ret = SERVER_SHM_ERROR;
			*additionalError = replyResult;
		}

	} else if (reqResult != SHM_ERROR_NONE) {
		ret = SERVER_SHM_ERROR;
		*additionalError = reqResult;
	}

	return ret;
}

int copyProcessData(shm_serverData *ssdt, processData *process, int *additionalError) {

	int ret = SERVER_ERROR_NONE;

	// Copy process data
	int copyResult = shm_copy_process_data(ssdt->shm, process);

	if (copyResult != SHM_ERROR_NONE) {
		ret = SERVER_SHM_ERROR;
		*additionalError = copyResult;
	}

	return ret;
}
