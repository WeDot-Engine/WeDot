/**************************************************************************/
/*  scope_guard.hpp                                                       */
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

#ifndef SCOPE_GUARD_HPP
#define SCOPE_GUARD_HPP

#define GDJ_CONCATENATE_IMPL(m_a, m_b) m_a##m_b
#define GDJ_CONCATENATE(m_a, m_b) GDJ_CONCATENATE_IMPL(m_a, m_b)
#define GDJ_UNIQUE_IDENTIFIER(m_prefix) GDJ_CONCATENATE(m_prefix, __COUNTER__)

template <typename TCallable>
class ScopeGuard {
public:
	// NOLINTNEXTLINE(hicpp-explicit-conversions)
	ScopeGuard(TCallable p_callable) :
			callable(std::move(p_callable)) {}

	ScopeGuard(const ScopeGuard &p_other) = delete;

	ScopeGuard(ScopeGuard &&p_other) = delete;

	~ScopeGuard() {
		if (!released) {
			callable();
		}
	}

	void release() { released = true; }

	ScopeGuard &operator=(const ScopeGuard &p_other) = delete;

	ScopeGuard &operator=(ScopeGuard &&p_other) = delete;

private:
	TCallable callable;

	bool released = false;
};

struct ScopeGuardHelper {
	template <typename TCallable>
	ScopeGuard<std::decay_t<TCallable>> operator+(TCallable &&p_callable) {
		return { std::forward<TCallable>(p_callable) };
	}
};

// NOLINTNEXTLINE(bugprone-macro-parentheses)
#define ON_SCOPE_EXIT auto GDJ_UNIQUE_IDENTIFIER(scope_guard) = ScopeGuardHelper() + [&]

#endif // SCOPE_GUARD_HPP
