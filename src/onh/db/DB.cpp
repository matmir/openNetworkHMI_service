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

#include "DB.h"
#include <sstream>

namespace onh {

DB::DB(MYSQL *connDB):
	conn(connDB) {
}

DB::DB(const DB &rhs):
	conn(rhs.conn) {
}

bool DB::checkStringValue(std::string val) {
	bool ret = true;
	char c = 0;

	for (unsigned int i=0; i < val.size(); ++i) {
		// Get one char
		c = val[i];

		// Allow only 0-9, A-Z, a-z, _
		if (!((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c == 95))) {
			// invalid character found
			ret = false;

			// stop the loop
			break;
		}
	}

	return ret;
}

DBResultPtr DB::executeQuery(const std::string &q) {
	if (!conn)
		throw DBException("Connection not initialized", "DB::executeQuery");

	// Query
	if (mysql_query(conn, q.c_str())) {
		std::stringstream s;
		s << "Error during query execute: " << mysql_error(conn);
		throw DBException(s.str(), "DB::executeQuery");
	}

	return DBResultPtr(new DBResult(conn));
}

void DB::executeSaveQuery(const std::string &q) {
	if (!conn)
		throw DBException("Connection not initialized", "DB::executeSaveQuery");

	// Query
	if (mysql_query(conn, q.c_str())) {
		std::stringstream s;
		s << "Error during query execute: " << mysql_error(conn);
		throw DBException(s.str(), "DB::executeSaveQuery");
	}
}

}  // namespace onh
