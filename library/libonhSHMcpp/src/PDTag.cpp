/**
 * Copyright (c) 2022 Mateusz Mirosławski
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

#include "onhSHMcpp/PDTag.h"
#include <type_traits>

using namespace onh;

template <class T>
PDTag<T>::PDTag(const processDataAddress &tagAddr, const processDataAccess &procDT):
	addr(tagAddr), _id(calculateId())
{
	pda = new processDataAccess(procDT);
}

template <class T>
PDTag<T>::PDTag(const PDTag &pdt):
	addr(pdt.addr), _id(calculateId())
{
	pda = new processDataAccess(*pdt.pda);
}

template <class T>
PDTag<T>::~PDTag() {
	if (pda)
		delete pda;
}

template <class T>
PDTag<T>::operator T() {

	T ret;

	// Check type
	if (std::is_same<T, bool>::value) {
		ret = pda->getBit(addr);
	} else if (std::is_same<T, BYTE>::value) {
		ret = pda->getByte(addr);
	} else if (std::is_same<T, WORD>::value) {
		ret = pda->getWord(addr);
	} else if (std::is_same<T, DWORD>::value) {
		ret = pda->getDWord(addr);
	} else if (std::is_same<T, int>::value) {
		ret = pda->getInt(addr);
	} else if (std::is_same<T, float>::value) {
		ret = pda->getReal(addr);
	}

	return ret;
}

template <class T>
PDTag<T> & PDTag<T>::operator=(const PDTag &pdt) {

	// Self assignment
	if (this == &pdt)
		return *this;

	// Check type
	if (std::is_same<T, bool>::value) {
		pda->writeBit(addr, pda->getBit(pdt.addr));
	} else if (std::is_same<T, BYTE>::value) {
		pda->writeByte(addr, pda->getByte(pdt.addr));
	} else if (std::is_same<T, WORD>::value) {
		pda->writeWord(addr, pda->getWord(pdt.addr));
	} else if (std::is_same<T, DWORD>::value) {
		pda->writeDWord(addr, pda->getDWord(pdt.addr));
	} else if (std::is_same<T, int>::value) {
		pda->writeInt(addr, pda->getInt(pdt.addr));
	} else if (std::is_same<T, float>::value) {
		pda->writeReal(addr, pda->getReal(pdt.addr));
	}

	return *this;
}

template <class T>
PDTag<T> & PDTag<T>::operator=(const T val) {

	// Check type
	if (std::is_same<T, bool>::value) {
		pda->writeBit(addr, val);
	} else if (std::is_same<T, BYTE>::value) {
		pda->writeByte(addr, val);
	} else if (std::is_same<T, WORD>::value) {
		pda->writeWord(addr, val);
	} else if (std::is_same<T, DWORD>::value) {
		pda->writeDWord(addr, val);
	} else if (std::is_same<T, int>::value) {
		pda->writeInt(addr, val);
	} else if (std::is_same<T, float>::value) {
		pda->writeReal(addr, val);
	}

	return *this;
}

template <class T>
PDTag<T> & PDTag<T>::operator+=(const PDTag &pdt) {

	// Check type
	if (std::is_same<T, bool>::value) {
		throw ShmException("Can not sum binary values", "PDTag<bool>::operator+= (PDTag<bool>)");
	} else if (std::is_same<T, BYTE>::value) {
		BYTE v = pda->getByte(addr) + pda->getByte(pdt.addr);
		pda->writeByte(addr, v);
	} else if (std::is_same<T, WORD>::value) {
		WORD v = pda->getWord(addr) + pda->getWord(pdt.addr);
		pda->writeWord(addr, v);
	} else if (std::is_same<T, DWORD>::value) {
		DWORD v = pda->getDWord(addr) + pda->getDWord(pdt.addr);
		pda->writeDWord(addr, v);
	} else if (std::is_same<T, int>::value) {
		int v = pda->getInt(addr) + pda->getInt(pdt.addr);
		pda->writeInt(addr, v);
	} else if (std::is_same<T, float>::value) {
		float v = pda->getReal(addr) + pda->getReal(pdt.addr);
		pda->writeReal(addr, v);
	}

	return *this;
}

template <class T>
PDTag<T> & PDTag<T>::operator+=(const T val) {

	// Check type
	if (std::is_same<T, bool>::value) {
		throw ShmException("Can not sum binary values", "PDTag<bool>::operator+= (bool)");
	} else if (std::is_same<T, BYTE>::value) {
		BYTE v = pda->getByte(addr) + val;
		pda->writeByte(addr, v);
	} else if (std::is_same<T, WORD>::value) {
		WORD v = pda->getWord(addr) + val;
		pda->writeWord(addr, v);
	} else if (std::is_same<T, DWORD>::value) {
		DWORD v = pda->getDWord(addr) + val;
		pda->writeDWord(addr, v);
	} else if (std::is_same<T, int>::value) {
		int v = pda->getInt(addr) + val;
		pda->writeInt(addr, v);
	} else if (std::is_same<T, float>::value) {
		float v = pda->getReal(addr) + val;
		pda->writeReal(addr, v);
	}

	return *this;
}

template <class T>
PDTag<T> & PDTag<T>::operator-=(const PDTag &pdt) {

	// Check type
	if (std::is_same<T, bool>::value) {
		throw ShmException("Can not subtract binary values", "PDTag<bool>::operator-= (PDTag<bool>)");
	} else if (std::is_same<T, BYTE>::value) {
		BYTE v = pda->getByte(addr) - pda->getByte(pdt.addr);
		pda->writeByte(addr, v);
	} else if (std::is_same<T, WORD>::value) {
		WORD v = pda->getWord(addr) - pda->getWord(pdt.addr);
		pda->writeWord(addr, v);
	} else if (std::is_same<T, DWORD>::value) {
		DWORD v = pda->getDWord(addr) - pda->getDWord(pdt.addr);
		pda->writeDWord(addr, v);
	} else if (std::is_same<T, int>::value) {
		int v = pda->getInt(addr) - pda->getInt(pdt.addr);
		pda->writeInt(addr, v);
	} else if (std::is_same<T, float>::value) {
		float v = pda->getReal(addr) - pda->getReal(pdt.addr);
		pda->writeReal(addr, v);
	}

	return *this;
}

template <class T>
PDTag<T> & PDTag<T>::operator-=(const T val) {

	// Check type
	if (std::is_same<T, bool>::value) {
		throw ShmException("Can not subtract binary values", "PDTag<bool>::operator-= (bool)");
	} else if (std::is_same<T, BYTE>::value) {
		BYTE v = pda->getByte(addr) - val;
		pda->writeByte(addr, v);
	} else if (std::is_same<T, WORD>::value) {
		WORD v = pda->getWord(addr) - val;
		pda->writeWord(addr, v);
	} else if (std::is_same<T, DWORD>::value) {
		DWORD v = pda->getDWord(addr) - val;
		pda->writeDWord(addr, v);
	} else if (std::is_same<T, int>::value) {
		int v = pda->getInt(addr) - val;
		pda->writeInt(addr, v);
	} else if (std::is_same<T, float>::value) {
		float v = pda->getReal(addr) - val;
		pda->writeReal(addr, v);
	}

	return *this;
}

template <class T>
PDTag<T> & PDTag<T>::operator*=(const PDTag &pdt) {

	// Check type
	if (std::is_same<T, bool>::value) {
		throw ShmException("Can not multiply binary values", "PDTag<bool>::operator*= (PDTag<bool>)");
	} else if (std::is_same<T, BYTE>::value) {
		BYTE v = pda->getByte(addr) * pda->getByte(pdt.addr);
		pda->writeByte(addr, v);
	} else if (std::is_same<T, WORD>::value) {
		WORD v = pda->getWord(addr) * pda->getWord(pdt.addr);
		pda->writeWord(addr, v);
	} else if (std::is_same<T, DWORD>::value) {
		DWORD v = pda->getDWord(addr) * pda->getDWord(pdt.addr);
		pda->writeDWord(addr, v);
	} else if (std::is_same<T, int>::value) {
		int v = pda->getInt(addr) * pda->getInt(pdt.addr);
		pda->writeInt(addr, v);
	} else if (std::is_same<T, float>::value) {
		float v = pda->getReal(addr) * pda->getReal(pdt.addr);
		pda->writeReal(addr, v);
	}

	return *this;
}

template <class T>
PDTag<T> & PDTag<T>::operator*=(const T val) {

	// Check type
	if (std::is_same<T, bool>::value) {
		throw ShmException("Can not multiply binary values", "PDTag<bool>::operator*= (bool)");
	} else if (std::is_same<T, BYTE>::value) {
		BYTE v = pda->getByte(addr) * val;
		pda->writeByte(addr, v);
	} else if (std::is_same<T, WORD>::value) {
		WORD v = pda->getWord(addr) * val;
		pda->writeWord(addr, v);
	} else if (std::is_same<T, DWORD>::value) {
		DWORD v = pda->getDWord(addr) * val;
		pda->writeDWord(addr, v);
	} else if (std::is_same<T, int>::value) {
		int v = pda->getInt(addr) * val;
		pda->writeInt(addr, v);
	} else if (std::is_same<T, float>::value) {
		float v = pda->getReal(addr) * val;
		pda->writeReal(addr, v);
	}

	return *this;
}

template <class T>
PDTag<T> & PDTag<T>::operator/=(const PDTag &pdt) {

	// Check type
	if (std::is_same<T, bool>::value) {
		throw ShmException("Can not divide binary values", "PDTag<bool>::operator/= (PDTag<bool>)");
	} else if (std::is_same<T, BYTE>::value) {
		BYTE v = pda->getByte(addr) / pda->getByte(pdt.addr);
		pda->writeByte(addr, v);
	} else if (std::is_same<T, WORD>::value) {
		WORD v = pda->getWord(addr) / pda->getWord(pdt.addr);
		pda->writeWord(addr, v);
	} else if (std::is_same<T, DWORD>::value) {
		DWORD v = pda->getDWord(addr) / pda->getDWord(pdt.addr);
		pda->writeDWord(addr, v);
	} else if (std::is_same<T, int>::value) {
		int v = pda->getInt(addr) / pda->getInt(pdt.addr);
		pda->writeInt(addr, v);
	} else if (std::is_same<T, float>::value) {
		float v = pda->getReal(addr) / pda->getReal(pdt.addr);
		pda->writeReal(addr, v);
	}

	return *this;
}

template <class T>
PDTag<T> & PDTag<T>::operator/=(const T val) {

	// Check type
	if (std::is_same<T, bool>::value) {
		throw ShmException("Can not divide binary values", "PDTag<bool>::operator/= (bool)");
	} else if (std::is_same<T, BYTE>::value) {
		BYTE v = pda->getByte(addr) / val;
		pda->writeByte(addr, v);
	} else if (std::is_same<T, WORD>::value) {
		WORD v = pda->getWord(addr) / val;
		pda->writeWord(addr, v);
	} else if (std::is_same<T, DWORD>::value) {
		DWORD v = pda->getDWord(addr) / val;
		pda->writeDWord(addr, v);
	} else if (std::is_same<T, int>::value) {
		int v = pda->getInt(addr) / val;
		pda->writeInt(addr, v);
	} else if (std::is_same<T, float>::value) {
		float v = pda->getReal(addr) / val;
		pda->writeReal(addr, v);
	}

	return *this;
}

template <class T>
T PDTag<T>::operator+(const PDTag &pdt) {

	T ret;

	// Check type
	if (std::is_same<T, bool>::value) {
		throw ShmException("Can not sum binary values", "PDTag<bool>::operator+ (PDTag<bool>)");
	} else if (std::is_same<T, BYTE>::value) {
		ret = pda->getByte(pdt.addr) + pda->getByte(addr);
	} else if (std::is_same<T, WORD>::value) {
		ret = pda->getWord(pdt.addr) + pda->getWord(addr);
	} else if (std::is_same<T, DWORD>::value) {
		ret = pda->getDWord(pdt.addr) + pda->getDWord(addr);
	} else if (std::is_same<T, int>::value) {
		ret = pda->getInt(pdt.addr) + pda->getInt(addr);
	} else if (std::is_same<T, float>::value) {
		ret = pda->getReal(pdt.addr) + pda->getReal(addr);
	}

	return ret;
}

template <class T>
T PDTag<T>::operator+(const T val) {

	T ret;

	// Check type
	if (std::is_same<T, bool>::value) {
		throw ShmException("Can not sum binary values", "PDTag<bool>::operator+ (bool)");
	} else if (std::is_same<T, BYTE>::value) {
		ret = pda->getByte(addr) + val;
	} else if (std::is_same<T, WORD>::value) {
		ret = pda->getWord(addr) + val;
	} else if (std::is_same<T, DWORD>::value) {
		ret = pda->getDWord(addr) + val;
	} else if (std::is_same<T, int>::value) {
		ret = pda->getInt(addr) + val;
	} else if (std::is_same<T, float>::value) {
		ret = pda->getReal(addr) + val;
	}

	return ret;
}

template <class T>
T PDTag<T>::operator-(const PDTag &pdt) {

	T ret;

	// Check type
	if (std::is_same<T, bool>::value) {
		throw ShmException("Can not subtract binary values", "PDTag<bool>::operator- (PDTag<bool>)");
	} else if (std::is_same<T, BYTE>::value) {
		ret = pda->getByte(addr) - pda->getByte(pdt.addr);
	} else if (std::is_same<T, WORD>::value) {
		ret = pda->getWord(addr) - pda->getWord(pdt.addr);
	} else if (std::is_same<T, DWORD>::value) {
		ret = pda->getDWord(addr) - pda->getDWord(pdt.addr);
	} else if (std::is_same<T, int>::value) {
		ret = pda->getInt(addr) - pda->getInt(pdt.addr);
	} else if (std::is_same<T, float>::value) {
		ret = pda->getReal(addr) - pda->getReal(pdt.addr);
	}

	return ret;
}

template <class T>
T PDTag<T>::operator-(const T val) {

	T ret;

	// Check type
	if (std::is_same<T, bool>::value) {
		throw ShmException("Can not subtract binary values", "PDTag<bool>::operator- (bool)");
	} else if (std::is_same<T, BYTE>::value) {
		ret = pda->getByte(addr) - val;
	} else if (std::is_same<T, WORD>::value) {
		ret = pda->getWord(addr) - val;
	} else if (std::is_same<T, DWORD>::value) {
		ret = pda->getDWord(addr) - val;
	} else if (std::is_same<T, int>::value) {
		ret = pda->getInt(addr) - val;
	} else if (std::is_same<T, float>::value) {
		ret = pda->getReal(addr) - val;
	}

	return ret;
}

template <class T>
T PDTag<T>::operator*(const PDTag &pdt) {

	T ret;

	// Check type
	if (std::is_same<T, bool>::value) {
		throw ShmException("Can not multiply binary values", "PDTag<bool>::operator* (PDTag<bool>)");
	} else if (std::is_same<T, BYTE>::value) {
		ret = pda->getByte(addr) * pda->getByte(pdt.addr);
	} else if (std::is_same<T, WORD>::value) {
		ret = pda->getWord(addr) * pda->getWord(pdt.addr);
	} else if (std::is_same<T, DWORD>::value) {
		ret = pda->getDWord(addr) * pda->getDWord(pdt.addr);
	} else if (std::is_same<T, int>::value) {
		ret = pda->getInt(addr) * pda->getInt(pdt.addr);
	} else if (std::is_same<T, float>::value) {
		ret = pda->getReal(addr) * pda->getReal(pdt.addr);
	}

	return ret;
}

template <class T>
T PDTag<T>::operator*(const T val) {

	T ret;

	// Check type
	if (std::is_same<T, bool>::value) {
		throw ShmException("Can not multiply binary values", "PDTag<bool>::operator* (bool)");
	} else if (std::is_same<T, BYTE>::value) {
		ret = pda->getByte(addr) * val;
	} else if (std::is_same<T, WORD>::value) {
		ret = pda->getWord(addr) * val;
	} else if (std::is_same<T, DWORD>::value) {
		ret = pda->getDWord(addr) * val;
	} else if (std::is_same<T, int>::value) {
		ret = pda->getInt(addr) * val;
	} else if (std::is_same<T, float>::value) {
		ret = pda->getReal(addr) * val;
	}

	return ret;
}

template <class T>
T PDTag<T>::operator/(const PDTag &pdt) {

	T ret;

	// Check type
	if (std::is_same<T, bool>::value) {
		throw ShmException("Can not divide binary values", "PDTag<bool>::operator/ (PDTag<bool>)");
	} else if (std::is_same<T, BYTE>::value) {
		ret = pda->getByte(addr) / pda->getByte(pdt.addr);
	} else if (std::is_same<T, WORD>::value) {
		ret = pda->getWord(addr) / pda->getWord(pdt.addr);
	} else if (std::is_same<T, DWORD>::value) {
		ret = pda->getDWord(addr) / pda->getDWord(pdt.addr);
	} else if (std::is_same<T, int>::value) {
		ret = pda->getInt(addr) / pda->getInt(pdt.addr);
	} else if (std::is_same<T, float>::value) {
		ret = pda->getReal(addr) / pda->getReal(pdt.addr);
	}

	return ret;
}

template <class T>
T PDTag<T>::operator/(const T val) {

	T ret;

	// Check type
	if (std::is_same<T, bool>::value) {
		throw ShmException("Can not divide binary values", "PDTag<bool>::operator/ (bool)");
	} else if (std::is_same<T, BYTE>::value) {
		ret = pda->getByte(addr) / val;
	} else if (std::is_same<T, WORD>::value) {
		ret = pda->getWord(addr) / val;
	} else if (std::is_same<T, DWORD>::value) {
		ret = pda->getDWord(addr) / val;
	} else if (std::is_same<T, int>::value) {
		ret = pda->getInt(addr) / val;
	} else if (std::is_same<T, float>::value) {
		ret = pda->getReal(addr) / val;
	}

	return ret;
}

template <class T>
const PDTag<T> & PDTag<T>::operator++() {

	// Check type
	if (std::is_same<T, bool>::value) {
		throw ShmException("Can not increment binary values", "PDTag<bool>::operator++");
	} else if (std::is_same<T, BYTE>::value) {
		BYTE v = pda->getByte(addr) + 1;
		pda->writeByte(addr, v);
	} else if (std::is_same<T, WORD>::value) {
		WORD v = pda->getWord(addr) + 1;
		pda->writeWord(addr, v);
	} else if (std::is_same<T, DWORD>::value) {
		DWORD v = pda->getDWord(addr) + 1;
		pda->writeDWord(addr, v);
	} else if (std::is_same<T, int>::value) {
		int v = pda->getInt(addr) + 1;
		pda->writeInt(addr, v);
	} else if (std::is_same<T, float>::value) {
		float v = pda->getReal(addr) + 1.0;
		pda->writeReal(addr, v);
	}

	return *this;
}

template <class T>
T PDTag<T>::operator++(int) {

	T v;

	// Check type
	if (std::is_same<T, bool>::value) {
		throw ShmException("Can not increment binary values", "PDTag<bool>::operator++ (f)");
	} else if (std::is_same<T, BYTE>::value) {
		v = pda->getByte(addr);
		pda->writeByte(addr, v + 1);
	} else if (std::is_same<T, WORD>::value) {
		v = pda->getWord(addr) ;
		pda->writeWord(addr, v + 1);
	} else if (std::is_same<T, DWORD>::value) {
		v = pda->getDWord(addr);
		pda->writeDWord(addr, v + 1);
	} else if (std::is_same<T, int>::value) {
		v = pda->getInt(addr);
		pda->writeInt(addr, v + 1);
	} else if (std::is_same<T, float>::value) {
		v = pda->getReal(addr);
		pda->writeReal(addr, v + 1.0);
	}

	return v;
}

template <class T>
TagId PDTag<T>::getId() const {
	return _id;
}

template <class T>
TagId PDTag<T>::calculateId() const {

	TagId id = addr.byteAddr * 100;

	// Check type
	if (std::is_same<T, bool>::value) {
		id += (addr.bitAddr * 10);
	}
	
	id += static_cast<unsigned int>(addr.area);

	return id;
}

template class PDTag<bool>;
template class PDTag<BYTE>;
template class PDTag<WORD>;
template class PDTag<DWORD>;
template class PDTag<int>;
template class PDTag<float>;
