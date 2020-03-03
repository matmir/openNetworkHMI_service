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

#ifndef SRC_UTILS_LOGGER_H
#define SRC_UTILS_LOGGER_H

#include <string>
#include <fstream>
#include "Exception.h"

namespace onh {

    /**
     * Logger class
     */
    class Logger {

        public:
            /**
             * Default constructor
             *
             * @param dirName Name of the directory where to write log files
             * @param fPrefix Log file name prefix
             */
            Logger(const std::string& dirName, const std::string& fPrefix = "");

            virtual ~Logger();

            /**
             * Write to the log file
             *
             * @param log String with information to write
             */
            void write(const std::string& log);

            /**
             * Clear logs (delete all files and open blank one)
             */
            void clear();

            /**
			 * Get log file path
			 *
			 * @return Log file path
			 */
            std::string getLoggerPath() const;

        private:

            /// Logger directory name
            std::string directoryName;

            /// Log file name prefix
            std::string filePrefix;

            /// Flag informs that directory is ready to write
            bool dirReady;

            /// Logger file handle
            std::ofstream logFile;

            /// Log file name
            std::string logFileName;

            /// Path to the log file
			std::string filePath;

            /**
             * Generate file name based on current date
             *
             * @return String with file name
             */
            std::string generateFileName();

            /**
             * Check log file names (create new log file when date changes)
             */
            void checkFiles();
    };

}

#endif // SRC_UTILS_LOGGER_H
