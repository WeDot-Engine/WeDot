/**************************************************************************/
/*  jolt_query_filter_3d.hpp                                              */
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

#ifndef JOLT_QUERY_FILTER_3D_HPP
#define JOLT_QUERY_FILTER_3D_HPP

#include "precompiled.hpp"

class JoltPhysicsDirectSpaceState3D;
class JoltSpace3D;

class JoltQueryFilter3D final
		: public JPH::BroadPhaseLayerFilter,
		  public JPH::ObjectLayerFilter,
		  public JPH::BodyFilter {
public:
	JoltQueryFilter3D(
			const JoltPhysicsDirectSpaceState3D &p_space_state,
			uint32_t p_collision_mask,
			bool p_collide_with_bodies,
			bool p_collide_with_areas,
			bool p_picking = false);

	bool ShouldCollide(JPH::BroadPhaseLayer p_broad_phase_layer) const override;

	bool ShouldCollide(JPH::ObjectLayer p_object_layer) const override;

	bool ShouldCollide(const JPH::BodyID &p_body_id) const override;

	bool ShouldCollideLocked(const JPH::Body &p_body) const override;

private:
	const JoltPhysicsDirectSpaceState3D &space_state;

	const JoltSpace3D &space;

	uint32_t collision_mask = 0;

	bool collide_with_bodies = false;

	bool collide_with_areas = false;

	bool picking = false;
};

#endif // JOLT_QUERY_FILTER_3D_HPP
