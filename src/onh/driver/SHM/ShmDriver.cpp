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

#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <string.h>
#include <sstream>
#include "../../utils/Delay.h"
#include "ShmDriver.h"
#include "sCommands.h"
#include "ShmProcessReader.h"
#include "ShmProcessWriter.h"
#include "ShmProcessUpdater.h"

namespace onh {

ShmDriver::ShmDriver(const std::string& segmentName, unsigned int connId):
	Driver("shm_"+std::to_string(connId)+"_"), sfd(0), shm(0), shmName(segmentName) {
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

	getLog() << LOG_INFO("SHM ("+shmName+") driver initialized");
}

ShmDriver::~ShmDriver() {
	// Unmap shared memory
	munmap(shm, smSize);

	// Close shared memory object
	close(sfd);

	getLog() << LOG_INFO("Shm driver closed");
}

void ShmDriver::triggerError(const std::string& msg, const std::string& fName) {
	getLog() << LOG_ERROR(fName << ": " << msg);
	throw DriverException(msg, fName);
}

DriverBufferPtr ShmDriver::getBuffer() {
	return nullptr;
}

DriverProcessReaderPtr ShmDriver::getReader() {
	return DriverProcessReaderPtr(new ShmProcessReader(process.getController()));
}

DriverProcessWriterPtr ShmDriver::getWriter() {
	return DriverProcessWriterPtr(new ShmProcessWriter(shmName, shm, driverLock.getAccess()));
}

DriverProcessUpdaterPtr ShmDriver::getUpdater() {
	return DriverProcessUpdaterPtr(new ShmProcessUpdater(shmName, shm, process.getController(false), driverLock.getAccess()));
}

}  // namespace onh
