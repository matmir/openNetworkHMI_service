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

#ifndef LOGGERTESTS_H_
#define LOGGERTESTS_H_

#include <gtest/gtest.h>
#include <utils/StringUtils.h>

#include "LoggerTestsFixtures.h"

/**
 * Check log file creation
 */
TEST_F(logsTest, log1) {

	log->write("Message from tests");

	// Test line from file
	std::string line;

	// Check log file
	std::ifstream lFile(log->getLoggerPath());
	if (lFile.is_open()) {
	    ASSERT_TRUE(getline(lFile, line));
	    lFile.close();
	} else {
		FAIL() << "Log file: " << log->getLoggerPath() << " not opened";
	}

	std::vector<std::string> msg = onh::StringUtils::explode(line, '|');

	ASSERT_STREQ("Message from tests", msg[1].c_str());
}

/**
 * Check clear log file
 */
TEST_F(logsTest, log2) {

	log->write("Message 1 from tests");

	// Test line from file
	std::string line;

	// Check log file
	std::ifstream lFile1(log->getLoggerPath());
	if (lFile1.is_open()) {
		ASSERT_TRUE(getline(lFile1, line));
		lFile1.close();
	} else {
		FAIL() << "Log file: " << log->getLoggerPath() << " not opened";
	}

	std::vector<std::string> msg = onh::StringUtils::explode(line, '|');

	ASSERT_STREQ("Message 1 from tests", msg[1].c_str());

	log->clear();
	line = "";

	// Check log file
	std::ifstream lFile2(log->getLoggerPath());
	if (lFile2.is_open()) {
		ASSERT_FALSE(getline(lFile2, line));
		lFile2.close();
	} else {
		FAIL() << "Log file: " << log->getLoggerPath() << " not opened";
	}
}

#endif /* LOGGERTESTS_H_ */
