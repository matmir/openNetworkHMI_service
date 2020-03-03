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

#include "onhSHMcpp/processDataAccess.h"
#include <string.h>

using namespace onh;

processDataAccess::processDataAccess():
	process(0)
{
}

processDataAccess::processDataAccess(processData *processDT, const MutexAccess& lock):
	process(processDT), processLock(lock)
{
}

processDataAccess::processDataAccess(const processDataAccess& pda):
	process(pda.process), processLock(pda.processLock)
{
}

processDataAccess::~processDataAccess() {
}

void processDataAccess::checkBitAddress(processDataAddress addr) {

	if (addr.bitAddr > 7)
		throw ShmException("Bit value is out of range", "processDataAccess::checkBitAddress");
}

void processDataAccess::checkArea(processDataAddress addr) {

	if ((addr.area <= 0) || (addr.area > 3))
		throw ShmException("Area value is out of range", "processDataAccess::checkArea");
}

bool processDataAccess::getBit(processDataAddress addr) {

	// Check bit address
	checkBitAddress(addr);

	// Check area
	checkArea(addr);

	// Check byte address
	if (addr.byteAddr >= PROCESS_DT_SIZE) {
		throw ShmException("Byte address is out of range", "processDataAccess::getBit");
	}

	// Byte data
	BYTE b = 0;

	// Lock access
	processLock.lock();
	// Get Byte
	switch (addr.area) {
		case PDA_INPUT: b = process->in[addr.byteAddr]; break;
		case PDA_OUTPUT: b = process->out[addr.byteAddr]; break;
		case PDA_MEMORY: b = process->mem[addr.byteAddr]; break;
	}
	// Unlock access
	processLock.unlock();

	// Read bit value
	bool v = (b >> addr.bitAddr & 0x01);

	return v;
}

std::vector<bool> processDataAccess::getBits(const std::vector<processDataAddress>& addr) {

	std::vector<bool> retV;

	for (unsigned int i=0; i<addr.size(); ++i) {
		// Read bit value
		retV.push_back(getBit(addr[i]));
	}

	return retV;
}

BYTE processDataAccess::getByte(processDataAddress addr) {

	// Check bit address
	checkBitAddress(addr);

	// Check area
	checkArea(addr);

	// Check byte address
	if (addr.byteAddr >= PROCESS_DT_SIZE) {
		throw ShmException("Byte address is out of range", "processDataAccess::getByte");
	}

	// Byte data
	BYTE b = 0;

	// Lock access
	processLock.lock();
	// Get Byte
	switch (addr.area) {
		case PDA_INPUT: b = process->in[addr.byteAddr]; break;
		case PDA_OUTPUT: b = process->out[addr.byteAddr]; break;
		case PDA_MEMORY: b = process->mem[addr.byteAddr]; break;
	}
	// Unlock access
	processLock.unlock();

	return b;
}

WORD processDataAccess::getWord(processDataAddress addr) {

	// Check bit address
	checkBitAddress(addr);

	// Check area
	checkArea(addr);

	// Check byte address
	if (addr.byteAddr >= PROCESS_DT_SIZE-1) {
		throw ShmException("Byte address is out of range", "processDataAccess::getWord");
	}

	// Prepare data
	BYTE b1 = 0;
	BYTE b2 = 0;
	WORD w = 0;
	WORD wt = 0;

	// Lock access
	processLock.lock();
	// Get data
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
	// Unlock access
	processLock.unlock();

	// Highest byte
	w = b2;
	w = w << 8;

	// Lower byte
	wt = b1;

	// One word
	w = (w | wt);

	return w;
}

DWORD processDataAccess::getDWord(processDataAddress addr) {

	// Check bit address
	checkBitAddress(addr);

	// Check area
	checkArea(addr);

	// Check byte address
	if (addr.byteAddr >= PROCESS_DT_SIZE-3) {
		throw ShmException("Byte address is out of range", "processDataAccess::getDWord");
	}

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

	// Lock access
	processLock.lock();
	// Get data
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
	// Unlock access
	processLock.unlock();

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

	return dw;
}

int processDataAccess::getInt(processDataAddress addr) {

	// Check bit address
	checkBitAddress(addr);

	// Check area
	checkArea(addr);

	// Check byte address
	if (addr.byteAddr >= PROCESS_DT_SIZE-(sizeof(int)-1)) {
		throw ShmException("Byte address is out of range", "processDataAccess::getInt");
	}

	// Int data
	int* v = 0;

	// Lock access
	processLock.lock();
	// Get data
	switch (addr.area) {
		case PDA_INPUT: v = (int*)&process->in[addr.byteAddr]; break;
		case PDA_OUTPUT: v = (int*)&process->out[addr.byteAddr]; break;
		case PDA_MEMORY: v = (int*)&process->mem[addr.byteAddr]; break;
	}
	// Unlock access
	processLock.unlock();

	return *v;
}

