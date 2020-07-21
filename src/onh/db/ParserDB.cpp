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

#include "ParserDB.h"
#include <sstream>
#include <mysql.h>
#include <iostream>

using namespace onh;

ParserDB::ParserDB(const DBCredentials & dbData):
	DB(mysql_init(NULL))
{

	// Check initializations
	if (!conn)
		throw Exception("Can not initialize DB structures", "ParserDB::ParserDB");

	// Connect
	if (!mysql_real_connect(conn, dbData.addr.c_str(), dbData.user.c_str(), dbData.pass.c_str(), dbData.db.c_str(), 0, NULL, 0)) {
		std::stringstream s;
		s << "Can not create connection for Parser DB: " << mysql_error(conn);
		throw Exception(s.str(), "DBManager::ParserDB::ParserDB");
	}

	// Create alarming DB
	pAlarmDB = new AlarmingDB(conn);
}

ParserDB::ParserDB(const ParserDB &tDB):
    DB(tDB)
{
    pAlarmDB = new AlarmingDB(*(tDB.pAlarmDB));
}

ParserDB::~ParserDB()
{
    if (pAlarmDB)
        delete pAlarmDB;

    if (conn)
		mysql_close(conn);
}

AlarmingDB& ParserDB::getAlarmDB() {

    if (!pAlarmDB)
        throw Exception("No AlarmingDB instance", "ParserDB::getAlarmDB");

    return *pAlarmDB;
}

const Tag ParserDB::getTag(const std::string& tagName)
{
    // Check tag name
    if (tagName.size() == 0)
        throw TagException(TagException::WRONG_NAME, "Tag name is empty", "ParserDB::getTag");

    if (!DB::checkStringValue(tagName))
        throw TagException(TagException::WRONG_NAME, "Tag name contains invalid characters", "ParserDB::getTag");

    // No data
    bool noData = false;

    // Query
    std::stringstream q;

    // Return value
    Tag tg;

    DBResult *result = 0;

    try {

        // Prepare query
        q << "SELECT * FROM tags WHERE tName=";
        q << "'" << tagName << "';";

        // Query
        result = executeQuery(q.str());

        if (result->rowsCount() == 1) {

            // Read data
            result->nextRow();

            // Get Tag
            tg = getTagFromResultset(result);

            // Release memory
            delete result;
            result = 0;

        } else {
            noData = true;
        }

    } catch (DBException &e) {

        if (result)
            delete result;

        throw Exception(e.what(), "ParserDB::getTag");
    }

    if (noData)
        throw TagException(TagException::NOT_EXIST, "Tag "+tagName+" does not exist in DB", "ParserDB::getTag");

    return tg;
}

std::stringstream ParserDB::prepareIN(const std::vector<std::string> &tagNames) {

	std::stringstream sTags;

	// Prepare SQL IN statement values
	for (unsigned int i=0; i<tagNames.size(); ++i) {

		// Check tag name
		if (tagNames[i].size() == 0)
			throw TagException(TagException::WRONG_NAME, "Tag name is empty", "ParserDB::getTags");

		if (!DB::checkStringValue(tagNames[i]))
			throw TagException(TagException::WRONG_NAME, "Tag name contains invalid characters", "ParserDB::getTags");

		// Add to string values
		sTags << "'" << tagNames[i] << "'";

		// Put separator?
		if (i < tagNames.size()-1) {
			sTags << ", ";
		}
	}

	return sTags;
}

void ParserDB::checkTagNamesExist(const std::vector<std::string> &tagNames, const std::vector<Tag> &vTag) {

	// Check if all names exist in vector
	bool exist = false;

	// Check names
	for (unsigned int i=0; i<tagNames.size(); ++i) {

		exist = false;

		// Check Tag objects
		for (unsigned int j=0; j<vTag.size(); ++j) {
			if (tagNames[i] == vTag[j].getName()) {
				exist = true;
				break;
			}
		}

		if (!exist)
			throw TagException(TagException::NOT_EXIST, "Tag "+tagNames[i]+" does not exist in DB", "ParserDB::getTags");
	}
}

std::vector<Tag> ParserDB::getTags(std::vector<std::string> tagNames) {

    std::vector<Tag> vTag; // Return vector
    std::stringstream sTags;

    // Check input values
    if (tagNames.size() <= 1) {
        throw TagException(TagException::WRONG_NAME, "Tag array should have more than 1 item", "ParserDB::getTags");
    }

    // Prepare SQL IN statement values
    sTags = prepareIN(tagNames);

    // No data
    bool noData = true;

    // Query
    std::stringstream q;

    // Return value
    Tag tg;

    DBResult *result = 0;

    try {

        // Prepare query
        q << "SELECT * FROM tags WHERE tName IN (";
        q << sTags.str() << ") ORDER BY FIELD(tName, " << sTags.str() << ");";

        // Query
        result = executeQuery(q.str());

        // Read data
        while (result->nextRow()) {

            noData = false;

            // Get Tag
            tg = getTagFromResultset(result);

            // Put into the vector
            vTag.push_back(tg);

        }

        // Release memory
        delete result;
        result = 0;

    } catch (DBException &e) {

        if (result)
            delete result;

        throw Exception(e.what(), "ParserDB::getTag");
    }

    // Check empty data
    if (noData || vTag.size()==0)
        throw TagException(TagException::NOT_EXIST, "Tags "+sTags.str()+" does not exist in DB", "ParserDB::getTags");

    // Check if all tags read from DB
    checkTagNamesExist(tagNames, vTag);

    return vTag;
}

Tag ParserDB::getTagFromResultset(DBResult *res) {

    // Return value
    Tag tg;
    TagType tt;
    processDataArea ta;

    // Tag type
	tt = (TagType)res->getUInt("tType");

	// Tag area
	ta = (processDataArea)res->getUInt("tArea");

    // Update tag object values
    tg.setId(res->getUInt("tid"));
    tg.setName(res->getString("tName"));
    tg.setType(tt);
    tg.setArea(ta);
    tg.setByteAddress(res->getUInt("tByteAddress"));
    tg.setBitAddress(res->getUInt("tBitAddress"));

    return tg;
}
