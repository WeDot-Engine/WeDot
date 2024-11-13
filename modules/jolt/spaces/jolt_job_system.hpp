/**************************************************************************/
/*  jolt_job_system.hpp                                                   */
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

#ifndef JOLT_JOB_SYSTEM_HPP
#define JOLT_JOB_SYSTEM_HPP

#include "precompiled.hpp"

class JoltJobSystem final : public JPH::JobSystemWithBarrier {
public:
	JoltJobSystem();

	void pre_step();

	void post_step();

#ifdef GDJ_CONFIG_EDITOR
	void flush_timings();
#endif // GDJ_CONFIG_EDITOR

private:
	class Job : public JPH::JobSystem::Job {
	public:
		Job(const char *p_name,
				JPH::ColorArg p_color,
				JPH::JobSystem *p_job_system,
				const JPH::JobSystem::JobFunction &p_job_function,
				JPH::uint32 p_dependency_count);

		Job(const Job &p_other) = delete;

		Job(Job &&p_other) = delete;

		~Job();

		static void push_completed(Job *p_job);

		static Job *pop_completed();

		void queue();

		Job &operator=(const Job &p_other) = delete;

		Job &operator=(Job &&p_other) = delete;

	private:
		static void _execute(void *p_user_data);

		inline static std::atomic<Job *> completed_head = nullptr;

#ifdef GDJ_CONFIG_EDITOR
		const char *name = nullptr;
#endif // GDJ_CONFIG_EDITOR

		int64_t task_id = -1;

		std::atomic<Job *> completed_next = nullptr;
	};

	int GetMaxConcurrency() const override;

	JPH::JobHandle CreateJob(
			const char *p_name,
			JPH::ColorArg p_color,
			const JPH::JobSystem::JobFunction &p_job_function,
			JPH::uint32 p_dependency_count = 0) override;

	void QueueJob(JPH::JobSystem::Job *p_job) override;

	void QueueJobs(JPH::JobSystem::Job **p_jobs, JPH::uint p_job_count) override;

	void FreeJob(JPH::JobSystem::Job *p_job) override;

	void _reclaim_jobs();

#ifdef GDJ_CONFIG_EDITOR
	// HACK(mihe): We use `const void*` here to avoid the cost of hashing the actual string, since
	// the job names are always literals and as such will point to the same address every time.
	inline static HashMap<const void *, uint64_t> timings_by_job;

	inline static SpinLock timings_lock;
#endif // GDJ_CONFIG_EDITOR

	FreeList<Job> jobs;

	int32_t thread_count = 0;
};

#endif // JOLT_JOB_SYSTEM_HPP
