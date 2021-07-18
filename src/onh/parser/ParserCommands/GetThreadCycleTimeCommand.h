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

#ifndef ONH_PARSER_PARSERCOMMANDS_GETTHREADCYCLETIMECOMMAND_H_
#define ONH_PARSER_PARSERCOMMANDS_GETTHREADCYCLETIMECOMMAND_H_

#include "../IParserCommand.h"
#include "../CommandParserException.h"
#include "../../thread/ThreadCycleControllers.h"

namespace onh {

/**
 * Parser GET_THREAD_CYCLE_TIME command
 */
class GetThreadCycleTimeCommand: public IParserCommand {
	public:
		/**
		 * GET_THREAD_CYCLE_TIME command constructor
		 *
		 * @param tcc Thread cycle controllers
		 * @param commandData String with command data
		 */
		GetThreadCycleTimeCommand(const ThreadCycleControllers& tcc,
						const std::string& commandData);

		/**
		 * Command Destructor
		 */
		virtual ~GetThreadCycleTimeCommand() = default;

		/**
		 * Execute parser command and get reply
		 *
		 * @return String with reply
		 */
		std::string execute() override;

	private:
		/// Thread cycle controllers
		ThreadCycleControllers cycleController;
		/// command data
		const std::string data;

		/**
		 * Prepare reply - OK
		 *
		 * @param tpcLogger Cycle time of the Tag logger thread
		 * @param tpcLoggerWriter Cycle time of the Tag logger writer thread
		 * @param tpcAlarming Cycle time of the Alarming thread
		 * @param tpcScript Cycle time of the Script system thread
		 * @param tpcUpdater Cycle time of the Process updater threads
		 * @param tpcPolling Cycle time of the Driver polling threads
		 *
		 * @return String with reply
		 */
		std::string prepareReply(CycleTimeData tpcLogger,
									CycleTimeData tpcLoggerWriter,
									CycleTimeData tpcAlarming,
									CycleTimeData tpcScript,
									const std::map<std::string, CycleTimeData>& tpcUpdater,
									const std::map<std::string, CycleTimeData>& tpcPolling);
};

}  // namespace onh

#endif  // ONH_PARSER_PARSERCOMMANDS_GETTHREADCYCLETIMECOMMAND_H_
