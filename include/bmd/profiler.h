/*
 * BMD
 * Copyright (C) 2020 Blue Moon Development. All rights reserved.
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * 
 * Contact: team@bluemoondev.org
 * 
 * File Name: profiler.h
 * Date File Created: 8/9/2020 at 2:14 PM
 * Author: Matt
 */

#ifndef BMD_PROFILER_H
#define BMD_PROFILER_H

#include <algorithm>
#include <chrono>
#include <string>

typedef std::chrono::duration<double, std::micro> fltmicro;

/**
* Very basic minimal profiler, use the PROFILER_START and PROFILER_STOP macros to use this.<p>
* #define BMD_PROFILE 1 before including this header to enable the profiler
*/
class Profiler
{
public:
	static void start(const char* name)
	{
		if(!instance().isStopped())
			stop();
		instance().setName(name);
		instance().setStart(std::chrono::steady_clock::now());
		instance().setStopped(false);
	}

	static void stop()
	{
		auto endTime = std::chrono::steady_clock::now();
		auto highResStart = fltmicro { instance().getStart().time_since_epoch() };
		auto elapsedTime =
				std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch() -
				std::chrono::time_point_cast<std::chrono::microseconds>(instance().getStart()).time_since_epoch();
		fprintf(stderr, "Profiler Result [%s] Duration: %lld ms (Start time %.3f)\n",
				instance().getName(), elapsedTime.count(), highResStart.count());
		instance().setStopped(true);
	}

private:

	Profiler() = default;
	static Profiler& instance()
	{
		static Profiler prof;
		return prof;
	}

	void setName(const char* name){
		m_name = name;
	}

	void setStart(std::chrono::time_point<std::chrono::steady_clock> start){
		m_start = start;
	}

	void setStopped(bool stopped){
		m_stopped = stopped;
	}

	const char* getName(){
		return m_name;
	}

	std::chrono::time_point<std::chrono::steady_clock> getStart(){
		return m_start;
	}

	bool isStopped(){
		return m_stopped;
	}

	const char* m_name{};
	std::chrono::time_point<std::chrono::steady_clock> m_start;
	bool m_stopped = true;
};



#ifndef BMD_PROFILE
	#define BMD_PROFILE 0
#endif

#if BMD_PROFILE
	#define PROFILER_START(name) Profiler::start(name)
	#define PROFILER_END Profiler::stop()
#else
	#define PROFILER_START(...)
	#define PROFILER_END
#endif


#endif //BMD_PROFILER_H
