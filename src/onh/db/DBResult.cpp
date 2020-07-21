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

#include "DBResult.h"
#include <sstream>

using namespace onh;

DBResult::DBResult(MYSQL *DBConn):
    conn(0), result(0), fields(0), row(0), fieldsCount(0)
{
	conn = DBConn;

	// Get data from DB
	result = mysql_store_result(conn);

	if (!result && mysql_errno(conn)) {
		std::stringstream s;
		s << "Store result error: " << mysql_error(conn);
		throw DBException(s.str(), "DBResult::DBResult");
	}

	// Get fields count
	fieldsCount = mysql_num_fields(result);

	if (fieldsCount==0 && mysql_errno(conn)) {
		std::stringstream s;
		s << "Get fields count error: " << mysql_error(conn);
		throw DBException(s.str(), "DBResult::DBResult");
	}

	// Get field names
	if (fieldsCount) {
		fields = mysql_fetch_fields(result);

		if (!fields && mysql_errno(conn)) {
			std::stringstream s;
			s << "Get fields error: " << mysql_error(conn);
			throw DBException(s.str(), "DBResult::DBResult");
		}
	}
}

DBResult::~DBResult()
{
    // Release memory
    mysql_free_result(result);
}

unsigned int DBResult::getFieldPos(const std::string &fName) {

    unsigned int pos = 0;
    bool ok = false;

	for (unsigned int i=0; i<fieldsCount; ++i) {

		if (fName == fields[i].name) {
			pos = i;
			ok = true;
			break;
		}
	}

	if (!ok) {
        std::stringstream s;
        s << "Field: " << fName << " does not exist in result array";
        throw DBException(s.str(), "DBResult::getFieldPos");
	}

	return pos;
}

bool DBResult::nextRow() {

    // Get row from result
    row = mysql_fetch_row(result);

    if (mysql_errno(conn)) {
        std::stringstream s;
        s << "Error getting next row: " << mysql_error(conn);
        throw DBException(s.str(), "DBResult::nextRow");
    }

    return (row==NULL)?(false):(true);
}

std::string DBResult::getString(const std::string &fName) {

    if (!row) {
        throw DBException("No data in row structure", "DBResult::getString");
    }

    return row[getFieldPos(fName)];
}

int DBResult::getInt(const std::string &fName) {

    if (!row) {
        throw DBException("No data in row structure", "DBResult::getInt");
    }

    int val = 0;
	std::istringstream iss(row[getFieldPos(fName)]);
	iss >> val;

	return val;
}

unsigned int DBResult::getUInt(const std::string &fName) {

    if (!row) {
        throw DBException("No data in row structure", "DBResult::getUInt");
    }

    unsigned int val = 0;
	std::istringstream iss(row[getFieldPos(fName)]);
	iss >> val;

	return val;
}

unsigned long int DBResult::getUInt64(const std::string &fName) {

    if (!row) {
        throw DBException("No data in row structure", "DBResult::getUInt64");
    }

    unsigned long int val = 0;
	std::istringstream iss(row[getFieldPos(fName)]);
	iss >> val;

	return val;
}

float DBResult::getReal(const std::string &fName) {

    if (!row) {
        throw DBException("No data in row structure", "DBResult::getReal");
    }

    float val = 0;
	std::istringstream iss(row[getFieldPos(fName)]);
	iss >> val;

	return val;
}

bool DBResult::isNull(const std::string &fName) {

    return (row[getFieldPos(fName)]==NULL)?(true):(false);
}

unsigned long int DBResult::rowsCount() {

    return mysql_num_rows(result);
}
