/**
 * This file is part of openNetworkHMI.
 * Copyright (c) 2025 Mateusz Mirosławski.
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
#include <chrono>
#include <thread>
#include "../../utils/Delay.h"
#include "ShmDriver.h"
#include "sCommands.h"
#include "ShmProcessReader.h"
#include "ShmProcessWriter.h"
#include "ShmProcessUpdater.h"

namespace {
	constexpr int SHM_ERROR = -1;

	// Reconnect wait time (seconds)
	constexpr int SHM_RECONNECT_TIME = 10;
}

namespace onh {

ShmDriver::ShmDriver(const std::string& segmentName, unsigned int connId):
	Driver("shm_"+std::to_string(connId)+"_"), sfd(SHM_ERROR), shm(0), shmName(segmentName) {
	if (shmName == "") {
		triggerError("SHM segment name is empty", "ShmDriver::ShmDriver");
	}
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

void ShmDriver::connect()
{
	bool connected = false;

	while (!connected)
	{
		// Open shared memory segment
		sfd = shm_open(shmName.c_str(), O_RDWR, 0666);
		if (sfd < 0)
		{
			getLog() << LOG_ERROR("SHM ("+shmName+") driver not opened - reconnecting");
			std::this_thread::sleep_for(std::chrono::seconds(SHM_RECONNECT_TIME));
			continue;
		}

		// Map shared memory segment in the address space of the process
		shm = (sMemory*) mmap(NULL, smSize, PROT_READ | PROT_WRITE, MAP_SHARED, sfd, 0);
		if (shm == MAP_FAILED) {
			getLog() << LOG_ERROR("SHM ("+shmName+") driver not mapped - reconnecting");
			std::this_thread::sleep_for(std::chrono::seconds(SHM_RECONNECT_TIME));
			continue;
		}

		connected = true;
	}

	getLog() << LOG_INFO("SHM ("+shmName+") driver initialized");
}

DriverBufferPtr ShmDriver::getBuffer()
{
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
