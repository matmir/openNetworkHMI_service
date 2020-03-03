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

#ifndef SRC_ONH_THREAD_SOCKET_SOCKETEXCEPTION_H_
#define SRC_ONH_THREAD_SOCKET_SOCKETEXCEPTION_H_

#include "../../utils/Exception.h"

namespace onh {

	/**
	 * Socket exception class
	 */
	class SocketException: public Exception {

		public:

			SocketException();

			/**
			 * Exception constructor with message
			 *
			 * @param desc Exception error
			 */
			SocketException(const std::string& desc);

			/**
			 * Exception constructor with message and function name
			 *
			 * @param desc Exception error
			 * @param fName Function from which exception was throwed
			 */
			SocketException(const std::string& desc, const std::string& fName);

			/**
			 * Exception constructor with message, errno and function name
			 *
			 * @param desc Exception error
			 * @param errorNumber errno value
			 * @param fName Function from which exception was throwed
			 */
			SocketException(const std::string& desc, int errorNumber, const std::string& fName);

			virtual ~SocketException();
	};

}

#endif /* SRC_ONH_THREAD_SOCKET_SOCKETEXCEPTION_H_ */
