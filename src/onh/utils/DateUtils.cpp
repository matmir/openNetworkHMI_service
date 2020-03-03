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

#include "DateUtils.h"

using namespace onh;

DateUtils::DateUtils()
{
}

DateUtils::~DateUtils()
{
}

std::string DateUtils::getTimestampString(bool addmSec, char dateSep, char dateTimeSep, char timeSep, char milliSep) {

	// Current time
	struct timeval time_now;
	gettimeofday(&time_now, NULL);
	time_t t = time_now.tv_sec;

	// Current milliseconds
	int millisec = time_now.tv_usec / 1000;

	// Local time
	struct tm now;
	localtime_r(&t, &now);

	return getTimestampStringFromTM(&now, millisec, addmSec, dateSep, dateTimeSep, timeSep, milliSep);
}

std::time_t DateUtils::getTimestamp(int &milliSeconds,
											std::string &currentTimestampString,
											bool addmSec,
											char dateSep,
											char dateTimeSep,
											char timeSep,
											char milliSep) {

	// Current time
	struct timeval time_now;
	gettimeofday(&time_now, NULL);
	time_t rawtime = time_now.tv_sec;

	// Current milliseconds
	milliSeconds = time_now.tv_usec / 1000;

	struct tm timeinfo;
	localtime_r(&rawtime, &timeinfo);

	// Current timestamp sting
	currentTimestampString = getTimestampStringFromTM(&timeinfo, milliSeconds, addmSec, dateSep, dateTimeSep, timeSep, milliSep);

	timeinfo.tm_isdst = 0;

	time_t currCV = mktime(&timeinfo);

	return currCV;
}

std::string DateUtils::getDate(char dateSep) {

	// Check separators
	if (dateSep == '\0') {
		throw Exception("Date separator is empty", "DateUtils::getTimestamp");
	}

	// Current time
	time_t t = time(0);

	struct tm now;
	localtime_r(&t, &now);

	std::stringstream s;

	// Current date
	s << (now.tm_year + 1900) << dateSep;

	// Add 0 before month
	if ((now.tm_mon + 1) < 10) {
		s << "0" << (now.tm_mon + 1) << dateSep;
	} else {
		s << (now.tm_mon + 1) << dateSep;
	}

	// Add 0 before day
	if (now.tm_mday < 10) {
		s << "0" << (now.tm_mday);
	} else {
		s << (now.tm_mday);
	}

	return s.str();
}

std::string DateUtils::getTimestampStringFromTM(struct tm* timeInfo,
										int mSec,
										bool addmSec,
										char dateSep,
										char dateTimeSep,
										char timeSep,
										char milliSep) {

	// Check separators
	if (dateSep == '\0') {
		throw Exception("Date separator is empty", "DateUtils::getTimestamp");
	}
	if (dateTimeSep == '\0') {
		throw Exception("Date and time separator is empty", "DateUtils::getTimestamp");
	}
	if (timeSep == '\0') {
		throw Exception("Time separator is empty", "DateUtils::getTimestamp");
	}
	if (milliSep == '\0') {
		throw Exception("Millisecond separator is empty", "DateUtils::getTimestamp");
	}

	std::stringstream s;

	// Current date
	s << (timeInfo->tm_year + 1900) << dateSep;

	// Add 0 before month
	if ((timeInfo->tm_mon + 1) < 10) {
		s << "0" << (timeInfo->tm_mon + 1) << dateSep;
	} else {
		s << (timeInfo->tm_mon + 1) << dateSep;
	}

	// Add 0 before day
	if (timeInfo->tm_mday < 10) {
		s << "0" << (timeInfo->tm_mday) << dateTimeSep;
	} else {
		s << (timeInfo->tm_mday) << dateTimeSep;
	}

	// Current time
	if (timeInfo->tm_hour < 10) {
		s << "0" << timeInfo->tm_hour << timeSep;
	} else {
		s << timeInfo->tm_hour << timeSep;
	}
	if (timeInfo->tm_min < 10) {
		s << "0" << timeInfo->tm_min << timeSep;
	} else {
		s << timeInfo->tm_min << timeSep;
	}
	if (timeInfo->tm_sec < 10) {
		s << "0" << timeInfo->tm_sec;
	} else {
		s << timeInfo->tm_sec;
	}

	// Milliseconds
	if (addmSec) {

		s << milliSep;

		if (mSec < 10) {
			s << "00";
		} else if (mSec < 100) {
			s << "0";
		}

		s << mSec;
	}

	return s.str();
}
