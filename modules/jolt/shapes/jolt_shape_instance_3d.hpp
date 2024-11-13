/**************************************************************************/
/*  jolt_shape_instance_3d.hpp                                            */
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

#ifndef JOLT_SHAPE_INSTANCE_3D_HPP
#define JOLT_SHAPE_INSTANCE_3D_HPP

#include "precompiled.hpp"

#include <core/math/transform_3d.h>

class JoltShapedObjectImpl3D;
class JoltShapeImpl3D;

class JoltShapeInstance3D {
public:
	JoltShapeInstance3D(
			JoltShapedObjectImpl3D *p_parent,
			JoltShapeImpl3D *p_shape,
			const Transform3D &p_transform = {},
			const Vector3 &p_scale = { 1.0f, 1.0f, 1.0f },
			bool p_disabled = false);

	JoltShapeInstance3D(const JoltShapeInstance3D &p_other) = delete;

	JoltShapeInstance3D(JoltShapeInstance3D &&p_other) noexcept;

	~JoltShapeInstance3D();

	uint32_t get_id() const { return id; }

	JoltShapeImpl3D *get_shape() const { return shape; }

	const JPH::Shape *get_jolt_ref() const { return jolt_ref; }

	const Transform3D &get_transform_unscaled() const { return transform; }

	Transform3D get_transform_scaled() const { return transform.scaled_local(scale); }

	void set_transform(const Transform3D &p_transform) { transform = p_transform; }

	const Vector3 &get_scale() const { return scale; }

	void set_scale(const Vector3 &p_scale) { scale = p_scale; }

	bool is_built() const { return jolt_ref != nullptr; }

	bool is_enabled() const { return !disabled; }

	bool is_disabled() const { return disabled; }

	void enable() { disabled = false; }

	void disable() { disabled = true; }

	bool try_build();

	JoltShapeInstance3D &operator=(const JoltShapeInstance3D &p_other) = delete;

	JoltShapeInstance3D &operator=(JoltShapeInstance3D &&p_other) noexcept;

private:
	inline static uint32_t next_id = 1;

	Transform3D transform;

	Vector3 scale;

	JPH::ShapeRefC jolt_ref;

	JoltShapedObjectImpl3D *parent = nullptr;

	JoltShapeImpl3D *shape = nullptr;

	uint32_t id = next_id++;

	bool disabled = false;
};

#endif // JOLT_SHAPE_INSTANCE_3D_HPP
