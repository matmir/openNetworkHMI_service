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
#include "DriverException.h"
#include <sstream>

using namespace onh;

ProcessWriter::ProcessWriter(const ProcessWriter &pw)
{
	// Create new instance of the driver writer
	driverWriter = pw.driverWriter->createNew();
}

ProcessWriter::ProcessWriter(DriverProcessWriter *dpw):
	driverWriter(dpw)
{
}

ProcessWriter::~ProcessWriter()
{
	if (driverWriter)
		delete driverWriter;
}

void ProcessWriter::setBit(const Tag& tg) {

	// Check driver writer
	if (!driverWriter) {
		throw Exception("Missing driver writer instance", "ProcessWriter::setBit");
	}

    // Check Tag type
    if (tg.getType() != TT_BIT) {

    	ProcessUtils::triggerTagTypeError(tg.getName(), "ProcessWriter::setBit");
    }

    processDataAddress addr = tg.getAddress();

    try {

        // Modify bit
    	driverWriter->setBit(addr);

    } catch(DriverException &e) {

        ProcessUtils::triggerError(e.what(), tg.getName(), "ProcessWriter::setBit");
    }
}

void ProcessWriter::resetBit(const Tag& tg) {

	// Check driver writer
	if (!driverWriter) {
		throw Exception("Missing driver writer instance", "ProcessWriter::resetBit");
	}

    // Check Tag type
    if (tg.getType() != TT_BIT) {

    	ProcessUtils::triggerTagTypeError(tg.getName(), "ProcessWriter::resetBit");
    }

    processDataAddress addr = tg.getAddress();

    try {

        // Modify bit
    	driverWriter->resetBit(addr);

    } catch(DriverException &e) {

        ProcessUtils::triggerError(e.what(), tg.getName(), "ProcessWriter::resetBit");
    }

}

void ProcessWriter::invertBit(const Tag& tg) {

	// Check driver writer
	if (!driverWriter) {
		throw Exception("Missing driver writer instance", "ProcessWriter::invertBit");
	}

    // Check Tag type
    if (tg.getType() != TT_BIT) {

    	ProcessUtils::triggerTagTypeError(tg.getName(), "ProcessWriter::invertBit");
    }

    processDataAddress addr = tg.getAddress();

    try {

        // Modify bit
    	driverWriter->invertBit(addr);

    } catch(DriverException &e) {

        ProcessUtils::triggerError(e.what(), tg.getName(), "ProcessWriter::invertBit");
    }
}

void ProcessWriter::setBits(const std::vector<Tag>& tags) {

	// Check driver writer
	if (!driverWriter) {
		throw Exception("Missing driver writer instance", "ProcessWriter::setBits");
	}

    // Check input values
    if (tags.size() == 0)
        throw Exception("Tags array is empty", "ProcessWriter::setBits");

    std::vector<processDataAddress> addr;

    // Prepare Tag addresses
    for (unsigned int i=0; i<tags.size(); ++i) {

        // Check Tag type
        if (tags[i].getType() != TT_BIT) {

        	ProcessUtils::triggerTagTypeError(tags[i].getName(), "ProcessWriter::setBits");
        }

        addr.push_back(tags[i].getAddress());

    }

    try {

        // Set bits
    	driverWriter->setBits(addr);

    } catch(DriverException &e) {

        ProcessUtils::triggerError(e.what(), "", "ProcessWriter::setBits");
    }
}

void ProcessWriter::writeByte(const Tag& tg, BYTE val) {

	// Check driver writer
	if (!driverWriter) {
		throw Exception("Missing driver writer instance", "ProcessWriter::writeByte");
	}

    // Check Tag type
    if (tg.getType() != TT_BYTE) {

    	ProcessUtils::triggerTagTypeError(tg.getName(), "ProcessWriter::writeByte");
    }

    processDataAddress addr = tg.getAddress();

    try {

        // Write byte
    	driverWriter->writeByte(addr, val);

    } catch(DriverException &e) {

        ProcessUtils::triggerError(e.what(), tg.getName(), "ProcessWriter::writeByte");
    }
}

void ProcessWriter::writeWord(const Tag& tg, WORD val) {

	// Check driver writer
	if (!driverWriter) {
		throw Exception("Missing driver writer instance", "ProcessWriter::writeWord");
	}

    // Check Tag type
    if (tg.getType() != TT_WORD) {

    	ProcessUtils::triggerTagTypeError(tg.getName(), "ProcessWriter::writeWord");
    }

    processDataAddress addr = tg.getAddress();

    try {

        // Write word
    	driverWriter->writeWord(addr, val);

    } catch(DriverException &e) {

        ProcessUtils::triggerError(e.what(), tg.getName(), "ProcessWriter::writeWord");
    }
}

void ProcessWriter::writeDWord(const Tag& tg, DWORD val) {

	// Check driver writer
	if (!driverWriter) {
		throw Exception("Missing driver writer instance", "ProcessWriter::writeDWord");
	}

    // Check Tag type
    if (tg.getType() != TT_DWORD) {

    	ProcessUtils::triggerTagTypeError(tg.getName(), "ProcessWriter::writeDWord");
    }

    processDataAddress addr = tg.getAddress();

    try {

        // Write word
    	driverWriter->writeDWord(addr, val);

    } catch(DriverException &e) {

        ProcessUtils::triggerError(e.what(), tg.getName(), "ProcessWriter::writeDWord");
    }
}

void ProcessWriter::writeInt(const Tag& tg, int val) {

	// Check driver writer
	if (!driverWriter) {
		throw Exception("Missing driver writer instance", "ProcessWriter::writeInt");
	}

    // Check Tag type
    if (tg.getType() != TT_INT) {

    	ProcessUtils::triggerTagTypeError(tg.getName(), "ProcessWriter::writeInt");
    }

    processDataAddress addr = tg.getAddress();

    try {

        // Write word
    	driverWriter->writeInt(addr, val);

    } catch(DriverException &e) {

        ProcessUtils::triggerError(e.what(), tg.getName(), "ProcessWriter::writeInt");
    }
}

void ProcessWriter::writeReal(const Tag& tg, float val) {

	// Check driver writer
	if (!driverWriter) {
		throw Exception("Missing driver writer instance", "ProcessWriter::writeReal");
	}

    // Check Tag type
    if (tg.getType() != TT_REAL) {

    	ProcessUtils::triggerTagTypeError(tg.getName(), "ProcessWriter::writeReal");
    }

    processDataAddress addr = tg.getAddress();

    try {

        // Write word
    	driverWriter->writeReal(addr, val);

    } catch(DriverException &e) {

        ProcessUtils::triggerError(e.what(), tg.getName(), "ProcessWriter::writeReal");
    }
}
