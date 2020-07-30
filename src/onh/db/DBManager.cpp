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

#include "DBManager.h"
#include "../utils/Exception.h"
#include <sstream>

using namespace onh;

DBManager::DBManager(const std::string& db, const std::string& addr, const std::string& user, const std::string& pass):
    connDB(0), connAlarming(0), connTagLogger(0), connTagLoggerWriter(0), connScript(0)
{
	dbC.db = db;
	dbC.addr = addr;
	dbC.user = user;
	dbC.pass = pass;

	initConnections();
}

DBManager::~DBManager()
{
    if (connDB)
        mysql_close(connDB);
    if (connAlarming)
        mysql_close(connAlarming);
    if (connTagLogger)
        mysql_close(connTagLogger);
    if (connTagLoggerWriter)
		mysql_close(connTagLoggerWriter);
    if (connScript)
        mysql_close(connScript);
}

void DBManager::initConnections() {

    // Initialize structures
    connDB = mysql_init(NULL);
    connAlarming = mysql_init(NULL);
    connTagLogger = mysql_init(NULL);
    connTagLoggerWriter = mysql_init(NULL);
    connScript = mysql_init(NULL);

    // Check initializations
    if (!connDB)
        throw Exception("Can not initialize DB structures", "DBManager::initConnections");
    if (!connAlarming)
        throw Exception("Can not initialize AlarmingDB structures", "DBManager::initConnections");
    if (!connTagLogger)
        throw Exception("Can not initialize TagLoggerDB structures", "DBManager::initConnections");
    if (!connTagLoggerWriter)
		throw Exception("Can not initialize TagLoggerWriterDB structures", "DBManager::initConnections");
    if (!connScript)
        throw Exception("Can not initialize ScriptDB structures", "DBManager::initConnections");

    // Reconnect option
	bool reconnect = true;
	mysql_options(connDB, MYSQL_OPT_RECONNECT, &reconnect);
	mysql_options(connAlarming, MYSQL_OPT_RECONNECT, &reconnect);
	mysql_options(connTagLogger, MYSQL_OPT_RECONNECT, &reconnect);
	mysql_options(connTagLoggerWriter, MYSQL_OPT_RECONNECT, &reconnect);
	mysql_options(connScript, MYSQL_OPT_RECONNECT, &reconnect);

    // Create connection for DB manager
    if (!mysql_real_connect(connDB, dbC.addr.c_str(), dbC.user.c_str(), dbC.pass.c_str(), dbC.db.c_str(), 0, NULL, 0)) {
        std::stringstream s;
        s << "Can not create connection for DB manager: " << mysql_error(connDB);
        throw Exception(s.str(), "DBManager::initConnections");
    }
    // Create connection for Alarming DB
    if (!mysql_real_connect(connAlarming, dbC.addr.c_str(), dbC.user.c_str(), dbC.pass.c_str(), dbC.db.c_str(), 0, NULL, 0)) {
        std::stringstream s;
        s << "Can not create connection for AlarmingDB: " << mysql_error(connAlarming);
        throw Exception(s.str(), "DBManager::initConnections");
    }
    // Create connection for Tag Logger DB
    if (!mysql_real_connect(connTagLogger, dbC.addr.c_str(), dbC.user.c_str(), dbC.pass.c_str(), dbC.db.c_str(), 0, NULL, 0)) {
        std::stringstream s;
        s << "Can not create connection for TagLoggerDB: " << mysql_error(connTagLogger);
        throw Exception(s.str(), "DBManager::initConnections");
    }
    // Create connection for Tag Logger Writer DB
	if (!mysql_real_connect(connTagLoggerWriter, dbC.addr.c_str(), dbC.user.c_str(), dbC.pass.c_str(), dbC.db.c_str(), 0, NULL, 0)) {
		std::stringstream s;
		s << "Can not create connection for TagLoggerWriterDB: " << mysql_error(connTagLoggerWriter);
		throw Exception(s.str(), "DBManager::initConnections");
	}
    // Create connection for Script DB
    if (!mysql_real_connect(connScript, dbC.addr.c_str(), dbC.user.c_str(), dbC.pass.c_str(), dbC.db.c_str(), 0, NULL, 0)) {
        std::stringstream s;
        s << "Can not create connection for ScriptDB: " << mysql_error(connScript);
        throw Exception(s.str(), "DBManager::initConnections");
    }
}

AlarmingDB DBManager::getAlarmingDB() {

    return AlarmingDB(connAlarming);
}

Config DBManager::getConfigDB() {

    return Config(connDB);
}

ScriptDB DBManager::getScriptDB() {

    return ScriptDB(connScript);
}

TagLoggerDB DBManager::getTagLoggerDB() {

    return TagLoggerDB(connTagLogger);
}

TagLoggerDB DBManager::getTagLoggerWriterDB() {

    return TagLoggerDB(connTagLoggerWriter);
}

DBCredentials DBManager::getCredentials() {

	return dbC;
}
