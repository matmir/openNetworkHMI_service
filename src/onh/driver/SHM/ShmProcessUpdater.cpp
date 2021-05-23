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

#include "ShmProcessUpdater.h"
#include <pthread.h>
#include <sys/mman.h>
#include <unistd.h>
#include "../DriverException.h"

namespace onh {

ShmProcessUpdater::ShmProcessUpdater(const std::string& segmentName,
										sMemory *smem,
										const GuardDataController<ShmProcessData> &gdc,
										const MutexAccess& lock):
	shmName(segmentName), shm(smem), process(gdc), driverLock(lock) {
}

ShmProcessUpdater::~ShmProcessUpdater() {
}

void ShmProcessUpdater::updateProcessData() {
	driverLock.lock();

	try {
		// Check SHM
		if (shm == MAP_FAILED || shm == 0) {
			throw DriverException("SHM ("+shmName+") is not initialized", "ShmProcessUpdater::updateProcessData");
		}

		// Lock process mutex
		if (pthread_mutex_lock(&shm->process.processMutex) != 0) {
			throw DriverException("Can not lock process mutex in SHM", "ShmProcessUpdater::updateProcessData");
		}

		// Copy process data
		process.setData(ShmProcessData(shm->process.procDT));

		// Unlock process mutex
		if (pthread_mutex_unlock(&shm->process.processMutex) != 0) {
			throw DriverException("Can not unlock process mutex in SHM", "ShmProcessUpdater::updateProcessData");
		}

		driverLock.unlock();
	} catch(...) {
		// Unlock access to the driver
		driverLock.unlock();

		// Re-throw exception
		throw;
	}
}

DriverProcessUpdater* ShmProcessUpdater::createNew() {
	return new ShmProcessUpdater(shmName, shm, process, driverLock);
}

}  // namespace onh
