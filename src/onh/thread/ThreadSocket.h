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

#ifndef ONH_THREAD_THREADSOCKET_H_
#define ONH_THREAD_THREADSOCKET_H_

#include <memory>
#include "ThreadExitData.h"
#include "../utils/GuardDataController.h"
#include "../utils/Logger.h"

namespace onh {

/**
 * Thread socket base class
 */
class ThreadSocket {
	public:
		/**
		 * Constructor
		 *
		 * @param gdcTED Thread exit data controller
		 * @param gdcSockDesc Socket file descriptor controller
		 * @param dirName Name of the directory where to write log files
		 * @param fPrefix Log file name prefix
		 */
		ThreadSocket(const GuardDataController<ThreadExitData> &gdcTED,
						const GuardDataController<int> &gdcSockDesc,
						const std::string& dirName,
						const std::string& fPrefix = "");

		/**
		 * Copy constructor - inactive
		 */
		ThreadSocket(const ThreadSocket&) = delete;

		/**
		 * Destructor
		 */
		virtual ~ThreadSocket();

		/**
		 * Thread program function
		 */
		virtual void operator()() = 0;

		/**
		 * Assignment operator - inactive
		 */
		ThreadSocket& operator=(const ThreadSocket&) = delete;

	private:
		/// Thread exit data controller
		GuardDataController<ThreadExitData> thExitController;

		/// Socket file descriptor controller
		GuardDataController<int> thSockDecsController;

		/// Logger object
		std::unique_ptr<Logger> log;

	protected:
		/**
		 * Get Exit controller
		 *
		 * @return Exit data controller
		 */
		const GuardDataController<ThreadExitData>& getExitController();

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
		 * Set Socket file descriptor
		 *
		 * @param sockFD Socket file descriptor
		 */
		void setSocketFD(int sockFD);

		/**
		 * Get logger instance
		 *
		 * @return Logger instance
		 */
		Logger& getLogger();
};

}  // namespace onh

#endif  // ONH_THREAD_THREADSOCKET_H_
