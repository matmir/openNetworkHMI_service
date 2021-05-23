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

#ifndef ONH_DB_TAGLOGGERDB_H_
#define ONH_DB_TAGLOGGERDB_H_

#include <vector>
#include "objs/TagLoggerItem.h"
#include "../driver/DriverRegisterTypes.h"
#include "DB.h"

namespace onh {

/// Forward declaration
class DBManager;

/**
 * Class for read/write Tag logger
 */
class TagLoggerDB: public DB {
	public:
		friend class DBManager;

		/**
		 * Copy constructor
		 *
		 * @param tlDB TagLoggerDB to copy
		 */
		TagLoggerDB(const TagLoggerDB &tlDB);

		virtual ~TagLoggerDB();

		/**
		 * Assign operator - inactive
		 */
		TagLoggerDB& operator=(const TagLoggerDB&) = delete;

		/**
		 * Get Tag logger items from DB
		 *
		 * @param enabled Get only enabled loggers
		 *
		 * @return Vector with Tag logger items
		 */
		std::vector<TagLoggerItem> getLoggers(bool enabled = true);

		/**
		 * Write current tag value to the DB
		 *
		 * @param loggerItem Tag logger item object
		 */
		void logTag(const TagLoggerItem& loggerItem);

	private:
		/**
		 * Constructor with connection param (allowed only from DBManager)
		 *
		 * @param connection Connection handle
		 */
		explicit TagLoggerDB(MYSQL *connDB);
};

}  // namespace onh

#endif  // ONH_DB_TAGLOGGERDB_H_
