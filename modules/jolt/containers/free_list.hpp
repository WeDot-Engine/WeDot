/**************************************************************************/
/*  free_list.hpp                                                         */
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

#ifndef FREE_LIST_HPP
#define FREE_LIST_HPP
#include <core/typedefs.h>

template <typename TElement>
class FreeList {
	using Implementation = JPH::FixedSizeFreeList<TElement>;

public:
	explicit FreeList(int32_t p_max_elements) {
		impl.Init((JPH::uint)p_max_elements, (JPH::uint)p_max_elements);
	}

	template <typename... TParams>
	_FORCE_INLINE_ TElement *construct(TParams &&...p_params) {
		const JPH::uint32 index = impl.ConstructObject(std::forward<TParams>(p_params)...);

		if (index == Implementation::cInvalidObjectIndex) {
			return nullptr;
		}

		return &impl.Get(index);
	}

	_FORCE_INLINE_ void destruct(TElement *p_value) { impl.DestructObject(p_value); }

private:
	Implementation impl;
};

#endif // FREE_LIST_HPP
