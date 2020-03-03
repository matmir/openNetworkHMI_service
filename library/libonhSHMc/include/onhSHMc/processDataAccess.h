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

#ifndef PROCESSDATAACCESS
#define PROCESSDATAACCESS

#include "processData.h"

/**
 * Error codes
 */
#define PROCESS_ERROR_NONE 0						// No error
#define PROCESS_ERROR_BIT_OUT_OF_RANGE 1			// Bit address out of range (max. 7)
#define PROCESS_ERROR_BYTE_OUT_OF_RANGE 2			// Byte address out of range
#define PROCESS_ERROR_AREA_OUT_OF_RANGE 3			// Invalid area value
#define PROCESS_ERROR_ARRAY_OUT_OF_RANGE 4			// Array is too small

/**
 * Check bit address in address
 *
 * @param addr Process data address
 *
 * @return Error number if occurs
 */
int PROCESS_CHECK_BIT_ADDRESS(processDataAddress addr);

/**
 * Check area value
 *
 * @param addr Process data address
 *
 * @return Error number if occurs
 */
int PROCESS_CHECK_AREA(processDataAddress addr);

/**
 * Clear process data
 *
 * @param process Process data structure
 */
void PROCESS_DATA_CLEAR(processData *process);

/**
 * Get bit from process data
 *
 * @param process Process data structure
 * @param addr Process data address
 * @param errNr Error number if occurs
 *
 * @return Bit value from process data
 */
char PROCESS_GET_BIT(processData *process, processDataAddress addr, int *errNr);

/**
 * Get bits from process data
 *
 * @param process Process data structure
 * @param addrTable Process data address table
 * @param valTable Array with return values
 * @param dataCount Number of data to read
 *
 * @return Error number
 */
int PROCESS_GET_BITS(processData *process, processDataAddress *addrTable, char *valTable, unsigned int dataCount);

/**
 * Get byte from process data
 *
 * @param process Process data structure
 * @param addr Process data address
 * @param errNr Error number if occurs
 *
 * @return Byte value from process data
 */
BYTE PROCESS_GET_BYTE(processData *process, processDataAddress addr, int *errNr);

/**
 * Get WORD from process data
 *
 * @param process Process data structure
 * @param addr Process data address
 * @param errNr Error number if occurs
 *
 * @return Word value from process data
 */
WORD PROCESS_GET_WORD(processData *process, processDataAddress addr, int *errNr);

/**
 * Get DWORD from process data
 *
 * @param process Process data structure
 * @param addr Process data address
 * @param errNr Error number if occurs
 *
 * @return Double word value from process data
 */
DWORD PROCESS_GET_DWORD(processData *process, processDataAddress addr, int *errNr);

/**
 * Get INT from process data
 *
 * @param process Process data structure
 * @param addr Process data address
 * @param errNr Error number if occurs
 *
 * @return Int value from process data
 */
int PROCESS_GET_INT(processData *process, processDataAddress addr, int *errNr);

/**
 * Get REAL from process data
 *
 * @param process Process data structure
 * @param addr Process data address
 * @param errNr Error number if occurs
 *
 * @return Real value from process data
 */
float PROCESS_GET_REAL(processData *process, processDataAddress addr, int *errNr);

/**
 * Set bit in process data
 *
 * @param process Process data structure
 * @param addr Process data address
 *
 * @return Error number
 */
int PROCESS_SET_BIT(processData *process, processDataAddress addr);

/**
 * Set bits in process data
 *
 * @param process Process data structure
 * @param addrTable Process data address table
 * @param dataCount Number of bits to set
 *
 * @return Error number
 */
int PROCESS_SET_BITS(processData *process, processDataAddress *addrTable, unsigned int dataCount);

/**
 * Reset bit in process data
 *
 * @param process Process data structure
 * @param addr Process data address
 *
 * @return Error number
 */
int PROCESS_RESET_BIT(processData *process, processDataAddress addr);

/**
 * Invert bit in process data
 *
 * @param process Process data structure
 * @param addr Process data address
 *
 * @return Error number
 */
int PROCESS_INVERT_BIT(processData *process, processDataAddress addr);

/**
 * Write BYTE in process data
 *
 * @param process Process data structure
 * @param addr Process data address
 * @param val Byte value
 *
 * @return Error number
 */
int PROCESS_WRITE_BYTE(processData *process, processDataAddress addr, BYTE val);

/**
 * Write WORD in process data
 *
 * @param process Process data structure
 * @param addr Process data address
 * @param val WORD value
 *
 * @return Error number
 */
int PROCESS_WRITE_WORD(processData *process, processDataAddress addr, WORD val);

/**
 * Write DWORD in process data
 *
 * @param process Process data structure
 * @param addr Process data address
 * @param val DWORD value
 *
 * @return Error number
 */
int PROCESS_WRITE_DWORD(processData *process, processDataAddress addr, DWORD val);

/**
 * Write INT in process data
 *
 * @param process Process data structure
 * @param addr Process data address
 * @param val Int value
 *
 * @return Error number
 */
int PROCESS_WRITE_INT(processData *process, processDataAddress addr, int val);

/**
 * Write REAL in process data
 *
 * @param process Process data structure
 * @param addr Process data address
 * @param val Real value
 *
 * @return Error number
 */
int PROCESS_WRITE_REAL(processData *process, processDataAddress addr, float val);

#endif /* PROCESSDATAACCESS */
