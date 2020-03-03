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

#include "onhSHMc/processDataAccess.h"
#include <stdio.h>
#include <string.h>

int PROCESS_CHECK_BIT_ADDRESS(processDataAddress addr) {

	int ret = 0;

	if (addr.bitAddr > 7) {
		ret = PROCESS_ERROR_BIT_OUT_OF_RANGE;
	}

	return ret;
}

int PROCESS_CHECK_AREA(processDataAddress addr) {

	int ret = 0;

	if (addr.area > 2) {
		ret = PROCESS_ERROR_AREA_OUT_OF_RANGE;
	}

	return ret;
}

void PROCESS_DATA_CLEAR(processData *process) {

	// clear all registers
	for (int i=0; i<PROCESS_DT_SIZE; ++i) {
		process->in[i] = 0;
		process->out[i] = 0;
		process->mem[i] = 0;
	}
}

char PROCESS_GET_BIT(processData *process, processDataAddress addr, int *errNr) {

	char retVal = 0;
	int err = PROCESS_ERROR_NONE;

	// Check bit address
	err = PROCESS_CHECK_BIT_ADDRESS(addr);

	if (err == PROCESS_ERROR_NONE) {

		// Check byte address
		if (addr.byteAddr >= PROCESS_DT_SIZE) {
			err = PROCESS_ERROR_BYTE_OUT_OF_RANGE;
		} else {

			// Check area
			err = PROCESS_CHECK_AREA(addr);
			if (err == PROCESS_ERROR_NONE) {

				// Get byte
				BYTE b = 0;

				switch (addr.area) {
					case PDA_INPUT: b = process->in[addr.byteAddr]; break;
					case PDA_OUTPUT: b = process->out[addr.byteAddr]; break;
					case PDA_MEMORY: b = process->mem[addr.byteAddr]; break;
				}

				// Read bit value
				retVal = (b >> addr.bitAddr & 0x01);
			}
		}
	}

	// Pass error
	*errNr = err;

	return retVal;
}

int PROCESS_GET_BITS(processData *process, processDataAddress *addrTable, char *valTable, unsigned int dataCount) {

	int err = PROCESS_ERROR_NONE;

	// Read data
	unsigned int i;
	for (i=0; i<dataCount; ++i) {

		// Check bit address
		err = PROCESS_CHECK_BIT_ADDRESS(addrTable[i]);

		if (err == PROCESS_ERROR_NONE) {

			// Check byte address
			if (addrTable[i].byteAddr >= PROCESS_DT_SIZE) {
				err = PROCESS_ERROR_BYTE_OUT_OF_RANGE;
				break;
			} else {

				// Check area
				err = PROCESS_CHECK_AREA(addrTable[i]);
				if (err == PROCESS_ERROR_NONE) {

					// Get byte
					BYTE b = 0;

					switch (addrTable[i].area) {
						case PDA_INPUT: b = process->in[addrTable[i].byteAddr]; break;
						case PDA_OUTPUT: b = process->out[addrTable[i].byteAddr]; break;
						case PDA_MEMORY: b = process->mem[addrTable[i].byteAddr]; break;
					}

					// Read bit value
					valTable[i] = (b >> addrTable[i].bitAddr & 0x01);
				} else {
					// Stop the loop
					break;
				}
			}
		} else {
			// Stop the loop
			break;
		}
	}

	return err;
}

BYTE PROCESS_GET_BYTE(processData *process, processDataAddress addr, int *errNr) {

	BYTE retVal = 0;
	int err = PROCESS_ERROR_NONE;

	// Check bit address
	err = PROCESS_CHECK_BIT_ADDRESS(addr);

	if (err == PROCESS_ERROR_NONE) {

		// Check byte address
		if (addr.byteAddr >= PROCESS_DT_SIZE) {
			err = PROCESS_ERROR_BYTE_OUT_OF_RANGE;
		} else {

			// Check area
			err = PROCESS_CHECK_AREA(addr);
			if (err == PROCESS_ERROR_NONE) {

				// Get byte
				BYTE b = 0;

				switch (addr.area) {
					case PDA_INPUT: b = process->in[addr.byteAddr]; break;
					case PDA_OUTPUT: b = process->out[addr.byteAddr]; break;
					case PDA_MEMORY: b = process->mem[addr.byteAddr]; break;
				}

				retVal = b;
			}
		}
	}

	// Pass error
	*errNr = err;

	return retVal;
}

