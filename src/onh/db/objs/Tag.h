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

#ifndef ONH_DB_OBJS_TAG_H_
#define ONH_DB_OBJS_TAG_H_

#include <string>
#include "TagException.h"
#include "../../driver/ProcessDataTypes.h"

namespace onh {

/**
 * Tag types
 */
typedef enum {
	TT_BIT = 1,
	TT_BYTE = 2,
	TT_WORD = 3,
	TT_DWORD = 4,
	TT_INT = 5,
	TT_REAL = 6
} TagType;

/**
 * Tag class
 */
class Tag {
	public:
		Tag();

		/**
		 * Tag constructor
		 *
		 * @param id Tag identifier
		 * @param cId Driver connection identifier
		 * @param name Tag name
		 * @param type Tag type
		 * @param address Tag address
		 */
		Tag(unsigned int id,
				unsigned int cId,
				const std::string& name,
				const TagType& type,
				const processDataAddress& address);

		/**
		 * Copy constructor - default
		 */
		Tag(const Tag&) = default;

		virtual ~Tag();

		/**
		 * Assign operator - default
		 */
		Tag& operator=(const Tag&) = default;

		/**
		 * Get Tag identifier
		 *
		 * @return Tag id
		 */
		unsigned int getId() const;

		/**
		 * Set Tag identifier
		 *
		 * @param id Tag identifier
		 */
		void setId(unsigned int id);

		/**
		 * Get Driver connection identifier
		 *
		 * @return Driver connection id
		 */
		unsigned int getConnId() const;

		/**
		 * Set Driver connection identifier
		 *
		 * @param id Driver connection identifier
		 */
		void setConnId(unsigned int id);

		/**
		 * Get Tag name
		 *
		 * @return Tag name
		 */
		std::string getName() const;

		/**
		 * Set Tag name
		 *
		 * @param nm Tag name
		 */
		void setName(const std::string& nm);

		/**
		 * Get Tag type
		 *
		 * @return Tag type
		 */
		const TagType& getType() const;

		/**
		 * Set Tag type
		 *
		 * @param type Tag type
		 */
		void setType(const TagType& type);

		/**
		 * Get Tag area
		 *
		 * @return Tag area
		 */
		const processDataArea& getArea() const;

		/**
		 * Set Tag area
		 *
		 * @param area Tag area
		 */
		void setArea(const processDataArea& area);

		/**
		 * Get Tag start byte address
		 *
		 * @return Tag start byte address
		 */
		unsigned int getByteAddress() const;

		/**
		 * Set Tag start byte address
		 *
		 * @param byteAddr Tag start byte address
		 */
		void setByteAddress(unsigned int byteAddr);

		/**
		 * Get Tag start bit address
		 *
		 * @return Tag start bit address
		 */
		unsigned int getBitAddress() const;

		/**
		 * Set Tag start bit address
		 *
		 * @param bitAddr Tag start bit address
		 */
		void setBitAddress(unsigned int bitAddr);

		/**
		 * Get Tag address
		 *
		 * @return Tag address
		 */
		const processDataAddress& getAddress() const;

		/**
		 * Set Tag address
		 *
		 * @param addr Tag address
		 */
		void setAddress(const processDataAddress& addr);

	private:
		/// Tag identifier
		unsigned int tid;

		/// Driver connection identifier
		unsigned int tConnId;

		/// Tag name
		std::string tName;

		/// Tag type
		TagType tType;

		/// Tag address
		processDataAddress tAddress;

		/**
		 * Check Tag identifier
		 *
		 * @param id Identifier
		 */
		void checkId(unsigned int id) const;

		/**
		 * Check Driver connection identifier
		 *
		 * @param id Identifier
		 */
		void checkConnId(unsigned int id) const;

		/**
		 * Check Tag name
		 * @param nm Tag name
		 */
		void checkName(const std::string& nm) const;

		/**
		 * Check Tag type
		 *
		 * @param type Tag type
		 */
		void checkType(const TagType& type) const;

		/**
		 * Check Tag area
		 *
		 * @param area Tag are
		 */
		void checkArea(const processDataArea& area) const;

		/**
		 * Check Tag bit address
		 *
		 * @param bitAddr Tag bit address
		 */
		void checkBitAddress(unsigned int bitAddr) const;
};

}  // namespace onh

#endif  // ONH_DB_OBJS_TAG_H_
