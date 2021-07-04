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

#include "BaseThreadProgram.h"
#include "../utils/GuardDataController.h"

namespace onh {

/**
 * Thread socket base class
 */
class ThreadSocket: public BaseThreadProgram {
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
		 * Assignment operator - inactive
		 */
		ThreadSocket& operator=(const ThreadSocket&) = delete;

	private:
		/// Socket file descriptor controller
		GuardDataController<int> thSockDecsController;

	protected:
		/**
		 * Set Socket file descriptor
		 *
		 * @param sockFD Socket file descriptor
		 */
		void setSocketFD(int sockFD);
};

}  // namespace onh

#endif  // ONH_THREAD_THREADSOCKET_H_
