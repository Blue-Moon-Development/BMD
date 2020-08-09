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
 * File Name: logger.cpp
 * Date File Created: 8/7/2020 at 2:11 AM
 * Author: Matt
 */

#include "bmd/logger.h"
#include "bmd/common.h"
#include "bmd/strutil.h"
#include "bmd/timer.h"
#include "bmd/errors.h"

file_t g_logFile;
int g_initialized;
fs_time lastTime;
int count = 0;

void findOldestFile(file_t* file, void* data)
{
	fs_time time;
	getLastModifiedTime(file, &time);
	if (count > 0)
	{
		int a = compareTimes(&time, &lastTime);
		if (a < 0)
		{
			getLastModifiedTime(file, &lastTime);
			copyStr((*(file_t*) data).path, file->path);
		}
	} else
	{
		getLastModifiedTime(file, &lastTime);
		copyStr((*(file_t*) data).path, file->path);
	}
	count++;
}


void initLog(const char* logPath, int mode, int maxArchives)
{
	if (!doesFileExist(logPath))
	{
		char buf[100];
		getCurrentTime(buf);
		char initBuf[500];
		//== == == ==
		sprintf(initBuf,
				"================================== Log created on %s ==================================\n\n",
				buf);
		writeFile(logPath, initBuf, "wt");
		loadFile(logPath, &g_logFile);
	} else
	{
		if (mode == LOG_MODE_OVERWRITE || mode == LOG_MODE_ARCHIVE)
		{
			if (mode == LOG_MODE_ARCHIVE)
			{

				file_t oldestLog;
				int error = createDir("./logs");
				if (!error)
				{
					traverse("./logs", findOldestFile, &oldestLog);
					if (count >= maxArchives)
					{
						remove(oldestLog.path);
						char bufTime[100];
						getCurrentTime(bufTime, "%m-%d-%Y_%H-%M-%S");
						char archivedLogPath[MAX_PATH_LENGTH];
						sprintf(archivedLogPath, "./logs/archived-log-%s.log", bufTime);
						rename(logPath, archivedLogPath);
					} else
					{
						char archivedLogPath[MAX_PATH_LENGTH];
						char bufTime[100];
						getCurrentTime(bufTime, "%m-%d-%Y_%H-%M-%S");
						sprintf(archivedLogPath, "./logs/archived-log-%s.log", bufTime);
						rename(logPath, archivedLogPath);
					}
				}
			}


			char buf[100];
			getCurrentTime(buf);
			char initBuf[500];
			//== == == ==
			sprintf(initBuf,
					"================================== Log created on %s ==================================\n\n",
					buf);
			writeFile(logPath, initBuf, "wt");
			loadFile(logPath, &g_logFile);
		} else if (mode == LOG_MODE_APPEND)
		{
			char buf[100];
			getCurrentTime(buf);
			char initBuf[500];
			sprintf(initBuf,
					"\n\n\n============================== Current log started on %s ==============================\n\n",
					buf);
			loadFile(logPath, &g_logFile);
			writeFile(&g_logFile, initBuf, "at");
		}
	}
	g_initialized = 1;
}

void logMessage(const char* level, const char* msg, const char* file, const char* func, int line)
{
	if (g_initialized)
	{
		char buf[100];
		getCurrentTime(buf);
		char data[2048] = { };
		sprintf(data, "\n[%s] [%s] [%s:%d] [%s] %s", buf, level, file, line, func, msg);
		writeFile(&g_logFile, data, "at");
		print("%s", data);
	}
}

void logMessageNoLevel(const char* msg, const char* file, const char* func, int line)
{
	if (g_initialized)
	{
		char data[2048] = { };
		sprintf(data, "\nStack Trace at [%s:%d] [%s]\n%s", file, line, func, msg);
		writeFile(&g_logFile, data, "at");
	}
}

void logTraceMessage(const char* msg, const char* file, const char* func, int line)
{
	logMessage(LEVEL_TRACE, msg, file, func, line);
}

void logDebugMessage(const char* msg, const char* file, const char* func, int line)
{
	logMessage(LEVEL_DEBUG, msg, file, func, line);
}

void logInfoMessage(const char* msg, const char* file, const char* func, int line)
{
	logMessage(LEVEL_INFO, msg, file, func, line);
}

void logWarnMessage(const char* msg, const char* file, const char* func, int line)
{
	logMessage(LEVEL_WARN, msg, file, func, line);
}

void logErrorMessage(const char* msg, const char* file, const char* func, int line)
{
	logMessage(LEVEL_ERROR, msg, file, func, line);
#if  defined(_MSC_VER) && defined(__cplusplus)
	LogStackWalker lsw(file, func, line);
	lsw.ShowCallstack();
	lsw.logStacktrace();
#endif
}

