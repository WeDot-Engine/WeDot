/**************************************************************************/
/*  jolt_physics_direct_space_state_3d.hpp                                */
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

#ifndef JOLT_PHYSICS_DIRECT_SPACE_STATE_3D_HPP
#define JOLT_PHYSICS_DIRECT_SPACE_STATE_3D_HPP
#include <servers/physics_server_3d.h>

#include "precompiled.hpp"

#include <servers/extensions/physics_server_3d_extension.h>

class JoltBodyImpl3D;
class JoltShapeImpl3D;
class JoltSpace3D;

class JoltPhysicsDirectSpaceState3D final : public PhysicsDirectSpaceState3D {
	GDCLASS(JoltPhysicsDirectSpaceState3D, PhysicsDirectSpaceState3D)

private:
	static void _bind_methods() {}

public:
	JoltPhysicsDirectSpaceState3D() = default;

	explicit JoltPhysicsDirectSpaceState3D(JoltSpace3D *p_space);

	bool intersect_ray(const RayParameters &p_parameters, RayResult &r_result) override;

	int32_t intersect_point(const PointParameters &p_parameters, ShapeResult *r_results, int p_result_max) override;

	int32_t intersect_shape(const ShapeParameters &p_parameters, ShapeResult *r_results, int p_result_max) override;

	bool cast_motion(const ShapeParameters &p_parameters, real_t &p_closest_safe, real_t &p_closest_unsafe, ShapeRestInfo *r_info = nullptr) override;

	bool collide_shape(const ShapeParameters &p_parameters, Vector3 *r_results, int p_result_max, int &r_result_count) override;

	bool rest_info(const ShapeParameters &p_parameters, ShapeRestInfo *r_info) override;

	Vector3 get_closest_point_to_object_volume(RID p_object, const Vector3 p_point) const override;

	bool test_body_motion(
			const JoltBodyImpl3D &p_body,
			const Transform3D &p_transform,
			const Vector3 &p_motion,
			float p_margin,
			int32_t p_max_collisions,
			bool p_collide_separation_ray,
			bool p_recovery_as_collision,
			PhysicsServer3DExtensionMotionResult *p_result) const;

	JoltSpace3D &get_space() const { return *space; }

private:
	bool _cast_motion_impl(
			const JPH::Shape &p_jolt_shape,
			const Transform3D &p_transform_com,
			const Vector3 &p_scale,
			const Vector3 &p_motion,
			bool p_ignore_overlaps,
			const JPH::CollideShapeSettings &p_settings,
			const JPH::BroadPhaseLayerFilter &p_broad_phase_layer_filter,
			const JPH::ObjectLayerFilter &p_object_layer_filter,
			const JPH::BodyFilter &p_body_filter,
			const JPH::ShapeFilter &p_shape_filter,
			real_t &p_closest_safe,
			real_t &p_closest_unsafe) const;

	bool _body_motion_recover(
			const JoltBodyImpl3D &p_body,
			const Transform3D &p_transform,
			float p_margin,
			Vector3 &p_recovery) const;

	bool _body_motion_cast(
			const JoltBodyImpl3D &p_body,
			const Transform3D &p_transform,
			const Vector3 &p_scale,
			const Vector3 &p_motion,
			bool p_collide_separation_ray,
			real_t &p_safe_fraction,
			real_t &p_unsafe_fraction) const;

	bool _body_motion_collide(
			const JoltBodyImpl3D &p_body,
			const Transform3D &p_transform,
			const Vector3 &p_motion,
			float p_margin,
			int32_t p_max_collisions,
			PhysicsServer3DExtensionMotionResult *p_result) const;

	void _generate_manifold(
			const JPH::CollideShapeResult &p_hit,
			JPH::ContactPoints &p_contact_points1,
			JPH::ContactPoints &p_contact_points2
#ifdef JPH_DEBUG_RENDERER
			,
			JPH::RVec3Arg p_center_of_mass
#endif // JPH_DEBUG_RENDERER
	) const;

	JoltSpace3D *space = nullptr;
};

#endif // JOLT_PHYSICS_DIRECT_SPACE_STATE_3D_HPP