WORD PROCESS_GET_WORD(processData *process, processDataAddress addr, int *errNr) {

	WORD retVal = 0;
	int err = PROCESS_ERROR_NONE;

	// Check bit address
	err = PROCESS_CHECK_BIT_ADDRESS(addr);

	if (err == PROCESS_ERROR_NONE) {

		// Check byte address
		if (addr.byteAddr >= PROCESS_DT_SIZE-1) {
			err = PROCESS_ERROR_BYTE_OUT_OF_RANGE;
		} else {

			// Check area
			err = PROCESS_CHECK_AREA(addr);
			if (err == PROCESS_ERROR_NONE) {

				// Prepare data
				BYTE b1 = 0;
				BYTE b2 = 0;
				WORD w = 0;
				WORD wt = 0;

				switch (addr.area) {
					case PDA_INPUT: {
						b1 = process->in[addr.byteAddr];
						b2 = process->in[addr.byteAddr+1];
					} break;
					case PDA_OUTPUT: {
						b1 = process->out[addr.byteAddr];
						b2 = process->out[addr.byteAddr+1];
					} break;
					case PDA_MEMORY: {
						b1 = process->mem[addr.byteAddr];
						b2 = process->mem[addr.byteAddr+1];
					} break;
				}

				// Highest byte
				w = b2;
				w = w << 8;

				// Lower byte
				wt = b1;

				// One word
				w = (w | wt);

				retVal = w;
			}
		}
	}

	// Pass error
	*errNr = err;

	return retVal;
}

DWORD PROCESS_GET_DWORD(processData *process, processDataAddress addr, int *errNr) {

	DWORD retVal = 0;
	int err = PROCESS_ERROR_NONE;

	// Check bit address
	err = PROCESS_CHECK_BIT_ADDRESS(addr);

	if (err == PROCESS_ERROR_NONE) {

		// Check byte address
		if (addr.byteAddr >= PROCESS_DT_SIZE-3) {
			err = PROCESS_ERROR_BYTE_OUT_OF_RANGE;
		} else {

			// Check area
			err = PROCESS_CHECK_AREA(addr);
			if (err == PROCESS_ERROR_NONE) {

				// Prepare data
				BYTE b1 = 0;
				BYTE b2 = 0;
				BYTE b3 = 0;
				BYTE b4 = 0;
				WORD w1 = 0;
				WORD w2 = 0;
				WORD wt = 0;
				DWORD dw = 0;
				DWORD dwt = 0;

				switch (addr.area) {
					case PDA_INPUT: {
						b1 = process->in[addr.byteAddr];
						b2 = process->in[addr.byteAddr+1];
						b3 = process->in[addr.byteAddr+2];
						b4 = process->in[addr.byteAddr+3];
					} break;
					case PDA_OUTPUT: {
						b1 = process->out[addr.byteAddr];
						b2 = process->out[addr.byteAddr+1];
						b3 = process->out[addr.byteAddr+2];
						b4 = process->out[addr.byteAddr+3];
					} break;
					case PDA_MEMORY: {
						b1 = process->mem[addr.byteAddr];
						b2 = process->mem[addr.byteAddr+1];
						b3 = process->mem[addr.byteAddr+2];
						b4 = process->mem[addr.byteAddr+3];
					} break;
				}

				// Highest word
				w2 = b4;
				w2 = w2 << 8;
				wt = b3;
				w2 = (w2 | wt);

				// Lower word
				w1 = b2;
				w1 = w1 << 8;
				wt = b1;
				w1 = (w1 | wt);

				// Dword
				dw = w2;
				dw = dw << 16;
				dwt = w1;
				dw = (dw | dwt);

				retVal = dw;
			}
		}
	}

	// Pass error
	*errNr = err;

	return retVal;
}

