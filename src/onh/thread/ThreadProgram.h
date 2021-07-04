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

#ifndef ONH_THREAD_THREADPROGRAM_H_
#define ONH_THREAD_THREADPROGRAM_H_

#include "BaseThreadProgram.h"
#include "../utils/GuardDataController.h"
#include "../utils/CycleTime.h"
#include "../utils/Delay.h"

namespace onh {

/**
 * Thread program base class
 */
class ThreadProgram: public BaseThreadProgram {
	public:
		/**
		 * Constructor
		 *
		 * @param gdcTED Thread exit data controller
		 * @param thCCC Thread cycle time controller
		 * @param updateInterval Thread wait time (ms)
		 * @param dirName Name of the directory where to write log files
		 * @param fPrefix Log file name prefix
		 */
		ThreadProgram(const GuardDataController<ThreadExitData> &gdcTED,
				const GuardDataController<CycleTimeData> &gdcCTD,
				unsigned int updateInterval,
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
		 * Assignment operator - inactive
		 */
		ThreadProgram& operator=(const ThreadProgram&) = delete;

	private:
		/// Thread program cycle time
		CycleTime thCycle;

		/// Timer delay object
		Delay thDelay;

		/// Thread cycle time data controller
		GuardDataController<CycleTimeData> thCycleTimeController;

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
		 * Thread wait
		 */
		void threadWait();

		/**
		 * Thread wait (no blocking)
		 */
		void threadWaitStart();

		/**
		 * Thread wait after start called (blocking)
		 */
		void threadWaitAfterStart();
};

}  // namespace onh

#endif  // ONH_THREAD_THREADPROGRAM_H_
