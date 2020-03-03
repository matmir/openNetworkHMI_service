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

#include "onhSHMcpp/ShmServer.h"
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include "onhSHMcpp/sCommands.h"

using namespace onh;

ShmServer::ShmServer(const std::string& shmSegmentName):
	exitProgram(false), sfd(0), smName(shmSegmentName), shm(0)
{
	if (smName == "")
		throw ShmException("Shared memory segment name is empty", "ShmServer::ShmServer");

	// Create the shared memory segment
	sfd = shm_open(smName.c_str(), O_CREAT | O_RDWR, 0666);
	if (sfd == -1)
		throw ShmException("shm_open failure", "ShmServer::ShmServer");

	// Configure the size of the shared memory segment
	if (ftruncate(sfd, smSize) == -1)
		throw ShmException("ftruncate failure", "ShmServer::ShmServer");

	// Map the shared memory segment in the address space of the process
	shm = (sMemory*)mmap(NULL, smSize, PROT_READ | PROT_WRITE, MAP_SHARED, sfd, 0);
	if (shm == MAP_FAILED)
		throw ShmException("Map failed", "ShmServer::ShmServer");

	// Mutex settings
	pthread_mutexattr_t mutex_attr;

	// Condition variable settings
	pthread_condattr_t cond_attr;

	if (pthread_mutexattr_init(&mutex_attr) != 0)
		throw ShmException("Mutex Initialize attribute error", "ShmServer::ShmServer");

	if (pthread_mutexattr_setpshared(&mutex_attr, PTHREAD_PROCESS_SHARED) != 0)
		throw ShmException("Mutex set the process-shared flag error", "ShmServer::ShmServer");

	// Init request mutex
	if (pthread_mutex_init(&shm->cs.requestMutex, &mutex_attr) != 0)
		throw ShmException("Request mutex initialize error", "ShmServer::ShmServer");

	// Init reply mutex
	if (pthread_mutex_init(&shm->cs.replyMutex, &mutex_attr) != 0)
		throw ShmException("Reply mutex initialize error", "ShmServer::ShmServer");

	// Init process mutex
	if (pthread_mutex_init(&shm->process.processMutex, &mutex_attr) != 0)
		throw ShmException("Process mutex initialize error", "ShmServer::ShmServer");

	// Condition variable attribute
	if (pthread_condattr_init(&cond_attr) != 0)
		throw ShmException("Condition variable initialize attribute error", "ShmServer::ShmServer");

	if (pthread_condattr_setpshared(&cond_attr, PTHREAD_PROCESS_SHARED) != 0)
		throw ShmException("Condition variable set the process-shared flag error", "ShmServer::ShmServer");

	// Init condition variable
	if (pthread_cond_init(&shm->cs.replyCondvar, &cond_attr) != 0)
		throw ShmException("Condition variable initialize error", "ShmServer::ShmServer");

	clearCSCommandData();
	clearCSSyncData();
	clearProcessData();
	clearInternalCommandData();

	// Process data access
	pda = new processDataAccess(&process, processLock.getAccess());
}

ShmServer::~ShmServer() {

	// Unmap shared memory
	munmap(shm, smSize);

	// Close shared memory object
	close(sfd);

	// Delete shared memory object
	shm_unlink(smName.c_str());

	if (pda)
		delete pda;
}

processDataAccess ShmServer::getProcessAccess() {

	return processDataAccess(&process, processLock.getAccess());
}

template <class T>
PDTag<T> ShmServer::getTag(const processDataAddress &tagAddr) {

	return PDTag<T>(tagAddr, *pda);
}

void ShmServer::clearInternalCommandData() {

	requestDT.command = 0;
	requestDT.len = 0;
	replyDT.command = 0;
	replyDT.len = 0;

	for (int i=0; i<CMD_DATA_SIZE; ++i) {
		requestDT.value[i] = 0;
		replyDT.value[i] = 0;
	}
}

void ShmServer::clearCSCommandData() {

	// Lock request mutex
	if (pthread_mutex_lock(&shm->cs.requestMutex) != 0)
		throw ShmException("Lock request mutex error", "ShmServer::clearCSCommandData");

	shm->cs.data.command = 0;
	shm->cs.data.len = 0;

	for (int i=0; i<CMD_DATA_SIZE; ++i) {
		shm->cs.data.value[i] = 0;
	}

	// Unlock request mutex
	if (pthread_mutex_unlock(&shm->cs.requestMutex) != 0)
		throw ShmException("Unlock request mutex error", "ShmServer::clearCSCommandData");
}

