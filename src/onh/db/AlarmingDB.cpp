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

#include "AlarmingDB.h"
#include <sstream>

using namespace onh;

AlarmingDB::AlarmingDB(MYSQL *connDB):
    DB(connDB)
{
}

AlarmingDB::AlarmingDB(const AlarmingDB &aDB):
    DB(aDB)
{
}

AlarmingDB::~AlarmingDB()
{
}

std::vector<AlarmDefinitionItem> AlarmingDB::getAlarms(bool enabled) {

    // Query
    std::stringstream q;
    std::string q1;
    std::stringstream tagIDs;

    // Return vector
    std::vector<AlarmDefinitionItem> vAlarms;

    // Return value
    Tag tg;
    Tag feedbackNotACK;
    Tag HWAck;
    TagType tt;
    processDataArea ta;
    AlarmDefinitionItem ad;
    AlarmDefinitionItem ad_clear;
    bool feedbackTag = false;
    bool HWAckTag = false;

    DBResult *result = 0;
	DBResult *result2 = 0;

    // Prepare query
    q << "SELECT * FROM alarms_definition ad, tags t, driver_connections dc WHERE ad.adtid=t.tid AND t.tConnId=dc.dcId ";
    q << "AND ad.adEnable=" << ((enabled)?("1"):("0")) << ";";

    try {
        // Query
        result = executeQuery(q.str());

        // Read data
        while (result->nextRow()) {

            ad = ad_clear;

            // Tag type
			tt = (TagType)result->getUInt("tType");

			// Tag area
			ta = (processDataArea)result->getUInt("tArea");

            // Update tag object values
            tg.setId(result->getUInt("tid"));
            tg.setConnId(result->getUInt("tConnId"));
            tg.setName(result->getString("tName"));
            tg.setType(tt);
            tg.setArea(ta);
            tg.setByteAddress(result->getUInt("tByteAddress"));
            tg.setBitAddress(result->getUInt("tBitAddress"));

            // Alarm trigger values
            bool intV = (tg.getType()==TT_INT)?(true):(false);
            AlarmDefinitionItem::triggerValues trVal;
            trVal.binVal = ((result->getInt("adTriggerB")==1)?(true):(false));
            if (intV) {
                trVal.intVal = result->getInt("adTriggerN");
            } else {
                trVal.dwVal = result->getUInt64("adTriggerN");
            }
            trVal.realVal = result->getReal("adTriggerR");

            // Alarm item
            ad.setId(result->getUInt("adid"));
            ad.setTag(tg);
            ad.setPriority(result->getUInt("adPriority"));
            ad.setMsg(result->getString("adMessage"));
            ad.setTrigger((AlarmDefinitionItem::triggers)result->getUInt("adTrigger"));
            ad.setTriggerValues(trVal);
            ad.setAutoAck(((result->getInt("adAutoAck")==1)?(true):(false)));
            ad.setActive(((result->getInt("adActive")==1)?(true):(false)));
            ad.setPending(((result->getInt("adPending")==1)?(true):(false)));

            // Check if there is feedback Tag
            tagIDs.str("");
            if (!result->isNull("adFeedbackNotACK")) {
                feedbackTag = true;
                tagIDs << result->getUInt("adFeedbackNotACK");
            }

            // Check if there is HW ack Tag
            if (!result->isNull("adHWAck")) {
                HWAckTag = true;
                if (!feedbackTag)
                    tagIDs << result->getUInt("adHWAck");
                else
                    tagIDs << ", " << result->getUInt("adHWAck");
            }

            if (tagIDs.str() != "") {
                tagIDs << ");";
                q1 = "SELECT * FROM tags t, driver_connections dc WHERE t.tConnId=dc.dcId AND t.tid IN ( "+tagIDs.str();

                // Call additional query
                result2 = executeQuery(q1);

                if (result2->rowsCount() == 2) {

                    result2->nextRow();

                    // Tag type
					tt = (TagType)result2->getUInt("tType");

					// Tag area
					ta = (processDataArea)result2->getUInt("tArea");

                    // Update tag object values
                    tg.setId(result2->getUInt("tid"));
                    tg.setConnId(result2->getUInt("tConnId"));
                    tg.setName(result2->getString("tName"));
                    tg.setType(tt);
                    tg.setArea(ta);
                    tg.setByteAddress(result2->getUInt("tByteAddress"));
                    tg.setBitAddress(result2->getUInt("tBitAddress"));

                    if (tg.getId()==result->getUInt("adFeedbackNotACK")) {
                    	feedbackNotACK = tg;
                    } else {
                    	HWAck = tg;
                    }

                    result2->nextRow();

                    // Tag type
					tt = (TagType)result2->getUInt("tType");

					// Tag area
					ta = (processDataArea)result2->getUInt("tArea");

                    // Update tag object values
                    tg.setId(result2->getUInt("tid"));
                    tg.setConnId(result2->getUInt("tConnId"));
                    tg.setName(result2->getString("tName"));
                    tg.setType(tt);
                    tg.setArea(ta);
                    tg.setByteAddress(result2->getUInt("tByteAddress"));
                    tg.setBitAddress(result2->getUInt("tBitAddress"));

                    if (tg.getId()==result->getUInt("adHWAck")) {
                    	HWAck = tg;
					} else {
						feedbackNotACK = tg;
					}

                } else if (result2->rowsCount() == 1) {
                    result2->nextRow();

                    // Tag type
					tt = (TagType)result2->getUInt("tType");

					// Tag area
					ta = (processDataArea)result2->getUInt("tArea");

                    // Update tag object values
                    tg.setId(result2->getUInt("tid"));
                    tg.setConnId(result2->getUInt("tConnId"));
                    tg.setName(result2->getString("tName"));
                    tg.setType(tt);
                    tg.setArea(ta);
                    tg.setByteAddress(result2->getUInt("tByteAddress"));
                    tg.setBitAddress(result2->getUInt("tBitAddress"));

                    if (feedbackTag)
                        feedbackNotACK = tg;
                    else
                        HWAck = tg;
                }

                // Release memory
                delete result2;
                result2 = 0;

            }

            if (feedbackTag)
                ad.setFeedbackNotAckTag(feedbackNotACK);

            if (HWAckTag)
                ad.setHWAckTag(HWAck);

            ad.setEnable(((result->getInt("adEnable")==1)?(true):(false)));

            // Put into the vector
            vAlarms.push_back(ad);

            feedbackTag = false;
            HWAckTag = false;

        }

        // Release memory
        delete result;

    } catch (DBException &e) {

        if (result)
            delete result;
        if (result2)
            delete result2;

        throw Exception(e.what(), "AlarmingDB::getAlarms");
    }

    return vAlarms;
}

