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

#ifndef MODBUSDRIVER_H
#define MODBUSDRIVER_H

#include "../Driver.h"
#include "../../utils/MutexContainer.h"
#include "modbusmaster.h"
#include "ModbusProcessReader.h"
#include "ModbusProcessDataContainer.h"

namespace onh {

    /**
	 * Modbus driver class
	 */
    class ModbusDriver: public Driver {

        public:

            /**
             * ModbusDriver Constructor
             *
             * @param cfg Modbus configuration structure
             */
            ModbusDriver(const modbusM::ModbusCfg& cfg);

            /**
			 * Copy constructor - inactive
			 */
            ModbusDriver(const ModbusDriver&) = delete;

            virtual ~ModbusDriver();

            /**
			 * Assign operator - inactive
			 */
            ModbusDriver& operator=(const ModbusDriver&) = delete;

            /**
             * Update process data (copy from load buffer)
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
             * Write real in process data.
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

        private:
            /// Process registers count
            WORD regCount;

            /// Maximum Byte address
            unsigned int maxByteCount;

            // Modbus process data
            ModbusProcessDataContainer processDT;

            // Modbus process data buffer
            ModbusProcessData buff;
            MutexContainer bufferLock;

            /// Modbus Master protocol
            modbusM::ModbusMaster *modbus;
            MutexContainer modbusLock;

            /**
			 * Connect to the slave device
			 */
            void connect();

            /**
             * Trigger error (write log and throw exception)
             *
             * @param msg Exception message
             * @param fName Function from which exception was throwed
             */
            void triggerError(const std::string& msg, const std::string& fName);
    };

}

#endif // MODBUSDRIVER_H
