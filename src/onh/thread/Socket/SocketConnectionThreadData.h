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

#ifndef SRC_ONH_THREAD_SOCKET_SOCKETCONNECTIONTHREADDATA_H_
#define SRC_ONH_THREAD_SOCKET_SOCKETCONNECTIONTHREADDATA_H_

#include "SocketThreadData.h"

namespace onh {

	/**
	 * Socket connection thread data structure
	 */
	typedef struct {

		/// Socket connection descriptor
		int connDescriptor;

		/// Socket thread data
		SocketThreadData sockThDT;

	} SocketConnectionThreadData;

}

#endif /* SRC_ONH_THREAD_SOCKET_SOCKETCONNECTIONTHREADDATA_H_ */
