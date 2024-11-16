/**************************************************************************/
/*  math.hpp                                                              */
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

#ifndef MATH_HPP
#define MATH_HPP

// NOLINTBEGIN(readability-identifier-naming)

#define Mathf_SQRT12 ((float)Math_SQRT12)
#define Mathf_SQRT2 ((float)Math_SQRT2)
#define Mathf_LN2 ((float)Math_LN2)
#define Mathf_PI ((float)Math_PI)
#define Mathf_TAU ((float)Math_TAU)
#define Mathf_E ((float)Math_E)
#define Mathf_INF ((float)Math_INF)
#define Mathf_NAN ((float)Math_NAN)

// NOLINTEND(readability-identifier-naming)

#ifdef GDJ_CONFIG_EDITOR

#define ENSURE_SCALE_NOT_ZERO(m_transform, m_msg)                                                 \
	if (unlikely((m_transform).basis.determinant() == 0.0f)) {                                    \
		WARN_PRINT(vformat(                                                                       \
				"%s "                                                                             \
				"The basis of the transform was singular, which is not supported by Godot Jolt. " \
				"This is likely caused by one or more axes having a scale of zero. "              \
				"The basis (and thus its scale) will be treated as identity.",                    \
				m_msg));                                                                          \
                                                                                                  \
		(m_transform).basis = Basis();                                                            \
	} else                                                                                        \
		((void)0)

#else // GDJ_CONFIG_EDITOR

#define ENSURE_SCALE_NOT_ZERO(m_transform, m_msg)

#endif // GDJ_CONFIG_EDITOR

#include "precompiled.hpp"

#include <core/math/transform_3d.h>

namespace godot::Math {

void decompose(Basis &p_basis, Vector3 &p_scale);

_FORCE_INLINE_ void decompose(Transform3D &p_transform, Vector3 &p_scale) {
	decompose(p_transform.basis, p_scale);
}

_FORCE_INLINE_ Basis decomposed(Basis p_basis, Vector3 &p_scale) {
	decompose(p_basis, p_scale);
	return p_basis;
}

_FORCE_INLINE_ Transform3D decomposed(Transform3D p_transform, Vector3 &p_scale) {
	decompose(p_transform, p_scale);
	return p_transform;
}

_FORCE_INLINE_ float square(float p_value) {
	return p_value * p_value;
}

} // namespace godot::Math

#endif // MATH_HPP
