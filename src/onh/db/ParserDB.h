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

#ifndef ONH_DB_PARSERDB_H_
#define ONH_DB_PARSERDB_H_

#include <vector>
#include "objs/Tag.h"
#include "DB.h"
#include "DBCredentials.h"
#include "AlarmingDB.h"

namespace onh {

/**
 * Class for read/write DB from Parser
 */
class ParserDB: public DB {
	public:
		/**
		 * Parser DB constructor
		 *
		 * @param dbData DB connection data
		 */
		explicit ParserDB(const DBCredentials & dbData);

		/**
		 * Copy constructor
		 *
		 * @param tDB PArserDB to copy
		 */
		ParserDB(const ParserDB &tDB);

		virtual ~ParserDB();

		/**
		 * Assign operator - inactive
		 */
		ParserDB& operator=(const ParserDB&) = delete;

		/**
		 * Get Tag data from DB
		 *
		 * @param tagName String with tag name
		 *
		 * @return Tag object
		 */
		const Tag getTag(const std::string& tagName);

		/**
		 * Get Tags data from DB
		 *
		 * @param tagNames Vector with tag names
		 * @return Vector with Tag objects
		 */
		std::vector<Tag> getTags(std::vector<std::string> tagNames);

		/**
		 * Get access to the alarming DB
		 *
		 * @return Reference to the AlarmingDB object
		 */
		AlarmingDB& getAlarmDB();

	private:
		/**
		 * Get Tag object from SQL resultset
		 *
		 * @param res Reference to the resultset
		 *
		 * @return  Tag objects
		 */
		Tag getTagFromResultset(const DBResult &res);

		/**
		 * Prepare SQL IN array statement
		 *
		 * @param tagNames Vector with tag names
		 *
		 * @return SQL IN array statement
		 */
		std::stringstream prepareIN(const std::vector<std::string> &tagNames);

		/**
		 * Check if Tag names exists in Tag vector
		 *
		 * @param tagNames Vector with tag names
		 * @param vTags Vector with Tag objects
		 */
		void checkTagNamesExist(const std::vector<std::string> &tagNames, const std::vector<Tag> &vTags);

		/// AlarmingDB object
		std::unique_ptr<AlarmingDB> pAlarmDB;
};

}  // namespace onh

#endif  // ONH_DB_PARSERDB_H_
