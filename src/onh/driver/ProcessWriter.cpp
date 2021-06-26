/**
 * This file is part of openNetworkHMI.
 * Copyright (c) 2021 Mateusz Mirosławski.
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
#include "ProcessDataTypes.h"
#include <sstream>

namespace onh {

ProcessWriter::ProcessWriter(const ProcessWriter &pw) {
	driverWriter.clear();

	for (auto& it : pw.driverWriter) {
		driverWriter.insert(std::pair<unsigned int, DriverProcessWriterPtr>(it.first, it.second->createNew()));
	}
}

ProcessWriter::ProcessWriter() {
	driverWriter.clear();
}

ProcessWriter::~ProcessWriter() {
}

void ProcessWriter::addWriter(unsigned int id, DriverProcessWriterPtr dpw) {
	// Check identifier
	if (id == 0) {
		throw Exception("Wrong driver process writer identifier",
						"ProcessWriter::addWriter");
	}

	// Check reader
	if (dpw == nullptr) {
		throw Exception("Missing driver process reader instance",
						"ProcessWriter::addWriter");
	}

	// Add reader
	driverWriter.insert(std::pair<unsigned int, DriverProcessWriterPtr>(id, std::move(dpw)));
}

void ProcessWriter::setBit(const Tag& tg) {
	// Check driver writer
	if (driverWriter.size() == 0) {
		throw Exception("Driver writer is empty", "ProcessWriter::setBit");
	}

	// Check Tag type
	if (tg.getType() != TT_BIT) {
		ProcessUtils::triggerTagTypeError(tg.getName(), "ProcessWriter::setBit");
	}

	processDataAddress addr = tg.getAddress();

	try {
		// Modify bit
		driverWriter.at(tg.getConnId())->setBit(addr);
	} catch(DriverException &e) {
		ProcessUtils::triggerError(e.what(), tg.getName(), "ProcessWriter::setBit");
	} catch(const std::out_of_range &e) {
		std::stringstream s;
		s << "Driver process writer with id: " << tg.getConnId() << " does not exist";
		ProcessUtils::triggerError(s.str(), tg.getName(), "ProcessWriter::setBit");
	}
}

void ProcessWriter::resetBit(const Tag& tg) {
	// Check driver writer
	if (driverWriter.size() == 0) {
		throw Exception("Driver writer is empty", "ProcessWriter::resetBit");
	}

	// Check Tag type
	if (tg.getType() != TT_BIT) {
		ProcessUtils::triggerTagTypeError(tg.getName(), "ProcessWriter::resetBit");
	}

	processDataAddress addr = tg.getAddress();

	try {
		// Modify bit
		driverWriter.at(tg.getConnId())->resetBit(addr);
	} catch(DriverException &e) {
		ProcessUtils::triggerError(e.what(), tg.getName(), "ProcessWriter::resetBit");
	} catch(const std::out_of_range &e) {
		std::stringstream s;
		s << "Driver process writer with id: " << tg.getConnId() << " does not exist";
		ProcessUtils::triggerError(s.str(), tg.getName(), "ProcessWriter::resetBit");
	}
}

void ProcessWriter::invertBit(const Tag& tg) {
	// Check driver writer
	if (driverWriter.size() == 0) {
		throw Exception("Driver writer is empty", "ProcessWriter::invertBit");
	}

	// Check Tag type
	if (tg.getType() != TT_BIT) {
		ProcessUtils::triggerTagTypeError(tg.getName(), "ProcessWriter::invertBit");
	}

	processDataAddress addr = tg.getAddress();

	try {
		// Modify bit
		driverWriter.at(tg.getConnId())->invertBit(addr);
	} catch(DriverException &e) {
		ProcessUtils::triggerError(e.what(),
									tg.getName(),
									"ProcessWriter::invertBit");
	} catch(const std::out_of_range &e) {
		std::stringstream s;
		s << "Driver process writer with id: " << tg.getConnId() << " does not exist";
		ProcessUtils::triggerError(s.str(), tg.getName(), "ProcessWriter::invertBit");
	}
}

void ProcessWriter::setBits(const std::vector<Tag>& tags) {
	// Check driver writer
	if (driverWriter.size() == 0) {
		throw Exception("Driver writer is empty", "ProcessWriter::setBits");
	}

	// Check input values
	if (tags.size() == 0)
		throw Exception("Tags array is empty", "ProcessWriter::setBits");

	std::vector<processDataAddress> vAddr;
	std::multimap<unsigned int, processDataAddress> addrs;

	// Prepare Tag addresses
	for (const Tag& tag : tags) {
		// Check Tag type
		if (tag.getType() != TT_BIT) {
			ProcessUtils::triggerTagTypeError(tag.getName(), "ProcessWriter::setBits");
		}

		addrs.insert(std::pair<unsigned int, processDataAddress>(tag.getConnId(),
																tag.getAddress()));
	}

	try {
		vAddr.clear();
		unsigned int oldId = 0;
		for (auto& it : addrs) {
			// First iteration
			if (oldId == 0) {
				vAddr.push_back(it.second);
			} else {
				// Change driver id
				if (it.first != oldId) {
					// Set bits
					driverWriter.at(oldId)->setBits(vAddr);
					vAddr.clear();
					// Add new address to the vector
					vAddr.push_back(it.second);
				} else {  // Driver id is the same as old
					// Put address to the vector
					vAddr.push_back(it.second);
				}
			}

			oldId = it.first;
		}

		if (vAddr.size() != 0) {
			driverWriter.at(oldId)->setBits(vAddr);
		}
	} catch(DriverException &e) {
		ProcessUtils::triggerError(e.what(), "", "ProcessWriter::setBits");
	}
}

void ProcessWriter::writeByte(const Tag& tg, BYTE val) {
	// Check driver writer
	if (driverWriter.size() == 0) {
		throw Exception("Driver writer is empty", "ProcessWriter::writeByte");
	}

	// Check Tag type
	if (tg.getType() != TT_BYTE) {
		ProcessUtils::triggerTagTypeError(tg.getName(), "ProcessWriter::writeByte");
	}

	processDataAddress addr = tg.getAddress();

	try {
		// Write byte
		driverWriter.at(tg.getConnId())->writeByte(addr, val);
	} catch(DriverException &e) {
		ProcessUtils::triggerError(e.what(),
									tg.getName(),
									"ProcessWriter::writeByte");
	} catch(const std::out_of_range &e) {
		std::stringstream s;
		s << "Driver process writer with id: " << tg.getConnId() << " does not exist";
		ProcessUtils::triggerError(s.str(), tg.getName(), "ProcessWriter::writeByte");
	}
}

void ProcessWriter::writeWord(const Tag& tg, WORD val) {
	// Check driver writer
	if (driverWriter.size() == 0) {
		throw Exception("Driver writer is empty", "ProcessWriter::writeWord");
	}

	// Check Tag type
	if (tg.getType() != TT_WORD) {
		ProcessUtils::triggerTagTypeError(tg.getName(), "ProcessWriter::writeWord");
	}

	processDataAddress addr = tg.getAddress();

	try {
		// Write word
		driverWriter.at(tg.getConnId())->writeWord(addr, val);
	} catch(DriverException &e) {
		ProcessUtils::triggerError(e.what(),
									tg.getName(),
									"ProcessWriter::writeWord");
	} catch(const std::out_of_range &e) {
		std::stringstream s;
		s << "Driver process writer with id: " << tg.getConnId() << " does not exist";
		ProcessUtils::triggerError(s.str(), tg.getName(), "ProcessWriter::writeWord");
	}
}

void ProcessWriter::writeDWord(const Tag& tg, DWORD val) {
	// Check driver writer
	if (driverWriter.size() == 0) {
		throw Exception("Driver writer is empty", "ProcessWriter::writeDWord");
	}

	// Check Tag type
	if (tg.getType() != TT_DWORD) {
		ProcessUtils::triggerTagTypeError(tg.getName(), "ProcessWriter::writeDWord");
	}

	processDataAddress addr = tg.getAddress();

	try {
		// Write word
		driverWriter.at(tg.getConnId())->writeDWord(addr, val);
	} catch(DriverException &e) {
		ProcessUtils::triggerError(e.what(),
									tg.getName(),
									"ProcessWriter::writeDWord");
	} catch(const std::out_of_range &e) {
		std::stringstream s;
		s << "Driver process writer with id: " << tg.getConnId() << " does not exist";
		ProcessUtils::triggerError(s.str(),
									tg.getName(),
									"ProcessWriter::writeDWord");
	}
}

void ProcessWriter::writeInt(const Tag& tg, int val) {
	// Check driver writer
	if (driverWriter.size() == 0) {
		throw Exception("Driver writer is empty", "ProcessWriter::writeInt");
	}

	// Check Tag type
	if (tg.getType() != TT_INT) {
		ProcessUtils::triggerTagTypeError(tg.getName(), "ProcessWriter::writeInt");
	}

	processDataAddress addr = tg.getAddress();

	try {
		// Write word
		driverWriter.at(tg.getConnId())->writeInt(addr, val);
	} catch(DriverException &e) {
		ProcessUtils::triggerError(e.what(), tg.getName(), "ProcessWriter::writeInt");
	} catch(const std::out_of_range &e) {
		std::stringstream s;
		s << "Driver process writer with id: " << tg.getConnId() << " does not exist";
		ProcessUtils::triggerError(s.str(), tg.getName(), "ProcessWriter::writeInt");
	}
}

void ProcessWriter::writeReal(const Tag& tg, float val) {
	// Check driver writer
	if (driverWriter.size() == 0) {
		throw Exception("Driver writer is empty", "ProcessWriter::writeReal");
	}

	// Check Tag type
	if (tg.getType() != TT_REAL) {
		ProcessUtils::triggerTagTypeError(tg.getName(), "ProcessWriter::writeReal");
	}

	processDataAddress addr = tg.getAddress();

	try {
		// Write word
		driverWriter.at(tg.getConnId())->writeReal(addr, val);
	} catch(DriverException &e) {
		ProcessUtils::triggerError(e.what(),
									tg.getName(),
									"ProcessWriter::writeReal");
	} catch(const std::out_of_range &e) {
		std::stringstream s;
		s << "Driver process writer with id: " << tg.getConnId() << " does not exist";
		ProcessUtils::triggerError(s.str(), tg.getName(), "ProcessWriter::writeReal");
	}
}

}  // namespace onh
