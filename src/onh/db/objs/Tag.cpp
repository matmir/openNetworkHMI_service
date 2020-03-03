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

#include "Tag.h"
#include "../DB.h"

using namespace onh;

Tag::Tag():
    tid(0), tName(""), tType(TT_BIT), tAddress({PDA_INPUT, 0, 0})
{
}

Tag::Tag(unsigned int id, const std::string& name, const TagType& type, const processDataAddress& address) {

	setId(id);
	setName(name);
	setType(type);
	setAddress(address);
}

Tag::~Tag()
{
}

void Tag::checkId(unsigned int id) const {

	if (id == 0)
		throw TagException(TagException::WRONG_ID, "Invalid tag identifier", "Tag::checkId");
}

void Tag::checkName(const std::string& nm) const {

	// Check empty
	if (nm.size() == 0)
		throw TagException(TagException::WRONG_NAME, "Tag name is empty", "Tag::checkName");

	// Check invalid characters
	if (!DB::checkStringValue(nm))
		throw TagException(TagException::WRONG_NAME, "Tag contains invalid characters", "Tag::checkName");
}

void Tag::checkType(const TagType& type) const {

	bool typeOK = false;

	// Check type
	switch (type) {
		case TT_BIT: typeOK = true; break;
		case TT_BYTE: typeOK = true; break;
		case TT_WORD: typeOK = true; break;
		case TT_DWORD: typeOK = true; break;
		case TT_INT: typeOK = true; break;
		case TT_REAL: typeOK = true; break;
	}

	if (!typeOK)
		throw TagException(TagException::WRONG_TYPE, "Tag has wrong type", "Tag::checkType");
}

void Tag::checkArea(const processDataArea& area) const {

	bool areaOK = false;

	// Check type
	switch (area) {
		case PDA_INPUT: areaOK = true; break;
		case PDA_OUTPUT: areaOK = true; break;
		case PDA_MEMORY: areaOK = true; break;
	}

	if (!areaOK)
		throw TagException(TagException::WRONG_AREA, "Tag has wrong area", "Tag::checkArea");
}

void Tag::checkBitAddress(unsigned int bitAddr) const {

	// Check bit range
	if (bitAddr > 7)
		throw TagException(TagException::BIT_ADDRESS_OUT_OF_RANGE, "Bit address is out of range", "Tag::checkBitAddress");
}

unsigned int Tag::getId() const {

	checkId(tid);

    return tid;
}

void Tag::setId(unsigned int id) {

    checkId(id);

    tid = id;
}

std::string Tag::getName() const {

    checkName(tName);

    return tName;
}

void Tag::setName(const std::string& nm) {

    checkName(nm);

    tName = nm;
}

const TagType& Tag::getType() const {

	checkType(tType);

    return tType;
}

void Tag::setType(const TagType& type) {

	checkType(type);

    tType = type;
}

const processDataArea& Tag::getArea() const {

	checkArea(tAddress.area);

    return tAddress.area;
}

void Tag::setArea(const processDataArea& area) {

	checkArea(area);

	tAddress.area = area;
}

unsigned int Tag::getByteAddress() const {

    return tAddress.byteAddr;
}

void Tag::setByteAddress(unsigned int byteAddr) {

	tAddress.byteAddr = byteAddr;
}

unsigned int Tag::getBitAddress() const {

	checkBitAddress(tAddress.bitAddr);

    return tAddress.bitAddr;
}

void Tag::setBitAddress(unsigned int bitAddr) {

	checkBitAddress(bitAddr);

    tAddress.bitAddr = bitAddr;
}

const processDataAddress& Tag::getAddress() const {

	checkArea(tAddress.area);
	checkBitAddress(tAddress.bitAddr);

	return tAddress;
}

void Tag::setAddress(const processDataAddress& addr) {

	setArea(addr.area);
	setByteAddress(addr.byteAddr);
	setBitAddress(addr.bitAddr);
}