float processDataAccess::getReal(processDataAddress addr) {

	// Check bit address
	checkBitAddress(addr);

	// Check area
	checkArea(addr);

	// Check byte address
	if (addr.byteAddr >= PROCESS_DT_SIZE-(sizeof(float)-1)) {
		throw ShmException("Byte address is out of range", "processDataAccess::getReal");
	}

	// Float data
	float f = 0;

	// Lock access
	processLock.lock();
	// Get data
	switch (addr.area) {
		case PDA_INPUT: memcpy(&f, &process->in[addr.byteAddr], sizeof f); break;
		case PDA_OUTPUT: memcpy(&f, &process->out[addr.byteAddr], sizeof f); break;
		case PDA_MEMORY: memcpy(&f, &process->mem[addr.byteAddr], sizeof f); break;
	}
	// Unlock access
	processLock.unlock();

	return f;
}

void processDataAccess::setBit(processDataAddress addr) {

	// Check bit address
	checkBitAddress(addr);

	// Check area
	checkArea(addr);

	// Check byte address
	if (addr.byteAddr >= PROCESS_DT_SIZE) {
		throw ShmException("Byte address is out of range", "processDataAccess::setBit");
	}

	// Prepare bit
	BYTE b = 1;

	// Shift on valid position
	b = (b << addr.bitAddr);

	// Lock access
	processLock.lock();
	// Modify data
	switch (addr.area) {
		case PDA_INPUT: process->in[addr.byteAddr] = (process->in[addr.byteAddr] | b); break;
		case PDA_OUTPUT: process->out[addr.byteAddr] = (process->out[addr.byteAddr] | b); break;
		case PDA_MEMORY: process->mem[addr.byteAddr] = (process->mem[addr.byteAddr] | b); break;
	}
	// Unlock access
	processLock.unlock();
}

void processDataAccess::writeBit(processDataAddress addr, bool val) {

	if (val) {
		setBit(addr);
	} else {
		resetBit(addr);
	}
}

void processDataAccess::setBits(const std::vector<processDataAddress>& addr) {

	for (unsigned int i=0; i<addr.size(); ++i) {

		setBit(addr[i]);
	}
}

void processDataAccess::resetBit(processDataAddress addr) {

	// Check bit address
	checkBitAddress(addr);

	// Check area
	checkArea(addr);

	// Check byte address
	if (addr.byteAddr >= PROCESS_DT_SIZE) {
		throw ShmException("Byte address is out of range", "processDataAccess::resetBit");
	}

	// Prepare bit
	BYTE b = 1;

	// Shift on valid position
	b = (b << addr.bitAddr);
	// Invert register values
	b = (b ^ 0xff);

	// Lock access
	processLock.lock();
	// Modify data
	switch (addr.area) {
		case PDA_INPUT: process->in[addr.byteAddr] = (process->in[addr.byteAddr] & b); break;
		case PDA_OUTPUT: process->out[addr.byteAddr] = (process->out[addr.byteAddr] & b); break;
		case PDA_MEMORY: process->mem[addr.byteAddr] = (process->mem[addr.byteAddr] & b); break;
	}
	// Unlock access
	processLock.unlock();
}

void processDataAccess::invertBit(processDataAddress addr) {

	// Check bit address
	checkBitAddress(addr);

	// Check area
	checkArea(addr);

	// Check byte address
	if (addr.byteAddr >= PROCESS_DT_SIZE) {
		throw ShmException("Byte address is out of range", "processDataAccess::invertBit");
	}

	// Prepare bit
	BYTE b = 1;

	// Shift on valid position
	b = (b << addr.bitAddr);

	// Lock access
	processLock.lock();
	// Modify data
	switch (addr.area) {
		case PDA_INPUT: process->in[addr.byteAddr] = (process->in[addr.byteAddr] ^ b); break;
		case PDA_OUTPUT: process->out[addr.byteAddr] = (process->out[addr.byteAddr] ^ b); break;
		case PDA_MEMORY: process->mem[addr.byteAddr] = (process->mem[addr.byteAddr] ^ b); break;
	}
	// Unlock access
	processLock.unlock();
}

