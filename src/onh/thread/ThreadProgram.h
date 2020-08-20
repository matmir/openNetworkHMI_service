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

#include "ThreadExitData.h"
#include "../utils/GuardDataController.h"
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
             * @param gdcTED Thread exit data controller
             * @param thCCC Thread cycle time controller
             * @param dirName Name of the directory where to write log files
             * @param fPrefix Log file name prefix
             */
            ThreadProgram(const GuardDataController<ThreadExitData> &gdcTED,
            		const GuardDataController<CycleTimeData> &gdcCTD,
            		const std::string& dirName,
					const std::string& fPrefix = "");

            /**
             * Copy constructor - inactive
             */
            ThreadProgram(const ThreadProgram&) = delete;

            /**
             * Destructor
             */
            virtual ~ThreadProgram();

            /**
             * Thread program function
             */
            virtual void operator()() = 0;

            /**
             * Assignment operator - inactive
             */
            ThreadProgram& operator=(const ThreadProgram&) = delete;

        private:
            /// Thread program cycle time
            CycleTime* thCycle;

			/// Thread exit data controller
            GuardDataController<ThreadExitData> thExitController;

			/// Thread cycle time data controller
			GuardDataController<CycleTimeData> thCycleTimeController;

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
             * Check if thread need to be closed
             *
             * @return True if thread need to be closed
             */
            bool isExitFlag();

            /**
             * Trigger exit from thread
             *
             * @param info Additional info about exit
             */
            void exit(const std::string& info);

            /**
			 * Get logger instance
			 *
			 * @return Logger instance
			 */
            Logger& getLogger();
    };

}

#endif // THREADPROGRAM_H
