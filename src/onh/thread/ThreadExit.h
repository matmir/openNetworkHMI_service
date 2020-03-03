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

#ifndef THREADEXIT_H
#define THREADEXIT_H

#include <string>
#include "../utils/MutexContainer.h"
#include "ThreadExitController.h"

namespace onh {

    /**
     * Thread exit class
     */
    class ThreadExit {

        public:

            ThreadExit();
            virtual ~ThreadExit();

            /**
             * Trigger exit
             */
            void exit();

            /**
             * Get exit information
             *
             * @return Additional information about exit
             */
            std::string getExitInfo();

            /**
             * Get exit controller object
             *
             * @return Exit controller object
             */
            ThreadExitController getExitController();

            /**
             * Get socket file descriptor
             *
             * @return Socket file descriptor
             */
            int getSocketFD();

        private:
            /**
             * Copy constructor
             */
            ThreadExit(const ThreadExit&) {};

            /**
             * Assign operator
             */
            void operator=(const ThreadExit&) {};

            /// Mutex for protecting data
            MutexContainer teLock;

            /// Exit flag triggered from main program
            bool exitFromMain;

            /// Exit flag triggered from thread
            bool exitFromThread;

            /// Additional information about exit
            std::string additionalInfo;

            /// Socket file descriptor (for shutdown socket)
            int socketFD;
    };

}

#endif // THREADEXIT_H
