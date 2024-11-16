/**************************************************************************/
/*  jolt_project_settings.hpp                                             */
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

#ifndef JOLT_PROJECT_SETTINGS_HPP
#define JOLT_PROJECT_SETTINGS_HPP

class JoltProjectSettings {
public:
	static void register_settings();

	static bool is_sleep_enabled();

	static float get_sleep_velocity_threshold();

	static float get_sleep_time_threshold();

	static bool use_shape_margins();

	static bool areas_detect_static_bodies();

	static bool report_all_kinematic_contacts();

	static bool use_enhanced_edge_removal();

	static float get_soft_body_point_margin();

	static bool use_joint_world_node_a();

	static float get_ccd_movement_threshold();

	static float get_ccd_max_penetration();

	static int32_t get_kinematic_recovery_iterations();

	static float get_kinematic_recovery_amount();

	static int32_t get_velocity_iterations();

	static int32_t get_position_iterations();

	static float get_position_correction();

	static float get_active_edge_threshold();

	static float get_bounce_velocity_threshold();

	static float get_contact_distance();

	static float get_contact_penetration();

	static bool is_pair_cache_enabled();

	static float get_pair_cache_distance();

	static float get_pair_cache_angle();

	static float get_max_linear_velocity();

	static float get_max_angular_velocity();

	static int32_t get_max_bodies();

	static int32_t get_max_pairs();

	static int32_t get_max_contact_constraints();

	static int32_t get_max_temp_memory_mib();

	static int64_t get_max_temp_memory_b();

	static bool should_run_on_separate_thread();

	static int32_t get_max_threads();
};

#endif // JOLT_PROJECT_SETTINGS_HPP