int PROCESS_GET_INT(processData *process, processDataAddress addr, int *errNr) {

	int retVal = 0;
	int err = PROCESS_ERROR_NONE;

	// Check bit address
	err = PROCESS_CHECK_BIT_ADDRESS(addr);

	if (err == PROCESS_ERROR_NONE) {

		// Check byte address
		if (addr.byteAddr >= PROCESS_DT_SIZE-(sizeof(int)-1)) {
			err = PROCESS_ERROR_BYTE_OUT_OF_RANGE;
		} else {

			// Check area
			err = PROCESS_CHECK_AREA(addr);
			if (err == PROCESS_ERROR_NONE) {

				// Get int
				int* v = 0;

				switch (addr.area) {
					case PDA_INPUT: v = (int*)&process->in[addr.byteAddr]; break;
					case PDA_OUTPUT: v = (int*)&process->out[addr.byteAddr]; break;
					case PDA_MEMORY: v = (int*)&process->mem[addr.byteAddr]; break;
				}

				// Read bit value
				retVal = *v;
			}
		}
	}

	// Pass error
	*errNr = err;

	return retVal;
}

float PROCESS_GET_REAL(processData *process, processDataAddress addr, int *errNr) {

	float retVal = 0;
	int err = PROCESS_ERROR_NONE;

	// Check bit address
	err = PROCESS_CHECK_BIT_ADDRESS(addr);

	if (err == PROCESS_ERROR_NONE) {

		// Check byte address
		if (addr.byteAddr >= PROCESS_DT_SIZE-(sizeof(float)-1)) {
			err = PROCESS_ERROR_BYTE_OUT_OF_RANGE;
		} else {

			// Check area
			err = PROCESS_CHECK_AREA(addr);
			if (err == PROCESS_ERROR_NONE) {

				// Get float
				switch (addr.area) {
					case PDA_INPUT: memcpy(&retVal, &process->in[addr.byteAddr], sizeof retVal); break;
					case PDA_OUTPUT: memcpy(&retVal, &process->out[addr.byteAddr], sizeof retVal); break;
					case PDA_MEMORY: memcpy(&retVal, &process->mem[addr.byteAddr], sizeof retVal); break;
				}
			}
		}
	}

	// Pass error
	*errNr = err;

	return retVal;
}

int PROCESS_SET_BIT(processData *process, processDataAddress addr) {

	int err = PROCESS_ERROR_NONE;

	// Check bit address
	err = PROCESS_CHECK_BIT_ADDRESS(addr);

	if (err == PROCESS_ERROR_NONE) {

		// Check byte address
		if (addr.byteAddr >= PROCESS_DT_SIZE) {
			err = PROCESS_ERROR_BYTE_OUT_OF_RANGE;
		} else {

			// Check area
			err = PROCESS_CHECK_AREA(addr);
			if (err == PROCESS_ERROR_NONE) {

				// Prepare bit
				BYTE b = 1;

				// Shift on valid position
				b = (b << addr.bitAddr);

				switch (addr.area) {
					case PDA_INPUT: process->in[addr.byteAddr] = (process->in[addr.byteAddr] | b); break;
					case PDA_OUTPUT: process->out[addr.byteAddr] = (process->out[addr.byteAddr] | b); break;
					case PDA_MEMORY: process->mem[addr.byteAddr] = (process->mem[addr.byteAddr] | b); break;
				}
			}
		}
	}

	return err;
}

int PROCESS_SET_BITS(processData *process, processDataAddress *addrTable, unsigned int dataCount) {

	int err = PROCESS_ERROR_NONE;

	// Read data
	for (unsigned int i=0; i<dataCount; ++i) {

		// Check bit address
		err = PROCESS_CHECK_BIT_ADDRESS(addrTable[i]);

		if (err == PROCESS_ERROR_NONE) {

			// Check byte address
			if (addrTable[i].byteAddr >= PROCESS_DT_SIZE) {
				err = PROCESS_ERROR_BYTE_OUT_OF_RANGE;
				break;
			} else {

				// Check area
				err = PROCESS_CHECK_AREA(addrTable[i]);
				if (err == PROCESS_ERROR_NONE) {

					// Prepare bit
					BYTE b = 1;

					// Shift on valid position
					b = (b << addrTable[i].bitAddr);

					switch (addrTable[i].area) {
						case PDA_INPUT: process->in[addrTable[i].byteAddr] = (process->in[addrTable[i].byteAddr] | b); break;
						case PDA_OUTPUT: process->out[addrTable[i].byteAddr] = (process->out[addrTable[i].byteAddr] | b); break;
						case PDA_MEMORY: process->mem[addrTable[i].byteAddr] = (process->mem[addrTable[i].byteAddr] | b); break;
					}

				} else {
					// Stop the loop
					break;
				}
			}
		} else {
			// Stop the loop
			break;
		}
	}

	return err;
}

