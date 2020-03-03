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

#ifndef THREADPROGRAM_H
#define THREADPROGRAM_H

#include "ThreadController.h"
#include "../utils/Logger.h"
#include "../utils/CycleTime.h"

namespace onh {

	/**
	 * Thread program base class
	 */
    class ThreadProgram {

        public:
            /**
             * Constructor
             *
             * @param thContrl Thread controller handle
             * @param dirName Name of the directory where to write log files
             * @param fPrefix Log file name prefix
             */
            ThreadProgram(const ThreadController &thContrl, const std::string& dirName, const std::string& fPrefix = "");

            virtual ~ThreadProgram();

            /**
             * Run thread program
             */
            virtual void run() = 0;

        private:
            /// Thread program cycle time
            CycleTime* thCycle;

            /// Thread controller handle
			ThreadController* thControll;

			/// Logger object
			Logger* log;

        protected:

            /**
             * Start measure cycle time of the thread
             */
            void startCycleMeasure();

            /**
             * Stop measure cycle time of the thread
             */
            void stopCycleMeasure();

            /**
             * Get measure cycle time of the thread
             *
             * @return Cycle time data structure
             */
            CycleTimeData getCycleTime();

            /**
			 * Get thread controller instance
			 *
			 * @return ThreadController instance
			 */
            ThreadController& getThreadController();

            /**
			 * Get logger instance
			 *
			 * @return Logger instance
			 */
            Logger& getLogger();
    };

}

#endif // THREADPROGRAM_H
