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

#ifndef SCRIPTITEM_H
#define SCRIPTITEM_H

#include "Tag.h"
#include "ScriptException.h"

namespace onh {

    /**
	 * Script item class
	 */
    class ScriptItem {

        public:

            ScriptItem();

            /**
             * Script item constructor
             *
             * @param id Script identifier
             * @param tag Tag object
             * @param name Script name
             * @param run Script run flag
             * @param lock Script lock flag
             * @param enable Script enable flag
             */
            ScriptItem(unsigned int id,
                        const Tag& tag,
                        const std::string& name,
                        bool run,
                        bool lock,
                        bool enabled);

            /**
             * Script item constructor with feedback tag
             *
             * @param id Script identifier
             * @param tag Tag object
             * @param name Script name
             * @param run Script run flag
             * @param lock Script lock flag
             * @param feedbackRun Tag informs controller that script is running
             * @param enable Script enable flag
             */
            ScriptItem(unsigned int id,
                        const Tag& tag,
                        const std::string& name,
                        bool run,
                        bool lock,
                        const Tag& feedbackRun,
                        bool enabled);

            /**
             * Script item copy constructor
             *
             * @param rhs Object to copy
             */
            ScriptItem(const ScriptItem& rhs);

            /**
             * Script item assignment operator
             *
             * @param rhs Script item object to copy
             */
            ScriptItem& operator=(const ScriptItem& rhs);

            virtual ~ScriptItem();

            /**
             * Get Script identifier
             *
             * @return Script id
             */
            unsigned int getId() const;

            /**
             * Set Script identifier
             *
             * @param id Script identifier
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
             *  Get Script name
             *
             * @return Script name
             */
            std::string getName() const;

            /**
             * Set Script name
             *
             * @param name Script name
             */
            void setName(const std::string& name);

            /**
             * Check script run flag
             *
             * @return True if script is running
             */
            bool isRunning() const;

            /**
             * Set script run flag
             *
             * @param run Script run flag
             */
            void setRun(bool run);

            /**
             * Check script lock flag
             *
             * @return True if script is locked
             */
            bool isLocked() const;

            /**
             * Set script lock flag
             *
             * @param lock Script lock flag
             */
            void setLock(bool lock);

            /**
             * Set Tag informs controller that script is running
             *
             * @param feedbackTag Controller Feedback Tag
             */
            void setFeedbackRunTag(const Tag& feedbackTag);

            /**
             * Get Tag informs controller that script is running
             *
             * @return Controller Feedback Tag
             */
            const Tag& getFeedbackRunTag() const;

            /**
             * Get Script enable flag
             *
             * @return Script enable flag
             */
            bool isEnabled() const;

            /**
             * Set Script enable flag
             *
             * @param enable Script enable flag
             */
            void setEnable(bool enable);

        private:

            /// Script identifier
            unsigned int scid;

            /// Tag object
            Tag* scTag;

            /// Script name
            std::string scName;

            /// Script run flag
            bool scRun;

            /// Script lock flag
            bool scLock;

            /// Tag informs controller that script is running (optional)
            Tag* scFeedbackRun;

            /// Script is enabled
            bool scEnable;

            /**
			 * Check identifier
			 *
			 * @param id Identifier
			 */
			void checkId(unsigned int id) const;

			/**
			 * Check script name
			 *
			 * @param nm script name
			 */
			void checkScriptName(const std::string& nm) const;

			/**
			 * Check if tag type is bit
			 *
			 * @param tg Tag
			 */
			void checkBitTagType(const Tag& tg) const;
    };

}

#endif // SCRIPTITEM_H
