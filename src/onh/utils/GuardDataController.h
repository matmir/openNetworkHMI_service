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

#ifndef SRC_ONH_UTILS_GUARDDATACONTROLLER_H_
#define SRC_ONH_UTILS_GUARDDATACONTROLLER_H_

#include "MutexAccess.h"
#include "Exception.h"

namespace onh {

	/// Forward declaration
	template <class T>
	class GuardDataContainer;

	/**
	 * Guarded data controller class
	 */
	template <class T>
	class GuardDataController {

		public:

			friend class GuardDataContainer<T>;

			/**
			 * Copy constructor
			 *
			 * @param gdc Data controller object to copy
			 */
			GuardDataController(const GuardDataController& gdc);

			virtual ~GuardDataController();

			/**
			 * Assign operator - inactive
			 */
			GuardDataController& operator=(const GuardDataController&) = delete;

			/**
			 * Get data
			 *
			 * @param dt Copy of the data
			 */
			void getData(T &dt);

			/**
			 * Set data
			 *
			 * @param newData Data to copy
			 */
			void setData(const T& newData);

			/**
			 * Set data from controller
			 *
			 * @param gdc Data controller object
			 */
			void setData(GuardDataController& gdc);

			/**
			 * Lock access to the data
			 */
			void lock();

			/**
			 * Unlock access to the data
			 */
			void unlock();

			/**
			 * Get reference to the data
			 *
			 * @return Reference to the data
			 */
			T& getDataRef();

		private:

			/**
			 * Constructor (allowed only from GuardDataContainer)
			 *
			 * @param dt Pointer to the data
			 * @param dtLock MutexAccess object for protecting data
			 * @param readFlag Read only flag
			 */
			GuardDataController(T *dt, const MutexAccess &dtLock, bool readFlag);

			/// Pointer to the data
			T *data;

			/// Mutex for protecting data
			MutexAccess dataLock;

			/// Read only flag
			bool readOnly;

			/// Run lock function flag
			bool lockCalled;

	};

	template <class T>
	GuardDataController<T>::GuardDataController(const GuardDataController& gdc):
		data(gdc.data), dataLock(gdc.dataLock), readOnly(gdc.readOnly), lockCalled(gdc.lockCalled)
	{
	}

	template <class T>
	GuardDataController<T>::GuardDataController(T *dt, const MutexAccess &dtLock, bool readFlag):
		data(dt), dataLock(dtLock), readOnly(readFlag), lockCalled(false)
	{
	}

	template <class T>
	GuardDataController<T>::~GuardDataController(){
	}

	template <class T>
	void GuardDataController<T>::getData(T &dt) {

		if (!data)
			throw Exception("Data handle not initialized", "GuardDataController::getData");

		// Lock access to the data
		dataLock.lock();

		// Copy data
		dt = *data;

		// Unlock access to the data
		dataLock.unlock();
	}

	template <class T>
	void GuardDataController<T>::setData(const T& newData) {

		if (!data)
			throw Exception("Data handle not initialized", "GuardDataController::setData");

		if (readOnly)
			throw Exception("Data controller is in read only state", "GuardDataController::setData");

		// Lock access to the data
		dataLock.lock();

		// Copy data
		*data = newData;

		// Unlock access to the data
		dataLock.unlock();
	}

	template <class T>
	void GuardDataController<T>::setData(GuardDataController<T>& gdc) {

		if (!data)
			throw Exception("Data handle not initialized", "GuardDataController::setData");

		if (readOnly)
			throw Exception("Data controller is in read only state", "GuardDataController::setData");

		// Lock access to the data
		dataLock.lock();
		gdc.dataLock.lock();

		// Copy data
		*data = *gdc.data;

		// Unlock access to the data
		gdc.dataLock.unlock();
		dataLock.unlock();
	}

	template <class T>
	void GuardDataController<T>::lock() {

		if (readOnly)
			throw Exception("Data controller is in read only state", "GuardDataController::lock");

		// Lock access to the data
		dataLock.lock();

		lockCalled = true;
	}

	template <class T>
	void GuardDataController<T>::unlock() {

		if (readOnly)
			throw Exception("Data controller is in read only state", "GuardDataController::unlock");

		if (lockCalled) {
			// Lock access to the data
			dataLock.unlock();

			lockCalled = false;
		}
	}

	template <class T>
	T& GuardDataController<T>::getDataRef() {

		if (readOnly)
			throw Exception("Data controller is in read only state", "GuardDataController::getDataRef");

		if (!data)
			throw Exception("Data handle not initialized", "GuardDataController::getDataRef");

		if (!lockCalled)
			throw Exception("Data are not locked", "GuardDataController::getDataRef");

		return *data;
	}

}

#endif /* SRC_ONH_UTILS_GUARDDATACONTROLLER_H_ */
