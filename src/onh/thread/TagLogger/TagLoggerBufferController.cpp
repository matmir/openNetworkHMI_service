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

TagLoggerBufferController::TagLoggerBufferController():
	buffLock(), buff(0), finishLock(), controllerInsertFinished(0), readOnly(false)
{
}

TagLoggerBufferController::TagLoggerBufferController(const TagLoggerBufferController& tlbc):
	buffLock(tlbc.buffLock), buff(tlbc.buff), finishLock(tlbc.finishLock), controllerInsertFinished(tlbc.controllerInsertFinished), readOnly(tlbc.readOnly)
{
}

TagLoggerBufferController::TagLoggerBufferController(const MutexAccess &bLock, std::vector<TagLoggerItem> *b, const MutexAccess &fLock, bool *finishFlag, bool readOnlyFlag):
	buffLock(bLock), buff(b), finishLock(fLock), controllerInsertFinished(finishFlag), readOnly(readOnlyFlag)
{
}

TagLoggerBufferController::~TagLoggerBufferController()
{
}

void TagLoggerBufferController::putData(const std::vector<TagLoggerItem> &data) {

	if (readOnly)
		throw Exception("Tag logger buffer controller is in read only state", "TagLoggerBufferController::putData");

	if (!buff)
		throw Exception("Buffer handle not initialized", "TagLoggerBufferController::putData");

	// Lock access to the buffer
	buffLock.lock();

	// Insert new data to the buffer
	for (unsigned int i=0; i<data.size(); ++i) {
		buff->push_back(data[i]);
	}

	// Unlock access to the buffer
	buffLock.unlock();
}

void TagLoggerBufferController::getData(std::vector<TagLoggerItem> &data) {

	if (!readOnly)
		throw Exception("Tag logger buffer controller is in write only state", "TagLoggerBufferController::getData");

	if (!buff)
		throw Exception("Buffer handle not initialized", "TagLoggerBufferController::getData");

	// Lock access to the buffer
	buffLock.lock();

	// Copy data from buffer to the input vector
	for (unsigned int i=0; i<buff->size(); ++i) {
		data.push_back(buff->at(i));
	}

	// Clear buffer
	buff->clear();

	// Unlock access to the buffer
	buffLock.unlock();
}

bool TagLoggerBufferController::isEmpty() {

	bool ret = false;

	// Lock access to the buffer
	buffLock.lock();

	// Check buffer size
	ret = (buff->size()==0)?(true):(false);

	// Unlock access to the buffer
	buffLock.unlock();

	return ret;
}

void TagLoggerBufferController::setFinished() {

	if (readOnly)
		throw Exception("Tag logger buffer controller is in read only state", "TagLoggerBufferController::setFinished");

	if (!controllerInsertFinished)
		throw Exception("Buffer handle not initialized", "TagLoggerBufferController::setFinished");

	// Lock access to the flag
	finishLock.lock();

	*controllerInsertFinished = true;

	// Unlock access to the flag
	finishLock.unlock();
}

bool TagLoggerBufferController::isFinished() {

	if (!readOnly)
		throw Exception("Tag logger buffer controller is in write only state", "TagLoggerBufferController::isFinished");

	if (!controllerInsertFinished)
		throw Exception("Buffer handle not initialized", "TagLoggerBufferController::isFinished");

	bool ret = false;

	// Lock access to the flag
	finishLock.lock();

	ret = *controllerInsertFinished;

	// Unlock access to the flag
	finishLock.unlock();

	return ret;
}