void ShmServer::clearCSSyncData() {

	// Lock request mutex
	if (pthread_mutex_lock(&shm->cs.requestMutex) != 0)
		throw ShmException("Lock request mutex error", "ShmServer::clearCSSyncData");

	shm->cs.requestIn = 0;
	shm->cs.replyIn = 0;

	// Unlock request mutex
	if (pthread_mutex_unlock(&shm->cs.requestMutex) != 0)
		throw ShmException("Unlock request mutex error", "ShmServer::clearCSSyncData");
}

void ShmServer::clearProcessData(bool internalDT, bool shmDT) {

	if (internalDT) {

			// Lock internal process mutex
			processLock.lock();

			for (int i=0; i<PROCESS_DT_SIZE; ++i) {
				process.in[i] = 0;
				process.out[i] = 0;
				process.mem[i] = 0;
			}

			// Unlock internal process mutex
			processLock.unlock();
		}

	if (shmDT) {

		// Lock process mutex
		if (pthread_mutex_lock(&shm->process.processMutex) != 0)
			throw ShmException("Lock process mutex error", "ShmServer::clearProcessData");

		for (int i=0; i<PROCESS_DT_SIZE; ++i) {
			shm->process.procDT.in[i] = 0;
			shm->process.procDT.out[i] = 0;
			shm->process.procDT.mem[i] = 0;
		}

		// Unlock process mutex
		if (pthread_mutex_unlock(&shm->process.processMutex) != 0)
			throw ShmException("Unlock process mutex error", "ShmServer::clearProcessData");
	}
}

void ShmServer::parseClientCommand() {

	// Check request
	if (isRequest()) {

		try {
			// Check values length
			if (requestDT.len>=CMD_DATA_SIZE)
				throw ShmException("Command data length is out of range", "ShmServer::parseClientCommand");

			// Parse command
			switch (requestDT.command) {
				case DRV_CMD_EXIT: CMD_EXIT(); break;
				case DRV_CMD_PING: CMD_PING(); break;
				case DRV_SET_BIT: CMD_SET_BIT(); break;
				case DRV_RESET_BIT: CMD_RESET_BIT(); break;
				case DRV_INVERT_BIT: CMD_INVERT_BIT(); break;
				case DRV_SET_BITS: CMD_SET_BITS(); break;
				case DRV_WRITE_BYTE: CMD_WRITE_BYTE(); break;
				case DRV_WRITE_WORD: CMD_WRITE_WORD(); break;
				case DRV_WRITE_DWORD: CMD_WRITE_DWORD(); break;
				case DRV_WRITE_INT: CMD_WRITE_INT(); break;
				case DRV_WRITE_REAL: CMD_WRITE_REAL(); break;
				default: throw ShmException("Invalid command", "ShmServer::parseClientCommand"); break;
			}
		} catch(ShmException &e) {
			// Reply error to client
			replyDT.command = DRV_CMD_NOK;
			// Error reply to client
			putReply();

			// Re-throw exception
			throw;
		}

		// Normal reply to client
		putReply();

	}
}

bool ShmServer::copyProcessData() {

	bool ret = false;

	// Try to lock internal process data
	if (processLock.tryLock()) {

		// Try to lock shm process mutex
		if (pthread_mutex_trylock(&shm->process.processMutex) == 0) {

			// Copy internal process data into shared memory
			shm->process.procDT = process;

			ret = true;

			// Unlock shm process mutex
			if (pthread_mutex_unlock(&shm->process.processMutex) != 0)
				throw ShmException("Unlock process mutex error", "ShmServer::copyProcessData");
		}

		// Unlock internal process data
		processLock.unlock();
	}

	return ret;
}

bool ShmServer::isExitFlag() const {

	return exitProgram;
}

void ShmServer::clearExitFlag() {

	exitProgram = false;
}

void ShmServer::clearAllData() {

	clearInternalCommandData();
	clearCSCommandData();
	clearCSSyncData();
	clearProcessData();
}

bool ShmServer::isRequest() {

	bool ret = false;

	// Clear internal request/reply data
	clearInternalCommandData();

	// Try to lock request mutex
	if (pthread_mutex_trylock(&shm->cs.requestMutex) == 0) {

		if ((shm->cs.requestIn == 1) && (shm->cs.replyIn == 0)) {

			// Read data
			requestDT.command = shm->cs.data.command;
			requestDT.len = shm->cs.data.len;
			// Read values
			if (requestDT.len<CMD_DATA_SIZE) {
				for (int i=0; i<requestDT.len; ++i) {
					requestDT.value[i] = shm->cs.data.value[i];
				}
			}

			ret = true;
		} else if ((shm->cs.requestIn == 1) && (shm->cs.replyIn == 1)) {
			// Wrong sync data - clear all command data
			clearInternalCommandData();
			clearCSCommandData();
			clearCSSyncData();
		}

		// Unlock request mutex
		if (pthread_mutex_unlock(&shm->cs.requestMutex) != 0)
			throw ShmException("Unlock request mutex error", "ShmServer::isRequest");
	}

	return ret;
}

