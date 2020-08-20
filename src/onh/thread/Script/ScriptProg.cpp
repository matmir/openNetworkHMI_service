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

#include "ScriptProg.h"

#include <stdlib.h>
#include <sstream>
#include <sys/stat.h>
#include <errno.h>
#include "../../utils/Exception.h"
#include "../../utils/DateUtils.h"
#include "../../db/ScriptDB.h"

using namespace onh;

ScriptProg::ScriptProg(const ProcessReader& pr,
						const ProcessWriter& pw,
						const ScriptDB& sdb,
						unsigned int updateInterval,
						const std::string& execScript,
						bool tstEnv,
						const GuardDataController<ThreadExitData> &gdcTED,
						const GuardDataController<CycleTimeData> &gdcCTD):
    ThreadProgram(gdcTED, gdcCTD,"script", "scriptLog_"), executeScript(execScript), testEnv(tstEnv)
{
    // Process reader
    prReader = new ProcessReader(pr);

    // Process writer
    prWriter = new ProcessWriter(pw);

    // Create delay
    itsDelay = new Delay(updateInterval);

    // Script DB access
    db = new ScriptDB(sdb);

    dirReady = false;

    // Create script redirected output directory log
    if (mkdir("logs/scriptOutput", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)) {
        if (errno == EEXIST) {
            dirReady = true;
        }
    } else {
        dirReady = true;
    }
}

ScriptProg::~ScriptProg()
{
    if (prReader)
        delete prReader;
    if (prWriter)
        delete prWriter;
    if (db)
        delete db;

    getLogger().write("Script system close");

    if (itsDelay)
        delete itsDelay;
}

void ScriptProg::operator()() {

    try {

    	getLogger().write("Start main loop");

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

            // Check scripts tags
            checkScripts();

            // Wait
            itsDelay->wait();

            // Stop thread cycle time measure
            stopCycleMeasure();
        }

    } catch (Exception &e) {

    	getLogger().write(e.what());

        // Exit application
    	exit("Script system");
    }
}

void ScriptProg::checkScripts() {

    // Get scripts
    std::vector<ScriptItem> sc = db->getScripts();

    std::string cmd;

    for (unsigned int i=0; i<sc.size(); ++i) {

        // Run script - check flags
        if (!sc[i].isRunning() && !sc[i].isLocked()) {

            // Check trigger Tag value - only true triggers script
            if (prReader->getBitValue(sc[i].getTag())) {

                // Prepare log file name (script output)
                std::string logFile = "logs/scriptOutput/";
                logFile += DateUtils::getTimestampString(false, '-', '_', '_');
                logFile += "_"+sc[i].getName()+".log";

                // Check environment - if 'test' we need to call script from test environment in Symfony
                if (testEnv) {
                	cmd = "APP_ENV=test ";
                } else {
                	cmd = "";
                }

                // Prepare command (run in background)
                cmd += executeScript+" "+sc[i].getName()+" > "+logFile+" 2>&1 &";

                // Set run flag
                db->setScriptRun(sc[i]);

                // Run script
                system(cmd.c_str());

                getLogger().write("Run script: "+cmd);

            }

        }

        // Set feedback tag
        if (sc[i].isRunning()) {

            try {
                // Set bit informs controller that script is running
                if (!prReader->getBitValue(sc[i].getFeedbackRunTag()))
                    prWriter->setBit(sc[i].getFeedbackRunTag());

            } catch (ScriptException &e) {
                if (e.getType() != ScriptException::ExceptionType::NO_FEEDBACK_RUN_TAG) {
                    // Re-throw exception
                    throw;
                }
            }

        } else {

            try {
                // Reset bit informs controller that script is running
                if (prReader->getBitValue(sc[i].getFeedbackRunTag()))
                    prWriter->resetBit(sc[i].getFeedbackRunTag());

            } catch (ScriptException &e) {
                if (e.getType() != ScriptException::ExceptionType::NO_FEEDBACK_RUN_TAG) {
                    // Re-throw exception
                    throw;
                }
            }

        }

        // Check lock flag
        if (sc[i].isLocked() && !sc[i].isRunning()) {

            // Check trigger tag value
            if (!prReader->getBitValue(sc[i].getTag())) {

                // Reset lock flag
                db->clearScriptLock(sc[i]);

                getLogger().write("Script unlocked: "+sc[i].getName());

            }

        }

    }
}
