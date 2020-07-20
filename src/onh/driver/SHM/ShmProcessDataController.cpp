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

#include "ShmProcessDataController.h"

using namespace onh;

ShmProcessDataController::ShmProcessDataController(const ShmProcessDataController& spdc):
	process(spdc.process), processLock(spdc.processLock)
{
}

ShmProcessDataController::ShmProcessDataController(const MutexAccess &pdLock, processData *procDT):
	process(procDT), processLock(pdLock)
{
}

ShmProcessDataController::~ShmProcessDataController() {
}

processData ShmProcessDataController::getProcessDataCopy() {

	if (!process)
		throw Exception("Process data handle not initialized", "ShmProcessDataController::getProcessDataCopy");

	processData pd;

	// Lock access to the process data
	processLock.lock();

	// Copy data
	pd = *process;

	// Unlock access to the process data
	processLock.unlock();

	return pd;
}
