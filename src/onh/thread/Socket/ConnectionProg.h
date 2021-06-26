/**
 * This file is part of openNetworkHMI.
 * Copyright (c) 2021 Mateusz Mirosławski.
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

#ifndef ONH_THREAD_SOCKET_CONNECTIONPROG_H_
#define ONH_THREAD_SOCKET_CONNECTIONPROG_H_

#include "../../driver/ProcessReader.h"
#include "../../driver/ProcessWriter.h"
#include "../../thread/ThreadCycleControllers.h"
#include "../BaseThreadProgram.h"
#include "../../utils/GuardDataController.h"
#include "../../db/DBCredentials.h"
#include "../../utils/Logger.h"
#include "Parser/CommandParser.h"

namespace onh {

/**
 * Socket connection class
 */
class ConnectionProgram: public BaseThreadProgram {
	public:
		/**
		 * Constructor
		 *
		 * @param connDescriptor Connection file descriptor
		 * @param pr Process reader
		 * @param pw Process writer
		 * @param cc Cycle time controllers
		 * @param db Database credentials
		 * @param gdcTED Thread exit controller
		 */
		ConnectionProgram(int connDescriptor,
							const ProcessReader& pr,
							const ProcessWriter& pw,
							const ThreadCycleControllers& cc,
							const DBCredentials& db,
							const GuardDataController<ThreadExitData> &gdcTED);

		/**
		 * Copy constructor
		 *
		 * @param rhs Object to copy
		 */
		ConnectionProgram(const ConnectionProgram& rhs);

		/**
		 * Destructor
		 */
		virtual ~ConnectionProgram();

		/**
		 * Thread program function
		 */
		void operator()() override;

		/**
		 * Assignment operator - inactive
		 */
		ConnectionProgram& operator=(const ConnectionProgram&) = delete;

	private:
		/// Connection file descriptor
		int connDesc;

		/// Process reader
		std::unique_ptr<ProcessReader> pReader;

		/// Process writer
		std::unique_ptr<ProcessWriter> pWriter;

		/// DB credentials
		DBCredentials dbCredentials;

		/// Cycle controllers
		ThreadCycleControllers cycleController;

		/// Command parser
		std::unique_ptr<CommandParser> parser;
};

}  // namespace onh

#endif  // ONH_THREAD_SOCKET_CONNECTIONPROG_H_
