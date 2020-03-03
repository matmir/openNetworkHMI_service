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

#include "Config.h"
#include <sstream>

using namespace onh;

Config::Config():
    DB()
{
}

Config::Config(MYSQL *connDB):
    DB(connDB)
{
}

Config::Config(const Config &cDB):
    DB(cDB)
{
}

Config::~Config()
{
}

std::string Config::getStringValue(const std::string& field) {

    if (field == "")
        throw Exception("Field is empty", "Config::getStringValue");

    DBResult *res = 0;

	// Return value
    std::string val;

    try {

        // Query
        res = executeQuery("SELECT * FROM configuration WHERE cName='"+field+"'");

        // Load data
        res->nextRow();

        // Parse data
        val = res->getString("cValue");

    } catch (DBException &e) {

        std::stringstream s;
        s << "Config::getStringValue (" << field << ")";
        throw Exception(e.what(), s.str());
    }

    // Release memory
    delete res;

    return val;
}

int Config::getIntValue(const std::string& field) {

    if (field == "")
        throw Exception("Field is empty", "Config::getIntValue");

    DBResult *res = 0;

	// Return value
    int iVal;

    try {

        // Query
        res = executeQuery("SELECT * FROM configuration WHERE cName='"+field+"'");

        // Load data
        res->nextRow();

        // Parse data
        iVal = res->getInt("cValue");

    } catch (DBException &e) {

        std::stringstream s;
        s << "Config::getIntValue (" << field << ")";
        throw Exception(e.what(), s.str());
    }

    // Release memory
    delete res;

    return iVal;
}

unsigned int Config::getUIntValue(const std::string& field) {

    if (field == "")
        throw Exception("Field is empty", "Config::getUIntValue");

    DBResult *res = 0;

	// Return value
    unsigned int iVal;

    try {

        // Query
        res = executeQuery("SELECT * FROM configuration WHERE cName='"+field+"'");

        // Load data
        res->nextRow();

        // Parse data
        iVal = res->getUInt("cValue");

    } catch (DBException &e) {

        std::stringstream s;
        s << "Config::getUIntValue (" << field << ")";
        throw Exception(e.what(), s.str());
    }

    // Release memory
    delete res;

    return iVal;
}

void Config::setValue(const std::string& field, int val) {

    if (field == "")
        throw Exception("Field is empty", "Config::setValue (int)");

    // Convert to string
    std::stringstream ss;
    ss << val;

    try {

        // Query
        executeSaveQuery("UPDATE configuration SET cValue='"+ss.str()+"' WHERE cName='"+field+"'");

    } catch (DBException &e) {

        std::stringstream s;
        s << "Config::setValue (int) (" << field << ")";
        throw Exception(e.what(), s.str());
    }
}

void Config::setValue(const std::string& field, const std::string& val) {

    if (field == "")
        throw Exception("Field is empty", "Config::setValue (string)");

    try {

        // Query
        executeSaveQuery("UPDATE configuration SET cValue='"+val+"' WHERE cName='"+field+"'");

    } catch (DBException &e) {

        std::stringstream s;
        s << "Config::setValue (string) (" << field << ")";
        throw Exception(e.what(), s.str());
    }
}
