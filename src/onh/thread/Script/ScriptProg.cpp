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

#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <sstream>
#include "ScriptProg.h"
#include "../../utils/Exception.h"
#include "../../utils/DateUtils.h"
#include "../../db/ScriptDB.h"

namespace onh {

// Max number running scripts
const unsigned int RUNNERS_POOL = 5;

ScriptProg::ScriptProg(const ProcessReader& pr,
						const ProcessWriter& pw,
						const ScriptDB& sdb,
						unsigned int updateInterval,
						const std::string& scriptDirPath,
						const GuardDataController<ThreadExitData> &gdcTED,
						const GuardDataController<CycleTimeData> &gdcCTD):
	ThreadProgram(gdcTED, gdcCTD, updateInterval, "script", "scriptLog_"),
	prReader(std::make_unique<ProcessReader>(pr)),
	prWriter(std::make_unique<ProcessWriter>(pw)),
	db(std::make_unique<ScriptDB>(sdb)),
	scriptDirectoryPath(scriptDirPath) {
	// Dir flag
	dirReady = false;

	// Create script redirected output directory log
	if (mkdir("logs/scriptOutput", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)) {
		if (errno == EEXIST) {
			dirReady = true;
		}
	} else {
		dirReady = true;
	}

	getLogger() << LOG_INFO("Script system initialized");
}

ScriptProg::~ScriptProg() {
	getLogger() << LOG_INFO("Script system closed");
}

void ScriptProg::operator()() {
	try {
		getLogger() << LOG_INFO("Start main loop");

		if (!prReader)
			throw Exception("No reader object");

		if (!prWriter)
			throw Exception("No writer object");
		if (!db)
			throw Exception("No DB object!");

		if (!dirReady)
			throw Exception("Log directory for script output does not exist");

		while(!isExitFlag()) {
			// Start thread cycle time measure
			startCycleMeasure();

			// Update process reader
			prReader->updateProcessData();

			// Check started scripts
			checkScriptRunners();

			// Check if new script need to be started
			checkScriptItems();

			// Wait
			threadWait();

			// Stop thread cycle time measure
			stopCycleMeasure();
		}
	} catch (Exception &e) {
		getLogger() << LOG_ERROR(e.what());

		// Exit application
		exit("Script system");
	}
}

void ScriptProg::checkScriptItems() {
	// Get scripts
	std::vector<ScriptItem> scripts = db->getScripts();

	for (auto& script : scripts) {
		// Run script - check flags
		if (!script.isRunning() && !script.isLocked()) {
			// Check trigger Tag value - only true triggers script
			if (prReader->getBitValue(script.getTag())) {
				// Run assigned script
				startScript(script);
			}
		}

		// Update controller script tags
		updateControllerTags(script);
	}
}

void ScriptProg::checkScriptRunners() {
	// Check running scripts
	for(auto it = runners.begin(); it != runners.end(); ) {
        if (it->second.finished()) {
			// Clear run flag
			db->clearScriptRun(it->first);
			// Remove runner
			it = runners.erase(it);
		} else {
			++it;
		}
    }
}

void ScriptProg::updateControllerTags(const ScriptItem &sc) {
	// Set feedback tag
	if (sc.isRunning()) {
		try {
			// Set bit informs controller that script is running
			if (!prReader->getBitValue(sc.getFeedbackRunTag()))
				prWriter->setBit(sc.getFeedbackRunTag());
		} catch (ScriptException &e) {
			if (e.getType() != ScriptException::ExceptionType::NO_FEEDBACK_RUN_TAG) {
				// Re-throw exception
				throw;
			}
		}

	} else {
		try {
			// Reset bit informs controller that script is running
			if (prReader->getBitValue(sc.getFeedbackRunTag()))
				prWriter->resetBit(sc.getFeedbackRunTag());
		} catch (ScriptException &e) {
			if (e.getType() != ScriptException::ExceptionType::NO_FEEDBACK_RUN_TAG) {
				// Re-throw exception
				throw;
			}
		}
	}

	// Check lock flag
	if (sc.isLocked() && !sc.isRunning()) {
		// Check trigger tag value
		if (!prReader->getBitValue(sc.getTag())) {
			// Reset lock flag
			db->clearScriptLock(sc);

			getLogger() << LOG_INFO("Script unlocked: "+sc.getName());
		}
	}
}

void ScriptProg::startScript(const ScriptItem &sc) {
	// Script path
	std::string scriptPath = createScriptPath(scriptDirectoryPath, sc.getName());

	// Check runners pool
	if (runners.size() < RUNNERS_POOL) {
		// Log file name (script output)
		std::string logFile = "logs/scriptOutput/";
		logFile += DateUtils::getTimestampString(false, '-', '_', '_');
		logFile += "_"+sc.getName()+".log";

		// Set run flag
		db->setScriptRun(sc);

		getLogger() << LOG_INFO("Run script: "+scriptPath);

		// Run script
		runners.emplace(std::piecewise_construct,
			std::forward_as_tuple(sc.getId()),
			std::forward_as_tuple(scriptPath, logFile));
	} else {
		getLogger() << LOG_INFO("No empty runners for script: "+scriptPath);
	}
}

std::string ScriptProg::createScriptPath(const std::string &scriptDir, const std::string &scriptName) const {
	// Check last letter
	if (scriptDir.back() == '/') {
		return scriptDir + scriptName;
	} else {
		return scriptDir + '/' + scriptName;
	}
}

}  // namespace onh
