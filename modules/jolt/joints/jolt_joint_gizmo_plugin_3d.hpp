/**************************************************************************/
/*  jolt_joint_gizmo_plugin_3d.hpp                                        */
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

#ifndef JOLT_JOINT_GIZMO_PLUGIN_3D_HPP
#define JOLT_JOINT_GIZMO_PLUGIN_3D_HPP

#include "precompiled.hpp"

#include <editor/editor_interface.h>
#include <editor/plugins/node_3d_editor_gizmos.h>

#ifdef GDJ_CONFIG_EDITOR

class JoltJointGizmoPlugin3D final : public EditorNode3DGizmoPlugin {
	GDCLASS_QUIET(JoltJointGizmoPlugin3D, EditorNode3DGizmoPlugin)

	static void _bind_methods() {}

public:
	JoltJointGizmoPlugin3D() = default;

	explicit JoltJointGizmoPlugin3D(EditorInterface *p_editor_interface);

	String get_gizmo_name() const override;

	void redraw(EditorNode3DGizmo *p_gizmo) override;

protected:
	bool has_gizmo(Node3D *p_spatial) override;
	Ref<EditorNode3DGizmo> create_gizmo(Node3D *p_spatial) override;

private:
	void _create_materials();

	void _create_redraw_timer(const Ref<EditorNode3DGizmo> &p_gizmo);

	void _redraw_gizmos();

	mutable HashSet2<Ref<EditorNode3DGizmo>> gizmos;

	EditorInterface *editor_interface = nullptr;

	bool initialized = false;
};

#endif // GDJ_CONFIG_EDITOR

#endif // JOLT_JOINT_GIZMO_PLUGIN_3D_HPP
