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

#include "ProcessWriter.h"
#include <sstream>

using namespace onh;

ProcessWriter::ProcessWriter():
    ProcessReadWrite(), driver(0), driverLock()
{
}

ProcessWriter::ProcessWriter(const ProcessWriter &pw):
    ProcessReadWrite(), driver(pw.driver), driverLock(pw.driverLock)
{
}

ProcessWriter::ProcessWriter(Driver* drv, const MutexAccess& lock):
    ProcessReadWrite(), driver(drv), driverLock(lock)
{
}

ProcessWriter::~ProcessWriter()
{
}

void ProcessWriter::setBit(const Tag& tg) {

	// Check driver
	if (!driver) {
		throw Exception("Missing driver instance", "ProcessWriter::setBit");
	}

    // Check Tag type
    if (tg.getType() != TT_BIT) {

        triggerTagTypeError(tg.getName(), "ProcessWriter::setBit");
    }

    processDataAddress addr = tg.getAddress();

    // Lock access to the driver
    driverLock.lock();

    try {

        // Modify bit
        driver->setBit(addr);

    } catch(DriverException &e) {
        driverLock.unlock();

        triggerError(e.what(), tg.getName(), "ProcessWriter::setBit");
    }

    // Unlock access to the driver
    driverLock.unlock();
}

void ProcessWriter::resetBit(const Tag& tg) {

	// Check driver
	if (!driver) {
		throw Exception("Missing driver instance", "ProcessWriter::resetBit");
	}

    // Check Tag type
    if (tg.getType() != TT_BIT) {

        triggerTagTypeError(tg.getName(), "ProcessWriter::resetBit");
    }

    processDataAddress addr = tg.getAddress();

    // Lock access to the driver
    driverLock.lock();

    try {

        // Modify bit
        driver->resetBit(addr);

    } catch(DriverException &e) {
        driverLock.unlock();

        triggerError(e.what(), tg.getName(), "ProcessWriter::resetBit");
    }

    // Unlock access to the driver
    driverLock.unlock();

}

void ProcessWriter::invertBit(const Tag& tg) {

	// Check driver
	if (!driver) {
		throw Exception("Missing driver instance", "ProcessWriter::invertBit");
	}

    // Check Tag type
    if (tg.getType() != TT_BIT) {

        triggerTagTypeError(tg.getName(), "ProcessWriter::invertBit");
    }

    processDataAddress addr = tg.getAddress();

    // Lock access to the driver
    driverLock.lock();

    try {

        // Modify bit
        driver->invertBit(addr);

    } catch(DriverException &e) {
        driverLock.unlock();

        triggerError(e.what(), tg.getName(), "ProcessWriter::invertBit");
    }

    // Unlock access to the driver
    driverLock.unlock();
}

void ProcessWriter::setBits(const std::vector<Tag>& tags) {

	// Check driver
	if (!driver) {
		throw Exception("Missing driver instance", "ProcessWriter::setBits");
	}

    // Check input values
    if (tags.size() == 0)
        throw Exception("Tags array is empty", "ProcessWriter::setBits");

    std::vector<processDataAddress> addr;

    // Prepare Tag addresses
    for (unsigned int i=0; i<tags.size(); ++i) {

        // Check Tag type
        if (tags[i].getType() != TT_BIT) {

            triggerTagTypeError(tags[i].getName(), "ProcessWriter::setBits");
        }

        addr.push_back(tags[i].getAddress());

    }

    // Lock access to the driver
    driverLock.lock();

    try {

        // Set bits
        driver->setBits(addr);

    } catch(DriverException &e) {
        driverLock.unlock();

        triggerError(e.what(), "", "ProcessWriter::setBits");
    }

    // Unlock access to the driver
    driverLock.unlock();
}

void ProcessWriter::writeByte(const Tag& tg, BYTE val) {

	// Check driver
	if (!driver) {
		throw Exception("Missing driver instance", "ProcessWriter::writeByte");
	}

    // Check Tag type
    if (tg.getType() != TT_BYTE) {

        triggerTagTypeError(tg.getName(), "ProcessWriter::writeByte");
    }

    processDataAddress addr = tg.getAddress();

    // Lock access to the driver
    driverLock.lock();

    try {

        // Write byte
        driver->writeByte(addr, val);

    } catch(DriverException &e) {
        driverLock.unlock();

        triggerError(e.what(), tg.getName(), "ProcessWriter::writeByte");
    }

    // Unlock access to the driver
    driverLock.unlock();
}

void ProcessWriter::writeWord(const Tag& tg, WORD val) {

	// Check driver
	if (!driver) {
		throw Exception("Missing driver instance", "ProcessWriter::writeWord");
	}

    // Check Tag type
    if (tg.getType() != TT_WORD) {

        triggerTagTypeError(tg.getName(), "ProcessWriter::writeWord");
    }

    processDataAddress addr = tg.getAddress();

    // Lock access to the driver
    driverLock.lock();

    try {

        // Write word
        driver->writeWord(addr, val);

    } catch(DriverException &e) {
        driverLock.unlock();

        triggerError(e.what(), tg.getName(), "ProcessWriter::writeWord");
    }

    // Unlock access to the driver
    driverLock.unlock();
}

void ProcessWriter::writeDWord(const Tag& tg, DWORD val) {

	// Check driver
	if (!driver) {
		throw Exception("Missing driver instance", "ProcessWriter::writeDWord");
	}

    // Check Tag type
    if (tg.getType() != TT_DWORD) {

        triggerTagTypeError(tg.getName(), "ProcessWriter::writeDWord");
    }

    processDataAddress addr = tg.getAddress();

    // Lock access to the driver
    driverLock.lock();

    try {

        // Write word
        driver->writeDWord(addr, val);

    } catch(DriverException &e) {
        driverLock.unlock();

        triggerError(e.what(), tg.getName(), "ProcessWriter::writeDWord");
    }

    // Unlock access to the driver
    driverLock.unlock();
}

void ProcessWriter::writeInt(const Tag& tg, int val) {

	// Check driver
	if (!driver) {
		throw Exception("Missing driver instance", "ProcessWriter::writeInt");
	}

    // Check Tag type
    if (tg.getType() != TT_INT) {

        triggerTagTypeError(tg.getName(), "ProcessWriter::writeInt");
    }

    processDataAddress addr = tg.getAddress();

    // Lock access to the driver
    driverLock.lock();

    try {

        // Write word
        driver->writeInt(addr, val);

    } catch(DriverException &e) {
        driverLock.unlock();

        triggerError(e.what(), tg.getName(), "ProcessWriter::writeInt");
    }

    // Unlock access to the driver
    driverLock.unlock();
}

void ProcessWriter::writeReal(const Tag& tg, float val) {

	// Check driver
	if (!driver) {
		throw Exception("Missing driver instance", "ProcessWriter::writeReal");
	}

    // Check Tag type
    if (tg.getType() != TT_REAL) {

        triggerTagTypeError(tg.getName(), "ProcessWriter::writeReal");
    }

    processDataAddress addr = tg.getAddress();

    // Lock access to the driver
    driverLock.lock();

    try {

        // Write word
        driver->writeReal(addr, val);

    } catch(DriverException &e) {
        driverLock.unlock();

        triggerError(e.what(), tg.getName(), "ProcessWriter::writeReal");
    }

    // Unlock access to the driver
    driverLock.unlock();
}
