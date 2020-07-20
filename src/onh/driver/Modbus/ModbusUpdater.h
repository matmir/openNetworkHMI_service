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

#ifndef MODBUSUPDATER_H
#define MODBUSUPDATER_H

#include "../DriverBuffer.h"
#include "../DriverException.h"
#include "modbusmaster.h"
#include "ModbusProcessData.h"
#include "../../utils/MutexAccess.h"

namespace onh {

    /// Forward declaration
	class ModbusDriver;

    /**
	 * Modbus updater class
	 */
    class ModbusUpdater: public DriverBuffer {

        public:

            friend class ModbusDriver;

            /**
			 * Copy constructor - inactive
			 */
			ModbusUpdater(const ModbusUpdater&) = delete;

            virtual ~ModbusUpdater();

            /**
			 * Assign operator - inactive
			 */
			ModbusUpdater& operator=(const ModbusUpdater&) = delete;

            /**
             * Update driver buffer (Get data from controller)
             */
            virtual void updateBuffer();

        private:

            /**
             * Constructor with parameters (allowed only from ModbusDriver)
             *
             * @param drv Driver instance
             * @param buffH Buffer structure
             * @param cnt Number of registers in buffer
             * @param driverL Driver Mutex locking structure
             * @param buffL Buffer Mutex locking structure
             */
            ModbusUpdater(modbusM::ModbusMaster* drv,
                             ModbusProcessData buffH,
                             WORD cnt,
                             const MutexAccess &malDriver,
                             const MutexAccess &malBuff);

            /**
             * Clear temporary registers
             */
            void clearTempRegisters();

            /**
             * Copy temporary registers to the buffer
             */
            void copyTempRegistersToBuffer();

            /// Driver instance
            modbusM::ModbusMaster* driver;
            MutexAccess driverLock;

            /// Modbus process data buffer structure
            ModbusProcessData buff;
            MutexAccess bufferLock;

            /// Modbus process data temporary buffer structure
            ModbusProcessData tempBuff;

            /// Register count to update
            WORD regCount;
    };

}
#endif // MODBUSUPDATER_H
