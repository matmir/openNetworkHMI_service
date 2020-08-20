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

#include "TagLoggerWriterProg.h"

using namespace onh;

TagLoggerWriterProg::TagLoggerWriterProg(const TagLoggerDB& tldb,
											const TagLoggerBufferController& tlbc,
											unsigned int updateInterval,
											const GuardDataController<ThreadExitData> &gdcTED,
											const GuardDataController<CycleTimeData> &gdcCTD):
	ThreadProgram(gdcTED, gdcCTD, "taglogger", "tagLogWriter_")
{
	// Create delay
	itsDelay = new Delay(updateInterval);

	// Create DB access
	db = new TagLoggerDB(tldb);

	// Create tag logger buffer controller
	tagLoggerBuffer = new TagLoggerBufferController(tlbc);
}

TagLoggerWriterProg::~TagLoggerWriterProg() {

	if (db)
		delete db;

	if (tagLoggerBuffer)
		delete tagLoggerBuffer;

	getLogger().write("Tag logger writer close");

	if (itsDelay)
		delete itsDelay;
}

void TagLoggerWriterProg::operator()() {

    try {

    	getLogger().write("Start main loop");

    	if (!db)
			throw Exception("No db object");

		if (!tagLoggerBuffer)
			throw Exception("No buffer object");

		// Run until tag logger thread is working or buffer has data
        while(!exitWriterProg()) {

            // Start thread cycle time measure
            startCycleMeasure();

            // Write data to DB
            writeDataToDB();

            // Wait
            itsDelay->wait();

            // Stop thread cycle time measure
            stopCycleMeasure();
        }

    } catch (Exception &e) {

    	getLogger().write(e.what());

        // Exit application
    	exit("Tag logger writer");
    }
}

bool TagLoggerWriterProg::exitWriterProg() {

	bool ret = false;

	// Check exit thread flag
	if (isExitFlag()) {

		// Check tag logger finish flag and data count
		if (tagLoggerBuffer->isFinished() && tagLoggerBuffer->isEmpty()) {

			ret = true;
		}
	}

	return ret;
}

void TagLoggerWriterProg::writeDataToDB() {

	// Vector with loggers to save in DB
	std::vector<TagLoggerItem> tagLogger;

	// Read data from buffer
	tagLoggerBuffer->getData(tagLogger);

	for (unsigned int i=0; i<tagLogger.size(); ++i) {

		// Write to DB
		db->logTag(tagLogger[i]);
	}
}
