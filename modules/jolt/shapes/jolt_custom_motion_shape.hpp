/**************************************************************************/
/*  jolt_custom_motion_shape.hpp                                          */
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

#ifndef JOLT_CUSTOM_MOTION_SHAPE_HPP
#define JOLT_CUSTOM_MOTION_SHAPE_HPP

#include "precompiled.hpp"

#include "shapes/jolt_custom_shape_type.hpp"
#include <core/variant/variant.h>

class JoltCustomMotionShape final : public JPH::ConvexShape {
public:
	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
	explicit JoltCustomMotionShape(const JPH::ConvexShape &p_shape) :
			JPH::ConvexShape(JoltCustomShapeSubType::MOTION), inner_shape(p_shape) {}

	bool MustBeStatic() const override { return false; }

	JPH::Vec3 GetCenterOfMass() const override { ERR_FAIL_D_NOT_IMPL(); }

	JPH::AABox GetLocalBounds() const override;

	JPH::uint GetSubShapeIDBitsRecursive() const override { ERR_FAIL_D_NOT_IMPL(); }

	JPH::AABox GetWorldSpaceBounds(
			[[maybe_unused]] JPH::Mat44Arg p_center_of_mass_transform,
			[[maybe_unused]] JPH::Vec3Arg p_scale) const override {
		ERR_FAIL_D_NOT_IMPL();
	}

	float GetInnerRadius() const override { ERR_FAIL_D_NOT_IMPL(); }

	JPH::MassProperties GetMassProperties() const override { ERR_FAIL_D_NOT_IMPL(); }

	const JPH::PhysicsMaterial *GetMaterial([[maybe_unused]] const JPH::SubShapeID &p_sub_shape_id) const override {
		ERR_FAIL_D_NOT_IMPL();
	}

	JPH::Vec3 GetSurfaceNormal(
			[[maybe_unused]] const JPH::SubShapeID &p_sub_shape_id,
			[[maybe_unused]] JPH::Vec3Arg p_local_surface_position) const override {
		ERR_FAIL_D_NOT_IMPL();
	}

	void GetSupportingFace(
			const JPH::SubShapeID &p_sub_shape_id,
			JPH::Vec3Arg p_direction,
			JPH::Vec3Arg p_scale,
			JPH::Mat44Arg p_center_of_mass_transform,
			JPH::Shape::SupportingFace &p_vertices) const override;

	JPH::uint64 GetSubShapeUserData([[maybe_unused]] const JPH::SubShapeID &p_sub_shape_id) const override {
		ERR_FAIL_D_NOT_IMPL();
	}

	JPH::TransformedShape GetSubShapeTransformedShape(
			[[maybe_unused]] const JPH::SubShapeID &p_sub_shape_id,
			[[maybe_unused]] JPH::Vec3Arg p_position_com,
			[[maybe_unused]] JPH::QuatArg p_rotation,
			[[maybe_unused]] JPH::Vec3Arg p_scale,
			[[maybe_unused]] JPH::SubShapeID &p_remainder) const override {
		ERR_FAIL_D_NOT_IMPL();
	}

	// clang-format off

	void GetSubmergedVolume(
		[[maybe_unused]] JPH::Mat44Arg p_center_of_mass_transform,
		[[maybe_unused]] JPH::Vec3Arg p_scale,
		[[maybe_unused]] const JPH::Plane& p_surface,
		[[maybe_unused]] float& p_total_volume,
		[[maybe_unused]] float& p_submerged_volume,
		[[maybe_unused]] JPH::Vec3& p_center_of_buoyancy
#ifdef JPH_DEBUG_RENDERER
		, [[maybe_unused]] JPH::RVec3Arg p_base_offset
#endif // JPH_DEBUG_RENDERER
	) const override {
		ERR_FAIL_NOT_IMPL();
	}

	// clang-format on

	const JPH::ConvexShape::Support *GetSupportFunction(
			JPH::ConvexShape::ESupportMode p_mode,
			JPH::ConvexShape::SupportBuffer &p_buffer,
			JPH::Vec3Arg p_scale) const override;

#ifdef JPH_DEBUG_RENDERER
	void Draw(
			[[maybe_unused]] JPH::DebugRenderer *p_renderer,
			[[maybe_unused]] JPH::RMat44Arg p_center_of_mass_transform,
			[[maybe_unused]] JPH::Vec3Arg p_scale,
			[[maybe_unused]] JPH::ColorArg p_color,
			[[maybe_unused]] bool p_use_material_colors,
			[[maybe_unused]] bool p_draw_wireframe) const override {
		ERR_FAIL_NOT_IMPL();
	}

	void DrawGetSupportFunction(
			[[maybe_unused]] JPH::DebugRenderer *p_renderer,
			[[maybe_unused]] JPH::RMat44Arg p_center_of_mass_transform,
			[[maybe_unused]] JPH::Vec3Arg p_scale,
			[[maybe_unused]] JPH::ColorArg p_color,
			[[maybe_unused]] bool p_draw_support_direction) const override {
		ERR_FAIL_NOT_IMPL();
	}

