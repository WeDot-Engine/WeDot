/**************************************************************************/
/*  jolt_debug_geometry_3d.hpp                                            */
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

#ifndef JOLT_DEBUG_GEOMETRY_3D_HPP
#define JOLT_DEBUG_GEOMETRY_3D_HPP

#include "precompiled.hpp"

#include "spaces/jolt_debug_renderer_3d.hpp"

#include <scene/3d/visual_instance_3d.h>

class JoltDebugGeometry3D final : public GeometryInstance3D {
	GDCLASS_QUIET(JoltDebugGeometry3D, GeometryInstance3D)

public:
	enum ColorScheme {
		COLOR_SCHEME_INSTANCE,
		COLOR_SCHEME_SHAPE_TYPE,
		COLOR_SCHEME_MOTION_TYPE,
		COLOR_SCHEME_SLEEP_STATE,
		COLOR_SCHEME_ISLAND
	};

private:
	static void _bind_methods();

public:
	JoltDebugGeometry3D();

	~JoltDebugGeometry3D() override;

	bool get_draw_bodies() const;

	void set_draw_bodies(bool p_enabled);

	bool get_draw_shapes() const;

	void set_draw_shapes(bool p_enabled);

	bool get_draw_constraints() const;

	void set_draw_constraints(bool p_enabled);

	bool get_draw_bounding_boxes() const;

	void set_draw_bounding_boxes(bool p_enabled);

	bool get_draw_centers_of_mass() const;

	void set_draw_centers_of_mass(bool p_enabled);

	bool get_draw_transforms() const;

	void set_draw_transforms(bool p_enabled);

	bool get_draw_velocities() const;

	void set_draw_velocities(bool p_enabled);

	bool get_draw_triangle_outlines() const;

	void set_draw_triangle_outlines(bool p_enabled);

	bool get_draw_soft_body_vertices() const;

	void set_draw_soft_body_vertices(bool p_enabled);

	bool get_draw_soft_body_edge_constraints() const;

	void set_draw_soft_body_edge_constraints(bool p_enabled);

	bool get_draw_soft_body_volume_constraints() const;

	void set_draw_soft_body_volume_constraints(bool p_enabled);

	bool get_draw_soft_body_predicted_bounds() const;

	void set_draw_soft_body_predicted_bounds(bool p_enabled);

	bool get_draw_constraint_reference_frames() const;

	void set_draw_constraint_reference_frames(bool p_enabled);

	bool get_draw_constraint_limits() const;

	void set_draw_constraint_limits(bool p_enabled);

	bool get_draw_as_wireframe() const;

	void set_draw_as_wireframe(bool p_enabled);

	ColorScheme get_draw_with_color_scheme() const;

	void set_draw_with_color_scheme(ColorScheme p_color_scheme);

	bool get_material_depth_test() const;

	void set_material_depth_test(bool p_enabled);

private:
#ifdef JPH_DEBUG_RENDERER
	JoltDebugRenderer3D::DrawSettings draw_settings;

	RID mesh;

	JoltDebugRenderer3D *debug_renderer = nullptr;

	Ref<StandardMaterial3D> default_material;
#endif // JPH_DEBUG_RENDERER
};

VARIANT_ENUM_CAST(JoltDebugGeometry3D::ColorScheme)

#endif // JOLT_DEBUG_GEOMETRY_3D_HPP
