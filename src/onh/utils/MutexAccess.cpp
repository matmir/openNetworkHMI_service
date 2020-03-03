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

#include "MutexAccess.h"

using namespace onh;

MutexAccess::MutexAccess():
    itsLock(0)
{
}

MutexAccess::MutexAccess(const MutexAccess& ma):
    itsLock(ma.itsLock)
{
}

MutexAccess::MutexAccess(pthread_mutex_t* mcLock):
    itsLock(mcLock)
{
}

MutexAccess::~MutexAccess()
{
}

void MutexAccess::lock() {

    if (!itsLock) {
        throw Exception("Lock mechanism not initialized", "MutexAccess::lock");
    }

    // Lock access to the data
	if (pthread_mutex_lock(itsLock) !=0) {
		throw Exception("Lock mutex error", "MutexAccess::lock");
	}
}

bool MutexAccess::tryLock() {

    if (!itsLock) {
        throw Exception("Lock mechanism not initialized", "MutexAccess::tryLock");
    }

    // Try lock access to the data
	return (pthread_mutex_trylock(itsLock)==0)?(true):(false);
}

void MutexAccess::unlock() {

    if (!itsLock) {
        throw Exception("Lock mechanism not initialized", "MutexAccess::unlock");
    }

    // Lock access to the data
	if (pthread_mutex_unlock(itsLock) !=0) {
		throw Exception("Unlock mutex error", "MutexAccess::unlock");
	}
}

MutexAccess& MutexAccess::operator=(const MutexAccess& ma) {

    // Check self assignment
    if(&ma == this)
        return *this;

    // Copy pointers
    itsLock = ma.itsLock;

    return *this;
}
