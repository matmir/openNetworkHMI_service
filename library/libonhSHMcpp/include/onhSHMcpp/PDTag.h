/**
 * Copyright (c) 2020 Mateusz Mirosławski
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of mosquitto nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef LIBRARY_LIBONHSHMCPP_SRC_PDTAG_H_
#define LIBRARY_LIBONHSHMCPP_SRC_PDTAG_H_

#include "onhSHMcpp/processDataAccess.h"

namespace onh {

	/**
	 * Process data Tag class
	 */
	template <class T>
	class PDTag {

		public:

			/**
			 * Constructor
			 *
			 * @param tagAddr Tag address
			 * @param procDT Process data access object
			 */
			PDTag(const processDataAddress &tagAddr, const processDataAccess &procDT);

			/**
			 * Copy constructor
			 *
			 * @param pdt Tag object to copy
			 */
			PDTag(const PDTag &pdt);

			virtual ~PDTag();

			/**
			 * Conversion to build in type
			 */
			operator T();

			/**
			 * Assignment operator (assign only tag value)
			 *
			 * @param pdt Tag object to copy
			 *
			 * @return Tag object
			 */
			PDTag & operator=(const PDTag &pdt);

			/**
			 * Assignment operator (assign only tag value)
			 *
			 * @param val Value to assign
			 *
			 * @return Tag object
			 */
			PDTag & operator=(const T val);

			/**
			 * += operator (values)
			 *
			 * @param pdt Tag object
			 *
			 * @return Tag object
			 */
			PDTag & operator+=(const PDTag &pdt);

			/**
			 * += operator (values)
			 *
			 * @param val Value to use
			 *
			 * @return Tag object
			 */
			PDTag & operator+=(const T val);

			/**
			 * -= operator (values)
			 *
			 * @param pdt Tag object
			 *
			 * @return Tag object
			 */
			PDTag & operator-=(const PDTag &pdt);

			/**
			 * -= operator (values)
			 *
			 * @param val Value to use
			 *
			 * @return Tag object
			 */
			PDTag & operator-=(const T val);

			/**
			 * *= operator (values)
			 *
			 * @param pdt Tag object
			 *
			 * @return Tag object
			 */
			PDTag & operator*=(const PDTag &pdt);

			/**
			 * *= operator (values)
			 *
			 * @param val Value to use
			 *
			 * @return Tag object
			 */
			PDTag & operator*=(const T val);

			/**
			 * /= operator (values)
			 *
			 * @param pdt Tag object
			 *
			 * @return Tag object
			 */
			PDTag & operator/=(const PDTag &pdt);

			/**
			 * /= operator (values)
			 *
			 * @param val Value to use
			 *
			 * @return Tag object
			 */
			PDTag & operator/=(const T val);

			/**
			 * Add operator (values)
			 *
			 * @param pdt Tag object
			 *
			 * @return Tag value
			 */
			T operator+(const PDTag &pdt);

			/**
			 * Add operator (values)
			 *
			 * @param val Value to assign
			 *
			 * @return Tag value
			 */
			T operator+(const T val);

			/**
			 * Sub operator (values)
			 *
			 * @param pdt Tag object
			 *
			 * @return Tag value
			 */
			T operator-(const PDTag &pdt);

			/**
			 * Sub operator (values)
			 *
			 * @param val Value to assign
			 *
			 * @return Tag value
			 */
			T operator-(const T val);

			/**
			 * Multiply operator (values)
			 *
			 * @param pdt Tag object
			 *
			 * @return Tag value
			 */
			T operator*(const PDTag &pdt);

			/**
			 * Add operator (values)
			 *
			 * @param val Value to assign
			 *
			 * @return Tag value
			 */
			T operator*(const T val);

			/**
			 * Divide operator (values)
			 *
			 * @param pdt Tag object
			 *
			 * @return Tag value
			 */
			T operator/(const PDTag &pdt);

			/**
			 * Divide operator (values)
			 *
			 * @param val Value to assign
			 *
			 * @return Tag value
			 */
			T operator/(const T val);

			/**
			 * Operator ++Tag
			 *
			 * @return Tag object
			 */
			const PDTag & operator++();

			/**
			 * Operator Tag++
			 *
			 * @param flag
			 *
			 * @return Tag value
			 */
			T operator++(int);

		private:

			/// Process data access
			processDataAccess *pda;

			/// Tag process address
			processDataAddress addr;
	};

} /* namespace onh */

#endif /* LIBRARY_LIBONHSHMCPP_SRC_PDTAG_H_ */