void ShmServer::putReply() {

	// Check values length
	if (replyDT.len>=CMD_DATA_SIZE)
		throw ShmException("Command data length is out of range", "ShmServer::putReply");

	// Lock request mutex
	if (pthread_mutex_lock(&shm->cs.requestMutex) != 0)
		throw ShmException("Lock request mutex error", "ShmServer::putReply");

	// Copy data
	shm->cs.data.command = replyDT.command;
	shm->cs.data.len = replyDT.len;

	for (int i=0; i<replyDT.len; ++i) {
		shm->cs.data.value[i] = replyDT.value[i];
	}

	shm->cs.requestIn = 0;
	shm->cs.replyIn = 1;

	// Unlock request mutex
	if (pthread_mutex_unlock(&shm->cs.requestMutex) != 0)
		throw ShmException("Unlock request mutex error", "ShmServer::putReply");

	// Lock reply mutex
	if (pthread_mutex_lock(&shm->cs.replyMutex) != 0)
		throw ShmException("Lock reply mutex error", "ShmServer::putReply");
	// Condition variable signaling
	if (pthread_cond_signal(&shm->cs.replyCondvar) != 0)
		throw ShmException("Condition variable signaling error", "ShmServer::putReply");
	// Unlock reply mutex
	if (pthread_mutex_unlock(&shm->cs.replyMutex) != 0)
		throw ShmException("Unlock reply mutex error", "ShmServer::putReply");
}

void ShmServer::CMD_EXIT() {

	// Check command
	if (requestDT.command != DRV_CMD_EXIT)
		throw ShmException("Invalid command", "ShmServer::CMD_EXIT");

	// Check data length
	if (requestDT.len != 0)
		throw ShmException("Invalid command data length", "ShmServer::CMD_EXIT");

	// Prepare reply command
	replyDT.command = DRV_CMD_OK;

	// Exit flag
	exitProgram = true;
}

void ShmServer::CMD_PING() {

	// Check command
	if (requestDT.command != DRV_CMD_PING)
		throw ShmException("Invalid command", "ShmServer::CMD_PING");

	// Check data length
	if (requestDT.len != 0)
		throw ShmException("Invalid command data length", "ShmServer::CMD_PING");

	// Prepare reply command
	replyDT.command = DRV_CMD_PONG;
}

void ShmServer::CMD_SET_BIT() {

	// Check command
	if (requestDT.command != DRV_SET_BIT)
		throw ShmException("Invalid command", "ShmServer::CMD_SET_BIT");

	// Check data length
	if (requestDT.len != 3)
		throw ShmException("Invalid command data length", "ShmServer::CMD_SET_BIT");

	// Prepare address structure
	processDataAddress addr;
	// Area
	switch (requestDT.value[0]) {
		case DRV_PROC_IN: addr.area = PDA_INPUT; break;
		case DRV_PROC_OUT: addr.area = PDA_OUTPUT; break;
		case DRV_PROC_MEM: addr.area = PDA_MEMORY; break;
		default: throw ShmException("Invalid driver area", "ShmServer::CMD_SET_BIT"); break;
	}
	// Byte address
	addr.byteAddr = requestDT.value[1];
	// Bit address
	addr.bitAddr = requestDT.value[2];

	// Set bit
	pda->setBit(addr);

	// Prepare reply command
	replyDT.command = DRV_CMD_OK;
}

void ShmServer::CMD_RESET_BIT() {

	// Check command
	if (requestDT.command != DRV_RESET_BIT)
		throw ShmException("Invalid command", "ShmServer::CMD_RESET_BIT");

	// Check data length
	if (requestDT.len != 3)
		throw ShmException("Invalid command data length", "ShmServer::CMD_RESET_BIT");

	// Prepare address structure
	processDataAddress addr;
	// Area
	switch (requestDT.value[0]) {
		case DRV_PROC_IN: addr.area = PDA_INPUT; break;
		case DRV_PROC_OUT: addr.area = PDA_OUTPUT; break;
		case DRV_PROC_MEM: addr.area = PDA_MEMORY; break;
		default: throw ShmException("Invalid driver area", "ShmServer::CMD_RESET_BIT"); break;
	}
	// Byte address
	addr.byteAddr = requestDT.value[1];
	// Bit address
	addr.bitAddr = requestDT.value[2];

	// Reset bit
	pda->resetBit(addr);

	// Prepare reply command
	replyDT.command = DRV_CMD_OK;
}

