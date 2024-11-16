/**************************************************************************/
/*  inline_vector.hpp                                                     */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#ifndef INLINE_VECTOR_HPP
#define INLINE_VECTOR_HPP

#include "containers/inline_allocator.hpp"
#include "local_vector2.hpp"

template <typename TElement, int32_t TCapacity>
class InlineVector final : public LocalVector2<TElement, InlineAllocator<TElement, TCapacity>> {
	using Base = LocalVector2<TElement, InlineAllocator<TElement, TCapacity>>;

public:
	InlineVector() { Base::reserve(TCapacity); }

	explicit InlineVector(int32_t p_capacity) {
		const int32_t capacity = MAX(p_capacity, TCapacity);
		Base::reserve(capacity);
	}

	InlineVector(const InlineVector &p_other) {
		const int32_t capacity = MAX(p_other.size(), TCapacity);
		Base::reserve(capacity);
		Base::operator=(p_other);
	}

	InlineVector(InlineVector &&p_other) noexcept {
		const int32_t capacity = MAX(p_other.size(), TCapacity);
		Base::reserve(capacity);
		Base::operator=(std::move(p_other));
	}

	InlineVector(std::initializer_list<TElement> p_list) {
		const auto list_size = (int32_t)std::distance(p_list.begin(), p_list.end());
		const int32_t capacity = MAX(list_size, TCapacity);
		Base::reserve(capacity);
		Base::operator=(p_list);
	}

	InlineVector &operator=(const InlineVector &p_other) {
		Base::operator=(p_other);
		return *this;
	}

	InlineVector &operator=(InlineVector &&p_other) noexcept {
		Base::operator=(std::move(p_other));
		return *this;
	}
};

#endif // INLINE_VECTOR_HPP
