/**************************************************************************/
/*  jolt_shape_instance_3d.cpp                                            */
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

#include "jolt_shape_instance_3d.hpp"

#include "shapes/jolt_shape_impl_3d.hpp"

JoltShapeInstance3D::JoltShapeInstance3D(
		JoltShapedObjectImpl3D *p_parent,
		JoltShapeImpl3D *p_shape,
		const Transform3D &p_transform,
		const Vector3 &p_scale,
		bool p_disabled) :
		transform(p_transform), scale(p_scale), parent(p_parent), shape(p_shape), disabled(p_disabled) {
	shape->add_owner(parent);
}

JoltShapeInstance3D::JoltShapeInstance3D(JoltShapeInstance3D &&p_other) noexcept
		:
		transform(p_other.transform), scale(p_other.scale), jolt_ref(std::move(p_other.jolt_ref)), parent(std::exchange(p_other.parent, nullptr)), shape(std::exchange(p_other.shape, nullptr)), id(p_other.id), disabled(p_other.disabled) {}

JoltShapeInstance3D::~JoltShapeInstance3D() {
	if (shape != nullptr) {
		shape->remove_owner(parent);
	}
}

bool JoltShapeInstance3D::try_build() {
	ERR_FAIL_COND_D(is_disabled());

	const JPH::ShapeRefC maybe_new_shape = shape->try_build();

	if (maybe_new_shape == nullptr) {
		jolt_ref = nullptr;
		return false;
	}

	if (jolt_ref != nullptr) {
		const auto *outer_shape = static_cast<const JPH::DecoratedShape *>(jolt_ref.GetPtr());

		if (outer_shape->GetInnerShape() == maybe_new_shape) {
			return true;
		}
	}

	jolt_ref = JoltShapeImpl3D::with_user_data(maybe_new_shape, (uint64_t)id);

	return true;
}

JoltShapeInstance3D &JoltShapeInstance3D::operator=(JoltShapeInstance3D &&p_other) noexcept {
	if (this != &p_other) {
		transform = p_other.transform;
		scale = p_other.scale;
		jolt_ref = std::move(p_other.jolt_ref);
		std::swap(parent, p_other.parent);
		std::swap(shape, p_other.shape);
		id = p_other.id;
		disabled = p_other.disabled;
	}

	return *this;
}
