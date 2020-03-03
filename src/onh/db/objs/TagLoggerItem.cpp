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

#include "TagLoggerItem.h"
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <cmath>
#include "../../utils/StringUtils.h"
#include "../../utils/DateUtils.h"

using namespace onh;

TagLoggerItem::TagLoggerItem():
    ltid(0), ltTag(Tag()), ltInterval(TagLoggerItem::I_1S), ltIntervalS(0), ltEnable(false)
{
	ltLast.timestamp = "";
	ltLast.value = "";
	ltCurrent.timestamp = "";
	ltCurrent.value = "";
}

TagLoggerItem::TagLoggerItem(unsigned int id,
                             const Tag& tag,
                             intervals interval,
                             unsigned int intervalSec,
                             const std::string& lastUpdate,
                             const std::string& lastValue,
                             bool enable)
{
	setId(id);
	setTag(tag);
	setInterval(interval);
	setIntervalSec(intervalSec);
	setLastUpdate(lastUpdate);
	setLastValue(lastValue);
	setEnable(enable);

	ltCurrent.timestamp = "";
	ltCurrent.value = "";
}

TagLoggerItem::~TagLoggerItem()
{
}

void TagLoggerItem::checkId(unsigned int id) const {

	if (id == 0)
		throw Exception("Invalid tag logger identifier", "TagLoggerItem::checkId");
}

unsigned int TagLoggerItem::getId() const {

    checkId(ltid);

    return ltid;
}

void TagLoggerItem::setId(unsigned int id) {

    checkId(id);

    ltid = id;
}

const Tag& TagLoggerItem::getTag() const {

    return ltTag;
}

void TagLoggerItem::setTag(const Tag& tag) {

    ltTag = tag;
}

void TagLoggerItem::checkInterval(const intervals& interval) const {

	bool intervalOK = false;

	// Check type
	switch (interval) {
		case I_100MS: intervalOK = true; break;
		case I_200MS: intervalOK = true; break;
		case I_500MS: intervalOK = true; break;
		case I_1S: intervalOK = true; break;
		case I_XS: intervalOK = true; break;
		case I_ON_CHANGE: intervalOK = true; break;
	}

	if (!intervalOK)
		throw Exception("Interval wrong value", "TagLoggerItem::checkInterval");
}

const TagLoggerItem::intervals& TagLoggerItem::getInterval() const {

	checkInterval(ltInterval);

    return ltInterval;
}

void TagLoggerItem::setInterval(const TagLoggerItem::intervals& interval) {

	checkInterval(interval);

    ltInterval = interval;
}

unsigned int TagLoggerItem::getIntervalSec() const {

    return ltIntervalS;
}

void TagLoggerItem::setIntervalSec(unsigned int intervalSec) {

    ltIntervalS = intervalSec;
}

void TagLoggerItem::checkLastUpdate(const std::string& lastUpdate) const {

	if (lastUpdate.length() == 0)
		throw Exception("Timestamp string is empty", "TagLoggerItem::checkLastUpdate");

	// Parse string format (2000-01-01 07:00:00.000)
	if (lastUpdate.length() != 23)
		throw Exception("Timestamp string wrong length", "TagLoggerItem::checkLastUpdate");

	char c = 0;

	// Check characters
	for (int i=0; i<23; ++i) {

		// Get one char
		c = lastUpdate[i];

		// check '-'
		if ((i==4)||(i==7)) {
			if (c != '-') {
				std::stringstream s;
				s << "Timestamp string wrong format. Pos " << i << " need to contain '-' character";
				throw Exception(s.str(), "TagLoggerItem::checkLastUpdate");
			}
		} else if (i==10) {
			if (c != ' ') {
				std::stringstream s;
				s << "Timestamp string wrong format. Pos " << i << " need to contain space";
				throw Exception(s.str(), "TagLoggerItem::checkLastUpdate");
			}
		} else if ((i==13)||(i==16)) {
			if (c != ':') {
				std::stringstream s;
				s << "Timestamp string wrong format. Pos " << i << " need to contain ':' character";
				throw Exception(s.str(), "TagLoggerItem::checkLastUpdate");
			}
		} else if (i==19) {
			if (c != '.') {
				std::stringstream s;
				s << "Timestamp string wrong format. Pos " << i << " need to contain '.' character";
				throw Exception(s.str(), "TagLoggerItem::checkLastUpdate");
			}
		} else {
			if (!(c >= 48 && c <= 57)) {
				std::stringstream s;
				s << "Timestamp string wrong format. Pos " << i << " need to be number";
				throw Exception(s.str(), "TagLoggerItem::checkLastUpdate");
			}
		}
	}
}

std::string TagLoggerItem::getLastUpdate() const {

    checkLastUpdate(ltLast.timestamp);

    return ltLast.timestamp;
}

void TagLoggerItem::setLastUpdate(const std::string& lastUpdate) {

	checkLastUpdate(lastUpdate);

	ltLast.timestamp = lastUpdate;
}

void TagLoggerItem::checkLastValue(const std::string& value) const {

	if (value.length() == 0)
		throw Exception("Value string is empty", "TagLoggerItem::checkLastValue");
}

const std::string& TagLoggerItem::getLastValue() const {

	checkLastValue(ltLast.value);

    return ltLast.value;
}