void processDataAccess::writeByte(processDataAddress addr, BYTE val) {

	// Check bit address
	checkBitAddress(addr);

	// Check area
	checkArea(addr);

	// Check byte address
	if (addr.byteAddr >= PROCESS_DT_SIZE) {
		throw ShmException("Byte address is out of range", "processDataAccess::writeByte");
	}

	// Lock access
	processLock.lock();
	// Modify data
	switch (addr.area) {
		case PDA_INPUT: process->in[addr.byteAddr] = val; break;
		case PDA_OUTPUT: process->out[addr.byteAddr] = val; break;
		case PDA_MEMORY: process->mem[addr.byteAddr] = val; break;
	}
	// Unlock access
	processLock.unlock();
}

void processDataAccess::writeWord(processDataAddress addr, WORD val) {

	// Check bit address
	checkBitAddress(addr);

	// Check area
	checkArea(addr);

	// Check byte address
	if (addr.byteAddr >= PROCESS_DT_SIZE-1) {
		throw ShmException("Byte address is out of range", "processDataAccess::writeWord");
	}

	// Pointer to word in process memory
	WORD *psInt = 0;

	// Lock access
	processLock.lock();
	// Init pointer
	switch (addr.area) {
		case PDA_INPUT: psInt = (WORD*)&process->in[addr.byteAddr]; break;
		case PDA_OUTPUT: psInt = (WORD*)&process->out[addr.byteAddr]; break;
		case PDA_MEMORY: psInt = (WORD*)&process->mem[addr.byteAddr]; break;
	}
	// Set value
	*psInt = val;
	// Unlock access
	processLock.unlock();
}

void processDataAccess::writeDWord(processDataAddress addr, DWORD val) {

	// Check bit address
	checkBitAddress(addr);

	// Check area
	checkArea(addr);

	// Check byte address
	if (addr.byteAddr >= PROCESS_DT_SIZE-3) {
		throw ShmException("Byte address is out of range", "processDataAccess::writeDWord");
	}

	// Pointer to double word in process memory
	DWORD *lpInt = 0;

	// Lock access
	processLock.lock();
	// Init pointer
	switch (addr.area) {
		case PDA_INPUT: lpInt = (DWORD*)&process->in[addr.byteAddr]; break;
		case PDA_OUTPUT: lpInt = (DWORD*)&process->out[addr.byteAddr]; break;
		case PDA_MEMORY: lpInt = (DWORD*)&process->mem[addr.byteAddr]; break;
	}
	// Set value
	*lpInt = val;
	// Unlock access
	processLock.unlock();
}

void processDataAccess::writeInt(processDataAddress addr, int val) {

	// Check bit address
	checkBitAddress(addr);

	// Check area
	checkArea(addr);

	// Check byte address
	if (addr.byteAddr >= PROCESS_DT_SIZE-(sizeof(int)-1)) {
		throw ShmException("Byte address is out of range", "processDataAccess::writeInt");
	}

	// Pointer to INT in process memory
	int *pInt = 0;

	// Lock access
	processLock.lock();
	// Init pointer
	switch (addr.area) {
		case PDA_INPUT: pInt = (int*)&process->in[addr.byteAddr]; break;
		case PDA_OUTPUT: pInt = (int*)&process->out[addr.byteAddr]; break;
		case PDA_MEMORY: pInt = (int*)&process->mem[addr.byteAddr]; break;
	}
	// Set value
	*pInt = val;
	// Unlock access
	processLock.unlock();
}

void processDataAccess::writeReal(processDataAddress addr, float val) {

	// Check bit address
	checkBitAddress(addr);

	// Check area
	checkArea(addr);

	// Check byte address
	if (addr.byteAddr >= PROCESS_DT_SIZE-(sizeof(float)-1)) {
		throw ShmException("Byte address is out of range", "processDataAccess::writeReal");
	}

	// Pointer to Real in process memory
	float *pReal = 0;

	// Lock access
	processLock.lock();

	// Init pointer
	switch (addr.area) {
		case PDA_INPUT: pReal = (float*)&process->in[addr.byteAddr]; break;
		case PDA_OUTPUT: pReal = (float*)&process->out[addr.byteAddr]; break;
		case PDA_MEMORY: pReal = (float*)&process->mem[addr.byteAddr]; break;
	}

	// Set value
	memcpy(pReal, &val, sizeof val);

	// Unlock access
	processLock.unlock();
}

void processDataAccess::clear(bool processIn, bool processOut, bool processMem) {

	int i = 0;

	if (processIn) {
		for (i=0; i<PROCESS_DT_SIZE; ++i) {
			process->in[i] = 0;
		}
	}

	if (processOut) {
		for (i=0; i<PROCESS_DT_SIZE; ++i) {
			process->out[i] = 0;
		}
	}

	if (processMem) {
		for (i=0; i<PROCESS_DT_SIZE; ++i) {
			process->mem[i] = 0;
		}
	}
}
