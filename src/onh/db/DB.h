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

#ifndef ONH_DB_DB_H_
#define ONH_DB_DB_H_

#include <mysql.h>
#include <string>
#include "DBResult.h"

namespace onh {

/**
 * Database access base class
 */
class DB {
	public:
		/**
		 * DB constructor
		 *
		 * @param connection DB handle
		 */
		explicit DB(MYSQL *connDB);

		/**
		 * Check string vale if contain invalid characters
		 *
		 * @param val String value
		 * @return True if string is valid
		 */
		static bool checkStringValue(std::string val);

		virtual ~DB() = default;

		/**
		 * Assign operator - inactive
		 */
		DB& operator=(const DB&) = delete;

	protected:
		/**
		 * Copy constructor
		 *
		 * @param rhs DB object to copy
		 */
		DB(const DB &rhs);

		/**
		 * Execute read query to the DB
		 *
		 * @param q SQL query
		 *
		 * @return Handle for DBResult object
		 */
		DBResultPtr executeQuery(const std::string &q);

		/**
		 * Execute save query to the DB
		 *
		 * @param q SQL query
		 */
		void executeSaveQuery(const std::string &q);

		/// DB connection instance
		MYSQL *conn;
};

}  // namespace onh

#endif  // ONH_DB_DB_H_
