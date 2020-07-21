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

#ifndef ALARMINGDB_H
#define ALARMINGDB_H

#include "objs/AlarmDefinitionItem.h"
#include <vector>
#include "DB.h"

namespace onh {

    /// Forward declaration
	class DBManager;

	/// Forward declaration
	class ParserDB;

    /**
	 * Class for read/write Alarm system DB
	 */
    class AlarmingDB: public DB {

        public:

            friend class DBManager;
            friend class ParserDB;

            /**
             * Copy constructor
             *
             * @param aDB AlarmDB object to copy
             */
            AlarmingDB(const AlarmingDB &aDB);

            virtual ~AlarmingDB();

            /**
			 * Assign operator - inactive
			 */
            AlarmingDB& operator=(const AlarmingDB&) = delete;

            /**
             * Get Alarm definition items from DB
             *
             * @param enabled Get only enabled alarm definitions
             *
             * @return Vector with Alarm definitions items
             */
            std::vector<AlarmDefinitionItem> getAlarms(bool enabled=true);

            /**
             * Set Alarm (put into pending table)
             *
             * @param alarm Alarm definition item object
             */
            void setAlarm(const AlarmDefinitionItem& alarm);

            /**
             * Update alarm state (active/inactive)
             *
             * @param alarm Alarm definition item object
             * @param state Alarm state
             */
            void updateAlarmState(const AlarmDefinitionItem& alarm, bool state);

            /**
             * Acknowledge pending alarm (apadid) or all pending alarms.
             *
             * @param apadid Alarm definition identifier (alarm to acknowledge)
             */
            void ackAlarm(unsigned int apadid=0);

        private:

            /**
             * Constructor with connection param (allowed only from DBManager)
             *
             * @param connection Connection handle
             */
            AlarmingDB(MYSQL *connDB);
    };

}

#endif // ALARMINGDB_H