void ShmServer::CMD_INVERT_BIT() {

	// Check command
	if (requestDT.command != DRV_INVERT_BIT)
		throw ShmException("Invalid command", "ShmServer::CMD_INVERT_BIT");

	// Check data length
	if (requestDT.len != 3)
		throw ShmException("Invalid command data length", "ShmServer::CMD_INVERT_BIT");

	// Prepare address structure
	processDataAddress addr;
	// Area
	switch (requestDT.value[0]) {
		case DRV_PROC_IN: addr.area = PDA_INPUT; break;
		case DRV_PROC_OUT: addr.area = PDA_OUTPUT; break;
		case DRV_PROC_MEM: addr.area = PDA_MEMORY; break;
		default: throw ShmException("Invalid driver area", "ShmServer::CMD_INVERT_BIT"); break;
	}
	// Byte address
	addr.byteAddr = requestDT.value[1];
	// Bit address
	addr.bitAddr = requestDT.value[2];

	// Invert bit
	pda->invertBit(addr);

	// Prepare reply command
	replyDT.command = DRV_CMD_OK;
}

void ShmServer::CMD_SET_BITS() {

	// Check command
	if (requestDT.command != DRV_SET_BITS)
		throw ShmException("Invalid command", "ShmServer::CMD_SET_BITS");

	// Check data length
	if ((requestDT.len == 0) || ((requestDT.len % 3) != 0))
		throw ShmException("Invalid command data length", "ShmServer::CMD_SET_BITS");

	int tagsCount = requestDT.len / 3;
	int dto = 0;

	// Address table
	std::vector<processDataAddress> addrV;
	processDataAddress addr;

	// Prepare address table
	for (int i=0; i<tagsCount; ++i) {

		// Area
		switch (requestDT.value[dto+0]) {
			case DRV_PROC_IN: addr.area = PDA_INPUT; break;
			case DRV_PROC_OUT: addr.area = PDA_OUTPUT; break;
			case DRV_PROC_MEM: addr.area = PDA_MEMORY; break;
			default: throw ShmException("Invalid driver area", "ShmServer::CMD_SET_BITS"); break;
		}
		// Byte address
		addr.byteAddr = requestDT.value[dto+1];
		// Bit address
		addr.bitAddr = requestDT.value[dto+2];

		// Next tag
		dto += 3;

		// Insert into the vector
		addrV.push_back(addr);
	}

	// Set bits
	pda->setBits(addrV);

	// Prepare reply command
	replyDT.command = DRV_CMD_OK;
}

void ShmServer::CMD_WRITE_BYTE() {

	// Check command
	if (requestDT.command != DRV_WRITE_BYTE)
		throw ShmException("Invalid command", "ShmServer::CMD_WRITE_BYTE");

	// Check data length
	if (requestDT.len != 3)
		throw ShmException("Invalid command data length", "ShmServer::CMD_WRITE_BYTE");

	// Prepare address structure
	processDataAddress addr;
	// Area
	switch (requestDT.value[0]) {
		case DRV_PROC_IN: addr.area = PDA_INPUT; break;
		case DRV_PROC_OUT: addr.area = PDA_OUTPUT; break;
		case DRV_PROC_MEM: addr.area = PDA_MEMORY; break;
		default: throw ShmException("Invalid driver area", "ShmServer::CMD_WRITE_BYTE"); break;
	}
	// Byte address
	addr.byteAddr = requestDT.value[1];
	// Bit address
	addr.bitAddr = 0;

	// Value
	BYTE val = requestDT.value[2];

	// Write BYTE
	pda->writeByte(addr, val);

	// Prepare reply command
	replyDT.command = DRV_CMD_OK;
}

void ShmServer::CMD_WRITE_WORD() {

	// Check command
	if (requestDT.command != DRV_WRITE_WORD)
		throw ShmException("Invalid command", "ShmServer::CMD_WRITE_WORD");

	// Check data length
	if (requestDT.len != 3)
		throw ShmException("Invalid command data length", "ShmServer::CMD_WRITE_WORD");

	// Prepare address structure
	processDataAddress addr;
	// Area
	switch (requestDT.value[0]) {
		case DRV_PROC_IN: addr.area = PDA_INPUT; break;
		case DRV_PROC_OUT: addr.area = PDA_OUTPUT; break;
		case DRV_PROC_MEM: addr.area = PDA_MEMORY; break;
		default: throw ShmException("Invalid driver area", "ShmServer::CMD_WRITE_WORD"); break;
	}
	// Byte address
	addr.byteAddr = requestDT.value[1];
	// Bit address
	addr.bitAddr = 0;

	// Value
	WORD val = requestDT.value[2];

	// Write WORD
	pda->writeWord(addr, val);

	// Prepare reply command
	replyDT.command = DRV_CMD_OK;
}

