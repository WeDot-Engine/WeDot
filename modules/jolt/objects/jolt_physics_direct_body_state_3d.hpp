/**************************************************************************/
/*  jolt_physics_direct_body_state_3d.hpp                                 */
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

#ifndef JOLT_PHYSICS_DIRECT_BODY_STATE_3D_HPP
#define JOLT_PHYSICS_DIRECT_BODY_STATE_3D_HPP

#include "precompiled.hpp"

#include <servers/physics_server_3d.h>

class JoltBodyImpl3D;

class JoltPhysicsDirectBodyState3D final : public PhysicsDirectBodyState3D {
	GDCLASS(JoltPhysicsDirectBodyState3D, PhysicsDirectBodyState3D)

private:
	static void _bind_methods() {}

public:
	JoltPhysicsDirectBodyState3D() = default;

	explicit JoltPhysicsDirectBodyState3D(JoltBodyImpl3D *p_body);

	Vector3 get_total_gravity() const override;
	real_t get_total_linear_damp() const override;
	real_t get_total_angular_damp() const override;

	Vector3 get_center_of_mass() const override;
	Vector3 get_center_of_mass_local() const override;
	Basis get_principal_inertia_axes() const override;
	real_t get_inverse_mass() const override;
	Vector3 get_inverse_inertia() const override;
	Basis get_inverse_inertia_tensor() const override;

	void set_linear_velocity(const Vector3 &p_velocity) override;
	Vector3 get_linear_velocity() const override;

	void set_angular_velocity(const Vector3 &p_velocity) override;
	Vector3 get_angular_velocity() const override;

	void set_transform(const Transform3D &p_transform) override;
	Transform3D get_transform() const override;

	Vector3 get_velocity_at_local_position(const Vector3 &p_local_position) const override;

	void apply_central_impulse(const Vector3 &p_impulse) override;
	void apply_impulse(const Vector3 &p_impulse, const Vector3 &p_position) override;
	void apply_torque_impulse(const Vector3 &p_impulse) override;

	void apply_central_force(const Vector3 &p_force) override;
	void apply_force(const Vector3 &p_force, const Vector3 &p_position) override;
	void apply_torque(const Vector3 &p_torque) override;

	void add_constant_central_force(const Vector3 &p_force) override;
	void add_constant_force(const Vector3 &p_force, const Vector3 &p_position) override;
	void add_constant_torque(const Vector3 &p_torque) override;

	void set_constant_force(const Vector3 &p_force) override;
	Vector3 get_constant_force() const override;

	void set_constant_torque(const Vector3 &p_torque) override;
	Vector3 get_constant_torque() const override;

	void set_sleep_state(bool p_enabled) override;
	bool is_sleeping() const override;

	int32_t get_contact_count() const override;

	Vector3 get_contact_local_position(int32_t p_contact_idx) const override;
	Vector3 get_contact_local_normal(int32_t p_contact_idx) const override;
	Vector3 get_contact_impulse(int32_t p_contact_idx) const override;
	int32_t get_contact_local_shape(int32_t p_contact_idx) const override;
	Vector3 get_contact_local_velocity_at_position(int32_t p_contact_idx) const override;

	RID get_contact_collider(int32_t p_contact_idx) const override;
	Vector3 get_contact_collider_position(int32_t p_contact_idx) const override;
	ObjectID get_contact_collider_id(int32_t p_contact_idx) const override;
	Object *get_contact_collider_object(int32_t p_contact_idx) const override;
	int32_t get_contact_collider_shape(int32_t p_contact_idx) const override;
	Vector3 get_contact_collider_velocity_at_position(int32_t p_contact_idx) const override;

	real_t get_step() const override;
	void integrate_forces() override;

	PhysicsDirectSpaceState3D *get_space_state() override;

private:
	JoltBodyImpl3D *body = nullptr;
};

#endif // JOLT_PHYSICS_DIRECT_BODY_STATE_3D_HPP
