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
#include "DriverException.h"
#include <sstream>

using namespace onh;

ProcessReader::ProcessReader(const ProcessReader &pr)
{
	driverReader.clear();

	for (auto& it : pr.driverReader) {
		driverReader.insert(std::pair<unsigned int, DriverProcessReader*>(it.first, it.second->createNew()));
	}
}

ProcessReader::ProcessReader()
{
	driverReader.clear();
}

ProcessReader::~ProcessReader()
{
	for (auto& reader : driverReader) {
		delete reader.second;
	}
}

void ProcessReader::addReader(unsigned int id, DriverProcessReader *dpr) {

	// Check identifier
	if (id == 0) {
		throw Exception("Wrong driver process reader identifier", "ProcessReader::addReader");
	}

	// Check reader
	if (dpr == nullptr) {
		throw Exception("Missing driver process reader instance", "ProcessReader::addReader");
	}

	// Add reader
	driverReader.insert(std::pair<unsigned int, DriverProcessReader*>(id, dpr));
}

bool ProcessReader::getBitValue(const Tag& tg) {

	// Check driver reader
	if (driverReader.size()==0) {
		throw Exception("Driver reader is empty", "ProcessReader::getBitValue");
	}

    // Check Tag type
    if (tg.getType() != TT_BIT) {

        ProcessUtils::triggerTagTypeError(tg.getName(), "ProcessReader::getBitValue");
    }

    bool v = false;

    processDataAddress addr = tg.getAddress();

    try {

        // Read bit
        v = driverReader.at(tg.getConnId())->getBitValue(addr);

    } catch(DriverException &e) {

    	ProcessUtils::triggerError(e.what(), tg.getName(), "ProcessReader::getBitValue");
    } catch(const std::out_of_range &e) {

    	std::stringstream s;
    	s << "Driver process reader with id: " << tg.getConnId() << " does not exist";
    	ProcessUtils::triggerError(s.str(), tg.getName(), "ProcessReader::getBitValue");
    }

    return v;
}

std::vector<bool> ProcessReader::getBitsValue(const std::vector<Tag>& tags) {

	// Check driver reader
	if (driverReader.size()==0) {
		throw Exception("Driver reader is empty", "ProcessReader::getBitsValue");
	}

    // Check input values
    if (tags.size() == 0)
        throw Exception("Tags array is empty", "ProcessReader::getBitsValue");

    std::vector<bool> ret;

	// Get values
	for (const Tag& tag : tags) {

		// Add value
		ret.push_back(getBitValue(tag));
	}

    if (ret.size() == 0)
        throw Exception("Output array is empty", "ProcessReader::getBitsValue");

    return ret;
}

BYTE ProcessReader::getByte(const Tag& tg) {

	// Check driver reader
	if (driverReader.size()==0) {
		throw Exception("Driver reader is empty", "ProcessReader::getByte");
	}

    // Check Tag type
    if (tg.getType() != TT_BYTE) {

    	ProcessUtils::triggerTagTypeError(tg.getName(), "ProcessReader::getByte");
    }

    BYTE b = 0;

    processDataAddress addr = tg.getAddress();

    try {

        // Read byte
        b = driverReader.at(tg.getConnId())->getByte(addr);

    } catch(DriverException &e) {

    	ProcessUtils::triggerError(e.what(), tg.getName(), "ProcessReader::getByte");
    } catch(const std::out_of_range &e) {

    	std::stringstream s;
    	s << "Driver process reader with id: " << tg.getConnId() << " does not exist";
    	ProcessUtils::triggerError(s.str(), tg.getName(), "ProcessReader::getByte");
    }

    return b;
}

WORD ProcessReader::getWord(const Tag& tg) {

	// Check driver reader
	if (driverReader.size()==0) {
		throw Exception("Driver reader is empty", "ProcessReader::getByte");
	}

    // Check Tag type
    if (tg.getType() != TT_WORD) {

    	ProcessUtils::triggerTagTypeError(tg.getName(), "ProcessReader::getWord");
    }

    WORD w = 0;

    processDataAddress addr = tg.getAddress();

    try {

        // Read word
        w = driverReader.at(tg.getConnId())->getWord(addr);

    } catch(DriverException &e) {

    	ProcessUtils::triggerError(e.what(), tg.getName(), "ProcessReader::getWord");
    } catch(const std::out_of_range &e) {

    	std::stringstream s;
    	s << "Driver process reader with id: " << tg.getConnId() << " does not exist";
    	ProcessUtils::triggerError(s.str(), tg.getName(), "ProcessReader::getWord");
    }

    return w;
}

DWORD ProcessReader::getDWord(const Tag& tg) {

	// Check driver reader
	if (driverReader.size()==0) {
		throw Exception("Driver reader is empty", "ProcessReader::getDWord");
	}

    // Check Tag type
    if (tg.getType() != TT_DWORD) {

    	ProcessUtils::triggerTagTypeError(tg.getName(), "ProcessReader::getDWord");
    }

    DWORD dw = 0;

    processDataAddress addr = tg.getAddress();

    try {

        // Read double word
        dw = driverReader.at(tg.getConnId())->getDWord(addr);

    } catch(DriverException &e) {

    	ProcessUtils::triggerError(e.what(), tg.getName(), "ProcessReader::getDWord");
    } catch(const std::out_of_range &e) {

    	std::stringstream s;
    	s << "Driver process reader with id: " << tg.getConnId() << " does not exist";
    	ProcessUtils::triggerError(s.str(), tg.getName(), "ProcessReader::getDWord");
    }

    return dw;
}

int ProcessReader::getInt(const Tag& tg) {

	// Check driver reader
	if (driverReader.size()==0) {
		throw Exception("Driver reader is empty", "ProcessReader::getInt");
	}

    // Check Tag type
    if (tg.getType() != TT_INT) {

    	ProcessUtils::triggerTagTypeError(tg.getName(), "ProcessReader::getInt");
    }

    int v = 0;

    processDataAddress addr = tg.getAddress();

    try {

        // Read int
        v = driverReader.at(tg.getConnId())->getInt(addr);

    } catch(DriverException &e) {

    	ProcessUtils::triggerError(e.what(), tg.getName(), "ProcessReader::getInt");
    } catch(const std::out_of_range &e) {

    	std::stringstream s;
    	s << "Driver process reader with id: " << tg.getConnId() << " does not exist";
    	ProcessUtils::triggerError(s.str(), tg.getName(), "ProcessReader::getInt");
    }

    return v;
}

float ProcessReader::getReal(const Tag& tg) {

	// Check driver reader
	if (driverReader.size()==0) {
		throw Exception("Driver reader is empty", "ProcessReader::getInt");
	}

    // Check Tag type
    if (tg.getType()!= TT_REAL) {

    	ProcessUtils::triggerTagTypeError(tg.getName(), "ProcessReader::getReal");
    }

    float f = 0;

    processDataAddress addr = tg.getAddress();

    try {

        // Read real
        f = driverReader.at(tg.getConnId())->getReal(addr);

    } catch(DriverException &e) {

    	ProcessUtils::triggerError(e.what(), tg.getName(), "ProcessReader::getReal");
    } catch(const std::out_of_range &e) {

    	std::stringstream s;
    	s << "Driver process reader with id: " << tg.getConnId() << " does not exist";
    	ProcessUtils::triggerError(s.str(), tg.getName(), "ProcessReader::getReal");
    }

    return f;
}

void ProcessReader::updateProcessData() {

	for (auto& reader : driverReader) {
		reader.second->updateProcessData();
	}
}
