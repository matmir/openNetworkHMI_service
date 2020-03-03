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

#ifndef THREADEXITCONTROLLER_H
#define THREADEXITCONTROLLER_H

#include "../utils/MutexAccess.h"

namespace onh {

    /// Forward declaration
	class ThreadExit;

	/**
	 * Thread exit controller class
	 */
    class ThreadExitController {

        public:

            friend class ThreadExit;

            /**
             * Copy constructor
             *
             * @param tec ThreadExitController object to copy
             */
            ThreadExitController(const ThreadExitController& tec);

            virtual ~ThreadExitController();

            /**
             * Check if thread need to be closed
             */
            bool exitThread();

            /**
             * Trigger exit from thread
             *
             * @param info Additional info about exit
             */
            void exit(const std::string &info);

            /**
             * Set Socket file descriptor
             *
             * @param sockFD Socket file descriptor
             */
            void setSocketFD(int sockFD);

        private:
            /**
             * Default constructor (allowed only from ThreadExit)
             */
            ThreadExitController();

            /**
             * Constructor (allowed only from ThreadExit)
             *
             * @param mal MutexAccess object
             * @param exFromMain Exit from main program flag handle
             * @param exFromThread Exit from thread program flag handle
             * @param adInfo Additional info handle
             * @param sockFD Socket file descriptor handle
             */
            ThreadExitController(const MutexAccess &mal, bool *exFromMain, bool *exFromThread, std::string *adInfo, int *sockFD);

            /**
             * @brief	Assign operator
             */
            void operator=(const ThreadExitController&) {};

            /// Mutex for protecting data
            MutexAccess maLock;

            /// Exit flag triggered from main program
            bool *exitFromMain;

            /// Exit flag triggered from thread
            bool *exitFromThread;

            /// Additional information about exit
            std::string *additionalInfo;

            /// Socket file descriptor (for socket shutdown)
            int *socketFD;
    };

}

#endif // THREADEXITCONTROLLER_H
