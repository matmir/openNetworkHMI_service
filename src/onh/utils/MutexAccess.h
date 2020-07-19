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

#ifndef SRC_UTILS_MUTEXACCESS_H
#define SRC_UTILS_MUTEXACCESS_H

#include <mutex>
#include "Exception.h"

namespace onh {

    /// Forward declaration
	class MutexContainer;

    /**
	 * Mutex access class.
	 */
    class MutexAccess {

        friend class MutexContainer;

        public:

            MutexAccess();

            /**
             * Copy constructor
             *
             * @param ma MutexAccess object
             */
            MutexAccess(const MutexAccess& ma);

            virtual ~MutexAccess();

            /**
             * Lock mutex
             */
            void lock();

            /**
			 * Try to lock mutex
			 *
			 * @return True if locked
			 */
			bool tryLock();

            /**
             * Unlock mutex
             */
            void unlock();

            /**
             * Assign operator
             *
             * @param ma MutexAccess object
             *
             * @return MutexAccess
             */
            MutexAccess& operator=(const MutexAccess& ma);

        private:

            /**
             * Constructor (allowed only from MutexContainer)
             *
             * @param mcLock Mutex handle
             */
            MutexAccess(std::mutex* mcLock);

            /// Handle for mutex
            std::mutex* itsLock;
    };

}

#endif // SRC_UTILS_MUTEXACCESS_H
