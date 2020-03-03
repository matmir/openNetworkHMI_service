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

#include "ScriptItem.h"

using namespace onh;

ScriptItem::ScriptItem():
    scid(0),
    scTag(0),
    scName(""),
    scRun(false),
    scLock(false),
	scFeedbackRun(0),
    scEnable(false)
{
}

ScriptItem::ScriptItem(unsigned int id,
                        const Tag& tag,
                        const std::string& name,
                        bool run,
                        bool lock,
                        bool enabled):
    scTag(0),
    scRun(run),
    scLock(lock),
	scFeedbackRun(0),
    scEnable(enabled)
{
	setId(id);
	setTag(tag);
	setName(name);
}

ScriptItem::ScriptItem(unsigned int id,
                        const Tag& tag,
                        const std::string& name,
                        bool run,
                        bool lock,
                        const Tag& feedbackRun,
                        bool enabled):
    scTag(0),
    scRun(run),
    scLock(lock),
	scFeedbackRun(0),
    scEnable(enabled)
{
	setId(id);
	setTag(tag);
	setName(name);
	setFeedbackRunTag(feedbackRun);
}

ScriptItem::ScriptItem(const ScriptItem& rhs):
	scid(rhs.scid),
	scName(rhs.scName),
    scRun(rhs.scRun),
    scLock(rhs.scLock),
    scEnable(rhs.scEnable)
{

	if (rhs.scTag)
		scTag = new Tag(*rhs.scTag);
	else
		scTag = 0;

    if (rhs.scFeedbackRun)
    	scFeedbackRun = new Tag(*rhs.scFeedbackRun);
    else
    	scFeedbackRun = 0;
}

ScriptItem::~ScriptItem()
{
	if (scTag)
		delete scTag;

    if (scFeedbackRun)
        delete scFeedbackRun;
}

ScriptItem& ScriptItem::operator=(const ScriptItem& rhs) {

    // Self assignment check
    if (this != &rhs) {

    	scid = rhs.scid;
    	scName = rhs.scName;
        scRun = rhs.scRun;
        scLock = rhs.scLock;
        scEnable = rhs.scEnable;

        if (scTag) {
        	delete scTag;
        	scTag = 0;
        }
        if (rhs.scTag)
			scTag = new Tag(*rhs.scTag);

        // Feedback run Tag
        if (scFeedbackRun) {
        	delete scFeedbackRun;
        	scFeedbackRun = 0;
        }
        if (rhs.scFeedbackRun) {
        	scFeedbackRun = new Tag(*rhs.scFeedbackRun);
        }
    }

    return *this;
}

void ScriptItem::checkId(unsigned int id) const {

	if (id == 0)
		throw ScriptException(ScriptException::ExceptionType::WRONG_ID,
								"Invalid script identifier",
								"ScriptItem::checkId");
}

unsigned int ScriptItem::getId() const {

    checkId(scid);

    return scid;
}

void ScriptItem::setId(unsigned int id) {

	checkId(id);

    scid = id;
}

const Tag& ScriptItem::getTag() const {

	if (!scTag)
		throw ScriptException(ScriptException::ExceptionType::NO_TAG,
				"Missing tag object in script item",
				"ScriptItem::getTag");

	checkBitTagType(*scTag);

    return *scTag;
}

void ScriptItem::setTag(const Tag& tag) {

	checkBitTagType(tag);

	if (scTag) {
		delete scTag;
		scTag = 0;
	}

	scTag = new Tag(tag);
}

void ScriptItem::checkScriptName(const std::string& nm) const {

	if (nm.length() == 0)
		throw ScriptException(ScriptException::ExceptionType::WRONG_NAME,
									"Script name is empty",
									"ScriptItem::checkScriptName");
}

std::string ScriptItem::getName() const {

	checkScriptName(scName);

    return scName;
}

void ScriptItem::setName(const std::string& name) {

	checkScriptName(name);

    scName = name;
}

bool ScriptItem::isRunning() const {

    return scRun;
}

void ScriptItem::setRun(bool run) {

    scRun = run;
}

bool ScriptItem::isLocked() const {

    return scLock;
}

void ScriptItem::setLock(bool lock) {

    scLock = lock;
}

void ScriptItem::checkBitTagType(const Tag& tg) const {

	if (tg.getType() != TT_BIT)
		throw ScriptException(ScriptException::ExceptionType::WRONG_TAG_TYPE,
									"Wrong tag type - need BIT type",
									"ScriptItem::checkBitTagType");
}

void ScriptItem::setFeedbackRunTag(const Tag& feedbackTag) {

	checkBitTagType(feedbackTag);

    if (scFeedbackRun) {
        delete scFeedbackRun;
        scFeedbackRun = 0;
    }

    scFeedbackRun = new Tag(feedbackTag);
}

const Tag& ScriptItem::getFeedbackRunTag() const {

    if (!scFeedbackRun)
        throw ScriptException(ScriptException::NO_FEEDBACK_RUN_TAG,
        							"No feedback run tag",
									"ScriptItem::getFeedbackRunTag");

    checkBitTagType(*scFeedbackRun);

    return *scFeedbackRun;
}

bool ScriptItem::isEnabled() const {

    return scEnable;
}

void ScriptItem::setEnable(bool enable) {

    scEnable = enable;
}
