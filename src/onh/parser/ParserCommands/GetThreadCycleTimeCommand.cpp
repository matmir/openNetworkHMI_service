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

#include <sstream>
#include "GetThreadCycleTimeCommand.h"
#include "../CommandList.h"

namespace onh {

/// Thread name separator
const char TN = ':';
/// Time values separator
const char TS = '?';
/// Cycle time values separator
const char CS = '!';

GetThreadCycleTimeCommand::GetThreadCycleTimeCommand(const ThreadCycleControllers& tcc,
								const std::string& commandData):
	cycleController(tcc), data(commandData) {
}

std::string GetThreadCycleTimeCommand::execute() {
	// Check data string
	if (data.length() == 0)
		throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "GetThreadCycleTimeCommand::execute");

	if (data != "1")
		throw CommandParserException(CommandParserException::WRONG_DATA,
										"Wrong data",
										"GetThreadCycleTimeCommand::execute");

	// Cycle times structures
	CycleTimeData LoggerCT, LoggerWriterCT, AlarmingCT, ScriptCT, tmp;
	std::map<std::string, CycleTimeData> UpdaterCT, PollingCT;

	// Get cycle time of the updaters and buffers
	for (auto& cntr : cycleController) {
		// Updater?
		if (cntr.first.find("Updater_") != std::string::npos) {
			// Get cycle time
			cntr.second.getData(tmp);
			UpdaterCT.insert(std::pair<std::string, CycleTimeData>(cntr.first, tmp));
		}

		// Driver buffer?
		if (cntr.first.find("DriverBuffer_") != std::string::npos) {
			// Get cycle time
			cntr.second.getData(tmp);
			PollingCT.insert(std::pair<std::string, CycleTimeData>(cntr.first, tmp));
		}
	}

	// Get cycle times of the threads
	cycleController.at("TagLogger").getData(LoggerCT);
	cycleController.at("TagLoggerWriter").getData(LoggerWriterCT);
	cycleController.at("Alarming").getData(AlarmingCT);
	cycleController.at("Script").getData(ScriptCT);

	return prepareReply(LoggerCT, LoggerWriterCT, AlarmingCT, ScriptCT, UpdaterCT, PollingCT);
}

std::string GetThreadCycleTimeCommand::prepareReply(CycleTimeData tpcLogger,
													CycleTimeData tpcLoggerWriter,
													CycleTimeData tpcAlarming,
													CycleTimeData tpcScript,
													const std::map<std::string, CycleTimeData>& tpcUpdater,
													const std::map<std::string, CycleTimeData>& tpcPolling) {
	std::stringstream s;

	s << GET_THREAD_CYCLE_TIME << CMD_SEPARATOR;
	s << tpcUpdater.size() << TS << tpcPolling.size() << CS;
	for (const auto& updater : tpcUpdater) {
		s << updater.first << TN  << updater.second.min << TS << updater.second.max << TS << updater.second.current << CS;
	}
	for (const auto& polling : tpcPolling) {
		s << polling.first << TN  << polling.second.min << TS << polling.second.max << TS << polling.second.current << CS;
	}
	s << "Logger" << TN << tpcLogger.min << TS << tpcLogger.max << TS << tpcLogger.current << CS;
	s << "LoggerWriter" << TN << tpcLoggerWriter.min << TS << tpcLoggerWriter.max << TS << tpcLoggerWriter.current << CS;
	s << "Alarming" << TN << tpcAlarming.min << TS << tpcAlarming.max << TS << tpcAlarming.current << CS;
	s << "Script" << TN << tpcScript.min << TS << tpcScript.max << TS << tpcScript.current;

	return s.str();
}

}  // namespace onh
