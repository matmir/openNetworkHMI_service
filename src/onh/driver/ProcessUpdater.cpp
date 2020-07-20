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

#include "ProcessUpdater.h"

using namespace onh;

ProcessUpdater::ProcessUpdater(const ProcessUpdater &pu):
	driver(pu.driver), driverLock(pu.driverLock)
{
}

ProcessUpdater::ProcessUpdater(Driver* drv, const MutexAccess& lock):
	driver(drv), driverLock(lock)
{
}

ProcessUpdater::~ProcessUpdater()
{
}

void ProcessUpdater::update() {

    try {
        // Lock access to the driver
    	driverLock.lock();

        // Update process data in driver
    	driver->updateProcessData();

        // Unlock access to the driver
        driverLock.unlock();
    } catch(...) {
        // Unlock access to the driver
    	driverLock.unlock();

        // Re-throw exception
        throw;
    }
}
