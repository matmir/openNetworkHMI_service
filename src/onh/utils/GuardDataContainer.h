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

#ifndef SRC_ONH_UTILS_GUARDDATACONTAINER_H_
#define SRC_ONH_UTILS_GUARDDATACONTAINER_H_

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
			GuardDataContainer(const T& newData);

			/**
			 * Copy constructor - inactive
			 */
			GuardDataContainer(const GuardDataContainer&) = delete;

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

		private:

			/// Guarded data
			T *data;

			/// Mutex for protecting data
			MutexContainer dataLock;
	};

	template <class T>
	GuardDataContainer<T>::GuardDataContainer():
		data(nullptr)
	{
		data = new T;
	}

	template <class T>
	GuardDataContainer<T>::GuardDataContainer(const T& newData):
		data(nullptr)
	{
		data = new T(newData);
	}

	template <class T>
	GuardDataContainer<T>::~GuardDataContainer() {
		if (data)
			delete data;
	}

	template <class T>
	GuardDataController<T> GuardDataContainer<T>::getController(bool readOnly) {

		return GuardDataController<T>(data, dataLock.getAccess(), readOnly);
	}

}

#endif /* SRC_ONH_UTILS_GUARDDATACONTAINER_H_ */
