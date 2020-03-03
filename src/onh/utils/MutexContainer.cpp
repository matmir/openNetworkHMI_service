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

#include "MutexContainer.h"

using namespace onh;

MutexContainer::MutexContainer() {

	// Initialize mutex
	if (pthread_mutex_init(&itsLock, NULL)) {
		throw Exception("Initialize mutex error", "MutexContainer::init");
	}
}

MutexContainer::~MutexContainer() {

	pthread_mutex_destroy(&itsLock);
}

void MutexContainer::lock() {

    // Lock access to the data
	if (pthread_mutex_lock(&itsLock) !=0) {
		throw Exception("Lock mutex error", "MutexContainer::lock");
	}
}

bool MutexContainer::tryLock() {

    // Try lock access to the data
	return (pthread_mutex_trylock(&itsLock)==0)?(true):(false);
}

void MutexContainer::unlock() {

    // Lock access to the data
	if (pthread_mutex_unlock(&itsLock) !=0) {
		throw Exception("Unlock mutex error", "MutexContainer::unlock");
	}
}

MutexAccess MutexContainer::getAccess() {

    return MutexAccess(&itsLock);
}
