/**
 * This file is part of openNetworkHMI.
 * Copyright (c) 2021 Mateusz Mirosławski.
 *
 * openNetworkHMI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * openNetworkHMI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with openNetworkHMI.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <pthread.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <sstream>
#include "ShmProcessWriter.h"
#include "../DriverUtils.h"
#include "../DriverException.h"
#include "sCommands.h"

namespace onh {

ShmProcessWriter::ShmProcessWriter(const std::string& segmentName, sMemory *smem, const MutexAccess& lock):
	shmName(segmentName), shm(smem), driverLock(lock) {
}

ShmProcessWriter::~ShmProcessWriter() {
}

extCMD ShmProcessWriter::putRequest(extCMD cmd) {
	// Check SHM
	if (shm == MAP_FAILED || shm == 0) {
		throw DriverException("SHM ("+shmName+") is not initialized", "ShmProcessWriter::putRequest");
	}

	extCMD ret;

	struct timespec condWait = {0, 0};

	// Lock request mutex
	if (pthread_mutex_lock(&shm->cs.requestMutex) != 0) {
		throw DriverException("Can not lock request mutex in SHM", "ShmProcessWriter::putRequest");
	}

	// Check if shm is ready to put data
	if ((shm->cs.requestIn == 0) && (shm->cs.replyIn == 0)) {
		// Copy command data
		shm->cs.data = cmd;

		// Set request flag
		shm->cs.requestIn = 1;

		// Unock request mutex
		if (pthread_mutex_unlock(&shm->cs.requestMutex) != 0) {
			throw DriverException("Can not unlock request mutex in SHM", "ShmProcessWriter::putRequest");
		}

		// Wait on condition variable
		if (pthread_mutex_lock(&shm->cs.replyMutex) != 0) {
			throw DriverException("Can not lock reply mutex in SHM", "ShmProcessWriter::putRequest");
		}

		// Wait on condition variable (5s)
		condWait.tv_sec = time(NULL) + 5;
		int timedOut = pthread_cond_timedwait(&shm->cs.replyCondvar, &shm->cs.replyMutex, &condWait);

		if (timedOut) {
			throw DriverException("Too long reply from controller", "ShmProcessWriter::putRequest");
		}

		if (pthread_mutex_unlock(&shm->cs.replyMutex) != 0) {
			throw DriverException("Can not unlock reply mutex in SHM", "ShmProcessWriter::putRequest");
		}

		// Lock request mutex
		if (pthread_mutex_lock(&shm->cs.requestMutex) != 0) {
			throw DriverException("Can not lock request mutex in SHM", "ShmProcessWriter::putRequest");
		}

		if ((shm->cs.requestIn == 0) && (shm->cs.replyIn == 1)) {
			// Read reply command
			ret = shm->cs.data;
			// Clear reply flag
			shm->cs.replyIn = 0;
		} else {
			throw DriverException("SHM is not ready to read data", "ShmProcessWriter::putRequest");
		}
		// Unock request mutex
		if (pthread_mutex_unlock(&shm->cs.requestMutex) != 0) {
			throw DriverException("Can not unlock request mutex in SHM", "ShmProcessWriter::putRequest");
		}

	} else {
		throw DriverException("SHM is not ready to put data", "ShmProcessWriter::putRequest");
	}

	return ret;
}

void ShmProcessWriter::modifyBit(processDataAddress addr, int drvFunc) {
	// Check bit address
	DriverUtils::DriverUtils::checkBitAddress(addr);

	// Check byte address
	if (addr.byteAddr >= PROCESS_DT_SIZE) {
		throw DriverException("Byte address is out of range", "ShmProcessWriter::modifyBit");
	}

	// Prepare command
	extCMD cmd;
	extCMD cmd_reply;
	cmd.command = drvFunc;
	cmd.len = 3;

	// Process area
	switch (addr.area) {
		case PDA_INPUT: cmd.value[0] = DRV_PROC_IN; break;
		case PDA_OUTPUT: cmd.value[0] = DRV_PROC_OUT; break;
		case PDA_MEMORY: cmd.value[0] = DRV_PROC_MEM; break;
		default: throw DriverException("Wrong address area", "ShmProcessWriter::modifyBit"); break;
	}

	// Byte address
	cmd.value[1] = addr.byteAddr;
	// Bit address
	cmd.value[2] = addr.bitAddr;

	// Send command
	cmd_reply = putRequest(cmd);

	if (cmd_reply.command != DRV_CMD_OK) {
		throw DriverException("Controller respond is ERROR", "ShmProcessWriter::modifyBit");
	}
}

void ShmProcessWriter::setBit(processDataAddress addr) {
	driverLock.lock();

	try {
		modifyBit(addr, DRV_SET_BIT);

		driverLock.unlock();
	} catch(...) {
		// Unlock access to the driver
		driverLock.unlock();

		// Re-throw exception
		throw;
	}
}

void ShmProcessWriter::resetBit(processDataAddress addr) {
	driverLock.lock();

	try {
		modifyBit(addr, DRV_RESET_BIT);

		driverLock.unlock();
	} catch(...) {
		// Unlock access to the driver
		driverLock.unlock();

		// Re-throw exception
		throw;
	}
}

void ShmProcessWriter::invertBit(processDataAddress addr) {
	driverLock.lock();

	try {
		modifyBit(addr, DRV_INVERT_BIT);

		driverLock.unlock();
	} catch(...) {
		// Unlock access to the driver
		driverLock.unlock();

		// Re-throw exception
		throw;
	}
}

void ShmProcessWriter::setBits(std::vector<processDataAddress> addr) {
	driverLock.lock();

	try {
		// Maximum number bits to set (one bit need 3 ints of data)
		unsigned int maxTags = CMD_DATA_SIZE / 3;
		if (addr.size() > maxTags) {
			std::stringstream s;
			s << "Too much bits to set - max numbers bits to set is " << maxTags << " received " << addr.size();

			throw DriverException(s.str(), "ShmProcessWriter::setBits");
		}

		// Prepare command
		extCMD cmd;
		extCMD cmd_reply;
		cmd.command = DRV_SET_BITS;
		cmd.len = addr.size() * 3;

		// Data offset
		int dto = 0;

		// Prepare command data
		for (unsigned int i=0; i < addr.size(); ++i) {
			// Check bit address
			DriverUtils::checkBitAddress(addr[i]);

			// Check byte address
			if (addr[i].byteAddr >= PROCESS_DT_SIZE) {
				throw DriverException("Byte address is out of range", "ShmProcessWriter::setBits");
			}

			// Process area
			switch (addr[i].area) {
				case PDA_INPUT: cmd.value[dto+0] = DRV_PROC_IN; break;
				case PDA_OUTPUT: cmd.value[dto+0] = DRV_PROC_OUT; break;
				case PDA_MEMORY: cmd.value[dto+0] = DRV_PROC_MEM; break;
				default: throw DriverException("Wrong address area", "ShmProcessWriter::setBits"); break;
			}

			// Byte address
			cmd.value[dto+1] = addr[i].byteAddr;
			// Bit address
			cmd.value[dto+2] = addr[i].bitAddr;

			// Set offset (for next tag)
			dto += 3;
		}

		// Send command
		cmd_reply = putRequest(cmd);

		if (cmd_reply.command != DRV_CMD_OK) {
			throw DriverException("Controller respond is ERROR", "ShmProcessWriter::setBits");
		}

		driverLock.unlock();
	} catch(...) {
		// Unlock access to the driver
		driverLock.unlock();

		// Re-throw exception
		throw;
	}
}

void ShmProcessWriter::writeByte(processDataAddress addr, BYTE val) {
	driverLock.lock();

	try {
		// Check bit address
		DriverUtils::checkBitAddress(addr);

		// Check byte address
		if (addr.byteAddr >= PROCESS_DT_SIZE) {
			throw DriverException("Byte address is out of range", "ShmProcessWriter::writeByte");
		}

		// Prepare command
		extCMD cmd;
		extCMD cmd_reply;
		cmd.command = DRV_WRITE_BYTE;
		cmd.len = 3;

		// Process area
		switch (addr.area) {
			case PDA_INPUT: cmd.value[0] = DRV_PROC_IN; break;
			case PDA_OUTPUT: cmd.value[0] = DRV_PROC_OUT; break;
			case PDA_MEMORY: cmd.value[0] = DRV_PROC_MEM; break;
			default: throw DriverException("Wrong address area", "ShmProcessWriter::writeByte"); break;
		}

		// Byte address
		cmd.value[1] = addr.byteAddr;
		// Bit address
		cmd.value[2] = val;

		// Send command
		cmd_reply = putRequest(cmd);

		if (cmd_reply.command != DRV_CMD_OK) {
			throw DriverException("Controller respond is ERROR", "ShmProcessWriter::writeByte");
		}

		driverLock.unlock();
	} catch(...) {
		// Unlock access to the driver
		driverLock.unlock();

		// Re-throw exception
		throw;
	}
}

void ShmProcessWriter::writeWord(processDataAddress addr, WORD val) {
	driverLock.lock();

	try {
		// Check bit address
		DriverUtils::checkBitAddress(addr);

		// Check byte address
		if (addr.byteAddr >= PROCESS_DT_SIZE-1) {
			throw DriverException("Byte address is out of range", "ShmProcessWriter::writeWord");
		}

		// Prepare command
		extCMD cmd;
		extCMD cmd_reply;
		cmd.command = DRV_WRITE_WORD;
		cmd.len = 3;

		// Process area
		switch (addr.area) {
			case PDA_INPUT: cmd.value[0] = DRV_PROC_IN; break;
			case PDA_OUTPUT: cmd.value[0] = DRV_PROC_OUT; break;
			case PDA_MEMORY: cmd.value[0] = DRV_PROC_MEM; break;
			default: throw DriverException("Wrong address area", "ShmProcessWriter::writeWord"); break;
		}

		// Byte address
		cmd.value[1] = addr.byteAddr;
		// Bit address
		cmd.value[2] = val;

		// Send command
		cmd_reply = putRequest(cmd);

		if (cmd_reply.command != DRV_CMD_OK) {
			throw DriverException("Controller respond is ERROR", "ShmProcessWriter::writeWord");
		}

		driverLock.unlock();
	} catch(...) {
		// Unlock access to the driver
		driverLock.unlock();

		// Re-throw exception
		throw;
	}
}

void ShmProcessWriter::writeDWord(processDataAddress addr, DWORD val) {
	driverLock.lock();

	try {
		// Check bit address
		DriverUtils::checkBitAddress(addr);

		// Check byte address
		if (addr.byteAddr >= PROCESS_DT_SIZE-3) {
			throw DriverException("Byte address is out of range", "ShmProcessWriter::writeDWord");
		}

		// Prepare command
		extCMD cmd;
		extCMD cmd_reply;
		cmd.command = DRV_WRITE_DWORD;
		cmd.len = 3;

		// Process area
		switch (addr.area) {
			case PDA_INPUT: cmd.value[0] = DRV_PROC_IN; break;
			case PDA_OUTPUT: cmd.value[0] = DRV_PROC_OUT; break;
			case PDA_MEMORY: cmd.value[0] = DRV_PROC_MEM; break;
			default: throw DriverException("Wrong address area", "ShmProcessWriter::writeDWord"); break;
		}

		// Byte address
		cmd.value[1] = addr.byteAddr;

		// Double word pointer in command data area
		DWORD* lInt = (DWORD*)&cmd.value[2];
		*lInt = val;

		// Send command
		cmd_reply = putRequest(cmd);

		if (cmd_reply.command != DRV_CMD_OK) {
			throw DriverException("Controller respond is ERROR", "ShmProcessWriter::writeDWord");
		}

		driverLock.unlock();
	} catch(...) {
		// Unlock access to the driver
		driverLock.unlock();

		// Re-throw exception
		throw;
	}
}

void ShmProcessWriter::writeInt(processDataAddress addr, int val) {
	driverLock.lock();

	try {
		// Check bit address
		DriverUtils::checkBitAddress(addr);

		// Check byte address
		if (addr.byteAddr >= PROCESS_DT_SIZE-3) {
			throw DriverException("Byte address is out of range", "ShmProcessWriter::writeInt");
		}

		// Prepare command
		extCMD cmd;
		extCMD cmd_reply;
		cmd.command = DRV_WRITE_INT;
		cmd.len = 3;

		// Process area
		switch (addr.area) {
			case PDA_INPUT: cmd.value[0] = DRV_PROC_IN; break;
			case PDA_OUTPUT: cmd.value[0] = DRV_PROC_OUT; break;
			case PDA_MEMORY: cmd.value[0] = DRV_PROC_MEM; break;
			default: throw DriverException("Wrong address area", "ShmProcessWriter::writeInt"); break;
		}

		// Byte address
		cmd.value[1] = addr.byteAddr;
		// Value
		cmd.value[2] = val;

		// Send command
		cmd_reply = putRequest(cmd);

		if (cmd_reply.command != DRV_CMD_OK) {
			throw DriverException("Controller respond is ERROR", "ShmProcessWriter::writeInt");
		}

		driverLock.unlock();
	} catch(...) {
		// Unlock access to the driver
		driverLock.unlock();

		// Re-throw exception
		throw;
	}
}

void ShmProcessWriter::writeReal(processDataAddress addr, float val) {
	driverLock.lock();

	try {
		// Check bit address
		DriverUtils::checkBitAddress(addr);

		// Check byte address
		if (addr.byteAddr >= PROCESS_DT_SIZE-3) {
			throw DriverException("Byte address is out of range", "ShmProcessWriter::writeReal");
		}

		// Prepare command
		extCMD cmd;
		extCMD cmd_reply;
		cmd.command = DRV_WRITE_REAL;
		cmd.len = 3;

		// Process area
		switch (addr.area) {
			case PDA_INPUT: cmd.value[0] = DRV_PROC_IN; break;
			case PDA_OUTPUT: cmd.value[0] = DRV_PROC_OUT; break;
			case PDA_MEMORY: cmd.value[0] = DRV_PROC_MEM; break;
			default: throw DriverException("Wrong address area", "ShmProcessWriter::writeReal"); break;
		}

		// Byte address
		cmd.value[1] = addr.byteAddr;
		// Float pointer to command data
		float* pReal = (float*)&cmd.value[2];
		memcpy(pReal, &val, sizeof val);

		// Send command
		cmd_reply = putRequest(cmd);

		if (cmd_reply.command != DRV_CMD_OK) {
			throw DriverException("Controller respond is ERROR", "ShmProcessWriter::writeReal");
		}

		driverLock.unlock();
	} catch(...) {
		// Unlock access to the driver
		driverLock.unlock();

		// Re-throw exception
		throw;
	}
}

DriverProcessWriterPtr ShmProcessWriter::createNew() {
	return DriverProcessWriterPtr(new ShmProcessWriter(shmName, shm, driverLock));
}

void ShmProcessWriter::sendServerExitCommand() {
	driverLock.lock();

	try {
		// Prepare command
		extCMD cmd;
		extCMD cmd_reply;
		cmd.command = DRV_CMD_EXIT;
		cmd.len = 0;

		// Send command
		cmd_reply = putRequest(cmd);

		if (cmd_reply.command != DRV_CMD_OK) {
			throw DriverException("Controller respond is ERROR", "ShmProcessWriter::sendServerExitCommand");
		}

		driverLock.unlock();
	} catch(...) {
		// Unlock access to the driver
		driverLock.unlock();

		// Re-throw exception
		throw;
	}
}

}  // namespace onh
