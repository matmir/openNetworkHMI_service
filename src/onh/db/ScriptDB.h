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

#ifndef SCRIPTDB_H
#define SCRIPTDB_H

#include "objs/ScriptItem.h"
#include <vector>
#include "DB.h"

namespace onh {

    /// Forward declaration
	class DBManager;

    /**
	 * Class for read/write Script system DB
	 */
    class ScriptDB: public DB {

        public:

            friend class DBManager;

            /**
             * Copy constructor
             *
             * @param sDB ScriptDB to copy
             */
            ScriptDB(const ScriptDB &sDB);

            virtual ~ScriptDB();

            /**
			 * Assign operator - inactive
			 */
            ScriptDB& operator=(const ScriptDB&) = delete;

            /**
             * Get script items from DB
             *
             * @param enabled Get only enabled scripts
             *
             * @return Vector with Alarm definitions items
             */
            std::vector<ScriptItem> getScripts(bool enabled=true);

            /**
             * Set Script run
             *
             * @param script Script item object
             */
            void setScriptRun(const ScriptItem& script);

            /**
             * Clear script lock
             *
             * @param script Script item object
             */
            void clearScriptLock(const ScriptItem& script);

        private:

            /**
             * Constructor with connection param (allowed only from DBManager)
             *
             * @param connection Connection handle
             */
            ScriptDB(MYSQL *connDB);
    };

}

#endif // SCRIPTDB_H