void AlarmingDB::setAlarm(const AlarmDefinitionItem& alarm) {

    // Query
    std::stringstream q;

    // Prepare query
    q << "INSERT INTO alarms_pending(apid, apadid, ap_active, ap_ack, ap_onTimestamp, ap_offTimestamp, ap_ackTimestamp) ";
    q << "VALUES (NULL, " << alarm.getId() << ", 1, 0, CURRENT_TIMESTAMP, NULL, NULL);";

    try {

        // Query
        executeSaveQuery(q.str());

    } catch (DBException &e) {

        throw Exception(e.what(), "AlarmingDB::setAlarm");

    }
}

void AlarmingDB::updateAlarmState(const AlarmDefinitionItem& alarm, bool state) {

    // Query
    std::stringstream q;

    // Prepare query
    if (state)
        q << "UPDATE alarms_pending SET ap_active=1 WHERE apadid=" << alarm.getId() <<";";
    else
        q << "UPDATE alarms_pending SET ap_active=0, ap_offTimestamp=CURRENT_TIMESTAMP WHERE apadid=" << alarm.getId() <<";";

    try {

        // Query
        executeSaveQuery(q.str());

        // Check if alarm is auto acknowledgment
        if (state == 0 && alarm.isAutoAck()) {
            ackAlarm(alarm.getId());
        }

    } catch (Exception &e) {

        throw Exception(e.what(), "AlarmingDB::updateAlarmState");

    }
}

void AlarmingDB::ackAlarm(unsigned int apadid) {

    // Query
    std::stringstream q;

    // Prepare query
    if (apadid == 0)
        q << "UPDATE alarms_pending SET ap_ack=1, ap_ackTimestamp=CURRENT_TIMESTAMP WHERE ap_active=0;";
    else
        q << "UPDATE alarms_pending SET ap_ack=1, ap_ackTimestamp=CURRENT_TIMESTAMP WHERE ap_active=0 AND apadid=" << apadid << ";";

    try {

        // Query 1
        executeSaveQuery(q.str());

        // Delete acknowledgment alarms
        q.str("");
        if (apadid == 0)
            q << "DELETE FROM alarms_pending WHERE ap_ack=1;";
        else
            q << "DELETE FROM alarms_pending WHERE ap_ack=1 AND apadid=" << apadid << ";";

        // Query 2
        executeSaveQuery(q.str());

    } catch (DBException &e) {

        throw Exception(e.what(), "AlarmingDB::ackAlarm");

    }
}
