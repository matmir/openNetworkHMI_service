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

#ifndef PROCESSDATA
#define PROCESSDATA

#include <stdint.h>

/// Process data array size
#define PROCESS_DT_SIZE 5000

/// Process data area numbers
#define PDA_INPUT 0
#define PDA_OUTPUT 1
#define PDA_MEMORY 2

// Type definitions
typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;

/**
 * Process data structure
 */
typedef struct {
	/// Process data inputs
	BYTE in[PROCESS_DT_SIZE];

	/// Process data outputs
	BYTE out[PROCESS_DT_SIZE];

	/// Process data memory
	BYTE mem[PROCESS_DT_SIZE];

} processData;

/**
 * Structure of the process data address
 */
typedef struct {
	/// Process data area (0 - input, 1 - output, 2 - memory)
	unsigned int area;
	/// Process data byte address
	unsigned int byteAddr;
	/// Process data bit address
	unsigned int bitAddr;
} processDataAddress;

#endif /* PROCESSDATA */
