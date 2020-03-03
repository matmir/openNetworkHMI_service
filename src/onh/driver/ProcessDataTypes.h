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

#ifndef ONH_DRIVER_PROCESSDATATYPES_H_
#define ONH_DRIVER_PROCESSDATATYPES_H_

namespace onh {

    /**
	 * Driver process data areas
	 */
    typedef enum {
        PDA_INPUT = 1,
        PDA_OUTPUT = 2,
        PDA_MEMORY = 3
    } processDataArea;

    /**
	 * Structure of the process data address
	 */
    typedef struct {
        /// Process data area
        processDataArea area;
        /// Process data byte address
        unsigned int byteAddr;
        /// Process data bit address
        unsigned int bitAddr;
    } processDataAddress;

}

#endif /* ONH_DRIVER_PROCESSDATATYPES_H_ */
