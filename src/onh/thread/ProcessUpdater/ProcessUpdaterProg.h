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

#ifndef PROCESSUPDATERPROG_H
#define PROCESSUPDATERPROG_H

#include "../../driver/ProcessUpdater.h"
#include "../../utils/Delay.h"
#include "../ThreadProgram.h"

namespace onh {

    /**
	 * Process data updater program class
	 */
    class ProcessUpdaterProg: public ThreadProgram {

        public:

            /**
             * Constructor
             *
             * @param pru Process updater
             * @param updateInterval Process update interval (milliseconds)
             * @param thEC Thread exit controller
             * @param thCCC Thread cycle time controller
             */
            ProcessUpdaterProg(const ProcessUpdater& pru,
            					unsigned int updateInterval,
								const ThreadExitController &thEC,
								const ThreadCycleContainerController &thCCC);

            /**
             * Copy constructor - inactive
             */
            ProcessUpdaterProg(const ProcessUpdaterProg&) = delete;

            virtual ~ProcessUpdaterProg();

            /**
			 * Thread program function
			 */
			virtual void operator()();

			/**
			 * Assignment operator - inactive
			 */
			ProcessUpdaterProg& operator=(const ProcessUpdaterProg&) = delete;

        private:

            /// Handle for process updater object
            ProcessUpdater* prUpdater;

            /// Timer delay object
            Delay* itsDelay;
    };
}

#endif // PROCESSUPDATERPROG_H