	void DrawGetSupportingFace(
			[[maybe_unused]] JPH::DebugRenderer *p_renderer,
			[[maybe_unused]] JPH::RMat44Arg p_center_of_mass_transform,
			[[maybe_unused]] JPH::Vec3Arg p_scale) const override {
		ERR_FAIL_NOT_IMPL();
	}
#endif // JPH_DEBUG_RENDERER

	bool CastRay(
			[[maybe_unused]] const JPH::RayCast &p_ray,
			[[maybe_unused]] const JPH::SubShapeIDCreator &p_sub_shape_id_creator,
			[[maybe_unused]] JPH::RayCastResult &p_hit) const override {
		ERR_FAIL_D_NOT_IMPL();
	}

	void CastRay(
			[[maybe_unused]] const JPH::RayCast &p_ray,
			[[maybe_unused]] const JPH::RayCastSettings &p_ray_cast_settings,
			[[maybe_unused]] const JPH::SubShapeIDCreator &p_sub_shape_id_creator,
			[[maybe_unused]] JPH::CastRayCollector &p_collector,
			[[maybe_unused]] const JPH::ShapeFilter &p_shape_filter = {}) const override {
		ERR_FAIL_NOT_IMPL();
	}

	void CollidePoint(
			[[maybe_unused]] JPH::Vec3Arg p_point,
			[[maybe_unused]] const JPH::SubShapeIDCreator &p_sub_shape_id_creator,
			[[maybe_unused]] JPH::CollidePointCollector &p_collector,
			[[maybe_unused]] const JPH::ShapeFilter &p_shape_filter = {}) const override {
		ERR_FAIL_NOT_IMPL();
	}

	void CollideSoftBodyVertices(
			[[maybe_unused]] JPH::Mat44Arg p_center_of_mass_transform,
			[[maybe_unused]] JPH::Vec3Arg p_scale,
			[[maybe_unused]] JPH::SoftBodyVertex *p_vertices,
			[[maybe_unused]] JPH::uint p_num_vertices,
			[[maybe_unused]] float p_delta_time,
			[[maybe_unused]] JPH::Vec3Arg p_displacement_due_to_gravity,
			[[maybe_unused]] int p_colliding_shape_index) const override {
		ERR_FAIL_NOT_IMPL();
	}

	void CollectTransformedShapes(
			[[maybe_unused]] const JPH::AABox &p_box,
			[[maybe_unused]] JPH::Vec3Arg p_position_com,
			[[maybe_unused]] JPH::QuatArg p_rotation,
			[[maybe_unused]] JPH::Vec3Arg p_scale,
			[[maybe_unused]] const JPH::SubShapeIDCreator &p_sub_shape_id_creator,
			[[maybe_unused]] JPH::TransformedShapeCollector &p_collector,
			[[maybe_unused]] const JPH::ShapeFilter &p_shape_filter = {}) const override {
		ERR_FAIL_NOT_IMPL();
	}

	void TransformShape(
			[[maybe_unused]] JPH::Mat44Arg p_center_of_mass_transform,
			[[maybe_unused]] JPH::TransformedShapeCollector &p_collector) const override {
		ERR_FAIL_NOT_IMPL();
	}

	void GetTrianglesStart(
			[[maybe_unused]] GetTrianglesContext &p_context,
			[[maybe_unused]] const JPH::AABox &p_box,
			[[maybe_unused]] JPH::Vec3Arg p_position_com,
			[[maybe_unused]] JPH::QuatArg p_rotation,
			[[maybe_unused]] JPH::Vec3Arg p_scale) const override {
		ERR_FAIL_NOT_IMPL();
	}

	int GetTrianglesNext(
			[[maybe_unused]] GetTrianglesContext &p_context,
			[[maybe_unused]] int p_max_triangles_requested,
			[[maybe_unused]] JPH::Float3 *p_triangle_vertices,
			[[maybe_unused]] const JPH::PhysicsMaterial **p_materials = nullptr) const override {
		ERR_FAIL_D_NOT_IMPL();
	}

	JPH::Shape::Stats GetStats() const override { return { sizeof(*this), 0 }; }

	float GetVolume() const override { ERR_FAIL_D_NOT_IMPL(); }

	bool IsValidScale([[maybe_unused]] JPH::Vec3Arg p_scale) const override {
		ERR_FAIL_D_NOT_IMPL();
	}

	const JPH::ConvexShape &get_inner_shape() const { return inner_shape; }

	void set_motion(JPH::Vec3Arg p_motion) { motion = p_motion; }

private:
	mutable JPH::ConvexShape::SupportBuffer inner_support_buffer;

	JPH::Vec3 motion = JPH::Vec3::sZero();

	const JPH::ConvexShape &inner_shape;
};

#endif // JOLT_CUSTOM_MOTION_SHAPE_HPP
