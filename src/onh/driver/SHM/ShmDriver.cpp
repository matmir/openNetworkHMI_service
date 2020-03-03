/**
 * This file is part of openNetworkHMI.
 * Copyright (c) 2020 Mateusz Mirosławski.
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

#include "../../utils/Delay.h"
#include "ShmDriver.h"
#include "sCommands.h"
#include <sstream>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <string.h>

using namespace onh;

ShmDriver::ShmDriver(const std::string& segmentName):
	Driver("shm_"), sfd(0), shm(0), shmName(segmentName)
{
	clearProcessData();

	if (shmName == "") {
		triggerError("SHM segment name is empty", "ShmDriver::ShmDriver");
	}

	// Open shared memory segment
	sfd = shm_open(shmName.c_str(), O_RDWR, 0666);

	// Map shared memory segment in the address space of the process
	shm = (sMemory*) mmap(NULL, smSize, PROT_READ | PROT_WRITE, MAP_SHARED, sfd, 0);

	if (shm == MAP_FAILED) {
		triggerError("SHM ("+shmName+") is not initialized", "ShmDriver::ShmDriver");
	}

	getLog().write("SHM ("+shmName+") driver initialized");
}

ShmDriver::~ShmDriver() {

	// Unmap shared memory
	munmap(shm, smSize);

	// Close shared memory object
	close(sfd);

	getLog().write("Shm driver closed");
}

void ShmDriver::triggerError(const std::string& msg, const std::string& fName) {

    std::string s = fName + ": " + msg;
    getLog().write(s);
    throw DriverException(msg, fName);
}

extCMD ShmDriver::putRequest(extCMD cmd) {

	// Check SHM
	if (shm == MAP_FAILED || shm == 0) {
		triggerError("SHM ("+shmName+") is not initialized", "ShmDriver::putRequest");
	}

	extCMD ret;

	struct timespec condWait = {0, 0};

	// Lock request mutex
	if (pthread_mutex_lock(&shm->cs.requestMutex) != 0) {
		triggerError("Can not lock request mutex in SHM", "ShmDriver::putRequest");
	}

	// Check if shm is ready to put data
	if ((shm->cs.requestIn == 0) && (shm->cs.replyIn == 0)) {

		// Copy command data
		shm->cs.data = cmd;

		// Set request flag
		shm->cs.requestIn = 1;

		// Unock request mutex
		if (pthread_mutex_unlock(&shm->cs.requestMutex) != 0) {
			triggerError("Can not unlock request mutex in SHM", "ShmDriver::putRequest");
		}

		// Wait on condition variable
		if (pthread_mutex_lock(&shm->cs.replyMutex) != 0) {
			triggerError("Can not lock reply mutex in SHM", "ShmDriver::putRequest");
		}

		// Wait on condition variable (5s)
		condWait.tv_sec = time(NULL) + 5;
		int timedOut = pthread_cond_timedwait(&shm->cs.replyCondvar, &shm->cs.replyMutex, &condWait);

		if (timedOut) {
			triggerError("Too long reply from controller", "ShmDriver::putRequest");
		}

		if (pthread_mutex_unlock(&shm->cs.replyMutex) != 0) {
			triggerError("Can not unlock reply mutex in SHM", "ShmDriver::putRequest");
		}

		// Lock request mutex
		if (pthread_mutex_lock(&shm->cs.requestMutex) != 0) {
			triggerError("Can not lock request mutex in SHM", "ShmDriver::putRequest");
		}

		if ((shm->cs.requestIn == 0) && (shm->cs.replyIn == 1)) {
			// Read reply command
			ret = shm->cs.data;
			// Clear reply flag
			shm->cs.replyIn = 0;
		} else {
			triggerError("SHM is not ready to read data", "ShmDriver::putRequest");
		}
		// Unock request mutex
		if (pthread_mutex_unlock(&shm->cs.requestMutex) != 0) {
			triggerError("Can not unlock request mutex in SHM", "ShmDriver::putRequest");
		}

	} else {

		triggerError("SHM is not ready to put data", "ShmDriver::putRequest");
	}

	return ret;

}

void ShmDriver::clearProcessData() {

	process.clear();

}

void ShmDriver::updateProcessData() {

	// Check SHM
	if (shm == MAP_FAILED || shm == 0) {
		triggerError("SHM ("+shmName+") is not initialized", "ShmDriver::updateProcessData");
	}

	// Lock process mutex
	if (pthread_mutex_lock(&shm->process.processMutex) != 0) {
		triggerError("Can not lock process mutex in SHM", "ShmDriver::updateProcessData");
	}

	// Copy process data
	process.update(shm->process.procDT);

	// Unlock process mutex
	if (pthread_mutex_unlock(&shm->process.processMutex) != 0) {
		triggerError("Can not unlock process mutex in SHM", "ShmDriver::updateProcessData");
	}
}

void ShmDriver::modifyBit(processDataAddress addr, int drvFunc) {

    // Check bit address
    DriverUtils::DriverUtils::checkBitAddress(addr);

    // Check byte address
    if (addr.byteAddr >= PROCESS_DT_SIZE) {

        triggerError("Byte address is out of range", "ShmDriver::modifyBit");
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
        default: triggerError("Wrong address area", "ShmDriver::modifyBit"); break;
    }

    // Byte address
    cmd.value[1] = addr.byteAddr;
    // Bit address
    cmd.value[2] = addr.bitAddr;

    // Send command
    cmd_reply = putRequest(cmd);

    if (cmd_reply.command != DRV_CMD_OK) {

        triggerError("Controller respond is ERROR", "ShmDriver::modifyBit");
    }

}

void ShmDriver::setBit(processDataAddress addr) {

    modifyBit(addr, DRV_SET_BIT);

}

void ShmDriver::resetBit(processDataAddress addr) {

    modifyBit(addr, DRV_RESET_BIT);

}

void ShmDriver::invertBit(processDataAddress addr) {

    modifyBit(addr, DRV_INVERT_BIT);

}

void ShmDriver::setBits(std::vector<processDataAddress> addr) {

    // Maximum number bits to set (one bit need 3 ints of data)
    unsigned int maxTags = CMD_DATA_SIZE / 3;
    if (addr.size() > maxTags) {

        std::stringstream s;
        s << "Too much bits to set - max numbers bits to set is " << maxTags << " received " << addr.size();

        triggerError(s.str(), "ShmDriver::setBits");
    }

    // Prepare command
    extCMD cmd;
    extCMD cmd_reply;
    cmd.command = DRV_SET_BITS;
    cmd.len = addr.size() * 3;

    // Data offset
    int dto = 0;

    // Prepare command data
    for (unsigned int i=0; i<addr.size(); ++i) {

        // Check bit address
        DriverUtils::checkBitAddress(addr[i]);

        // Check byte address
        if (addr[i].byteAddr >= PROCESS_DT_SIZE) {

            triggerError("Byte address is out of range", "ShmDriver::setBits");
        }

        // Process area
        switch (addr[i].area) {
            case PDA_INPUT: cmd.value[dto+0] = DRV_PROC_IN; break;
            case PDA_OUTPUT: cmd.value[dto+0] = DRV_PROC_OUT; break;
            case PDA_MEMORY: cmd.value[dto+0] = DRV_PROC_MEM; break;
            default: triggerError("Wrong address area", "ShmDriver::setBits"); break;
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

        triggerError("Controller respond is ERROR", "ShmDriver::setBits");
    }

}

void ShmDriver::writeByte(processDataAddress addr, BYTE val) {

    // Check bit address
    DriverUtils::checkBitAddress(addr);

    // Check byte address
    if (addr.byteAddr >= PROCESS_DT_SIZE) {

        triggerError("Byte address is out of range", "ShmDriver::writeByte");
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
        default: triggerError("Wrong address area", "ShmDriver::writeByte"); break;
    }

    // Byte address
    cmd.value[1] = addr.byteAddr;
    // Bit address
    cmd.value[2] = val;

    // Send command
    cmd_reply = putRequest(cmd);

    if (cmd_reply.command != DRV_CMD_OK) {

        triggerError("Controller respond is ERROR", "ShmDriver::writeByte");
    }

}

void ShmDriver::writeWord(processDataAddress addr, WORD val) {

    // Check bit address
    DriverUtils::checkBitAddress(addr);

    // Check byte address
    if (addr.byteAddr >= PROCESS_DT_SIZE-1) {

        triggerError("Byte address is out of range", "ShmDriver::writeWord");
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
        default: triggerError("Wrong address area", "ShmDriver::writeWord"); break;
    }

    // Byte address
    cmd.value[1] = addr.byteAddr;
    // Bit address
    cmd.value[2] = val;

    // Send command
    cmd_reply = putRequest(cmd);

    if (cmd_reply.command != DRV_CMD_OK) {

        triggerError("Controller respond is ERROR", "ShmDriver::writeWord");
    }

}

void ShmDriver::writeDWord(processDataAddress addr, DWORD val) {

    // Check bit address
    DriverUtils::checkBitAddress(addr);

    // Check byte address
    if (addr.byteAddr >= PROCESS_DT_SIZE-3) {

        triggerError("Byte address is out of range", "ShmDriver::writeDWord");
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
        default: triggerError("Wrong address area", "ShmDriver::writeDWord"); break;
    }

    // Byte address
    cmd.value[1] = addr.byteAddr;

    // Double word pointer in command data area
    DWORD* lInt = (DWORD*)&cmd.value[2];
    *lInt = val;

    // Send command
    cmd_reply = putRequest(cmd);

    if (cmd_reply.command != DRV_CMD_OK) {

        triggerError("Controller respond is ERROR", "ShmDriver::writeDWord");
    }

}

void ShmDriver::writeInt(processDataAddress addr, int val) {

    // Check bit address
    DriverUtils::checkBitAddress(addr);

    // Check byte address
    if (addr.byteAddr >= PROCESS_DT_SIZE-3) {

        triggerError("Byte address is out of range", "ShmDriver::writeInt");
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
        default: triggerError("Wrong address area", "ShmDriver::writeInt"); break;
    }

    // Byte address
    cmd.value[1] = addr.byteAddr;
    // Value
    cmd.value[2] = val;

    // Send command
    cmd_reply = putRequest(cmd);

    if (cmd_reply.command != DRV_CMD_OK) {

        triggerError("Controller respond is ERROR", "ShmDriver::writeInt");
    }
}

void ShmDriver::writeReal(processDataAddress addr, float val) {

    // Check bit address
    DriverUtils::checkBitAddress(addr);

    // Check byte address
    if (addr.byteAddr >= PROCESS_DT_SIZE-3) {

        triggerError("Byte address is out of range", "ShmDriver::writeReal");
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
        default: triggerError("Wrong address area", "ShmDriver::writeReal"); break;
    }

    // Byte address
    cmd.value[1] = addr.byteAddr;
    // Float pointer to command data
    float* pReal = (float*)&cmd.value[2];
    memcpy(pReal, &val, sizeof val);

    // Send command
    cmd_reply = putRequest(cmd);

    if (cmd_reply.command != DRV_CMD_OK) {

        triggerError("Controller respond is ERROR", "ShmDriver::writeReal");
    }
}

DriverBuffer* ShmDriver::getBuffer() {

    return 0;
}

DriverProcessReader* ShmDriver::getReader() {

	return new ShmProcessReader(process.getController());
}

void ShmDriver::sendServerExitCommand() {

	// Prepare command
	extCMD cmd;
	extCMD cmd_reply;
	cmd.command = DRV_CMD_EXIT;
	cmd.len = 0;

	// Send command
	cmd_reply = putRequest(cmd);

	if (cmd_reply.command != DRV_CMD_OK) {

		triggerError("Controller respond is ERROR", "ShmDriver::sendServerExitCommand");
	}
}
