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

#ifndef SOCKETPROGRAM_H
#define SOCKETPROGRAM_H

#define THREADS_POOL 20

#include <pthread.h>
#include "Socket.h"
#include "../ThreadProgram.h"

namespace onh {

    /**
	 * Socket program class
	 */
    class SocketProgram: public ThreadProgram {

        public:
            /**
             * Constructor
             *
             * @param thData Socket thread data structure
             */
    		SocketProgram(const SocketThreadData &thData);

            virtual ~SocketProgram();

            /**
             * Run socket program
             */
            void run();

        private:

            /// Socket thread data
            SocketThreadData socketThData;

            /// Socket object
            Socket *sock;

            /// Connection threads pool
            pthread_t tConn[THREADS_POOL];

            /// Connection threads counter
            int thCounter;

            /**
             * Create connection thread
             *
             * @param connFD Connection file descriptor
             */
            void createConnectionThread(int connFD);

            /**
             * Wait on threads
             */
            void waitOnThreads();
    };

}

#endif // SOCKETPROGRAM_H
