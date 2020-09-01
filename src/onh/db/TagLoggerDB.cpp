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

#include "TagLoggerDB.h"
#include <sstream>

using namespace onh;

TagLoggerDB::TagLoggerDB(const TagLoggerDB &tlDB):
    DB(tlDB)
{
}

TagLoggerDB::TagLoggerDB(MYSQL *connDB):
    DB(connDB)
{
}

TagLoggerDB::~TagLoggerDB()
{
}

std::vector<TagLoggerItem> TagLoggerDB::getLoggers(bool enabled) {

    // Query
    std::stringstream q;

    // Return vector
    std::vector<TagLoggerItem> vTagLoggers;

    // Return value
    Tag tg;
    TagType tt;
    processDataArea ta;
    TagLoggerItem tl;

    DBResult *result = 0;

    try {

        // Prepare query
        q << "SELECT * FROM log_tags lt, tags t, driver_connections dc WHERE lt.lttid=t.tid AND t.tConnId=dc.dcId ";
        q << "AND lt.ltEnable=" << ((enabled)?("1"):("0")) << ";";

        // Query
        result = executeQuery(q.str());

        // Read data
        while (result->nextRow()) {

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

            // Tag logger
            tl.setId(result->getUInt("ltid"));
            tl.setTag(tg);
            tl.setInterval((TagLoggerItem::intervals)result->getUInt("ltInterval"));
            tl.setIntervalSec(result->getUInt("ltIntervalS"));

            if (result->isNull("ltLastUPD")) {
                tl.setLastUpdate("2000-01-01 07:00:00.000");
            } else {
                tl.setLastUpdate(result->getString("ltLastUPD"));
            }

            tl.setLastValue(result->getString("ltLastValue"));
            tl.setEnable(((result->getInt("ltEnable")==1)?(true):(false)));

            // Put into the vector
            vTagLoggers.push_back(tl);
        }

        // Release memory
        delete result;
        result = 0;

    } catch (DBException &e) {

        if (result)
            delete result;

        throw Exception(e.what(), "TagLoggerDB::getLoggers");
    }

    return vTagLoggers;
}

void TagLoggerDB::logTag(const TagLoggerItem& loggerItem) {

	/*
		On table log_xxx must be a trigger!

		CREATE TRIGGER tr1_log_BIT AFTER INSERT ON log_BIT FOR EACH ROW UPDATE log_tags SET ltLastUPD = NEW.lbTimeStamp WHERE lttid = NEW.lbtid;
	*/

	// Table name to write
	std::string tableName;
	// Table column names
	std::string tableColumns;

	// Query
	std::stringstream q;

	// Prepare table names
	switch (loggerItem.getTag().getType()) {

		case TT_BIT: {
			tableName = "log_BIT_";
			tableColumns = "lbtid, lbValue, lbTimeStamp";
		}; break;
		case TT_BYTE: {
			tableName = "log_BYTE_";
			tableColumns = "lbytid, lbyValue, lbyTimeStamp";
		}; break;
		case TT_WORD: {
			tableName = "log_WORD_";
			tableColumns = "lwtid, lwValue, lwTimeStamp";
		}; break;
		case TT_DWORD: {
			tableName = "log_DWORD_";
			tableColumns = "ldtid, ldValue, ldTimeStamp";
		}; break;
		case TT_INT: {
			tableName = "log_INT_";
			tableColumns = "linttid, lintValue, lintTimeStamp";
		}; break;
		case TT_REAL: {
			tableName = "log_REAL_";
			tableColumns = "lrtid, lrValue, lrTimeStamp";
		}; break;
	}

	try {

		// Prepare query
		q << "INSERT INTO " << tableName << loggerItem.getId() << " (" << tableColumns << ") VALUES (" << loggerItem.getTag().getId() << ", ";
		q << loggerItem.getCurrentTimeValue().value << ", '" << loggerItem.getCurrentUpdate() << "');";

		// Query
		executeSaveQuery(q.str());

	} catch (DBException &e) {

        throw Exception(e.what(), "TagLoggerDB::logTag");
    }
}
