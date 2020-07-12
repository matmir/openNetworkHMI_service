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

#ifndef THREADSOCKET_H
#define THREADSOCKET_H

#include "ThreadExitController.h"
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
             * @param thEC Thread exit controller
             * @param dirName Name of the directory where to write log files
             * @param fPrefix Log file name prefix
             */
    		ThreadSocket(const ThreadExitController &thEC,
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

			/// Thread exit controller
			ThreadExitController *thExitControll;

			/// Logger object
			Logger* log;

        protected:

            /**
             * Check if thread need to be closed
             *
             * @return True if thread need to be closed
             */
            bool isExitFlag() const;

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

}

#endif // THREADSOCKET_H
