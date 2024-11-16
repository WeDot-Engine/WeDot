/**************************************************************************/
/*  register_types.cpp                                                    */
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

/* register_types.cpp */

#include "register_types.h"

#include <servers/physics_server_3d.h>

#include <joints/jolt_cone_twist_joint_3d.hpp>
#include <joints/jolt_generic_6dof_joint.hpp>
#include <joints/jolt_hinge_joint_3d.hpp>
#include <joints/jolt_joint_3d.hpp>
#include <joints/jolt_pin_joint_3d.hpp>
#include <joints/jolt_slider_joint_3d.hpp>
#include <objects/jolt_physics_direct_body_state_3d.hpp>
#include <servers/jolt_globals.hpp>
#include <servers/jolt_physics_server_3d.hpp>
#include <servers/jolt_project_settings.hpp>
#include <spaces/jolt_physics_direct_space_state_3d.hpp>

static PhysicsServer3D *_createJoltPhysics3DCallback() {
	return memnew(JoltPhysicsServer3D());
}

void initialize_jolt_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SERVERS) {
		return;
	}
	switch (p_level) {
		case MODULE_INITIALIZATION_LEVEL_CORE:
			break;
		case MODULE_INITIALIZATION_LEVEL_SERVERS:
			jolt_initialize();
			JoltProjectSettings::register_settings();

			ClassDB::register_class<JoltPhysicsDirectBodyState3D>();
			ClassDB::register_class<JoltPhysicsDirectSpaceState3D>();
			ClassDB::register_class<JoltPhysicsServer3D>();

			PhysicsServer3DManager::get_singleton()->register_server("JoltPhysics3D", callable_mp_static(_createJoltPhysics3DCallback));
			PhysicsServer3DManager::get_singleton()->set_default_server("JoltPhysics3D");

			break;
		case MODULE_INITIALIZATION_LEVEL_SCENE:

			ClassDB::register_class<JoltJoint3D>(true);
			ClassDB::register_class<JoltPinJoint3D>();
			ClassDB::register_class<JoltHingeJoint3D>();
			ClassDB::register_class<JoltSliderJoint3D>();
			ClassDB::register_class<JoltConeTwistJoint3D>();
			ClassDB::register_class<JoltGeneric6DOFJoint3D>();
			break;
		case MODULE_INITIALIZATION_LEVEL_EDITOR:
			break;
	}
}

void uninitialize_jolt_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		jolt_deinitialize();
	}
	// Nothing to do here in this example.
}