void TagLoggerItem::setLastValue(const std::string& lastValue) {

	checkLastValue(lastValue);

	ltLast.value = lastValue;
}

std::string TagLoggerItem::getCurrentUpdate() const {

	if (ltCurrent.timestamp == "")
		throw Exception("Current update timestamp is empty", "TagLoggerItem::getCurrentUpdate");

	return ltCurrent.timestamp;
}

bool TagLoggerItem::isEnabled() const {

    return ltEnable;
}

void TagLoggerItem::setEnable(bool enable) {

    ltEnable = enable;
}

bool TagLoggerItem::isNeededUpdate(const std::string& tagValue) {

    bool ret = false;

    // Current milliseconds
	int currentMS = 0;

	// Current timestamp string
	std::string currentTSS;

    // Current timestamp
    std::time_t currentTS = DateUtils::getTimestamp(currentMS, currentTSS, true);

    // Tag last update timestamp
    std::time_t tagTS = getTagUpdateTimestamp();

    // Timestamp difference
    double tsDiff = difftime(currentTS, tagTS);

    // Tag last update milliseconds
    int tagMS = getTagUpdateMilliseconds();

    // Check update type
    switch (ltInterval) {

        case TagLoggerItem::I_100MS: {

            // Millisecond update?
            ret = msUpdate(tsDiff, tagMS, currentMS, 100);

        }; break;

        case TagLoggerItem::I_200MS: {

            // Millisecond update?
            ret = msUpdate(tsDiff, tagMS, currentMS, 200);

        }; break;

        case TagLoggerItem::I_500MS: {

            // Millisecond update?
            ret = msUpdate(tsDiff, tagMS, currentMS, 500);

        }; break;

        case TagLoggerItem::I_1S: {

            // 1 second update
            if (tsDiff >= 1.0) {
                ret = true;
            }

        }; break;

        case TagLoggerItem::I_XS: {

            if (ltIntervalS == 0)
                throw Exception("Interval seconds can not be 0", "TagLoggerItem::isNeededUpdate");

            // X second update
            if (tsDiff >= ltIntervalS) {
                ret = true;
            }

        }; break;

        case TagLoggerItem::I_ON_CHANGE: {

			// Compare values
			if (tagValue != getLastValue())
				ret = true;

        }; break;

    }

    // Update logger current timestamp and value
    if (ret) {
    	ltCurrent.timestamp = currentTSS;
    	ltCurrent.value = tagValue;
    }

    return ret;
}

std::time_t TagLoggerItem::getTagUpdateTimestamp() const {

    checkLastUpdate(ltLast.timestamp);

    std::vector<std::string> v;
    // Explode string (YYYY-MM-DD HH:MM:SS.MSS) to get time without milliseconds
    v = StringUtils::explode(ltLast.timestamp,'.');

    // Check exploded data count
    if (v.size() != 2)
        throw Exception("Wrong exploded data count", "TagLoggerItem::getTagUpdateTimestamp");

    struct tm tmTUPD;

    // Init structure
    memset(&tmTUPD, 0, sizeof(struct tm));

    // Parse string
	strptime(v[0].c_str(), "%Y-%m-%d %H:%M:%S", &tmTUPD);

	time_t timeUPD = mktime(&tmTUPD);

	if (timeUPD == -1)
        throw Exception("Error during creation timestamp", "TagLoggerItem::getTagUpdateTimestamp");

	return timeUPD;
}

int TagLoggerItem::getTagUpdateMilliseconds() const {

	checkLastUpdate(ltLast.timestamp);

    std::vector<std::string> v;

    // Explode string (YYYY-MM-DD HH:MM:SS.MSS) to get milliseconds
    v = StringUtils::explode(ltLast.timestamp,'.');

    // Check exploded data count
    if (v.size() != 2)
        throw Exception("Wrong exploded data count", "TagLoggerItem::getTagUpdateMilliseconds");

    // Convert to milliseconds
    int ms = 0;
    std::istringstream iss(v[1]);
    iss >> ms;

    // Check value
    if (ms >=1000 || ms < 0)
        throw Exception("Wrong milliseconds value", "TagLoggerItem::getTagUpdateMilliseconds");

    return ms;
}

bool TagLoggerItem::msUpdate(double dTS,unsigned int tagMillisec,unsigned int currentMillisec, unsigned int msFactor) const {

    bool ret = false;

    if ((dTS > 1.0) || (dTS < 0.0)) {
        ret = true;
    } else if (dTS == 1.0) {

        unsigned int A = 1000 - tagMillisec;
        unsigned int B = currentMillisec + A;

        if (B >= msFactor)
            ret = true;

    } else if (dTS == 0.0) {

        unsigned msD = abs(currentMillisec-tagMillisec);

        if (msD >= msFactor)
            ret = true;

    }

    return ret;
}

void TagLoggerItem::setLastTimeValue(const timeVal& tv) {

	checkLastUpdate(tv.timestamp);
	checkLastValue(tv.value);

	ltLast = tv;
}

TagLoggerItem::timeVal TagLoggerItem::getLastTimeValue() const {

	checkLastUpdate(ltLast.timestamp);
	checkLastValue(ltLast.value);

	return ltLast;
}

TagLoggerItem::timeVal TagLoggerItem::getCurrentTimeValue() const {

	checkLastUpdate(ltCurrent.timestamp);
	checkLastValue(ltCurrent.value);

	return ltCurrent;
}