int PROCESS_RESET_BIT(processData *process, processDataAddress addr) {

	int err = PROCESS_ERROR_NONE;

	// Check bit address
	err = PROCESS_CHECK_BIT_ADDRESS(addr);

	if (err == PROCESS_ERROR_NONE) {

		// Check byte address
		if (addr.byteAddr >= PROCESS_DT_SIZE) {
			err = PROCESS_ERROR_BYTE_OUT_OF_RANGE;
		} else {

			// Check area
			err = PROCESS_CHECK_AREA(addr);
			if (err == PROCESS_ERROR_NONE) {

				// Prepare bit
				BYTE b = 1;

				// Shift on valid position
				b = (b << addr.bitAddr);
				// Invert register values
				b = (b ^ 0xff);

				switch (addr.area) {
					case PDA_INPUT: process->in[addr.byteAddr] = (process->in[addr.byteAddr] & b); break;
					case PDA_OUTPUT: process->out[addr.byteAddr] = (process->out[addr.byteAddr] & b); break;
					case PDA_MEMORY: process->mem[addr.byteAddr] = (process->mem[addr.byteAddr] & b); break;
				}
			}
		}
	}

	return err;
}

int PROCESS_INVERT_BIT(processData *process, processDataAddress addr) {

	int err = PROCESS_ERROR_NONE;

	// Check bit address
	err = PROCESS_CHECK_BIT_ADDRESS(addr);

	if (err == PROCESS_ERROR_NONE) {

		// Check byte address
		if (addr.byteAddr >= PROCESS_DT_SIZE) {
			err = PROCESS_ERROR_BYTE_OUT_OF_RANGE;
		} else {

			// Check area
			err = PROCESS_CHECK_AREA(addr);
			if (err == PROCESS_ERROR_NONE) {

				// Prepare bit
				BYTE b = 1;

				// Shift on valid position
				b = (b << addr.bitAddr);

				switch (addr.area) {
					case PDA_INPUT: process->in[addr.byteAddr] = (process->in[addr.byteAddr] ^ b); break;
					case PDA_OUTPUT: process->out[addr.byteAddr] = (process->out[addr.byteAddr] ^ b); break;
					case PDA_MEMORY: process->mem[addr.byteAddr] = (process->mem[addr.byteAddr] ^ b); break;
				}
			}
		}
	}

	return err;
}

int PROCESS_WRITE_BYTE(processData *process, processDataAddress addr, BYTE val) {

	int err = PROCESS_ERROR_NONE;

	// Check bit address
	err = PROCESS_CHECK_BIT_ADDRESS(addr);

	if (err == PROCESS_ERROR_NONE) {

		// Check byte address
		if (addr.byteAddr >= PROCESS_DT_SIZE) {
			err = PROCESS_ERROR_BYTE_OUT_OF_RANGE;
		} else {

			// Check area
			err = PROCESS_CHECK_AREA(addr);
			if (err == PROCESS_ERROR_NONE) {

				switch (addr.area) {
					case PDA_INPUT: process->in[addr.byteAddr] = val; break;
					case PDA_OUTPUT: process->out[addr.byteAddr] = val; break;
					case PDA_MEMORY: process->mem[addr.byteAddr] = val; break;
				}
			}
		}
	}

	return err;
}

