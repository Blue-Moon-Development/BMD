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
 * File Name: errors.cpp
 * Date File Created: 8/7/2020 at 3:06 PM
 * Author: Matt
 */

#include "bmd/errors.h"
#include "bmd/logger.h"

#if defined(_MSC_VER) && defined(__cplusplus)
void LogStackWalker::OnOutput(LPCSTR szText)
{
	if(BMD_VERBOSE)
		printf(szText);
	//logMessageNoLevel(szText, m_file, m_func, m_line);
	StackWalker::OnOutput(szText);
}

void
LogStackWalker::OnCallstackEntry(StackWalker::CallstackEntryType eType, StackWalker::CallstackEntry& entry)
{
	//logMessageNoLevel(entry.name, entry.lineFileName, entry.moduleName, entry.lineNumber);
	info.push_back(entry);
	StackWalker::OnCallstackEntry(eType, entry);
}

void LogStackWalker::logStacktrace()
{
	std::string data;
	for(const auto& i : info)
	{
		data.append("In ");
		data.append(i.name); //function
		data.append(" at ");
		data.append(i.lineFileName); // file name
		data.append(":");
		char ln[10];
		long nln = 0;
		//if(i.lineNumber != 0)
			nln = (long)i.lineNumber - 1;
		//if(i.lineNumber == 0)
		sprintf(ln, "%ld", nln); // Line number
		data.append(ln);
		data.append(" of module ");
		data.append(i.moduleName); //exe name
		data.append(" (sym type ");
		data.append(i.symTypeString); // PDB (when debug, i assume different when not debug)
		data.append(")\n");
	}
	logMessageNoLevel(data.c_str(), m_file, m_func, m_line);
}

#endif



const char* getErrorString(int error)
{
	switch (error)
	{
		case BMD_NO_ERROR:
			return errString(BMD_NO_ERROR);
		case BMD_ERROR_NOT_YET_IMPLEMENTED:
			return errString(BMD_ERROR_NOT_YET_IMPLEMENTED);
		case BMD_ERROR_NOT_SUPPORTED_BY_PLATFORM:
			return errString(BMD_ERROR_NOT_SUPPORTED_BY_PLATFORM);
		case BMD_ERROR_CHAR_NOT_IN_STRING:
			return errString(BMD_ERROR_CHAR_NOT_IN_STRING);
		case BMD_ERROR_OPEN_DIR:
			return errString(BMD_ERROR_OPEN_DIR);
		case BMD_ERROR_CLOSE_DIR:
			return errString(BMD_ERROR_CLOSE_DIR);
		case BMD_ERROR_NEXT_FILE:
			return errString(BMD_ERROR_NEXT_FILE);
		case BMD_ERROR_READ_FILE:
			return errString(BMD_ERROR_READ_FILE);
		case BMD_ERROR_NULL_FILE:
			return errString(BMD_ERROR_NULL_FILE);
		case BMD_ERROR_FILE_NOT_FOUND:
			return errString(BMD_ERROR_FILE_NOT_FOUND);
		case BMD_ERROR_FILE_TIME:
			return errString(BMD_ERROR_FILE_TIME);
		case BMD_ERROR_CHAR_NOT_FOUND:
			return errString(BMD_ERROR_CHAR_NOT_FOUND);
		case BMD_ERROR_NULL_STRING:
			return errString(BMD_ERROR_NULL_STRING);
		case BMD_ERROR_EXCEEDS_LENGTH:
			return errString(BMD_ERROR_EXCEEDS_LENGTH);
		case BMD_ERROR_INVALID_MEMORY_ALLOCATION:
			return errString(BMD_ERROR_INVALID_MEMORY_ALLOCATION);
		case BMD_ERROR_NOT_A_FILE:
			return errString(BMD_ERROR_NOT_A_FILE);
		case BMD_ERROR_TRAVERSE:
			return errString(BMD_ERROR_TRAVERSE);
		case BMD_ERROR_PATH_NOT_FOUND:
			return errString(BMD_ERROR_PATH_NOT_FOUND);
		case BMD_ERROR_CREATE_DIR:
			return errString(BMD_ERROR_CREATE_DIR);

		default:
			return "Invalid Error";
	}
}

