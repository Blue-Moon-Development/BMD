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
 * File Name: profiler.c
 * Date File Created: 8/12/2020 at 4:35 PM
 * Author: Matt
 */

#include "bmd/profiler.h"

#if !BMD_DEBUGGING && !BMD_VERBOSE
#include <stdio.h>
#endif


const char* g_name;
timer_t g_timer;

void start_profiler_internal(const char* name)
{
	g_name = name;
	initTimer(&g_timer);
}

void stop_profiler_internal()
{
	tickTimer(&g_timer);
	int64_f s = seconds(&g_timer, g_timer.elapsedTime);
	int64_f ms = milliseconds(&g_timer, g_timer.elapsedTime);
	int64_f us = microseconds(&g_timer, g_timer.elapsedTime);
	char abrev[3] = { (char) 230, 's', 0 };
	if (us >= 1000)
	{
		us %= 1000;
		if (ms >= 1000)
		{
			ms %= 1000;
		}
	}

	if (s >= 1)
	{
		if (ms >= 1 && us < 1)
			fprintf(stderr, "Profiler [%s] Duration: %lli s %lli ms -- Start time: %lli -- End time: %lli\n",
					g_name, s, ms, g_timer.startTime, g_timer.currentTime);
		else if (ms >= 1 && us >= 1)
			fprintf(stderr,
					"Profiler [%s] Duration: %lli s %lli ms %lli %s -- Start time: %lli -- End time: %lli\n",
					g_name, s, ms, us, abrev, g_timer.startTime, g_timer.currentTime);
		else if (ms < 1 && us < 1)
			fprintf(stderr, "Profiler [%s] Duration: %lli s -- Start time: %lli -- End time: %lli\n",
					g_name, s, g_timer.startTime, g_timer.currentTime);
		else if (ms < 1 && us >= 1)
			fprintf(stderr, "Profiler [%s] Duration: %lli s %lli %s -- Start time: %lli -- End time: %lli\n",
					g_name, s, us, abrev, g_timer.startTime, g_timer.currentTime);
	} else if (ms >= 1)
	{
		if (us >= 1)
			fprintf(stderr, "Profiler [%s] Duration: %lli ms %lli %s -- Start time: %lli -- End time: %lli\n",
					g_name, ms, us, abrev, g_timer.startTime, g_timer.currentTime);
		else
			fprintf(stderr, "Profiler [%s] Duration: %lli ms -- Start time: %lli -- End time: %lli\n",
					g_name, ms, g_timer.startTime, g_timer.currentTime);
	} else if (us >= 1)
	{
		fprintf(stderr, "Profiler [%s] Duration: %lli %s -- Start time: %lli -- End time: %lli\n",
				g_name, us, abrev, g_timer.startTime, g_timer.currentTime);
	}


}


