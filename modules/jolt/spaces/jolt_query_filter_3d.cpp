/**************************************************************************/
/*  jolt_query_filter_3d.cpp                                              */
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

#include "jolt_query_filter_3d.hpp"

#include "objects/jolt_object_impl_3d.hpp"
#include "spaces/jolt_broad_phase_layer.hpp"
#include "spaces/jolt_physics_direct_space_state_3d.hpp"
#include "spaces/jolt_space_3d.hpp"

JoltQueryFilter3D::JoltQueryFilter3D(
		const JoltPhysicsDirectSpaceState3D &p_space_state,
		uint32_t p_collision_mask,
		bool p_collide_with_bodies,
		bool p_collide_with_areas,
		bool p_picking) :
		space_state(p_space_state), space(space_state.get_space()), collision_mask(p_collision_mask), collide_with_bodies(p_collide_with_bodies), collide_with_areas(p_collide_with_areas), picking(p_picking) {}

bool JoltQueryFilter3D::ShouldCollide(JPH::BroadPhaseLayer p_broad_phase_layer) const {
	const auto broad_phase_layer = (JPH::BroadPhaseLayer::Type)p_broad_phase_layer;

	switch (broad_phase_layer) {
		case (JPH::BroadPhaseLayer::Type)JoltBroadPhaseLayer::BODY_STATIC:
		case (JPH::BroadPhaseLayer::Type)JoltBroadPhaseLayer::BODY_DYNAMIC: {
			return collide_with_bodies;
		} break;
		case (JPH::BroadPhaseLayer::Type)JoltBroadPhaseLayer::AREA_DETECTABLE:
		case (JPH::BroadPhaseLayer::Type)JoltBroadPhaseLayer::AREA_UNDETECTABLE: {
			return collide_with_areas;
		} break;
		default: {
			ERR_FAIL_D_REPORT(vformat("Unhandled broad phase layer: '%d'.", broad_phase_layer));
		}
	}
}

bool JoltQueryFilter3D::ShouldCollide(JPH::ObjectLayer p_object_layer) const {
	JPH::BroadPhaseLayer object_broad_phase_layer = {};
	uint32_t object_collision_layer = 0;
	uint32_t object_collision_mask = 0;

	space.map_from_object_layer(
			p_object_layer,
			object_broad_phase_layer,
			object_collision_layer,
			object_collision_mask);

	return (collision_mask & object_collision_layer) != 0;
}

bool JoltQueryFilter3D::ShouldCollide([[maybe_unused]] const JPH::BodyID &p_body_id) const {
	return true;
}

bool JoltQueryFilter3D::ShouldCollideLocked(const JPH::Body &p_body) const {
	auto *object = reinterpret_cast<JoltObjectImpl3D *>(p_body.GetUserData());

	//TODO
	return (!picking || object->is_pickable()) /*&& !space_state.is_body_excluded_from_query(object->get_rid())*/;
}
