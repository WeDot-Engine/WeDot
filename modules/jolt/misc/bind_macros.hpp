/**************************************************************************/
/*  bind_macros.hpp                                                       */
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

#ifndef BIND_MACROS_HPP
#define BIND_MACROS_HPP

#define EXPAND(x) x

#define BIND_METHOD_0_ARGS(m_class, m_name) \
	ClassDB::bind_method(D_METHOD(#m_name), &m_class::m_name)

#define BIND_METHOD_N_ARGS(m_class, m_name, ...) \
	ClassDB::bind_method(D_METHOD(#m_name, __VA_ARGS__), &m_class::m_name)

#define BIND_METHOD_SELECT(_1, _2, _3, _4, _5, _6, _7, _8, _9, m_macro, ...) m_macro

#define BIND_METHOD(...)        \
	EXPAND(BIND_METHOD_SELECT(  \
			__VA_ARGS__,        \
			BIND_METHOD_N_ARGS, \
			BIND_METHOD_N_ARGS, \
			BIND_METHOD_N_ARGS, \
			BIND_METHOD_N_ARGS, \
			BIND_METHOD_N_ARGS, \
			BIND_METHOD_N_ARGS, \
			BIND_METHOD_N_ARGS, \
			BIND_METHOD_0_ARGS)(__VA_ARGS__))

#define BIND_PROPERTY_HINTED(m_name, m_type, m_hint, m_hint_str) \
	ClassDB::add_property(                                       \
			get_class_static(),                                  \
			PropertyInfo(m_type, m_name, m_hint, m_hint_str),    \
			"set_" m_name,                                       \
			"get_" m_name)

#define BIND_PROPERTY_RANGED(m_name, m_type, m_hint_str) \
	BIND_PROPERTY_HINTED(m_name, m_type, PROPERTY_HINT_RANGE, m_hint_str)

#define BIND_PROPERTY_ENUM(m_name, m_hint_str) \
	BIND_PROPERTY_HINTED(m_name, Variant::INT, PROPERTY_HINT_ENUM, m_hint_str)

#define BIND_PROPERTY_0(m_name, m_type) \
	BIND_PROPERTY_HINTED(m_name, m_type, PROPERTY_HINT_NONE, "")

#define BIND_PROPERTY_1(m_name, m_type, m_hint_str) \
	BIND_PROPERTY_HINTED(m_name, m_type, PROPERTY_HINT_NONE, m_hint_str)

#define BIND_PROPERTY_SELECT(_1, _2, _3, m_macro, ...) m_macro

#define BIND_PROPERTY(...) \
	EXPAND(BIND_PROPERTY_SELECT(__VA_ARGS__, BIND_PROPERTY_1, BIND_PROPERTY_0)(__VA_ARGS__))

// HACK(mihe): Ideally we would use `ADD_SUBGROUP` instead of this `BIND_SUBPROPERTY` stuff, but
// there's a bug in `DocTools::generate` where you'll sometimes get errors about some empty class
// name when you have multiple sub-groups of the same name.

#define BIND_SUBPROPERTY_HINTED(m_prefix, m_name, m_type, m_hint, m_hint_str) \
	ClassDB::add_property(                                                    \
			get_class_static(),                                               \
			PropertyInfo(m_type, m_prefix "/" m_name, m_hint, m_hint_str),    \
			"set_" m_prefix "_" m_name,                                       \
			"get_" m_prefix "_" m_name)

#define BIND_SUBPROPERTY_RANGED(m_prefix, m_name, m_type, m_hint_str) \
	BIND_SUBPROPERTY_HINTED(m_prefix, m_name, m_type, PROPERTY_HINT_RANGE, m_hint_str)

#define BIND_SUBPROPERTY_ENUM(m_prefix, m_name, m_hint_str) \
	BIND_SUBPROPERTY_HINTED(m_prefix, m_name, Variant::INT, PROPERTY_HINT_ENUM, m_hint_str)

#define BIND_SUBPROPERTY_0(m_prefix, m_name, m_type) \
	BIND_SUBPROPERTY_HINTED(m_prefix, m_name, m_type, PROPERTY_HINT_NONE, "")

#define BIND_SUBPROPERTY_1(m_prefix, m_name, m_type, m_hint_str) \
	BIND_SUBPROPERTY_HINTED(m_prefix, m_name, m_type, PROPERTY_HINT_NONE, m_hint_str)

#define BIND_SUBPROPERTY_SELECT(_1, _2, _3, _4, m_macro, ...) m_macro

#define BIND_SUBPROPERTY(...) \
	EXPAND(BIND_SUBPROPERTY_SELECT(__VA_ARGS__, BIND_SUBPROPERTY_1, BIND_SUBPROPERTY_0)(__VA_ARGS__))

#endif // BIND_MACROS_HPP
