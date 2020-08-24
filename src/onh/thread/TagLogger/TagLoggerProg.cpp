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

#include "TagLoggerProg.h"

#include <stdlib.h>
#include <sstream>
#include "../../utils/Exception.h"
#include "../../utils/DateUtils.h"
#include "../../db/TagLoggerDB.h"

using namespace onh;

TagLoggerProg::TagLoggerProg(const ProcessReader& pr,
								const TagLoggerDB& tldb,
								const TagLoggerBufferController& tlbc,
								unsigned int updateInterval,
								const GuardDataController<ThreadExitData> &gdcTED,
								const GuardDataController<CycleTimeData> &gdcCTD):
    ThreadProgram(gdcTED, gdcCTD, updateInterval, "taglogger", "tagLog_")
{
    // Process reader
    prReader = new ProcessReader(pr);

    // Create DB access
    db = new TagLoggerDB(tldb);

    // Create tag logger buffer controller
    tagLoggerBuffer = new TagLoggerBufferController(tlbc);
}

TagLoggerProg::~TagLoggerProg()
{
    if (prReader)
        delete prReader;

    if (db)
        delete db;

    if (tagLoggerBuffer)
    	delete tagLoggerBuffer;

    getLogger().write("Tag logger close");
}

void TagLoggerProg::operator()() {

    try {

    	getLogger().write("Start main loop");

        if (!prReader)
            throw Exception("No reader object");

        if (!db)
			throw Exception("No db object");

        if (!tagLoggerBuffer)
			throw Exception("No buffer object");

        while(!isExitFlag()) {

        	// Start delay
        	threadWaitStart();

            // Start thread cycle time measure
            startCycleMeasure();

            // Update process reader
			prReader->updateProcessData();

            // Tag update in DB
            updateTags();

            // Wait
            threadWaitAfterStart();

            // Stop thread cycle time measure
            stopCycleMeasure();
        }

        // Inform writing thread that we are finished putting data to the buffer
        tagLoggerBuffer->setFinished();

    } catch (Exception &e) {

    	getLogger().write(e.what());

        // Exit application
    	exit("Tag logger");

    	tagLoggerBuffer->setFinished();
    }
}

void TagLoggerProg::updateTags() {

    // Get enabled loggers
    std::vector<TagLoggerItem> vTagLogger = db->getLoggers();

    // Vector with loggers to save in DB
    std::vector<TagLoggerItem> tagLoggerToSave;

    std::stringstream s;

    // Check loggers
    for (unsigned int i=0; i<vTagLogger.size(); ++i) {

    	// Set last values
    	initLoggerLastValue(vTagLogger[i]);

        // Check Tag type
        if (vTagLogger[i].getTag().getType() == TT_BIT) {
            // Get current Tag value
            bool tagVal = prReader->getBitValue(vTagLogger[i].getTag());

            // Convert to the string
            s.str("");
            s << ((tagVal)?("1"):("0"));

            // Check if we need to update tag
            if (vTagLogger[i].isNeededUpdate(s.str())) {

            	// Get current values and store as last for next cycle
            	storeLastValue(vTagLogger[i]);

                // Log Tag value
            	tagLoggerToSave.push_back(vTagLogger[i]);
            }
        } else if (vTagLogger[i].getTag().getType() == TT_BYTE) {
            // Get current Tag value
            BYTE tagVal = prReader->getByte(vTagLogger[i].getTag());

            // Convert to the string
            s.str("");
            s << ((int)tagVal);

            // Check if we need to update tag
            if (vTagLogger[i].isNeededUpdate(s.str())) {

            	// Get current values and store as last for next cycle
            	storeLastValue(vTagLogger[i]);

                // Log Tag value
            	tagLoggerToSave.push_back(vTagLogger[i]);
            }
        } else if (vTagLogger[i].getTag().getType() == TT_WORD) {
            // Get current Tag value
            WORD tagVal = prReader->getWord(vTagLogger[i].getTag());

            // Convert to the string
            s.str("");
            s << tagVal;

            // Check if we need to update tag
            if (vTagLogger[i].isNeededUpdate(s.str())) {

            	// Get current values and store as last for next cycle
            	storeLastValue(vTagLogger[i]);

                // Log Tag value
            	tagLoggerToSave.push_back(vTagLogger[i]);
            }
        } else if (vTagLogger[i].getTag().getType() == TT_DWORD) {
            // Get current Tag value
            DWORD tagVal = prReader->getDWord(vTagLogger[i].getTag());

            // Convert to the string
            s.str("");
            s << tagVal;

            // Check if we need to update tag
            if (vTagLogger[i].isNeededUpdate(s.str())) {

            	// Get current values and store as last for next cycle
            	storeLastValue(vTagLogger[i]);

                // Log Tag value
            	tagLoggerToSave.push_back(vTagLogger[i]);
            }
        } else if (vTagLogger[i].getTag().getType() == TT_INT) {
            // Get current Tag value
            int tagVal = prReader->getInt(vTagLogger[i].getTag());

            // Convert to the string
            s.str("");
            s << tagVal;

            // Check if we need to update tag
            if (vTagLogger[i].isNeededUpdate(s.str())) {

            	// Get current values and store as last for next cycle
            	storeLastValue(vTagLogger[i]);

                // Log Tag value
            	tagLoggerToSave.push_back(vTagLogger[i]);
            }
        } else if (vTagLogger[i].getTag().getType() == TT_REAL) {
            // Get current Tag value
            float tagVal = prReader->getReal(vTagLogger[i].getTag());

            // Convert to the string
            s.str("");
            s << tagVal;

            // Check if we need to update tag
            if (vTagLogger[i].isNeededUpdate(s.str())) {

            	// Get current values and store as last for next cycle
            	storeLastValue(vTagLogger[i]);

                // Log Tag value
            	tagLoggerToSave.push_back(vTagLogger[i]);
            }
        }

    }

    // Check if there are data to save
    if (tagLoggerToSave.size() > 0) {

    	// Send data to the DB buffer
    	tagLoggerBuffer->putData(tagLoggerToSave);
    }
}

void TagLoggerProg::storeLastValue(const TagLoggerItem& tagLog) {

	// Get logger current values and store as last for next cycle
	loggerLastValue[tagLog.getId()] = tagLog.getCurrentTimeValue();
}

void TagLoggerProg::initLoggerLastValue(TagLoggerItem& tagLog) {

	// Search last value
	std::map<unsigned int, TagLoggerItem::timeVal>::iterator it = loggerLastValue.find(tagLog.getId());

	if (it != loggerLastValue.end()) {
		tagLog.setLastTimeValue(it->second);
	}
}
