/**************************************************************************/
/*  jolt_custom_empty_shape.cpp                                           */
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

#include "jolt_custom_empty_shape.hpp"

namespace {

JPH::Shape *construct_empty() {
	return new JoltCustomEmptyShape();
}

void collide_noop(
		[[maybe_unused]] const JPH::Shape *p_shape1,
		[[maybe_unused]] const JPH::Shape *p_shape2,
		[[maybe_unused]] JPH::Vec3Arg p_scale1,
		[[maybe_unused]] JPH::Vec3Arg p_scale2,
		[[maybe_unused]] JPH::Mat44Arg p_center_of_mass_transform1,
		[[maybe_unused]] JPH::Mat44Arg p_center_of_mass_transform2,
		[[maybe_unused]] const JPH::SubShapeIDCreator &p_sub_shape_id_creator1,
		[[maybe_unused]] const JPH::SubShapeIDCreator &p_sub_shape_id_creator2,
		[[maybe_unused]] const JPH::CollideShapeSettings &p_collide_shape_settings,
		[[maybe_unused]] JPH::CollideShapeCollector &p_collector,
		[[maybe_unused]] const JPH::ShapeFilter &p_shape_filter) {}

void cast_noop(
		[[maybe_unused]] const JPH::ShapeCast &p_shape_cast,
		[[maybe_unused]] const JPH::ShapeCastSettings &p_shape_cast_settings,
		[[maybe_unused]] const JPH::Shape *p_shape,
		[[maybe_unused]] JPH::Vec3Arg p_scale,
		[[maybe_unused]] const JPH::ShapeFilter &p_shape_filter,
		[[maybe_unused]] JPH::Mat44Arg p_center_of_mass_transform2,
		[[maybe_unused]] const JPH::SubShapeIDCreator &p_sub_shape_id_creator1,
		[[maybe_unused]] const JPH::SubShapeIDCreator &p_sub_shape_id_creator2,
		[[maybe_unused]] JPH::CastShapeCollector &p_collector) {}

} // namespace

JPH::ShapeSettings::ShapeResult JoltCustomEmptyShapeSettings::Create() const {
	if (mCachedResult.IsEmpty()) {
		new JoltCustomEmptyShape(*this, mCachedResult);
	}

	return mCachedResult;
}

void JoltCustomEmptyShape::register_type() {
	JPH::ShapeFunctions &shape_functions = JPH::ShapeFunctions::sGet(JoltCustomShapeSubType::EMPTY);

	shape_functions.mConstruct = construct_empty;
	shape_functions.mColor = JPH::Color::sBlack;

	for (const JPH::EShapeSubType sub_type : JPH::sAllSubShapeTypes) {
		JPH::CollisionDispatch::sRegisterCollideShape(
				JoltCustomShapeSubType::EMPTY,
				sub_type,
				collide_noop);

		JPH::CollisionDispatch::sRegisterCollideShape(
				sub_type,
				JoltCustomShapeSubType::EMPTY,
				collide_noop);

		JPH::CollisionDispatch::sRegisterCastShape(
				JoltCustomShapeSubType::EMPTY,
				sub_type,
				cast_noop);

		JPH::CollisionDispatch::sRegisterCastShape(
				sub_type,
				JoltCustomShapeSubType::EMPTY,
				cast_noop);
	}
}

JPH::Vec3 JoltCustomEmptyShape::GetCenterOfMass() const {
	// HACK(mihe): In Godot Physics you're able to provide a custom center-of-mass to a shapeless
	// body without affecting its inertia. We can't emulate this behavior while relying on Jolt's
	// `OffsetCenterOfMassShape` due to it translating its inner mass properties (and thus our
	// inertia) by the center of mass provided to it. So instead we have this shape provide its own.
	return center_of_mass;
}

JPH::MassProperties JoltCustomEmptyShape::GetMassProperties() const {
	JPH::MassProperties mass_properties;

	// HACK(mihe): Since this shape has no volume we can't really give it a correct set of mass
	// properties, so instead we just give it some random/arbitrary ones.
	mass_properties.mMass = 1.0f;
	mass_properties.mInertia = JPH::Mat44::sIdentity();

	return mass_properties;
}
