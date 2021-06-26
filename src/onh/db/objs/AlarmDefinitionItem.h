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

#ifndef ONH_DB_OBJS_ALARMDEFINITIONITEM_H_
#define ONH_DB_OBJS_ALARMDEFINITIONITEM_H_

#include <memory>
#include "Tag.h"
#include "AlarmException.h"
#include "../../driver/DriverRegisterTypes.h"

namespace onh {

/**
 * Alarm definition item class
 */
class AlarmDefinitionItem {
	public:
		/**
		 * Alarm trigger types
		 */
		typedef enum {
			/// Tag binary
			T_BIN = 1,
			/// Tag > value
			T_Tag_GT_value = 2,
			/// Tag < value
			T_Tag_LT_value = 3,
			/// Tag >=value
			T_Tag_GE_value = 4,
			/// Tag <= value
			T_Tag_LE_value = 5,
			/// Tag = value
			T_Tag_EQ_value = 6,
			/// Tag != value
			T_Tag_NE_value = 7
		} triggers;

		/**
		 * Alarm trigger values
		 */
		class triggerValues {
			public:
				triggerValues(): binVal(false), dwVal(0), intVal(0), realVal(0.0) {}

				/**
				 * Constructor
				 *
				 * @param b Binary trigger value
				 * @param dw DWORD trigger value
				 * @param i INT trigger value
				 * @param r REAL trigger value
				 */
				triggerValues(bool b, DWORD dw, int i, float r): binVal(b), dwVal(dw), intVal(i), realVal(r) {}

				/// Binary trigger value
				bool binVal;
				/// Numeric (DWORD) trigger value
				DWORD dwVal;
				/// Numeric (INT) trigger value
				int intVal;
				/// Real trigger value
				float realVal;
		};

		/**
		 * Checking alarm triggering return values
		 */
		class triggerRet {
			public:
				triggerRet(): trigger(false), active(false), activeUpdate(false) {}

				/// Trigger status (put into the pending table)
				bool trigger;
				/// Alarm status
				bool active;
				/// Flag informs that active flag need to be updated
				bool activeUpdate;
		};

		AlarmDefinitionItem();

		/**
		 * Alarm definition item constructor
		 *
		 * @param id Alarm definition identifier
		 * @param tag Tag object
		 * @param priority Alarm priority (1 - High, 2 - Normal, 3 - Warning, ...)
		 * @param msg Alarm message
		 * @param trig Alarm trigger
		 * @param trigVal Alarm trigger values
		 * @param aAck Alarm is automatic acknowledgment
		 * @param active Alarm is active
		 * @param pending Alarm is in pending table
		 * @param enable Alarm definition enable flag
		 */
		AlarmDefinitionItem(unsigned int id,
							const Tag& tag,
							unsigned char priority,
							const std::string& msg,
							triggers trig,
							triggerValues trigVal,
							bool aAck,
							bool active,
							bool pending,
							bool enabled);

		/**
		 * Alarm definition item constructor with feedback Tags
		 *
		 * @param id Alarm definition identifier
		 * @param tag Tag object
		 * @param priority Alarm priority (1 - High, 2 - Normal, 3 - Warning, ...)
		 * @param msg Alarm message
		 * @param trig Alarm trigger
		 * @param trigVal Alarm trigger values
		 * @param aAck Alarm is automatic acknowledgment
		 * @param active Alarm is active
		 * @param pending Alarm is in pending table
		 * @param feedbackNotAck Tag informs controller that alarm is not acknowledgment
		 * @param hwAck Controller HW acknowledgment Tag
		 * @param enable Alarm definition enable flag
		 */
		AlarmDefinitionItem(unsigned int id,
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
							bool enabled);

		/**
		 * Alarm definition item copy constructor
		 *
		 * @param rhs Alarm definition item object to copy
		 */
		AlarmDefinitionItem(const AlarmDefinitionItem& rhs);

		/**
		 * Alarm definition item assignment operator
		 *
		 * @param rhs Alarm definition item object to copy
		 */
		AlarmDefinitionItem& operator=(const AlarmDefinitionItem& rhs);

		virtual ~AlarmDefinitionItem();

		/**
		 * Get Alarm definition identifier
		 *
		 * @return Alarm definition id
		 */
		unsigned int getId() const;

		/**
		 * Set Alarm definition identifier
		 *
		 * @param id Alarm definition identifier
		 */
		void setId(unsigned int id);

		/**
		 * Get Tag object
		 *
		 * @return Tag object
		 */
		const Tag& getTag() const;

		/**
		 * Set Tag object
		 *
		 * @param tag Tag object
		 */
		void setTag(const Tag& tag);

		/**
		 * Get Alarm priority
		 *
		 * @return Alarm priority
		 */
		unsigned char getPriority() const;

		/**
		 * Set Alarm priority
		 *
		 * @param pr Alarm priority
		 */
		void setPriority(unsigned char pr);

		/**
		 * Get Alarm message
		 *
		 * @return Alarm message
		 */
		const std::string& getMsg() const;

		/**
		 * Set Alarm message
		 *
		 * @param msg Alarm message
		 */
		void setMsg(const std::string& msg);

		/**
		 * Get Alarm trigger
		 *
		 * @return Alarm trigger
		 */
		const triggers& getTrigger() const;

		/**
		 * Set Alarm trigger
		 *
		 * @param tr Alarm trigger
		 */
		void setTrigger(const triggers& tr);

		/**
		 * Get Alarm trigger values
		 *
		 * @return Alarm trigger values
		 */
		const triggerValues& getTriggerValues() const;

