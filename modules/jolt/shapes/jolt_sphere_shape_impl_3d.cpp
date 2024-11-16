/**************************************************************************/
/*  jolt_sphere_shape_impl_3d.cpp                                         */
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

#include "jolt_sphere_shape_impl_3d.hpp"

Variant JoltSphereShapeImpl3D::get_data() const {
	return radius;
}

void JoltSphereShapeImpl3D::set_data(const Variant &p_data) {
	ERR_FAIL_COND(p_data.get_type() != Variant::FLOAT);

	const float new_radius = p_data;
	QUIET_FAIL_COND(new_radius == radius);

	radius = new_radius;

	destroy();
}

String JoltSphereShapeImpl3D::to_string() const {
	return vformat("{radius=%f}", radius);
}

JPH::ShapeRefC JoltSphereShapeImpl3D::_build() const {
	ERR_FAIL_COND_D_MSG(
			radius <= 0.0f,
			vformat(
					"Godot Jolt failed to build sphere shape with %s. "
					"Its radius must be greater than 0. "
					"This shape belongs to %s.",
					to_string(),
					_owners_to_string()));

	const JPH::SphereShapeSettings shape_settings(radius);
	const JPH::ShapeSettings::ShapeResult shape_result = shape_settings.Create();

	ERR_FAIL_COND_D_MSG(
			shape_result.HasError(),
			vformat(
					"Godot Jolt failed to build sphere shape with %s. "
					"It returned the following error: '%s'. "
					"This shape belongs to %s.",
					to_string(),
					to_godot(shape_result.GetError()),
					_owners_to_string()));

	return shape_result.Get();
}
