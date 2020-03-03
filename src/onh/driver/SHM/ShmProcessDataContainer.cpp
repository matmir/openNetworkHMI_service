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

#include "ShmProcessDataContainer.h"

using namespace onh;

ShmProcessDataContainer::ShmProcessDataContainer() {

}

ShmProcessDataContainer::~ShmProcessDataContainer() {
}

ShmProcessDataController ShmProcessDataContainer::getController() {

	return ShmProcessDataController(processLock.getAccess(), &process);
}

void ShmProcessDataContainer::update(const processData& newDT) {

	// Lock access to the process data
	processLock.lock();

	process = newDT;

	// Unlock access to the process data
	processLock.unlock();
}

void ShmProcessDataContainer::clear() {

	// Lock access to the process data
	processLock.lock();

	for (int i=0; i<PROCESS_DT_SIZE; ++i) {
		process.in[i] = 0;
		process.out[i] = 0;
		process.mem[i] = 0;
	}

	// Unlock access to the process data
	processLock.unlock();
}
