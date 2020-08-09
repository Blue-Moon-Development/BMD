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


extern void initLog(const char* logPath, int mode, int maxArchives = 5);
extern void logMessage(const char* level, const char* msg, const char* file, const char* func, int line);
extern void logMessageNoLevel(const char* msg, const char* file, const char* func, int line);

extern void logTraceMessage(const char* msg, const char* file, const char* func, int line);
extern void logDebugMessage(const char* msg, const char* file, const char* func, int line);
extern void logInfoMessage(const char* msg, const char* file, const char* func, int line);
extern void logWarnMessage(const char* msg, const char* file, const char* func, int line);
extern void logErrorMessage(const char* msg, const char* file, const char* func, int line);


#define logTrace(msg) logTraceMessage(msg, __FILE__, __FUNCTION__, __LINE__)
#define logDebug(msg) logDebugMessage(msg, __FILE__, __FUNCTION__, __LINE__)
#define logInfo(msg) logInfoMessage(msg, __FILE__, __FUNCTION__, __LINE__)
#define logWarn(msg) logWarnMessage(msg, __FILE__, __FUNCTION__, __LINE__)
#define logError(msg) logErrorMessage(msg, __FILE__, __FUNCTION__, __LINE__)

#endif //BMD_LOGGER_H
