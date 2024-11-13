/**************************************************************************/
/*  jolt_custom_double_sided_shape.cpp                                    */
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

#include "jolt_custom_double_sided_shape.hpp"

#include <core/error/error_macros.h>

namespace {

JPH::Shape *construct_double_sided() {
	return new JoltCustomDoubleSidedShape();
}

void collide_double_sided_vs_shape(
		const JPH::Shape *p_shape1,
		const JPH::Shape *p_shape2,
		JPH::Vec3Arg p_scale1,
		JPH::Vec3Arg p_scale2,
		JPH::Mat44Arg p_center_of_mass_transform1,
		JPH::Mat44Arg p_center_of_mass_transform2,
		const JPH::SubShapeIDCreator &p_sub_shape_id_creator1,
		const JPH::SubShapeIDCreator &p_sub_shape_id_creator2,
		const JPH::CollideShapeSettings &p_collide_shape_settings,
		JPH::CollideShapeCollector &p_collector,
		const JPH::ShapeFilter &p_shape_filter) {
	ERR_FAIL_COND(p_shape1->GetSubType() != JoltCustomShapeSubType::DOUBLE_SIDED);

	const auto *shape1 = static_cast<const JoltCustomDoubleSidedShape *>(p_shape1);

	JPH::CollideShapeSettings new_collide_shape_settings = p_collide_shape_settings;
	new_collide_shape_settings.mBackFaceMode = JPH::EBackFaceMode::CollideWithBackFaces;

	JPH::CollisionDispatch::sCollideShapeVsShape(
			shape1->GetInnerShape(),
			p_shape2,
			p_scale1,
			p_scale2,
			p_center_of_mass_transform1,
			p_center_of_mass_transform2,
			p_sub_shape_id_creator1,
			p_sub_shape_id_creator2,
			new_collide_shape_settings,
			p_collector,
			p_shape_filter);
}

void collide_shape_vs_double_sided(
		const JPH::Shape *p_shape1,
		const JPH::Shape *p_shape2,
		JPH::Vec3Arg p_scale1,
		JPH::Vec3Arg p_scale2,
		JPH::Mat44Arg p_center_of_mass_transform1,
		JPH::Mat44Arg p_center_of_mass_transform2,
		const JPH::SubShapeIDCreator &p_sub_shape_id_creator1,
		const JPH::SubShapeIDCreator &p_sub_shape_id_creator2,
		const JPH::CollideShapeSettings &p_collide_shape_settings,
		JPH::CollideShapeCollector &p_collector,
		const JPH::ShapeFilter &p_shape_filter) {
	ERR_FAIL_COND(p_shape2->GetSubType() != JoltCustomShapeSubType::DOUBLE_SIDED);

	const auto *shape2 = static_cast<const JoltCustomDoubleSidedShape *>(p_shape2);

	JPH::CollideShapeSettings new_collide_shape_settings = p_collide_shape_settings;
	new_collide_shape_settings.mBackFaceMode = JPH::EBackFaceMode::CollideWithBackFaces;

	JPH::CollisionDispatch::sCollideShapeVsShape(
			p_shape1,
			shape2->GetInnerShape(),
			p_scale1,
			p_scale2,
			p_center_of_mass_transform1,
			p_center_of_mass_transform2,
			p_sub_shape_id_creator1,
			p_sub_shape_id_creator2,
			new_collide_shape_settings,
			p_collector,
			p_shape_filter);
}

} // namespace

JPH::ShapeSettings::ShapeResult JoltCustomDoubleSidedShapeSettings::Create() const {
	if (mCachedResult.IsEmpty()) {
		new JoltCustomDoubleSidedShape(*this, mCachedResult);
	}

	return mCachedResult;
}

void JoltCustomDoubleSidedShape::register_type() {
	JPH::ShapeFunctions &shape_functions = JPH::ShapeFunctions::sGet(
			JoltCustomShapeSubType::DOUBLE_SIDED);

	shape_functions.mConstruct = construct_double_sided;
	shape_functions.mColor = JPH::Color::sPurple;

	for (const JPH::EShapeSubType sub_type : JPH::sAllSubShapeTypes) {
		JPH::CollisionDispatch::sRegisterCollideShape(
				JoltCustomShapeSubType::DOUBLE_SIDED,
				sub_type,
				collide_double_sided_vs_shape);

		JPH::CollisionDispatch::sRegisterCollideShape(
				sub_type,
				JoltCustomShapeSubType::DOUBLE_SIDED,
				collide_shape_vs_double_sided);
	}
}
