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
 * File Name: logger.h
 * Date File Created: 8/7/2020 at 12:30 AM
 * Author: Matt
 */

#ifndef BMD_LOGGER_H
#define BMD_LOGGER_H

// TODO: Multiple levels of logging - trace/fine, debug, info, warn, error
// TODO: Overwrite same file as option
// TODO: Append to same file as option
// TODO: Archive files up to X times

#include "files.h"

#define LEVEL_TRACE "trace"
#define LEVEL_DEBUG "debug"
#define LEVEL_INFO "info"
#define LEVEL_WARN "warn"
#define LEVEL_ERROR "error"

#define LOG_MODE_OVERWRITE 1
#define LOG_MODE_APPEND 2
#define LOG_MODE_ARCHIVE 3


// TODO: Messages being print to console should definitely depend if 'debug' is enabled, but what about outputting to the files?
// Certainly could hinder performance, but isn't the point of log files so users can send to devs for error reports?
// Maybe have general output logging only in debug, but warn/error goes to file regardless?

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void initLog(const char* logPath, int mode, int maxArchives);
void logMessage(const char* level, const char* msg, const char* file, const char* func, int line);
void logMessageNoLevel(const char* msg, const char* file, const char* func, int line);

void logTraceMessage(const char* msg, const char* file, const char* func, int line);
void logDebugMessage(const char* msg, const char* file, const char* func, int line);
void logInfoMessage(const char* msg, const char* file, const char* func, int line);
void logWarnMessage(const char* msg, const char* file, const char* func, int line);
void logErrorMessage(const char* msg, const char* file, const char* func, int line);

#ifdef __cplusplus
};
#endif // __cplusplus


#define logTrace(msg) logTraceMessage(msg, __FILE__, __FUNCTION__, __LINE__)
#define logDebug(msg) logDebugMessage(msg, __FILE__, __FUNCTION__, __LINE__)
#define logInfo(msg) logInfoMessage(msg, __FILE__, __FUNCTION__, __LINE__)
#define logWarn(msg) logWarnMessage(msg, __FILE__, __FUNCTION__, __LINE__)
#define logError(msg) logErrorMessage(msg, __FILE__, __FUNCTION__, __LINE__)

// TODO: Seems fairly slow with the profiler. Need to compare to spdlog. If spdlog is significantly faster,
// then why bother having this logger in bmd if i myself wouldn't use it?

#ifdef BMD_HEADERS_ONLY
	#ifndef BMD_LOGGER_IMPL
		#define BMD_LOGGER_IMPL
		#include "bmd/common.h"
#include "bmd/strutil.h"
#include "bmd/timer.h"

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
}
	#endif
#endif

#endif //BMD_LOGGER_H
