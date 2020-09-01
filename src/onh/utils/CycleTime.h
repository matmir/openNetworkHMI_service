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

#ifndef ONH_UTILS_CYCLETIME_H
#define ONH_UTILS_CYCLETIME_H

#include <time.h>
#include <string>

namespace onh {

    /**
     * Cycle time data structure
     */
    typedef struct CycleTimeData {
        /// Minimum cycle time (ms) of the program
        double min;
        /// Maximum cycle time (ms) of the program
        double max;
        /// Current cycle time (ms) of the program
        double current;

        CycleTimeData(): min(0), max(0), current(0) {}
    } CycleTimeData;

    /**
     * Cycle time class
     */
    class CycleTime {

        public:

    		/**
    		 * Constructor
    		 */
            CycleTime();

            /**
             * Copy constructor - inactive
             */
            CycleTime(const CycleTime&) = delete;

            virtual ~CycleTime();

            /**
			 * Assign operator - inactive
			 */
            CycleTime& operator=(const CycleTime&) = delete;

            /**
             * Start measuring cycle time
             */
            void start();

            /**
             * Stop measuring cycle time
             */
            void stop();

            /**
             * Get measured cycle time
             *
             * @return Measured cycle time
             */
            CycleTimeData getCycle() const;

        private:

            /// Cycle time
            CycleTimeData cycle;

            /// First cycle flag
            bool firstCycle;

            /// Start time of the cycle
            struct timespec cycleStart;
            /// Stop time of the cycle
            struct timespec cycleStop;
    };

}

#endif // ONH_UTILS_CYCLETIME_H
