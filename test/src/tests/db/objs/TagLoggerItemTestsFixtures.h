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

#ifndef TESTS_DB_OBJS_TAGLOGGERITEMTESTSFIXTURES_H_
#define TESTS_DB_OBJS_TAGLOGGERITEMTESTSFIXTURES_H_

#include <gtest/gtest.h>
#include <time.h>
#include <sys/time.h>
#include <db/objs/TagLoggerItem.h>

class tagLoggerItemTests: public ::testing::Test {
	protected:
		void SetUp() override {

			tg = new onh::Tag(
					5,
					"TestTag1",
					onh::TT_BIT,
					{onh::PDA_INPUT, 4, 6}
			);
		}

		void TearDown() override {
			if (tg)
				delete tg;
		}

		std::string createTimestamp(int addsec, int addms) {

			if (addms <= -1000 || addms >= 1000) {
				throw onh::Exception("Wrong millisexond value");
			}

			// Current milliseconds
			struct timeval tvTime;
			gettimeofday(&tvTime, NULL);
			int msec = tvTime.tv_usec / 1000;

			int secMod = 0;

			if (addms != 0) {
				int msecc = msec+addms;
				if (msecc<0) {
					secMod = -1;
					msec = 1000+msecc;
				} else if (msecc >= 1000) {
					secMod = 1;
					msec = msecc-1000;
				} else {
					msec = msecc;
				}
			}

			// Current time
			std::time_t rawtime = time(NULL);
			std::time_t modtime = rawtime + secMod + addsec;

			struct tm *timeinfo;

			timeinfo = localtime(&modtime);

			std::stringstream s;

			// (YYYY-MM-DD HH:MM:SS.MSS)
			s << timeinfo->tm_year+1900 << "-" << add0(timeinfo->tm_mon+1) << "-" << add0(timeinfo->tm_mday);
			s << " " << add0(timeinfo->tm_hour) << ":" << add0(timeinfo->tm_min) << ":" << add0(timeinfo->tm_sec);
			s << "." << add00(msec);

			//std::cout << s.str() << " secmod: " << secMod << " addsec: " << addsec << std::endl;

			return s.str();
		}

		// Logger tag
		onh::Tag *tg;

	private:

		std::string add0(int val) {

			std::stringstream s;

			if (val<10) {
				s << "0";
			}

			s << val;

			return s.str();
		}

		std::string add00(int val) {

			std::stringstream s;

			if (val<10) {
				s << "00";
			} else if (val>=10 && val <= 99) {
				s << "0";
			}

			s << val;

			return s.str();
		}
};

#endif /* TESTS_DB_OBJS_TAGLOGGERITEMTESTSFIXTURES_H_ */
