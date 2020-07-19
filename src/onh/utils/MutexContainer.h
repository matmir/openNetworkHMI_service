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

#ifndef ONH_UTILS_MUTEXCONTAINER_H
#define ONH_UTILS_MUTEXCONTAINER_H

#include <mutex>
#include "Exception.h"
#include "MutexAccess.h"

namespace onh {

    /**
	 * Mutex container class.
	 */
    class MutexContainer {

        public:

            MutexContainer();

            /**
			 * Copy constructor - inactive
			 */
			MutexContainer(const MutexContainer&) = delete;

            virtual ~MutexContainer();

            /**
			 * Assign operator - inactive
			 */
			void operator=(const MutexContainer&) = delete;

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
             * Get MutexAccess object
             *
             * @return MutexAccess object
             */
            MutexAccess getAccess();

        private:

            /// Mutex
            std::mutex itsLock;
    };

}

#endif // ONH_UTILS_MUTEXCONTAINER_H
