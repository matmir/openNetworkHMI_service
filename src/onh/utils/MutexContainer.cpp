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
#include <system_error>
#include <sstream>

using namespace onh;

MutexContainer::MutexContainer() {

}

MutexContainer::~MutexContainer() {

}

void MutexContainer::lock() {

    // Lock access to the data
    try {

    	itsLock.lock();

    } catch (const std::system_error& e) {
    	std::stringstream s;
    	s << "Lock mutex error code: " << e.code() << ", msg: " << e.what();

    	throw Exception(s.str(), "MutexContainer::lock");
    }
}

bool MutexContainer::tryLock() {

    // Try lock access to the data
	return itsLock.try_lock();
}

void MutexContainer::unlock() {

    // Unlock access to the data
	itsLock.unlock();
}

MutexAccess MutexContainer::getAccess() {

    return MutexAccess(&itsLock);
}
