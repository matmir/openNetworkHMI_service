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

#ifndef ALARMINGPROG_H
#define ALARMINGPROG_H

#include "../../driver/ProcessReader.h"
#include "../../driver/ProcessWriter.h"
#include "../../utils/Delay.h"
#include "../../db/objs/AlarmDefinitionItem.h"
#include "../../db/AlarmingDB.h"
#include "../ThreadProgram.h"

namespace onh {

    class AlarmingProg: public ThreadProgram {

        public:

            /**
             * Constructor
             *
             * @param pr Process reader
             * @param pw Process writer
             * @param adb Alarming DB
             * @param updateInterval Alarm update interval (milliseconds)
             * @param thEC Thread exit controller
             * @param thCCC Thread cycle time controller
             */
            AlarmingProg(const ProcessReader& pr,
							const ProcessWriter& pw,
							const AlarmingDB& adb,
							unsigned int updateInterval,
							const ThreadExitController &thEC,
							const ThreadCycleContainerController &thCCC);

            /**
			 * Copy constructor - inactive
			 */
            AlarmingProg(const AlarmingProg&) = delete;

            virtual ~AlarmingProg();

            /**
			 * Thread program function
			 */
			virtual void operator()();

			/**
			 * Assignment operator - inactive
			 */
			AlarmingProg& operator=(const AlarmingProg&) = delete;

        private:

            /// Handle for process reader object
            ProcessReader* prReader;

            /// Handle for process writer object
            ProcessWriter* prWriter;

            /// Timer delay object
            Delay* itsDelay;

            /// Alarmin DB access
            AlarmingDB *db;

            /// Check alarms
            void checkAlarms();
    };

}

#endif // ALARMINGPROG_H
