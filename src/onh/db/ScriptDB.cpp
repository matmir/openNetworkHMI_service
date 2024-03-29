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

#include "ScriptDB.h"
#include <sstream>
#include "../utils/Exception.h"

namespace onh {

ScriptDB::ScriptDB(const ScriptDB &sDB):
	DB(sDB) {
}

ScriptDB::ScriptDB(MYSQL *connDB):
	DB(connDB) {
}

ScriptDB::~ScriptDB() {
}

std::vector<ScriptItem> ScriptDB::getScripts(bool enabled) {
	std::stringstream tagID;

	// Query
	std::stringstream q;
	std::string q1;

	// Return vector
	std::vector<ScriptItem> vScripts;

	// Return value
	Tag tg;
	TagType tt;
	processDataArea ta;
	ScriptItem sc;
	ScriptItem sc_clear;

	// Prepare query
	q << "SELECT * FROM scripts sc, tags t, driver_connections dc WHERE sc.scTagId=t.tid AND t.tConnId=dc.dcId ";
	q << "AND sc.scEnable=" << ((enabled)?("1"):("0")) << ";";

	try {
		// Query
		auto result = executeQuery(q.str());

		// Read data
		while (result->nextRow()) {
			sc = sc_clear;

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

			// Script item
			sc.setId(result->getUInt("scid"));
			sc.setTag(tg);
			sc.setName(result->getString("scName"));
			sc.setRun(((result->getInt("scRun") == 1)?(true):(false)));
			sc.setLock(((result->getInt("scLock") == 1)?(true):(false)));

			// Check if there is feedback Tag
			if (!result->isNull("scFeedbackRun")) {
				tagID << result->getUInt("scFeedbackRun");
				q1 = "SELECT * FROM tags t, driver_connections dc WHERE t.tConnId=dc.dcId AND tid="+tagID.str();

				// Call additional query
				auto result2 = executeQuery(q1);

				if (result2->rowsCount() == 1) {
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

					// Set feedback tag
					sc.setFeedbackRunTag(tg);
				}
			}

			sc.setEnable(((result->getInt("scEnable") == 1)?(true):(false)));

			// Put into the vector
			vScripts.push_back(sc);
		}
	} catch (DBException &e) {
		throw Exception(e.what(), "ScriptDB::getScripts");
	}

	return vScripts;
}

void ScriptDB::setScriptRun(const ScriptItem& script) {
	// Query
	std::stringstream q;

	// Prepare query
	q << "UPDATE scripts SET scRun=1, scLock=1 WHERE scid=" << script.getId() <<";";

	try {
		// Query
		executeSaveQuery(q.str());
	} catch (DBException &e) {
		throw Exception(e.what(), "ScriptDB::setScriptRun");
	}
}

void ScriptDB::clearScriptRun(unsigned int scriptId) {
	// Query
	std::stringstream q;

	// Prepare query
	q << "UPDATE scripts SET scRun=0 WHERE scid=" << scriptId <<";";

	try {
		// Query
		executeSaveQuery(q.str());
	} catch (Exception &e) {
		throw Exception(e.what(), "ScriptDB::clearScriptRun");
	}
}

void ScriptDB::clearScriptLock(const ScriptItem& script) {
	// Query
	std::stringstream q;

	// Prepare query
	q << "UPDATE scripts SET scLock=0 WHERE scid=" << script.getId() <<";";

	try {
		// Query
		executeSaveQuery(q.str());
	} catch (Exception &e) {
		throw Exception(e.what(), "ScriptDB::clearScriptLock");
	}
}

}  // namespace onh
