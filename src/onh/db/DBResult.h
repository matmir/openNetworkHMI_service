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

#ifndef DBRESULT_H
#define DBRESULT_H

#include <string>
#include <mysql.h>
#include "DBException.h"

namespace onh {

    /// Forward declaration
	class DB;

    /**
	 * Database query result class
	 */
    class DBResult {

        public:

            friend class DB;

            virtual ~DBResult();

            /**
             * Get string value from result
             *
             * @param fName Table field name
             * @return DB data as string
             */
            std::string getString(const std::string &fName);

            /**
             * Get integer value from result
             *
             * @param fName Table field name
             *
             * @return DB data as integer
             */
            int getInt(const std::string &fName);

            /**
             * Get unsigned integer value from result
             *
             * @param fName Table field name
             *
             * @return DB data as unsigned integer
             */
            unsigned int getUInt(const std::string &fName);

            /**
             * Get unsigned long integer value from result
             *
             * @param fName Table field name
             *
             * @return DB data as unsigned long integer
             */
            unsigned long int getUInt64(const std::string &fName);

            /**
             * Get real value from result
             *
             * @param fName Table field name
             *
             * @return DB data as real
             */
            float getReal(const std::string &fName);

            /**
             * Check if field value in row is null
             *
             * @param fName Table field name
             *
             * @return True if data is NULL
             */
            bool isNull(const std::string &fName);

            /**
             * Get next row data
             *
             * @return True if data exist
             */
            bool nextRow();

            /**
             * Get rows count from result
             *
             * @return Rows count
             */
            unsigned long int rowsCount();

        private:
            /**
             * Default constructor (allowed only from DB)
             */
            DBResult();

            /**
             * Copy constructor
             */
            DBResult(const DBResult&) {};

            /**
             * Assign operator
             */
            void operator=(const DBResult&) {};

            /**
             * Store result from MySQL into structures
             *
             * @param DBConn Connection handle
             */
            void storeResult(MYSQL *DBConn);

            /**
             * Get field name position in result
             *
             * @param fName Field name
             *
             * @return Field position
             */
            unsigned int getFieldPos(const std::string &fName);

            /// MySQL connection handle
            MYSQL *conn;
            /// MySQL result structure
            MYSQL_RES *result;
            /// MySQL table fields structure
            MYSQL_FIELD *fields;
            /// MySQL row data
            MYSQL_ROW row;

            /// Result fields count
            unsigned int fieldsCount;
    };

}

#endif // DBRESULT_H
