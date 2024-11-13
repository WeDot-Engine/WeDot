/**************************************************************************/
/*  jolt_pin_joint_impl_3d.hpp                                            */
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

#ifndef JOLT_PIN_JOINT_IMPL_3D_HPP
#define JOLT_PIN_JOINT_IMPL_3D_HPP

#include "precompiled.hpp"

#include "joints/jolt_joint_impl_3d.hpp"

#include <core/math/vector3.h>
#include <servers/physics_server_3d.h>

class JoltBodyImpl3D;
class JoltSpace3D;

class JoltPinJointImpl3D final : public JoltJointImpl3D {
public:
	JoltPinJointImpl3D(
			const JoltJointImpl3D &p_old_joint,
			JoltBodyImpl3D *p_body_a,
			JoltBodyImpl3D *p_body_b,
			const Vector3 &p_local_a,
			const Vector3 &p_local_b);

	PhysicsServer3D::JointType get_type() const override { return PhysicsServer3D::JOINT_TYPE_PIN; }

	Vector3 get_local_a() const { return local_ref_a.origin; }

	void set_local_a(const Vector3 &p_local_a);

	Vector3 get_local_b() const { return local_ref_b.origin; }

	void set_local_b(const Vector3 &p_local_b);

	double get_param(PhysicsServer3D::PinJointParam p_param) const;

	void set_param(PhysicsServer3D::PinJointParam p_param, double p_value);

	float get_applied_force() const;

	void rebuild() override;

private:
	static JPH::Constraint *_build_pin(
			JPH::Body *p_jolt_body_a,
			JPH::Body *p_jolt_body_b,
			const Transform3D &p_shifted_ref_a,
			const Transform3D &p_shifted_ref_b);

	void _points_changed();
};

#endif // JOLT_PIN_JOINT_IMPL_3D_HPP
