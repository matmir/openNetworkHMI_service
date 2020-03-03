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

#ifndef TAGLOGGERDB_H
#define TAGLOGGERDB_H

#include "objs/TagLoggerItem.h"
#include "../driver/DriverRegisterTypes.h"
#include <vector>
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
             * Get Tag logger items from DB
             *
             * @param enabled Get only enabled loggers
             *
             * @return Vector with Tag logger items
             */
            std::vector<TagLoggerItem> getLoggers(bool enabled=true);

            /**
			 * Write current tag value to the DB
			 *
			 * @param loggerItem Tag logger item object
			 */
			void logTag(const TagLoggerItem& loggerItem);

        private:
            /**
             * Default constructor (allowed only from DBManager)
             */
            TagLoggerDB();

            /**
             * Constructor with connection param (allowed only from DBManager)
             *
             * @param connection Connection handle
             */
            TagLoggerDB(MYSQL *connDB);

            /**
             * Assign operator
             */
            void operator=(const TagLoggerDB&) {};
    };

}

#endif // TAGLOGGERDB_H
