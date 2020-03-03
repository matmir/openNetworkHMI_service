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

#include "Logger.h"
#include <sys/stat.h>
#include <errno.h>
#include <ctime>
#include <sstream>
#include <syslog.h>
#include <stdlib.h>
#include "DateUtils.h"

using namespace onh;

Logger::Logger(const std::string& dirName, const std::string& fPrefix):
    directoryName(dirName), filePrefix(fPrefix), dirReady(false), logFileName(""), filePath("")
{
    bool createDir = false;
    std::string tmpDir = "logs/" + dirName;

    // Create main log directory
    if (mkdir("logs", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)) {
        if (errno == EEXIST) {
            createDir = true;
        }
    } else {
        createDir = true;
    }

    // Create subdirectory
    if (createDir) {

        if (mkdir(tmpDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)) {
            if (errno == EEXIST) {
                dirReady = true;
            }
        } else {
            dirReady = true;
        }

    }
}

Logger::~Logger()
{
    if (logFile.is_open()) {
        logFile.close();
    }
}

std::string Logger::generateFileName() {

    std::stringstream s;

    // File prefix
    if (filePrefix != "")
        s << filePrefix;

    // Current date
    s << DateUtils::getDate('.');

    return s.str();
}

void Logger::checkFiles() {

    // Temporary file name
    std::string tmpFileName = generateFileName();

    // Path to the log file
    filePath = "logs/" + directoryName + '/' + tmpFileName + ".log";

    // Check if file is already opened
    if (logFile.is_open()) {
        // Check file names
        if (tmpFileName != logFileName) {

            // Close current file
            logFile.close();

            // Open new file
            logFile.open(filePath.c_str(), std::ios::out | std::ios::app);

            logFileName = tmpFileName;
        }
    } else {

        // Open new file
        logFile.open(filePath.c_str(), std::ios::out | std::ios::app);

        logFileName = tmpFileName;
    }

    if (!logFile.is_open()) {
    	std::string s = "Logger error: Log "+filePath+" not opened";
        throw Exception(s, "Logger::checkFiles");
    }

}

void Logger::write(const std::string& log) {

    if (!dirReady) {
    	std::string s = "Logger error: Log "+directoryName+" directory not ready";
        throw Exception(s, "Logger::write");
    }

    // Entry timestamp
    std::string ts = DateUtils::getTimestampString();

    // Check log files
    checkFiles();

    // Write log
    logFile << ts << '|' << log << std::endl;
    logFile.close();
}

void Logger::clear() {

    // Check if file is already opened
    if (logFile.is_open()) {
        logFile.close();
    }

    // Path to the logs
    std::string filePath = "logs/" + directoryName + "/*.log";
    // Prepare remove command
    std::string cmd = "rm "+filePath;

    // Remove all logger files
    system(cmd.c_str());

    // Open blank file
    checkFiles();
}

std::string Logger::getLoggerPath() const {

	return filePath;
}
