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

#ifndef ONH_UTILS_GUARDDATACONTAINER_H_
#define ONH_UTILS_GUARDDATACONTAINER_H_

#include <memory>
#include "MutexContainer.h"
#include "Exception.h"
#include "GuardDataController.h"

namespace onh {

/**
 * Guarded data container class
 */
template <class T>
class GuardDataContainer {
	public:
		/**
		 * Default constructor
		 */
		GuardDataContainer();

		/**
		 * Constructor with data
		 *
		 * @param newData Data to store in container
		 */
		explicit GuardDataContainer(const T& newData);

		/**
		 * Copy constructor
		 *
		 * @param gdc Data container object to copy
		 */
		GuardDataContainer(const GuardDataContainer& gdc);

		virtual ~GuardDataContainer();

		/**
		 * Assign operator - inactive
		 */
		GuardDataContainer& operator=(const GuardDataContainer&) = delete;

		/**
		 * Get guarded data controller object
		 *
		 * @return Guarded data controller object
		 */
		GuardDataController<T> getController(bool readOnly = true);

		/**
		 * Get internal controller object
		 *
		 * @return Internal controller object
		 */
		GuardDataController<T>& controll();

	private:
		/// Guarded data
		std::shared_ptr<T> data;

		/// Mutex for protecting data
		MutexContainer dataLock;

		/// Internal controller object
		std::unique_ptr<GuardDataController<T>> itsController;
};

template <class T>
GuardDataContainer<T>::GuardDataContainer():
	data(std::make_shared<T>()), itsController(nullptr) {
}

template <class T>
GuardDataContainer<T>::GuardDataContainer(const T& newData):
	data(std::make_shared<T>(T(newData))), itsController(nullptr) {
}

template <class T>
GuardDataContainer<T>::GuardDataContainer(const GuardDataContainer& gdc):
	data(std::make_shared<T>(T(*gdc.data))), itsController(nullptr) {
}

template <class T>
GuardDataContainer<T>::~GuardDataContainer() {
}

template <class T>
GuardDataController<T> GuardDataContainer<T>::getController(bool readOnly) {
	return GuardDataController<T>(data, dataLock.getAccess(), readOnly);
}

template <class T>
GuardDataController<T>& GuardDataContainer<T>::controll() {
	if (itsController == nullptr)
		itsController = std::unique_ptr<GuardDataController<T>>(new GuardDataController<T>(data,
																							dataLock.getAccess(),
																							false));

	return *itsController;
}

}  // namespace onh

#endif  // ONH_UTILS_GUARDDATACONTAINER_H_
