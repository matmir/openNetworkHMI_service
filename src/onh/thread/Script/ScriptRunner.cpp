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

#include "ScriptRunner.h"
#include <stdlib.h>
#include <chrono>
#include <sstream>
#include <fstream>

namespace onh {

ScriptRunner::ScriptRunner(const std::string &scriptPath, const std::string &scriptOutputLogName):
	script(scriptPath),
	scriptLog(scriptOutputLogName),
	scriptFinished(false) {
	// Start thread
	th = std::thread([&] {
        // Full command string
		std::string cmd = script+" > "+scriptLog+" 2>&1";

		// Start time
		auto execStart = std::chrono::steady_clock::now();
		// Execute command
		system(cmd.c_str());
		// Start time
		auto execStop = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::milli> elapsed = execStop-execStart;

		// Read run log
		std::ifstream runLog(scriptLog);
		std::stringstream runLogBuffer;
		runLogBuffer << runLog.rdbuf();
		runLog.close();

		// Log content
		std::stringstream logStream;
		logStream << "Run script " << script << " ...\n";
		logStream << "Script execution (" << elapsed.count() << " milliseconds) finished.\n";
		logStream << "Script output:\n";
		logStream << runLogBuffer.str();

		// Update log file
		std::ofstream newOutLog(scriptLog);
		newOutLog << logStream.str();

		// Set finished flag
		scriptFinished = true;
    });
}

ScriptRunner::~ScriptRunner() {
	th.join();
}

bool ScriptRunner::finished() const {
	return scriptFinished;
}

}  // namespace onh