int PROCESS_WRITE_WORD(processData *process, processDataAddress addr, WORD val) {

	int err = PROCESS_ERROR_NONE;

	// Check bit address
	err = PROCESS_CHECK_BIT_ADDRESS(addr);

	if (err == PROCESS_ERROR_NONE) {

		// Check byte address
		if (addr.byteAddr >= PROCESS_DT_SIZE-1) {
			err = PROCESS_ERROR_BYTE_OUT_OF_RANGE;
		} else {

			// Check area
			err = PROCESS_CHECK_AREA(addr);
			if (err == PROCESS_ERROR_NONE) {

				// Pointer to word in process memory
				WORD *psInt = 0;

				switch (addr.area) {
					case PDA_INPUT: psInt = (WORD*)&process->in[addr.byteAddr]; break;
					case PDA_OUTPUT: psInt = (WORD*)&process->out[addr.byteAddr]; break;
					case PDA_MEMORY: psInt = (WORD*)&process->mem[addr.byteAddr]; break;
				}

				// Set value
				*psInt = val;
			}
		}
	}

	return err;
}

int PROCESS_WRITE_DWORD(processData *process, processDataAddress addr, DWORD val) {

	int err = PROCESS_ERROR_NONE;

	// Check bit address
	err = PROCESS_CHECK_BIT_ADDRESS(addr);

	if (err == PROCESS_ERROR_NONE) {

		// Check byte address
		if (addr.byteAddr >= PROCESS_DT_SIZE-3) {
			err = PROCESS_ERROR_BYTE_OUT_OF_RANGE;
		} else {

			// Check area
			err = PROCESS_CHECK_AREA(addr);
			if (err == PROCESS_ERROR_NONE) {

				// Pointer to double word in process memory
				DWORD *lpInt = 0;

				switch (addr.area) {
					case PDA_INPUT: lpInt = (DWORD*)&process->in[addr.byteAddr]; break;
					case PDA_OUTPUT: lpInt = (DWORD*)&process->out[addr.byteAddr]; break;
					case PDA_MEMORY: lpInt = (DWORD*)&process->mem[addr.byteAddr]; break;
				}

				// Set value
				*lpInt = val;
			}
		}
	}

	return err;
}

int PROCESS_WRITE_INT(processData *process, processDataAddress addr, int val) {

	int err = PROCESS_ERROR_NONE;

	// Check bit address
	err = PROCESS_CHECK_BIT_ADDRESS(addr);

	if (err == PROCESS_ERROR_NONE) {

		// Check byte address
		if (addr.byteAddr >= PROCESS_DT_SIZE-(sizeof(int)-1)) {
			err = PROCESS_ERROR_BYTE_OUT_OF_RANGE;
		} else {

			// Check area
			err = PROCESS_CHECK_AREA(addr);
			if (err == PROCESS_ERROR_NONE) {

				// Pointer to INT in process memory
				int *pInt = 0;

				switch (addr.area) {
					case PDA_INPUT: pInt = (int*)&process->in[addr.byteAddr]; break;
					case PDA_OUTPUT: pInt = (int*)&process->out[addr.byteAddr]; break;
					case PDA_MEMORY: pInt = (int*)&process->mem[addr.byteAddr]; break;
				}

				// Set value
				*pInt = val;
			}
		}
	}

	return err;
}

int PROCESS_WRITE_REAL(processData *process, processDataAddress addr, float val) {

	int err = PROCESS_ERROR_NONE;

	// Check bit address
	err = PROCESS_CHECK_BIT_ADDRESS(addr);

	if (err == PROCESS_ERROR_NONE) {

		// Check byte address
		if (addr.byteAddr >= PROCESS_DT_SIZE-(sizeof(float)-1)) {
			err = PROCESS_ERROR_BYTE_OUT_OF_RANGE;
		} else {

			// Check area
			err = PROCESS_CHECK_AREA(addr);
			if (err == PROCESS_ERROR_NONE) {

				// Pointer to Real in process memory
				float *pReal = 0;

				switch (addr.area) {
					case PDA_INPUT: pReal = (float*)&process->in[addr.byteAddr]; break;
					case PDA_OUTPUT: pReal = (float*)&process->out[addr.byteAddr]; break;
					case PDA_MEMORY: pReal = (float*)&process->mem[addr.byteAddr]; break;
				}

				// Set value
				memcpy(pReal, &val, sizeof val);
			}
		}
	}

	return err;
}
