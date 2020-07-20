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

#ifndef PROCESSWRITER_H
#define PROCESSWRITER_H

#include <vector>
#include "ProcessUtils.h"
#include "Driver.h"
#include "../utils/MutexAccess.h"
#include "../db/objs/Tag.h"

namespace onh {

    /// Forward declaration
	class ProcessManager;

	/**
	 * Process writer class
	 */
    class ProcessWriter {

        public:

            friend class ProcessManager;

            /**
             * Copy constructor
             *
             * @param pw ProcessWriter object to copy
             */
            ProcessWriter(const ProcessWriter &pw);

            virtual ~ProcessWriter();

            /**
			 * Assign operator - inactive
			 */
            ProcessWriter& operator=(const ProcessWriter &pw) = delete;

            /**
             * Set bit in process data
             *
             * @param tg Tag object
             */
            void setBit(const Tag& tg);

            /**
             * Reset bit in process data
             *
             * @param tg Tag object
             */
            void resetBit(const Tag& tg);

            /**
             * Invert bit in process data
             *
             * @param tg Tag object
             */
            void invertBit(const Tag& tg);

            /**
             * Set bits in process data
             *
             * @param tg tags Tags array
             */
            void setBits(const std::vector<Tag>& tags);

            /**
             * Write byte in process data
             *
             * @param tg Tag object
             * @param val Byte value
             */
            void writeByte(const Tag& tg, BYTE val);

            /**
             * Write word in process data
             *
             * @param tg Tag object
             * @param val Word value
             */
            void writeWord(const Tag& tg, WORD val);

            /**
             * Write double word in process data
             *
             * @param tg Tag object
             * @param val Double word value
             */
            void writeDWord(const Tag& tg, DWORD val);

            /**
             * Write INT in process data
             *
             * @param tg Tag object
             * @param val INT value
             */
            void writeInt(const Tag& tg, int val);

            /**
             * Write Real in process data.
             *
             * @param tg Tag object
             * @param val Real value
             */
            void writeReal(const Tag& tg, float val);

        private:

            /**
             * Constructor with parameters (allowed only from ProcessManager)
             *
             * @param drv Driver instance
             * @param lock Mutex access
             */
            ProcessWriter(Driver* drv, const MutexAccess& lock);

            /// Driver instance
			Driver* driver;

			/// Mutex for protecting driver
			MutexAccess driverLock;
    };

}

#endif // PROCESSWRITER_H
