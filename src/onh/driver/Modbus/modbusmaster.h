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

#ifndef MODBUSMASTER_H
#define MODBUSMASTER_H

#include <string.h>
#include <sys/types.h>
#include <modbus.h>

#include "modbusmasterCfg.h"
#include "modbusexception.h"
#include "../DriverRegisterTypes.h"

namespace modbusM {

    /**
     * ModbusMaster class
     */
    class ModbusMaster {

        public:
    		/**
    		 * Constructor
    		 *
    		 * @param cfg Modbus configuration structure
    		 */
            ModbusMaster(const ModbusCfg& cfg);

            /**
			 * Copy constructor - inactive
			 */
            ModbusMaster(const ModbusMaster&) = delete;

            ~ModbusMaster();

            /**
			 * Assign operator - inactive
			 */
            ModbusMaster& operator=(const ModbusMaster&) = delete;

            /**
             * Connect to the slave
             *
             * @return True if connected
             */
            void connect();

            /**
             * Disconnect from slave
             */
            void disconnect();

            /**
             * Read input registers from controller
             *
             * @param regAddress Register start address
             * @param quantity Number of registers to read
             * @param buff Buffer on register values
             */
            void READ_INPUT_REGISTERS(WORD regAddress, WORD quantity, WORD *buff);

            /**
             * Read holding registers from controller
             *
             * @param regAddress Register start address
             * @param quantity Number of registers to read
             * @param buff Buffer on register values
             */
            void READ_HOLDING_REGISTERS(WORD regAddress, WORD quantity, WORD *buff);

            /**
             * Write single holding register in controller
             *
             * @param regAddress Register start address
             * @param value Register value
             */
            void WRITE_SINGLE_REGISTER(WORD regAddress, WORD value);

            /**
             * Write multiple holding registers in controller
             *
             * @param regAddress Register start address
             * @param quantity Number of registers to write
             * @param values Buffer with register values
             */
            void WRITE_MULTIPLE_REGISTERS(WORD regAddress, WORD quantity, WORD *values);

        private:

            /// Modbus communication structure
            modbus_t *mb;

            /// Modbus configuration structure
            ModbusCfg config;
    };

}

#endif // MODBUSMASTER_H
