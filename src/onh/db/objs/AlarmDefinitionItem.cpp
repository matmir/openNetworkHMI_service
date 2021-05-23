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

#include "AlarmDefinitionItem.h"

namespace onh {

AlarmDefinitionItem::AlarmDefinitionItem():
	adid(0),
	adTag(Tag()),
	adPriority(0),
	adMessage(""),
	adTrigger(AlarmDefinitionItem::T_BIN),
	adTriggerVal(triggerValues()),
	adAutoAck(false),
	adActive(false),
	adPending(false),
	adEnable(false) {
	adFeedbackNotAck = 0;
	adHWAck = 0;
}

AlarmDefinitionItem::AlarmDefinitionItem(unsigned int id,
										 const Tag& tag,
										 unsigned char priority,
										 const std::string& msg,
										 triggers trig,
										 triggerValues trigVal,
										 bool aAck,
										 bool active,
										 bool pending,
										 bool enabled) {
	setId(id);
	setTag(tag);
	setPriority(priority);
	setMsg(msg);
	setTrigger(trig);
	setTriggerValues(trigVal);
	setAutoAck(aAck);
	setActive(active);
	setPending(pending);
	setEnable(enabled);
	adFeedbackNotAck = 0;
	adHWAck = 0;
}

AlarmDefinitionItem::AlarmDefinitionItem(unsigned int id,
										 const Tag& tag,
										 unsigned char priority,
										 const std::string& msg,
										 triggers trig,
										 triggerValues trigVal,
										 bool aAck,
										 bool active,
										 bool pending,
										 const Tag& feedbackNotAck,
										 const Tag& hwAck,
										 bool enabled) {
	setId(id);
	setTag(tag);
	setPriority(priority);
	setMsg(msg);
	setTrigger(trig);
	setTriggerValues(trigVal);
	setAutoAck(aAck);
	setActive(active);
	setPending(pending);
	setEnable(enabled);
	adFeedbackNotAck = new Tag(feedbackNotAck);
	adHWAck = new Tag(hwAck);
}

AlarmDefinitionItem::AlarmDefinitionItem(const AlarmDefinitionItem& rhs):
	adid(rhs.adid),
	adTag(rhs.adTag),
	adPriority(rhs.adPriority),
	adMessage(rhs.adMessage),
	adTrigger(rhs.adTrigger),
	adTriggerVal(rhs.adTriggerVal),
	adAutoAck(rhs.adAutoAck),
	adActive(rhs.adActive),
	adPending(rhs.adPending),
	adEnable(rhs.adEnable) {
	if (rhs.adFeedbackNotAck)
		adFeedbackNotAck = new Tag(*rhs.adFeedbackNotAck);
	else
		adFeedbackNotAck = 0;

	if (rhs.adHWAck)
		adHWAck = new Tag(*rhs.adHWAck);
	else
		adHWAck = 0;
}

AlarmDefinitionItem& AlarmDefinitionItem::operator=(const AlarmDefinitionItem& rhs) {
	// Self assignment check
	if (this != &rhs) {
		adid = rhs.adid;
		adTag = rhs.adTag;
		adPriority = rhs.adPriority;
		adMessage = rhs.adMessage;
		adTrigger = rhs.adTrigger;
		adTriggerVal = rhs.adTriggerVal;
		adAutoAck = rhs.adAutoAck;
		adActive = rhs.adActive;
		adPending = rhs.adPending;
		adEnable = rhs.adEnable;

		if (adFeedbackNotAck)
			delete adFeedbackNotAck;

		if (adHWAck)
			delete adHWAck;

		// Feedback No ACK Tag
		if (rhs.adFeedbackNotAck) {
			adFeedbackNotAck = new Tag(*rhs.adFeedbackNotAck);
		} else {
			adFeedbackNotAck = 0;
		}

		// HW ACK Tag
		if (rhs.adHWAck) {
			adHWAck = new Tag(*rhs.adHWAck);
		} else {
			adHWAck = 0;
		}
	}

	return *this;
}

AlarmDefinitionItem::~AlarmDefinitionItem() {
	if (adFeedbackNotAck)
		delete adFeedbackNotAck;

	if (adHWAck)
		delete adHWAck;
}

void AlarmDefinitionItem::checkId(unsigned int id) const {
	if (id == 0)
		throw AlarmException(AlarmException::ExceptionType::WRONG_ID,
								"Invalid alarm definition identifier",
								"AlarmDefinitionItem::checkId");
}

unsigned int AlarmDefinitionItem::getId() const {
	checkId(adid);

	return adid;
}

void AlarmDefinitionItem::setId(unsigned int id) {
	checkId(id);

	adid = id;
}

const Tag& AlarmDefinitionItem::getTag() const {
	return adTag;
}

void AlarmDefinitionItem::setTag(const Tag& tag) {
	adTag = tag;
}

unsigned char AlarmDefinitionItem::getPriority() const {
	return adPriority;
}

void AlarmDefinitionItem::setPriority(unsigned char pr) {
	adPriority = pr;
}

void AlarmDefinitionItem::checkMsg(const std::string& msg) const {
	if (msg.length() == 0)
		throw AlarmException(AlarmException::ExceptionType::WRONG_MSG,
								"Message string is empty",
								"AlarmDefinitionItem::getMsg");
}

const std::string& AlarmDefinitionItem::getMsg() const {
	checkMsg(adMessage);

	return adMessage;
}

void AlarmDefinitionItem::setMsg(const std::string& msg) {
	checkMsg(msg);

	adMessage = msg;
}

void AlarmDefinitionItem::checkTrigger(const triggers& trig) const {
	bool triggerOK = false;

	// Check type
	switch (trig) {
		case T_BIN: triggerOK = true; break;
		case T_Tag_GT_value: triggerOK = true; break;
		case T_Tag_LT_value: triggerOK = true; break;
		case T_Tag_GE_value: triggerOK = true; break;
		case T_Tag_LE_value: triggerOK = true; break;
		case T_Tag_EQ_value: triggerOK = true; break;
		case T_Tag_NE_value: triggerOK = true; break;
	}

	if (!triggerOK)
		throw AlarmException(AlarmException::ExceptionType::WRONG_TRIGGER,
										"Wrong trigger value",
										"AlarmDefinitionItem::checkTrigger");
}

const AlarmDefinitionItem::triggers& AlarmDefinitionItem::getTrigger() const {
	checkTrigger(adTrigger);

	return adTrigger;
}

void AlarmDefinitionItem::setTrigger(const triggers& tr) {
	checkTrigger(tr);

	adTrigger = tr;
}

const AlarmDefinitionItem::triggerValues& AlarmDefinitionItem::getTriggerValues() const {
	return adTriggerVal;
}

void AlarmDefinitionItem::setTriggerValues(const triggerValues& trigVal) {
	adTriggerVal = trigVal;
}

bool AlarmDefinitionItem::isAutoAck() const {
	return adAutoAck;
}

void AlarmDefinitionItem::setAutoAck(bool aack) {
	adAutoAck = aack;
}

bool AlarmDefinitionItem::isActive() const {
	return adActive;
}

void AlarmDefinitionItem::setActive(bool act) {
	adActive = act;
}

bool AlarmDefinitionItem::isPending() const {
	return adPending;
}

void AlarmDefinitionItem::setPending(bool pending) {
	adPending = pending;
}

void AlarmDefinitionItem::checkBitTagType(const Tag& tg) const {
	if (tg.getType() != TT_BIT)
		throw AlarmException(AlarmException::ExceptionType::WRONG_TAG_TYPE,
											"Wrong tag type - need BIT type",
											"AlarmDefinitionItem::checkBitTagType");
}

void AlarmDefinitionItem::setFeedbackNotAckTag(const Tag& feedbackNotAckTag) {
	checkBitTagType(feedbackNotAckTag);

	if (adFeedbackNotAck) {
		delete adFeedbackNotAck;
		adFeedbackNotAck = 0;
	}

	adFeedbackNotAck = new Tag(feedbackNotAckTag);
}

const Tag& AlarmDefinitionItem::getFeedbackNotAckTag() const {
	if (!adFeedbackNotAck)
		throw AlarmException(AlarmException::NO_FEEDBACK_NOT_ACK_TAG,
									"No feedback not ack tag",
									"AlarmDefinitionItem::getFeedbackNotAckTag");

	checkBitTagType(*adFeedbackNotAck);

	return *adFeedbackNotAck;
}

void AlarmDefinitionItem::setHWAckTag(const Tag& ackTag) {
	checkBitTagType(ackTag);

	if (adHWAck) {
		delete adHWAck;
		adHWAck = 0;
	}

	adHWAck = new Tag(ackTag);
}

const Tag& AlarmDefinitionItem::getHWAckTag() const {
	if (!adHWAck)
		throw AlarmException(AlarmException::NO_HW_ACK_TAG,
									"No HW ack tag",
									"AlarmDefinitionItem::getHWAckTag");

	checkBitTagType(*adHWAck);

	return *adHWAck;
}

bool AlarmDefinitionItem::isEnabled() const {
	return adEnable;
}

void AlarmDefinitionItem::setEnable(bool enable) {
	adEnable = enable;
}

void AlarmDefinitionItem::checkUpdateAndTrigger(triggerRet& tr) const {
	// Check if alarm state need to be updated
	if (isActive() != tr.active) {
		tr.activeUpdate = true;
	}

	// Check if alarm need to be added to the pending table
	if (tr.active && !isPending()) {
		tr.trigger = true;
	}
}

AlarmDefinitionItem::triggerRet AlarmDefinitionItem::checkTrigger(bool tagValue) const {
	// Return value;
	AlarmDefinitionItem::triggerRet ret;

	// Check Tag type
	if (adTag.getType() != TT_BIT)
		throw AlarmException(AlarmException::ExceptionType::WRONG_TAG_TYPE,
									"Wrong tag type",
									"AlarmDefinitionItem::checkTrigger (BIN)");

	// Check trigger type
	if (getTrigger() != AlarmDefinitionItem::T_BIN)
		throw AlarmException(AlarmException::ExceptionType::WRONG_TRIGGER,
									"Wrong trigger type",
									"AlarmDefinitionItem::checkTrigger (BIN)");

	// Check alarm state
	if (tagValue == getTriggerValues().binVal) {
		ret.active = true;
	}

	// Check if alarm state need to be updated and added to the pending table
	checkUpdateAndTrigger(ret);

	return ret;
}

AlarmDefinitionItem::triggerRet AlarmDefinitionItem::checkTrigger(BYTE tagValue) const {
	// Return value;
	AlarmDefinitionItem::triggerRet ret;

	// Check Tag type
	if (adTag.getType() != TT_BYTE)
		throw AlarmException(AlarmException::ExceptionType::WRONG_TAG_TYPE,
									"Wrong tag type",
									"AlarmDefinitionItem::checkTrigger (BYTE)");

	// Check trigger type
	if (getTrigger() == AlarmDefinitionItem::T_BIN)
		throw AlarmException(AlarmException::ExceptionType::WRONG_TRIGGER,
									"Wrong trigger type",
									"AlarmDefinitionItem::checkTrigger (BYTE)");

	// Check trigger
	switch (getTrigger()) {
		case AlarmDefinitionItem::T_Tag_GT_value: {
			if (tagValue > getTriggerValues().dwVal) {
				ret.active = true;
			}
		} break;
		case AlarmDefinitionItem::T_Tag_LT_value: {
			if (tagValue < getTriggerValues().dwVal) {
				ret.active = true;
			}
		} break;
		case AlarmDefinitionItem::T_Tag_GE_value: {
			if (tagValue >= getTriggerValues().dwVal) {
				ret.active = true;
			}
		} break;
		case AlarmDefinitionItem::T_Tag_LE_value: {
			if (tagValue <= getTriggerValues().dwVal) {
				ret.active = true;
			}
		} break;
		case AlarmDefinitionItem::T_Tag_EQ_value: {
			if (tagValue == getTriggerValues().dwVal) {
				ret.active = true;
			}
		} break;
		case AlarmDefinitionItem::T_Tag_NE_value: {
			if (tagValue != getTriggerValues().dwVal) {
				ret.active = true;
			}
		} break;
		default: ret.active = false; break;
	}

	// Check if alarm state need to be updated and added to the pending table
	checkUpdateAndTrigger(ret);

	return ret;
}

AlarmDefinitionItem::triggerRet AlarmDefinitionItem::checkTrigger(WORD tagValue) const {
	// Return value;
	AlarmDefinitionItem::triggerRet ret;

	// Check Tag type
	if (adTag.getType() != TT_WORD)
		throw AlarmException(AlarmException::ExceptionType::WRONG_TAG_TYPE,
									"Wrong tag type",
									"AlarmDefinitionItem::checkTrigger (WORD)");

	// Check trigger type
	if (getTrigger() == AlarmDefinitionItem::T_BIN)
		throw AlarmException(AlarmException::ExceptionType::WRONG_TRIGGER,
									"Wrong trigger type",
									"AlarmDefinitionItem::checkTrigger (WORD)");

	// Check trigger
	switch (getTrigger()) {
		case AlarmDefinitionItem::T_Tag_GT_value: {
			if (tagValue > getTriggerValues().dwVal) {
				ret.active = true;
			}
		} break;
		case AlarmDefinitionItem::T_Tag_LT_value: {
			if (tagValue < getTriggerValues().dwVal) {
				ret.active = true;
			}
		} break;
		case AlarmDefinitionItem::T_Tag_GE_value: {
			if (tagValue >= getTriggerValues().dwVal) {
				ret.active = true;
			}
		} break;
		case AlarmDefinitionItem::T_Tag_LE_value: {
			if (tagValue <= getTriggerValues().dwVal) {
				ret.active = true;
			}
		} break;
		case AlarmDefinitionItem::T_Tag_EQ_value: {
			if (tagValue == getTriggerValues().dwVal) {
				ret.active = true;
			}
		} break;
		case AlarmDefinitionItem::T_Tag_NE_value: {
			if (tagValue != getTriggerValues().dwVal) {
				ret.active = true;
			}
		} break;
		default: ret.active = false; break;
	}

	// Check if alarm state need to be updated and added to the pending table
	checkUpdateAndTrigger(ret);

	return ret;
}

AlarmDefinitionItem::triggerRet AlarmDefinitionItem::checkTrigger(DWORD tagValue) const {
	// Return value;
	AlarmDefinitionItem::triggerRet ret;

	// Check Tag type
	if (adTag.getType() != TT_DWORD)
		throw AlarmException(AlarmException::ExceptionType::WRONG_TAG_TYPE,
									"Wrong tag type",
									"AlarmDefinitionItem::checkTrigger (DWORD)");

	// Check trigger type
	if (getTrigger() == AlarmDefinitionItem::T_BIN)
		throw AlarmException(AlarmException::ExceptionType::WRONG_TRIGGER,
									"Wrong trigger type",
									"AlarmDefinitionItem::checkTrigger (DWORD)");

	// Check trigger
	switch (getTrigger()) {
		case AlarmDefinitionItem::T_Tag_GT_value: {
			if (tagValue > getTriggerValues().dwVal) {
				ret.active = true;
			}
		} break;
		case AlarmDefinitionItem::T_Tag_LT_value: {
			if (tagValue < getTriggerValues().dwVal) {
				ret.active = true;
			}
		} break;
		case AlarmDefinitionItem::T_Tag_GE_value: {
			if (tagValue >= getTriggerValues().dwVal) {
				ret.active = true;
			}
		} break;
		case AlarmDefinitionItem::T_Tag_LE_value: {
			if (tagValue <= getTriggerValues().dwVal) {
				ret.active = true;
			}
		} break;
		case AlarmDefinitionItem::T_Tag_EQ_value: {
			if (tagValue == getTriggerValues().dwVal) {
				ret.active = true;
			}
		} break;
		case AlarmDefinitionItem::T_Tag_NE_value: {
			if (tagValue != getTriggerValues().dwVal) {
				ret.active = true;
			}
		} break;
		default: ret.active = false; break;
	}

	// Check if alarm state need to be updated and added to the pending table
	checkUpdateAndTrigger(ret);

	return ret;
}

AlarmDefinitionItem::triggerRet AlarmDefinitionItem::checkTrigger(int tagValue) const {
	// Return value;
	AlarmDefinitionItem::triggerRet ret;

	// Check Tag type
	if (adTag.getType() != TT_INT)
		throw AlarmException(AlarmException::ExceptionType::WRONG_TAG_TYPE,
									"Wrong tag type",
									"AlarmDefinitionItem::checkTrigger (INT)");

	// Check trigger type
	if (getTrigger() == AlarmDefinitionItem::T_BIN)
		throw AlarmException(AlarmException::ExceptionType::WRONG_TRIGGER,
										"Wrong trigger type",
										"AlarmDefinitionItem::checkTrigger (INT)");

	// Check trigger
	switch (getTrigger()) {
		case AlarmDefinitionItem::T_Tag_GT_value: {
			if (tagValue > getTriggerValues().intVal) {
				ret.active = true;
			}
		} break;
		case AlarmDefinitionItem::T_Tag_LT_value: {
			if (tagValue < getTriggerValues().intVal) {
				ret.active = true;
			}
		} break;
		case AlarmDefinitionItem::T_Tag_GE_value: {
			if (tagValue >= getTriggerValues().intVal) {
				ret.active = true;
			}
		} break;
		case AlarmDefinitionItem::T_Tag_LE_value: {
			if (tagValue <= getTriggerValues().intVal) {
				ret.active = true;
			}
		} break;
		case AlarmDefinitionItem::T_Tag_EQ_value: {
			if (tagValue == getTriggerValues().intVal) {
				ret.active = true;
			}
		} break;
		case AlarmDefinitionItem::T_Tag_NE_value: {
			if (tagValue != getTriggerValues().intVal) {
				ret.active = true;
			}
		} break;
		default: ret.active = false; break;
	}

	// Check if alarm state need to be updated and added to the pending table
	checkUpdateAndTrigger(ret);

	return ret;
}

AlarmDefinitionItem::triggerRet AlarmDefinitionItem::checkTrigger(float tagValue) const {
	// Return value;
	AlarmDefinitionItem::triggerRet ret;

	// Check Tag type
	if (adTag.getType() != TT_REAL)
		throw AlarmException(AlarmException::ExceptionType::WRONG_TAG_TYPE,
									"Wrong tag type",
									"AlarmDefinitionItem::checkTrigger (REAL)");

	// Check trigger type
	if (getTrigger() == AlarmDefinitionItem::T_BIN)
		throw AlarmException(AlarmException::ExceptionType::WRONG_TRIGGER,
											"Wrong trigger type",
											"AlarmDefinitionItem::checkTrigger (REAL)");

	// Check trigger
	switch (getTrigger()) {
		case AlarmDefinitionItem::T_Tag_GT_value: {
			if (tagValue > getTriggerValues().realVal) {
				ret.active = true;
			}
		} break;
		case AlarmDefinitionItem::T_Tag_LT_value: {
			if (tagValue < getTriggerValues().realVal) {
				ret.active = true;
			}
		} break;
		case AlarmDefinitionItem::T_Tag_GE_value: {
			if (tagValue >= getTriggerValues().realVal) {
				ret.active = true;
			}
		} break;
		case AlarmDefinitionItem::T_Tag_LE_value: {
			if (tagValue <= getTriggerValues().realVal) {
				ret.active = true;
			}
		} break;
		case AlarmDefinitionItem::T_Tag_EQ_value: {
			if (tagValue == getTriggerValues().realVal) {
				ret.active = true;
			}
		} break;
		case AlarmDefinitionItem::T_Tag_NE_value: {
			if (tagValue != getTriggerValues().realVal) {
				ret.active = true;
			}
		} break;
		default: ret.active = false; break;
	}

	// Check if alarm state need to be updated and added to the pending table
	checkUpdateAndTrigger(ret);

	return ret;
}

}  // namespace onh
