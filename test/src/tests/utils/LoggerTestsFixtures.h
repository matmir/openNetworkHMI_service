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

#ifndef FIXTURES_LOGSTEST_H_
#define FIXTURES_LOGSTEST_H_

#include <gtest/gtest.h>
#include <utils/Logger.h>

class logsTest: public ::testing::Test {
	protected:
		void SetUp() override {

			// Remove all logger files
			system("rm -r -f logs");

			// Create logger object
			log = new onh::Logger("test1", "tst_");
		}

		void TearDown() override {
			if (log) {
				delete log;
			}

			// Remove all logger files
			system("rm -r logs");
		}

		// Log
		onh::Logger *log;
};

#endif /* FIXTURES_LOGSTEST_H_ */