void ShmServer::CMD_WRITE_DWORD() {

	// Check command
	if (requestDT.command != DRV_WRITE_DWORD)
		throw ShmException("Invalid command", "ShmServer::CMD_WRITE_DWORD");

	// Check data length
	if (requestDT.len != 3)
		throw ShmException("Invalid command data length", "ShmServer::CMD_WRITE_DWORD");

	// Prepare address structure
	processDataAddress addr;
	// Area
	switch (requestDT.value[0]) {
		case DRV_PROC_IN: addr.area = PDA_INPUT; break;
		case DRV_PROC_OUT: addr.area = PDA_OUTPUT; break;
		case DRV_PROC_MEM: addr.area = PDA_MEMORY; break;
		default: throw ShmException("Invalid driver area", "ShmServer::CMD_WRITE_DWORD"); break;
	}
	// Byte address
	addr.byteAddr = requestDT.value[1];
	// Bit address
	addr.bitAddr = 0;

	// Pointer to double word in command data
	DWORD *val = (DWORD*)&requestDT.value[2];

	// Write WORD
	pda->writeDWord(addr, *val);

	// Prepare reply command
	replyDT.command = DRV_CMD_OK;
}

void ShmServer::CMD_WRITE_INT() {

	// Check command
	if (requestDT.command != DRV_WRITE_INT)
		throw ShmException("Invalid command", "ShmServer::CMD_WRITE_INT");

	// Check data length
	if (requestDT.len != 3)
		throw ShmException("Invalid command data length", "ShmServer::CMD_WRITE_INT");

	// Prepare address structure
	processDataAddress addr;
	// Area
	switch (requestDT.value[0]) {
		case DRV_PROC_IN: addr.area = PDA_INPUT; break;
		case DRV_PROC_OUT: addr.area = PDA_OUTPUT; break;
		case DRV_PROC_MEM: addr.area = PDA_MEMORY; break;
		default: throw ShmException("Invalid driver area", "ShmServer::CMD_WRITE_INT"); break;
	}
	// Byte address
	addr.byteAddr = requestDT.value[1];
	// Bit address
	addr.bitAddr = 0;

	// Value
	int val = requestDT.value[2];

	// Write WORD
	pda->writeInt(addr, val);

	// Prepare reply command
	replyDT.command = DRV_CMD_OK;
}

void ShmServer::CMD_WRITE_REAL() {

	// Check command
	if (requestDT.command != DRV_WRITE_REAL)
		throw ShmException("Invalid command", "ShmServer::CMD_WRITE_REAL");

	// Check data length
	if (requestDT.len != 3)
		throw ShmException("Invalid command data length", "ShmServer::CMD_WRITE_REAL");

	// Prepare address structure
	processDataAddress addr;
	// Area
	switch (requestDT.value[0]) {
		case DRV_PROC_IN: addr.area = PDA_INPUT; break;
		case DRV_PROC_OUT: addr.area = PDA_OUTPUT; break;
		case DRV_PROC_MEM: addr.area = PDA_MEMORY; break;
		default: throw ShmException("Invalid driver area", "ShmServer::CMD_WRITE_REAL"); break;
	}
	// Byte address
	addr.byteAddr = requestDT.value[1];
	// Bit address
	addr.bitAddr = 0;

	// Pointer to Real in command data
	float *val = (float*)&requestDT.value[2];

	// Write WORD
	pda->writeReal(addr, *val);

	// Prepare reply command
	replyDT.command = DRV_CMD_OK;
}

template PDTag<bool> ShmServer::getTag<bool>(const processDataAddress &tagAddr);
template PDTag<BYTE> ShmServer::getTag<BYTE>(const processDataAddress &tagAddr);
template PDTag<WORD> ShmServer::getTag<WORD>(const processDataAddress &tagAddr);
template PDTag<DWORD> ShmServer::getTag<DWORD>(const processDataAddress &tagAddr);
template PDTag<int> ShmServer::getTag<int>(const processDataAddress &tagAddr);
template PDTag<float> ShmServer::getTag<float>(const processDataAddress &tagAddr);
