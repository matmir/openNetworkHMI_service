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

#ifndef DRIVERBUFFERUPDATER_H
#define DRIVERBUFFERUPDATER_H

#include "DriverBuffer.h"

namespace onh {

    /// Forward declaration
	class ProcessManager;

    /**
	 * Controller buffer updater class
	 */
    class DriverBufferUpdater {

        public:

            friend class ProcessManager;

            /**
             * Copy constructor
             *
             * @param dbu DriverBufferUpdater to copy
             */
            DriverBufferUpdater(const DriverBufferUpdater &dbu);

            virtual ~DriverBufferUpdater();

            /**
             * Update driver buffer
             */
            void update();

        private:
            /**
             * Default constructor (allowed only from ProcessManager)
             */
            DriverBufferUpdater();

            /**
             * Constructor with parameters (allowed only from ProcessManager)
             *
             * @param dbh Driver buffer handle
             */
            DriverBufferUpdater(DriverBuffer *dbh);

            /// Driver buffer handle
            DriverBuffer *drvBuffer;

    };

}

#endif // DRIVERBUFFERUPDATER_H
