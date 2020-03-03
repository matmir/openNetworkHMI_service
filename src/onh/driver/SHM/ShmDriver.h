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

#ifndef SRC_DRIVER_KSHMDRIVER_H_
#define SRC_DRIVER_KSHMDRIVER_H_

#include "../Driver.h"
#include "../../utils/MutexContainer.h"
#include "ShmProcessReader.h"
#include "ShmProcessDataContainer.h"
#include "sMemory.h"
#include "processData.h"

namespace onh {

	/**
	 * Shared memory client class
	 */
	class ShmDriver: public Driver {

        public:
            /**
             * Default Shared memory client constructor
             *
             * @param segmentName Shared memory segment name
             */
            ShmDriver(const std::string& segmentName);

            virtual ~ShmDriver();

            /**
             * Update process data (copy from shared memory)
             */
            virtual void updateProcessData();

            /**
             * Set bit in process data
             *
             * @param addr Process data address
             */
            virtual void setBit(processDataAddress addr);

            /**
             * Reset bit in process data
             *
             * @param addr Process data address
             */
            virtual void resetBit(processDataAddress addr);

            /**
             * Invert bit in process data
             *
             * @param addr Process data address
             */
            virtual void invertBit(processDataAddress addr);

            /**
             * Set bits in process data
             *
             * @param addr Process data address
             */
            virtual void setBits(std::vector<processDataAddress> addr);

            /**
             * Write byte in process data
             *
             * @param addr Process data address
             * @param val Value to write
             */
            virtual void writeByte(processDataAddress addr, BYTE val);

            /**
             * Write word in process data
             *
             * @param addr Process data address
             * @param val Value to write
             */
            virtual void writeWord(processDataAddress addr, WORD val);

            /**
             * Write double word in process data
             *
             * @param addr Process data address
             * @param val Value to write
             */
            virtual void writeDWord(processDataAddress addr, DWORD val);

            /**
             * Write int in process data
             *
             * @param addr Process data address
             * @param val Value to write
             */
            virtual void writeInt(processDataAddress addr, int val);

            /**
             * Write real in process data
             *
             * @param addr Process data address
             * @param val Value to write
             */
            virtual void writeReal(processDataAddress addr, float val);

            /**
             * Get driver buffer handle
             *
             * @return Driver buffer handle
             */
            virtual DriverBuffer* getBuffer();

            /**
			 * Get driver process data reader
			 *
			 * @return Driver process data reader handle
			 */
			virtual DriverProcessReader* getReader();

            /**
			 * Send exit command to the server
			 */
            void sendServerExitCommand();

        private:

            /// Shared memory id
			int sfd;

			/// Shared memory size
            const int smSize = sizeof(sMemory);

            /// Shared memory structure
            sMemory *shm;

            /// Shared memory segment name
            std::string shmName;

            /// Copy of the controller process data
            ShmProcessDataContainer process;

            /**
             * Puts a request to server
             *
             * @param cmd The command
             *
             * @return Server reply command
             */
            extCMD putRequest(extCMD cmd);

            /**
			 * Clear process data
			 */
			void clearProcessData();

            /**
             * Modify bit in process memory
             *
             * @param addr The command
             * @param drvFunc Bit function
             */
            void modifyBit(processDataAddress addr, int drvFunc);

            /**
             * Trigger error (write log and throw exception)
             *
             * @param msg Exception message
             * @param fName Function from which exception was throwed
             */
            void triggerError(const std::string& msg, const std::string& fName);
	};

}

#endif /* SRC_DRIVER_KSHMDRIVER_H_ */
