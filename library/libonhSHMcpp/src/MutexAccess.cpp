/**
 * Copyright (c) 2020 Mateusz Mirosławski
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of mosquitto nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "onhSHMcpp/MutexAccess.h"

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
        throw ShmException("Lock mechanism not initialized", "MutexAccess::lock");
    }

    // Lock access to the data
	if (pthread_mutex_lock(itsLock) != 0) {
		throw ShmException("Lock mutex error", "MutexAccess::lock");
	}
}

bool MutexAccess::tryLock() {

    if (!itsLock) {
        throw ShmException("Lock mechanism not initialized", "MutexAccess::tryLock");
    }

    // Try lock access to the data
	return (pthread_mutex_trylock(itsLock)==0)?(true):(false);
}

void MutexAccess::unlock() {

    if (!itsLock) {
        throw ShmException("Lock mechanism not initialized", "MutexAccess::unlock");
    }

    // Lock access to the data
	if (pthread_mutex_unlock(itsLock) != 0) {
		throw ShmException("Unlock mutex error", "MutexAccess::unlock");
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
