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

#include "AlarmingProg.h"

#include <sstream>
#include "../../utils/Exception.h"
#include "../../db/AlarmingDB.h"

using namespace onh;

AlarmingProg::AlarmingProg(const ProcessReader& pr,
							const ProcessWriter& pw,
							const AlarmingDB& adb,
							unsigned int updateInterval,
							const GuardDataController<ThreadExitData> &gdcTED,
							const GuardDataController<CycleTimeData> &gdcCTD):
    ThreadProgram(gdcTED, gdcCTD, "alarming", "alarmLog_")
{
    // Process Reader
    prReader = new ProcessReader(pr);

    // Process Writer
    prWriter = new ProcessWriter(pw);

    // Create delay
    itsDelay = new Delay(updateInterval);

    // Create Alarming DB
    db = new AlarmingDB(adb);
}

AlarmingProg::~AlarmingProg()
{
    if (prReader)
        delete prReader;
    if (prWriter)
        delete prWriter;
    if (db)
        delete db;

    getLogger().write("Alarming close");

    if (itsDelay)
        delete itsDelay;
}

void AlarmingProg::operator()() {

    try {

    	getLogger().write("Start main loop");

        if (!prReader)
            throw Exception("No reader object");

        if (!prWriter)
            throw Exception("No writer object");

        while(!isExitFlag()) {

            // Start thread cycle time measure
            startCycleMeasure();

            // Update process reader
            prReader->updateProcessData();

            // Check alarms
            checkAlarms();

            // Wait
            itsDelay->wait();

            // Stop thread cycle time measure
            stopCycleMeasure();
        }

    } catch (Exception &e) {

        std::stringstream s;
        s << "AlarmingProg::run: " << e.what();
        getLogger().write(s.str());

        // Exit application
        exit("Alarming system");
    }
}

void AlarmingProg::checkAlarms() {

    // Get alarms
    std::vector<AlarmDefinitionItem> ad = db->getAlarms();

    // Alarm state - trigger return
    AlarmDefinitionItem::triggerRet tr;

    for (unsigned int i=0; i<ad.size(); ++i) {

        // Check tag type
        if (ad[i].getTag().getType() == TT_BIT) {

            // Get tag value
            bool tv = prReader->getBitValue(ad[i].getTag());

            // Check alarm state
            tr = ad[i].checkTrigger(tv);

        } else if (ad[i].getTag().getType() == TT_BYTE) {

            // Get tag value
            BYTE tv = prReader->getByte(ad[i].getTag());

            // Check alarm state
            tr = ad[i].checkTrigger(tv);

        } else if (ad[i].getTag().getType() == TT_WORD) {

            // Get tag value
            WORD tv = prReader->getWord(ad[i].getTag());

            // Check alarm state
            tr = ad[i].checkTrigger(tv);

        } else if (ad[i].getTag().getType() == TT_DWORD) {

            // Get tag value
            DWORD tv = prReader->getDWord(ad[i].getTag());

            // Check alarm state
            tr = ad[i].checkTrigger(tv);

        } else if (ad[i].getTag().getType() == TT_INT) {

            // Get tag value
            int tv = prReader->getInt(ad[i].getTag());

            // Check alarm state
            tr = ad[i].checkTrigger(tv);

        } else if (ad[i].getTag().getType() == TT_REAL) {

            // Get tag value
            float tv = prReader->getReal(ad[i].getTag());

            // Check alarm state
            tr = ad[i].checkTrigger(tv);

        }

        if (tr.trigger) {
            // Set alarm
            db->setAlarm(ad[i]);

        } else if (tr.activeUpdate) {
            // Update alarm state
            db->updateAlarmState(ad[i], tr.active);
        }

        // Feedback Tags
        if (ad[i].isPending()) {

            try {
                // Set bit informs controller that alarm is not acknowledgment
                if (!prReader->getBitValue(ad[i].getFeedbackNotAckTag())) {
                    prWriter->setBit(ad[i].getFeedbackNotAckTag());
                }

            } catch (AlarmException &e) {
                if (e.getType() != AlarmException::ExceptionType::NO_FEEDBACK_NOT_ACK_TAG) {
                    // Re-throw exception
                    throw;
                }
            }

            try {
                // HW alarm acknowledgment
                if (prReader->getBitValue(ad[i].getHWAckTag())) {
                    db->ackAlarm(ad[i].getId());
                }
            } catch (AlarmException &e) {
                if (e.getType() != AlarmException::ExceptionType::NO_HW_ACK_TAG) {
                    // Re-throw exception
                    throw;
                }
            }

        } else {

            try {
                // Reset bit informs controller that alarm is not acknowledgment
                if (prReader->getBitValue(ad[i].getFeedbackNotAckTag())) {
                    prWriter->resetBit(ad[i].getFeedbackNotAckTag());
                }

            } catch (AlarmException &e) {
                if (e.getType() != AlarmException::ExceptionType::NO_FEEDBACK_NOT_ACK_TAG) {
                    // Re-throw exception
                    throw;
                }
            }

        }

    }
}
