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
 * File Name: main.cpp
 * Date File Created: 8/10/2020 at 7:16 PM
 * Author: Matt
 */

#include <bmd/logger.h>
#define BMD_PROFILE 1
#include <bmd/profiler.h>

int main(int argc, char** argv)
{
	initLog("./info.log", LOG_MODE_APPEND, 5);
	PROFILER_START("All log tests");
	//PROFILER_START("Log profiling");
	logInfo("This is a test log for C++");
	//PROFILER_END;
	logTrace("This is a test log for C++");
	logDebug("This is a test log for C++");
	logWarn("This is a test log for C++");
	logError("This is a test log for C++");
	logError("This is a test log for C++");
	PROFILER_END;
	return 0;
}

