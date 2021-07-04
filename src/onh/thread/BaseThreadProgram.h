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

#ifndef ONH_THREAD_BASETHREADPROGRAM_H_
#define ONH_THREAD_BASETHREADPROGRAM_H_

#include <memory>
#include "ThreadExitData.h"
#include "../utils/GuardDataController.h"
#include "../utils/logger/TextLogger.h"
#include "../utils/CycleTime.h"
#include "../utils/Delay.h"

namespace onh {

/**
 * Base Thread program class
 */
class BaseThreadProgram {
	public:
		/**
		 * Constructor
		 *
		 * @param gdcTED Thread exit data controller
		 * @param dirName Name of the directory where to write log files
		 * @param fPrefix Log file name prefix
		 * @param printLogMsg Flag prtints log init and destruct messages
		 */
		BaseThreadProgram(const GuardDataController<ThreadExitData> &gdcTED,
				const std::string& dirName,
				const std::string& fPrefix = "",
				bool printLogMsg = true);

		/**
		 * Copy constructor - inactive
		 */
		BaseThreadProgram(const BaseThreadProgram&) = delete;

		/**
		 * Destructor
		 */
		virtual ~BaseThreadProgram();

		/**
		 * Thread program function
		 */
		virtual void operator()() = 0;

		/**
		 * Assignment operator - inactive
		 */
		BaseThreadProgram& operator=(const BaseThreadProgram&) = delete;

	private:
		/// Flag prints log init and destruct messages
		bool printMsg;

		/// Thread exit data controller
		GuardDataController<ThreadExitData> thExitController;

		/// Logger object
		std::unique_ptr<ILogger> log;

	protected:
		/**
		 * Get Exit controller
		 *
		 * @return Exit data controller
		 */
		const GuardDataController<ThreadExitData>& getExitController() const;

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
		ILogger& getLogger();
};

}  // namespace onh

#endif  // ONH_THREAD_BASETHREADPROGRAM_H_
