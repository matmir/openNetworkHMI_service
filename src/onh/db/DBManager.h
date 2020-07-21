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

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <string>
#include <mysql.h>
#include "AlarmingDB.h"
#include "Config.h"
#include "ScriptDB.h"
#include "ParserDB.h"
#include "TagLoggerDB.h"
#include "DBCredentials.h"

namespace onh {

    /**
	 * Class for manage DB connections
	 */
    class DBManager {

        public:

            /**
             * DB manager constructor
             *
             * @param addr DB address
             * @param user DB user
             * @param pass DB password
             */
            DBManager(const std::string& db, const std::string& addr, const std::string& user, const std::string& pass);

            /**
			 * Copy constructor - inactive
			 */
            DBManager(const DBManager&) = delete;

            virtual ~DBManager();

            /**
			 * Assignment operator - inactive
			 */
            DBManager& operator=(const DBManager&) = delete;

            /**
             * Get AlarmingDB object
             *
             * @return AlarmingDB object
             */
            AlarmingDB getAlarmingDB();

            /**
             * Get ConfigDB object
             *
             * @return ConfigDB object
             */
            Config getConfigDB();

            /**
             * Get ScriptDB object
             *
             * @return ScriptDB object
             */
            ScriptDB getScriptDB();

            /**
             * Get TagLoggerDB object
             *
             * @return TagLoggerDB object
             */
            TagLoggerDB getTagLoggerDB();

            /**
			 * Get TagLoggerWriterDB object
			 *
			 * @return TagLoggerDB object
			 */
			TagLoggerDB getTagLoggerWriterDB();

			/**
			 * Get database credentials
			 *
			 * @return Database credentials
			 */
			DBCredentials getCredentials();

        private:

			/// Database credentials
			DBCredentials dbC;

            /// DB connection instance for DB manager
            MYSQL *connDB;
            /// DB connection instance for Alarming system
            MYSQL *connAlarming;
            /// DB connection instance for Tag logger system
            MYSQL *connTagLogger;
            /// DB connection instance for Tag logger writer system
			MYSQL *connTagLoggerWriter;
            /// DB connection instance for Script system
            MYSQL *connScript;

            /**
			 * Initialize DB connections
			 */
			void initConnections();
    };

}

#endif // DBMANAGER_H