		/**
		 * Set Alarm trigger values
		 *
		 * @param trigVal Alarm trigger values
		 */
		void setTriggerValues(const triggerValues& trigVal);

		/**
		 * Flag informs that alarm is automatic acknowledgment
		 *
		 * @return True if alarm is automatic acknowledgment
		 */
		bool isAutoAck() const;

		/**
		 * Set flag informs that alarm is automatic acknowledgment
		 *
		 * @param aack Alarm automatic acknowledgment flag
		 */
		void setAutoAck(bool aack);

		/**
		 * Flag informs that alarm is active
		 *
		 * @return True if alarm is active
		 */
		bool isActive() const;

		/**
		 * Set flag informs that alarm is active
		 *
		 * @param act Alarm activation flag
		 */
		void setActive(bool act);

		/**
		 * Is alarm in the pending table
		 *
		 * @return True if alarm is in pending table
		 */
		bool isPending() const;

		/**
		 * Set Alarm definition pending flag
		 *
		 * @param pending Alarm definition pending flag
		 */
		void setPending(bool pending);

		/**
		 * Set Tag informs controller that alarm is not acknowledgment
		 *
		 * @param feedbackNotAckTag Controller Feedback Tag
		 */
		void setFeedbackNotAckTag(const Tag& feedbackNotAckTag);

		/**
		 * Get Tag informs controller that alarm is not acknowledgment
		 *
		 * @return Controller Feedback Tag
		 */
		const Tag& getFeedbackNotAckTag() const;

		/**
		 * Set Tag HW alarm acknowledgment
		 *
		 * @param feedbackNotAckTag Controller HW acknowledgment Tag
		 */
		void setHWAckTag(const Tag& ackTag);

		/**
		 * Get Controller HW acknowledgment Tag
		 *
		 * @return Controller HW acknowledgment Tag
		 */
		const Tag& getHWAckTag() const;

		/**
		 * Get Alarm definition enable flag
		 *
		 * @return Alarm definition enable flag
		 */
		bool isEnabled() const;

		/**
		 * Set Alarm definition enable flag
		 *
		 * @param enable Alarm definition enable flag
		 */
		void setEnable(bool enable);

		/**
		 * Check if alarm should be triggered (put into the pending table).
		 * Check if active flag should be updated.
		 *
		 * @param tagValue Tag value (BIN)
		 * @return Flags with trigger and active information.
		 */
		triggerRet checkTrigger(bool tagValue) const;

		/**
		 * Check if alarm should be triggered (put into the pending table).
		 * Check if active flag should be updated.
		 *
		 * @param tagValue Tag value (BYTE)
		 * @return Flags with trigger and active information.
		 */
		triggerRet checkTrigger(BYTE tagValue) const;

		/**
		 * Check if alarm should be triggered (put into the pending table).
		 * Check if active flag should be updated.
		 *
		 * @param tagValue Tag value (WORD)
		 * @return Flags with trigger and active information.
		 */
		triggerRet checkTrigger(WORD tagValue) const;

		/**
		 * Check if alarm should be triggered (put into the pending table).
		 * Check if active flag should be updated.
		 *
		 * @param tagValue Tag value (DWORD)
		 * @return Flags with trigger and active information.
		 */
		triggerRet checkTrigger(DWORD tagValue) const;

		/**
		 * Check if alarm should be triggered (put into the pending table).
		 * Check if active flag should be updated.
		 *
		 * @param tagValue Tag value (INT)
		 * @return Flags with trigger and active information.
		 */
		triggerRet checkTrigger(int tagValue) const;

		/**
		 * Check if alarm should be triggered (put into the pending table).
		 * Check if active flag should be updated.
		 *
		 * @param tagValue Tag value (REAL)
		 * @return Flags with trigger and active information.
		 */
		triggerRet checkTrigger(float tagValue) const;

	private:
		/// Alarm definition identifier
		unsigned int adid;

		/// Tag object
		Tag adTag;

		/// Alarm priority
		unsigned char adPriority;

		/// Alarm message
		std::string adMessage;

		/// Alarm trigger
		triggers adTrigger;

		/// Alarm trigger value
		triggerValues adTriggerVal;

		/// Flag informs that alarm is automatic acknowledgment
		bool adAutoAck;

		/// Flag informs that alarm is active
		bool adActive;

		/// Flag informs that alarm is already in pending table
		bool adPending;

		/// Tag informs controller that alarm is not acknowledgment (optional)
		std::unique_ptr<Tag> adFeedbackNotAck;

		/// Tag HW alarm acknowledgment (optional)
		std::unique_ptr<Tag> adHWAck;

		/// Alarm definition is enabled
		bool adEnable;

		/**
		 * Check identifier
		 *
		 * @param id Identifier
		 */
		void checkId(unsigned int id) const;

		/**
		 * Check message value
		 *
		 * @param msg Message
		 */
		void checkMsg(const std::string& msg) const;

		/**
		 * Check trigger value
		 *
		 * @param trig Trigger
		 */
		void checkTrigger(const triggers& trig) const;

		/**
		 * Check if tag type is bit
		 *
		 * @param tg Tag
		 */
		void checkBitTagType(const Tag& tg) const;

		/**
		 * Check if alarm state need to be updated and added to the pending table
		 *
		 * @param tr Alarm triggering return values
		 */
		void checkUpdateAndTrigger(triggerRet& tr) const;
};

}  // namespace onh

#endif  // ONH_DB_OBJS_ALARMDEFINITIONITEM_H_
