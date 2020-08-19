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
#include "ShmProcessReader.h"
#include "ShmProcessWriter.h"
#include "ShmProcessUpdater.h"
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

DriverBuffer* ShmDriver::getBuffer() {

    return nullptr;
}

DriverProcessReader* ShmDriver::getReader() {

	return new ShmProcessReader(process.getController());
}

DriverProcessWriter* ShmDriver::getWriter() {

	return new ShmProcessWriter(shmName, shm, driverLock.getAccess());
}

DriverProcessUpdater* ShmDriver::getUpdater() {

	return new ShmProcessUpdater(shmName, shm, process.getController(false), driverLock.getAccess());
}
