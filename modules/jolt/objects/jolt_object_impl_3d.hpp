/**************************************************************************/
/*  jolt_object_impl_3d.hpp                                               */
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

#ifndef JOLT_OBJECT_IMPL_3D_HPP
#define JOLT_OBJECT_IMPL_3D_HPP

#include "precompiled.hpp"

#include "shapes/jolt_shape_instance_3d.hpp"

#include <core/object/object.h>
#include <core/object/object_id.h>
#include <core/templates/rid.h>

class JoltAreaImpl3D;
class JoltBodyImpl3D;
class JoltShapedObjectImpl3D;
class JoltShapeImpl3D;
class JoltSoftBodyImpl3D;
class JoltSpace3D;

class JoltObjectImpl3D {
public:
	enum ObjectType : int8_t {
		OBJECT_TYPE_INVALID,
		OBJECT_TYPE_BODY,
		OBJECT_TYPE_SOFT_BODY,
		OBJECT_TYPE_AREA
	};

	explicit JoltObjectImpl3D(ObjectType p_object_type);

	virtual ~JoltObjectImpl3D() = 0;

	ObjectType get_type() const { return object_type; }

	bool is_body() const { return object_type == OBJECT_TYPE_BODY; }

	bool is_soft_body() const { return object_type == OBJECT_TYPE_SOFT_BODY; }

	bool is_area() const { return object_type == OBJECT_TYPE_AREA; }

	bool is_shaped() const { return object_type != OBJECT_TYPE_SOFT_BODY; }

	JoltShapedObjectImpl3D *as_shaped() {
		return is_shaped() ? reinterpret_cast<JoltShapedObjectImpl3D *>(this) : nullptr;
	}

	const JoltShapedObjectImpl3D *as_shaped() const {
		return is_shaped() ? reinterpret_cast<const JoltShapedObjectImpl3D *>(this) : nullptr;
	}

	JoltBodyImpl3D *as_body() {
		return is_body() ? reinterpret_cast<JoltBodyImpl3D *>(this) : nullptr;
	}

	const JoltBodyImpl3D *as_body() const {
		return is_body() ? reinterpret_cast<const JoltBodyImpl3D *>(this) : nullptr;
	}

	JoltSoftBodyImpl3D *as_soft_body() {
		return is_soft_body() ? reinterpret_cast<JoltSoftBodyImpl3D *>(this) : nullptr;
	}

	const JoltSoftBodyImpl3D *as_soft_body() const {
		return is_soft_body() ? reinterpret_cast<const JoltSoftBodyImpl3D *>(this) : nullptr;
	}

	JoltAreaImpl3D *as_area() {
		return is_area() ? reinterpret_cast<JoltAreaImpl3D *>(this) : nullptr;
	}

	const JoltAreaImpl3D *as_area() const {
		return is_area() ? reinterpret_cast<const JoltAreaImpl3D *>(this) : nullptr;
	}

	RID get_rid() const { return rid; }

	void set_rid(const RID &p_rid) { rid = p_rid; }

	ObjectID get_instance_id() const { return instance_id; }

	void set_instance_id(ObjectID p_id) { instance_id = p_id; }

	JPH::BodyID get_jolt_id() const { return jolt_id; }

	Object *get_instance_unsafe() const;

	Object *get_instance_wrapped() const;

	JoltSpace3D *get_space() const { return space; }

	void set_space(JoltSpace3D *p_space);

	uint32_t get_collision_layer() const { return collision_layer; }

	void set_collision_layer(uint32_t p_layer);

	uint32_t get_collision_mask() const { return collision_mask; }

	void set_collision_mask(uint32_t p_mask);

	virtual Vector3 get_velocity_at_position(const Vector3 &p_position) const = 0;

	bool is_pickable() const { return pickable; }

	void set_pickable(bool p_enabled) { pickable = p_enabled; }

	bool can_collide_with(const JoltObjectImpl3D &p_other) const;

	bool can_interact_with(const JoltObjectImpl3D &p_other) const;

	virtual bool can_interact_with(const JoltBodyImpl3D &p_other) const = 0;

	virtual bool can_interact_with(const JoltSoftBodyImpl3D &p_other) const = 0;

	virtual bool can_interact_with(const JoltAreaImpl3D &p_other) const = 0;

	virtual bool reports_contacts() const = 0;

	virtual void pre_step(float p_step, JPH::Body &p_jolt_body);

	virtual void post_step(float p_step, JPH::Body &p_jolt_body);

	String to_string() const;

protected:
	virtual JPH::BroadPhaseLayer _get_broad_phase_layer() const = 0;

	virtual JPH::ObjectLayer _get_object_layer() const = 0;

	virtual void _add_to_space() = 0;

	virtual void _remove_from_space();

	void _reset_space();

	void _update_object_layer();

	virtual void _collision_layer_changed();

	virtual void _collision_mask_changed();

	virtual void _space_changing() {}

	virtual void _space_changed() {}

	LocalVector2<JoltShapeInstance3D> shapes;

	RID rid;

	ObjectID instance_id;

	JoltSpace3D *space = nullptr;

	JPH::BodyID jolt_id;

	uint32_t collision_layer = 1;

	uint32_t collision_mask = 1;

	ObjectType object_type = OBJECT_TYPE_INVALID;

	bool pickable = false;
};

#endif // JOLT_OBJECT_IMPL_3D_HPP
