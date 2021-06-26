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

#ifndef ONH_DB_DBRESULT_H_
#define ONH_DB_DBRESULT_H_

#include <mysql.h>
#include <string>
#include <memory>
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

		/**
		 * Copy constructor - inactive
		 */
		DBResult(const DBResult&) = delete;

		virtual ~DBResult();

		/**
		 * Assign operator - inactive
		 */
		DBResult& operator=(const DBResult&) = delete;

		/**
		 * Get string value from result
		 *
		 * @param fName Table field name
		 * @return DB data as string
		 */
		std::string getString(const std::string &fName) const;

		/**
		 * Get integer value from result
		 *
		 * @param fName Table field name
		 *
		 * @return DB data as integer
		 */
		int getInt(const std::string &fName) const;

		/**
		 * Get unsigned integer value from result
		 *
		 * @param fName Table field name
		 *
		 * @return DB data as unsigned integer
		 */
		unsigned int getUInt(const std::string &fName) const;

		/**
		 * Get unsigned long integer value from result
		 *
		 * @param fName Table field name
		 *
		 * @return DB data as unsigned long integer
		 */
		unsigned long int getUInt64(const std::string &fName) const;

		/**
		 * Get real value from result
		 *
		 * @param fName Table field name
		 *
		 * @return DB data as real
		 */
		float getReal(const std::string &fName) const;

		/**
		 * Check if field value in row is null
		 *
		 * @param fName Table field name
		 *
		 * @return True if data is NULL
		 */
		bool isNull(const std::string &fName) const;

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
		unsigned long int rowsCount() const;

	private:
		/**
		 * Default constructor (allowed only from DB)
		 *
		 * @param DBConn Connection handle
		 */
		explicit DBResult(MYSQL *DBConn);

		/**
		 * Get field name position in result
		 *
		 * @param fName Field name
		 *
		 * @return Field position
		 */
		unsigned int getFieldPos(const std::string &fName) const;

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

using DBResultPtr = std::unique_ptr<DBResult>;

}  // namespace onh

#endif  // ONH_DB_DBRESULT_H_
