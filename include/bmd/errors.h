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
 * File Name: errors.h
 * Date File Created: 7/29/2020 at 11:03 PM
 * Author: Matt
 */

#ifndef BMD_ERRORS_H
#define BMD_ERRORS_H

#include "common.h"
#include "types.h"

#define checkError(error) if(error) return error;
#define checkErrorMsg(error, format, ...) if(error) {    \
if(BMD_DEBUGGING) {                                            \
fprintf(stderr, "Error (%i):\n", error);                \
fprintf(stderr, format, ##__VA_ARGS__);                            \
}                                                        \
return error;                                        \
}

#define BMD_NO_ERROR 0
#define BMD_OKAY BMD_NO_ERROR
#define BMD_OK BMD_OKAY
#define BMD_ERROR_NOT_YET_IMPLEMENTED -1
#define BMD_ERROR_NOT_SUPPORTED_BY_PLATFORM -2
#define BMD_ERROR_CHAR_NOT_IN_STRING -3
#define BMD_ERROR_OPEN_DIR -4
#define BMD_ERROR_CLOSE_DIR -5
#define BMD_ERROR_NEXT_FILE -6
#define BMD_ERROR_READ_FILE -7
#define BMD_ERROR_NULL_FILE -8
#define BMD_ERROR_FILE_NOT_FOUND -9
#define BMD_ERROR_FILE_TIME -10
#define BMD_ERROR_CHAR_NOT_FOUND -11
#define BMD_ERROR_NULL_STRING -12
#define BMD_ERROR_EXCEEDS_LENGTH -13
#define BMD_ERROR_INVALID_MEMORY_ALLOCATION -14
#define BMD_ERROR_NOT_A_FILE -15
#define BMD_ERROR_TRAVERSE -16
#define BMD_ERROR_PATH_NOT_FOUND -17
#define BMD_ERROR_CREATE_DIR -18


#define errNoToStr(error) #error
#define errString(error) "(" errNoToStr(error) ") " #error

extern const char* getErrorString(int error);




#if defined(_MSC_VER) && defined(__cplusplus)
	#include <StackWalker.h>
	#include <string>
	#define STACKTRACE LogStackWalker(__FILE__, __FUNCTION__, __LINE__)
	class LogStackWalker : public StackWalker
	{
	public:
		LogStackWalker(const char* file, const char* func, int line) :
		m_file(file),
		m_func(func),
		m_line(line),
		StackWalker() {}

		void logStacktrace();
	protected:
		void OnOutput(LPCSTR szText) override;
		void OnCallstackEntry(CallstackEntryType eType, CallstackEntry &entry) override;
		const char* m_file;
		const char* m_func;
		int m_line;
		list<CallstackEntry> info;
	};


#endif

#endif //BMD_ERRORS_H
