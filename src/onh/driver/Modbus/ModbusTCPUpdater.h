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

#ifndef MODBUSTCPUPDATER_H
#define MODBUSTCPUPDATER_H

#include "../DriverBuffer.h"
#include "../DriverException.h"
#include "modbustcpmaster.h"
#include "ModbusTCPProcessData.h"
#include "../../utils/MutexAccess.h"

namespace onh {

    /// Forward declaration
	class ModbusTCP;

    /**
	 * Modbus TCP updater class
	 */
    class ModbusTCPUpdater: public DriverBuffer {

        public:

            friend class ModbusTCP;

            virtual ~ModbusTCPUpdater();

            /**
             * Update driver buffer (Get data from controller)
             */
            virtual void updateBuffer();

        private:
            /**
             * Default constructor (allowed only from ModbusTCP)
             */
            ModbusTCPUpdater();

            /**
             * Copy constructor (allowed only from ModbusTCP)
             *
             * @param mtu ModbusTCPUpdater object
             */
            ModbusTCPUpdater(const ModbusTCPUpdater &mtu);

            /**
             * Constructor with parameters (allowed only from ModbusTCP)
             *
             * @param drv Driver instance
             * @param buffH Buffer structure
             * @param cnt Number of registers in buffer
             * @param driverL Driver Mutex locking structure
             * @param buffL Buffer Mutex locking structure
             */
            ModbusTCPUpdater(modbusTCP::ModbusTCPMaster* drv,
                             ModbusTCPProcessData buffH,
                             WORD cnt,
                             const MutexAccess &malDriver,
                             const MutexAccess &malBuff);

            /**
             * Assign operator (allowed only from ModbusTCP)
             *
             * @param mtu ModbusTCPUpdater object
             */
            ModbusTCPUpdater& operator=(const ModbusTCPUpdater &mtu);

            /**
             * Clear temporary registers
             */
            void clearTempRegisters();

            /**
             * Copy temporary registers to the buffer
             */
            void copyTempRegistersToBuffer();

            /// Driver instance
            modbusTCP::ModbusTCPMaster* driver;
            MutexAccess driverLock;

            /// Modbus process data buffer structure
            ModbusTCPProcessData buff;
            MutexAccess bufferLock;

            /// Modbus process data temporary buffer structure
            ModbusTCPProcessData tempBuff;

            /// Register count to update
            WORD regCount;
    };

}
#endif // MODBUSTCPUPDATER_H
