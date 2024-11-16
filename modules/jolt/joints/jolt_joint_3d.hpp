/**************************************************************************/
/*  jolt_joint_3d.hpp                                                     */
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

#ifndef JOLT_JOINT_3D_HPP
#define JOLT_JOINT_3D_HPP
#include <scene/3d/node_3d.h>
#include <scene/3d/physics/physics_body_3d.h>

class JoltPhysicsServer3D;

class JoltJoint3D : public Node3D {
	GDCLASS(JoltJoint3D, Node3D)
private:
	static void _bind_methods() {}

public:
	JoltJoint3D();

	~JoltJoint3D() override;

	NodePath get_node_a() const { return node_a; }

	void set_node_a(const NodePath &p_path);

	NodePath get_node_b() const { return node_b; }

	void set_node_b(const NodePath &p_path);

	PhysicsBody3D *get_body_a() const;

	PhysicsBody3D *get_body_b() const;

	bool get_enabled() const { return enabled; }

	void set_enabled(bool p_enabled);

	bool get_exclude_nodes_from_collision() const { return collision_excluded; }

	void set_exclude_nodes_from_collision(bool p_excluded);

	int32_t get_solver_velocity_iterations() const { return velocity_iterations; }

	void set_solver_velocity_iterations(int32_t p_iterations);

	int32_t get_solver_position_iterations() const { return position_iterations; }

	void set_solver_position_iterations(int32_t p_iterations);

	PackedStringArray _get_configuration_warnings() const;

protected:
	static PhysicsServer3D *_get_physics_server();

	static JoltPhysicsServer3D *_get_jolt_physics_server();

	Transform3D _get_body_local_transform(const PhysicsBody3D &p_body) const;

	bool _is_valid() const { return valid; }

	bool _is_invalid() const { return !valid; }

	virtual void _configure(
			[[maybe_unused]] PhysicsBody3D *p_body_a,
			[[maybe_unused]] PhysicsBody3D *p_body_b) {}

	void _notification(int32_t p_what);

	void _body_exiting_tree();

	void _connect_bodies();

	void _disconnect_bodies();

	bool _validate();

	bool _configure();

	bool _build();

	void _destroy();

	void _update_enabled();

	void _update_collision_exclusion();

	void _update_velocity_iterations();

	void _update_position_iterations();

	void _nodes_changing();

	void _nodes_changed();

	void _configuration_warnings_changed();

	void _enabled_changed();

	void _collision_exclusion_changed();

	void _velocity_iterations_changed();

	void _position_iterations_changed();

	String warning;

	RID rid;

	NodePath node_a;

	NodePath node_b;

	int32_t velocity_iterations = 0;

	int32_t position_iterations = 0;

	bool valid = false;

	bool enabled = true;

	bool collision_excluded = true;
};

#endif // JOLT_JOINT_3D_HPP
