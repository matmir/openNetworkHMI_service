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

#include "TagLoggerBufferController.h"

using namespace onh;

TagLoggerBufferController::TagLoggerBufferController(const TagLoggerBufferController& tlbc):
	buff(tlbc.buff), controllerInsertFinished(tlbc.controllerInsertFinished), readOnly(tlbc.readOnly)
{
}

TagLoggerBufferController::TagLoggerBufferController(const loggerBufferController &lbc, const GuardDataController<bool> &gdcf, bool readOnlyFlag):
	buff(lbc), controllerInsertFinished(gdcf), readOnly(readOnlyFlag)
{
}

TagLoggerBufferController::~TagLoggerBufferController()
{
}

void TagLoggerBufferController::putData(const std::vector<TagLoggerItem> &data) {

	if (readOnly)
		throw Exception("Tag logger buffer controller is in read only state", "TagLoggerBufferController::putData");

	// Lock access to the buffer
	buff.lock();

	// Insert new data to the buffer
	for (unsigned int i=0; i<data.size(); ++i) {
		buff.getDataRef().push_back(data[i]);
	}

	// Unlock access to the buffer
	buff.unlock();
}

void TagLoggerBufferController::getData(std::vector<TagLoggerItem> &data) {

	if (!readOnly)
		throw Exception("Tag logger buffer controller is in write only state", "TagLoggerBufferController::getData");

	// Lock access to the buffer
	buff.lock();

	// Copy data from buffer to the input vector
	for (unsigned int i=0; i<buff.getDataRef().size(); ++i) {
		data.push_back(buff.getDataRef().at(i));
	}

	// Clear buffer
	buff.getDataRef().clear();

	// Unlock access to the buffer
	buff.unlock();
}

bool TagLoggerBufferController::isEmpty() {

	bool ret = false;

	// Lock access to the buffer
	buff.lock();

	// Check buffer size
	ret = (buff.getDataRef().size()==0)?(true):(false);

	// Unlock access to the buffer
	buff.unlock();

	return ret;
}

void TagLoggerBufferController::setFinished() {

	if (readOnly)
		throw Exception("Tag logger buffer controller is in read only state", "TagLoggerBufferController::setFinished");

	controllerInsertFinished.setData(true);
}

bool TagLoggerBufferController::isFinished() {

	bool ret = false;

	controllerInsertFinished.getData(ret);

	return ret;
}
