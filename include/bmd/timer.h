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
 * File Name: timer.h
 * Date File Created: 8/7/2020 at 2:00 PM
 * Author: Matt
 */

#ifndef BMD_TIMER_H
#define BMD_TIMER_H

#define DEFAULT_TIME_FORMAT "%m-%d-%Y %H:%M:%S"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef __cplusplus
	void getCurrentTime(char (&timeStr)[100], const char* format);
#else
void getCurrentTime(char timeStr[100], const char* format);
#endif


#ifdef __cplusplus
};
#endif // __cplusplus

#ifdef BMD_HEADERS_ONLY
	#ifndef BMD_TIMER_IMPL
		#define BMD_TIMER_IMPL
#include <time.h>

#ifdef __cplusplus
void getCurrentTime(char (&timeStr)[100], const char* format)
	#else
void getCurrentTime(char timeStr[100], const char* format)
	#endif
{
	time_t rawTime;
	struct tm* timeInfo;
	time(&rawTime);
	timeInfo = localtime(&rawTime);
	strftime(timeStr, 100, format, timeInfo);
}
	#endif // BMD_TIMER_IMPL
#endif // BMD_HEADERS_ONLY

#endif //BMD_TIMER_H
