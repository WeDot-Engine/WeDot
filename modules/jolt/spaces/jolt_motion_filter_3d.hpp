/**************************************************************************/
/*  jolt_motion_filter_3d.hpp                                             */
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

#ifndef JOLT_MOTION_FILTER_3D_HPP
#define JOLT_MOTION_FILTER_3D_HPP

#include "precompiled.hpp"

class JoltBodyImpl3D;
class JoltPhysicsServer3D;
class JoltSpace3D;

class JoltMotionFilter3D final
		: public JPH::BroadPhaseLayerFilter,
		  public JPH::ObjectLayerFilter,
		  public JPH::BodyFilter,
		  public JPH::ShapeFilter {
public:
	explicit JoltMotionFilter3D(const JoltBodyImpl3D &p_body, bool p_collide_separation_ray = true);

	bool ShouldCollide(JPH::BroadPhaseLayer p_broad_phase_layer) const override;

	bool ShouldCollide(JPH::ObjectLayer p_object_layer) const override;

	bool ShouldCollide(const JPH::BodyID &p_jolt_id) const override;

	bool ShouldCollideLocked(const JPH::Body &p_jolt_body) const override;

	bool ShouldCollide(const JPH::Shape *p_jolt_shape, const JPH::SubShapeID &p_jolt_shape_id)
			const override;

	bool ShouldCollide(
			const JPH::Shape *p_jolt_shape_self,
			const JPH::SubShapeID &p_jolt_shape_id_self,
			const JPH::Shape *p_jolt_shape_other,
			const JPH::SubShapeID &p_jolt_shape_id_other) const override;

private:
	const JoltPhysicsServer3D &physics_server;

	const JoltBodyImpl3D &body_self;

	const JoltSpace3D &space;

	bool collide_separation_ray = false;
};

#endif // JOLT_MOTION_FILTER_3D_HPP
