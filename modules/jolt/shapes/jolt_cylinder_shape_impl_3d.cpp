/**************************************************************************/
/*  jolt_cylinder_shape_impl_3d.cpp                                       */
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

#include "jolt_cylinder_shape_impl_3d.hpp"

#include "servers/jolt_project_settings.hpp"

namespace {

constexpr float MARGIN_FACTOR = 0.08f;

} // namespace

Variant JoltCylinderShapeImpl3D::get_data() const {
	Dictionary data;
	data["height"] = height;
	data["radius"] = radius;
	return data;
}

void JoltCylinderShapeImpl3D::set_data(const Variant &p_data) {
	ERR_FAIL_COND(p_data.get_type() != Variant::DICTIONARY);

	const Dictionary data = p_data;

	const Variant maybe_height = data.get("height", {});
	ERR_FAIL_COND(maybe_height.get_type() != Variant::FLOAT);

	const Variant maybe_radius = data.get("radius", {});
	ERR_FAIL_COND(maybe_radius.get_type() != Variant::FLOAT);

	const float new_height = maybe_height;
	const float new_radius = maybe_radius;

	QUIET_FAIL_COND(new_height == height && new_radius == radius);

	height = new_height;
	radius = new_radius;

	destroy();
}

void JoltCylinderShapeImpl3D::set_margin(float p_margin) {
	QUIET_FAIL_COND(margin == p_margin);
	QUIET_FAIL_COND(!JoltProjectSettings::use_shape_margins());

	margin = p_margin;

	destroy();
}

String JoltCylinderShapeImpl3D::to_string() const {
	return vformat("{height=%f radius=%f margin=%f}", height, radius, margin);
}

JPH::ShapeRefC JoltCylinderShapeImpl3D::_build() const {
	const float half_height = height / 2.0f;
	const float height_margin = half_height * MARGIN_FACTOR;
	const float radius_margin = radius * MARGIN_FACTOR;
	const float shrunk_margin = MIN(margin, MIN(height_margin, radius_margin));
	const float actual_margin = JoltProjectSettings::use_shape_margins() ? shrunk_margin : 0.0f;

	const JPH::CylinderShapeSettings shape_settings(half_height, radius, actual_margin);
	const JPH::ShapeSettings::ShapeResult shape_result = shape_settings.Create();

	ERR_FAIL_COND_D_MSG(
			shape_result.HasError(),
			vformat(
					"Godot Jolt failed to build cylinder shape with %s. "
					"It returned the following error: '%s'. "
					"This shape belongs to %s.",
					to_string(),
					to_godot(shape_result.GetError()),
					_owners_to_string()));

	return shape_result.Get();
}
