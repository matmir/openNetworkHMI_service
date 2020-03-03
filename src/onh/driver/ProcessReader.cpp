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

#include "ProcessReader.h"
#include <sstream>

using namespace onh;

ProcessReader::ProcessReader():
	ProcessReadWrite(), driverReader(0)
{
}

ProcessReader::ProcessReader(const ProcessReader &pr):
	ProcessReadWrite()
{
	// Create new instance of the driver reader
	driverReader = pr.driverReader->createNew();
}

ProcessReader::ProcessReader(DriverProcessReader *dpr):
	ProcessReadWrite(), driverReader(dpr)
{
}

ProcessReader::~ProcessReader()
{
	if (driverReader)
		delete driverReader;
}

bool ProcessReader::getBitValue(const Tag& tg) {

	// Check driver reader
	if (!driverReader) {
		throw Exception("Missing driver reader instance", "ProcessReader::getBitValue");
	}

    // Check Tag type
    if (tg.getType() != TT_BIT) {

        triggerTagTypeError(tg.getName(), "ProcessReader::getBitValue");
    }

    bool v = false;

    processDataAddress addr = tg.getAddress();

    try {

        // Read bit
        v = driverReader->getBitValue(addr);

    } catch(DriverException &e) {

        triggerError(e.what(), tg.getName(), "ProcessReader::getBitValue");
    }

    return v;
}

std::vector<bool> ProcessReader::getBitsValue(const std::vector<Tag>& tags) {

	// Check driver reader
	if (!driverReader) {
		throw Exception("Missing driver reader instance", "ProcessReader::getBitsValue");
	}

    // Check input values
    if (tags.size() == 0)
        throw Exception("Tags array is empty", "ProcessReader::getBitsValue");

    std::vector<bool> ret;
    std::vector<processDataAddress> addr;

    // Check tags
    for (unsigned int i=0; i<tags.size(); ++i) {

        // Check Tag type
        if (tags[i].getType() != TT_BIT) {

            triggerTagTypeError(tags[i].getName(), "ProcessReader::getBitsValue");
        }

        // Prepare address
        addr.push_back(tags[i].getAddress());
    }

    try {

        // Read bits
        ret = driverReader->getBitsValue(addr);

    } catch(DriverException &e) {

        triggerError(e.what(), "", "ProcessReader::getBitsValue");
    }

    if (ret.size() == 0)
        throw Exception("Output array is empty", "ProcessReader::getBitsValue");

    return ret;
}

BYTE ProcessReader::getByte(const Tag& tg) {

	// Check driver reader
	if (!driverReader) {
		throw Exception("Missing driver reader instance", "ProcessReader::getByte");
	}

    // Check Tag type
    if (tg.getType() != TT_BYTE) {

        triggerTagTypeError(tg.getName(), "ProcessReader::getByte");
    }

    BYTE b = 0;

    processDataAddress addr = tg.getAddress();

    try {

        // Read byte
        b = driverReader->getByte(addr);

    } catch(DriverException &e) {

        triggerError(e.what(), tg.getName(), "ProcessReader::getByte");
    }

    return b;
}

WORD ProcessReader::getWord(const Tag& tg) {

	// Check driver reader
	if (!driverReader) {
		throw Exception("Missing driver reader instance", "ProcessReader::getWord");
	}

    // Check Tag type
    if (tg.getType() != TT_WORD) {

        triggerTagTypeError(tg.getName(), "ProcessReader::getWord");
    }

    WORD w = 0;

    processDataAddress addr = tg.getAddress();

    try {

        // Read word
        w = driverReader->getWord(addr);

    } catch(DriverException &e) {

        triggerError(e.what(), tg.getName(), "ProcessReader::getWord");
    }

    return w;
}

DWORD ProcessReader::getDWord(const Tag& tg) {

	// Check driver reader
	if (!driverReader) {
		throw Exception("Missing driver reader instance", "ProcessReader::getDWord");
	}

    // Check Tag type
    if (tg.getType() != TT_DWORD) {

        triggerTagTypeError(tg.getName(), "ProcessReader::getDWord");
    }

    DWORD dw = 0;

    processDataAddress addr = tg.getAddress();

    try {

        // Read double word
        dw = driverReader->getDWord(addr);

    } catch(DriverException &e) {

        triggerError(e.what(), tg.getName(), "ProcessReader::getDWord");
    }

    return dw;
}

int ProcessReader::getInt(const Tag& tg) {

	// Check driver reader
	if (!driverReader) {
		throw Exception("Missing driver reader instance", "ProcessReader::getInt");
	}

    // Check Tag type
    if (tg.getType() != TT_INT) {

        triggerTagTypeError(tg.getName(), "ProcessReader::getInt");
    }

    int v = 0;

    processDataAddress addr = tg.getAddress();

    try {

        // Read int
        v = driverReader->getInt(addr);

    } catch(DriverException &e) {

        triggerError(e.what(), tg.getName(), "ProcessReader::getInt");
    }

    return v;
}

float ProcessReader::getReal(const Tag& tg) {

	// Check driver reader
	if (!driverReader) {
		throw Exception("Missing driver reader instance", "ProcessReader::getReal");
	}

    // Check Tag type
    if (tg.getType()!= TT_REAL) {

        triggerTagTypeError(tg.getName(), "ProcessReader::getReal");
    }

    float f = 0;

    processDataAddress addr = tg.getAddress();

    try {

        // Read real
        f = driverReader->getReal(addr);

    } catch(DriverException &e) {

        triggerError(e.what(), tg.getName(), "ProcessReader::getReal");
    }

    return f;
}

void ProcessReader::updateProcessData() {

	driverReader->updateProcessData();
}
