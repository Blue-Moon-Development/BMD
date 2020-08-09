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
 * File Name: files.cpp
 * Date File Created: 7/29/2020 at 10:19 PM
 * Author: Matt
 */

#include "bmd/files.h"
#include "bmd/errors.h"
#include "bmd/common.h"
#include "bmd/strutil.h"
#include "bmd/logger.h"


const char* getExt(file_t* file)
{
	char* cpyOfName = file->name;
	char* period = NULL;
	while (*cpyOfName++)
	{
		if (*cpyOfName == '.')
		{
			period = cpyOfName;
			break;
		}
	}

	if (period) copyStr_s(file->ext, period, MAX_EXT_LENGTH);
	else file->ext[ 0 ] = 0;
	return file->ext;
}

int doesFileHaveExt(file_t* file, const char* ext)
{
	// strcmp returns 0 if they match, so !strcmp returns 0 when it's not 0 and 1 when it is 0
	return !strcmp(file->ext, ext);
}


int loadFile(const char* dirPath, const char* fileName, file_t* file)
{
	int error = BMD_NO_ERROR;
	dir_t dir;
	error = openDir(&dir, dirPath);
	if (error) return error;
	file_t temp;
	while (dir.hasNext)
	{
		error = loadFile(&dir, &temp);
		if (error) return error;
		if (temp.isFile && strcmp(temp.name, fileName) == 0)
		{
			copyStr_s(file->path, temp.path, MAX_PATH_LENGTH);
			copyStr_s(file->name, temp.name, MAX_FILENAME_LENGTH);
			copyStr_s(file->ext, temp.ext, MAX_EXT_LENGTH);
			file->isDir = temp.isDir;
			file->isFile = temp.isFile;
			file->size = temp.size;
			closeDir(&dir);
			return error;
		}
		error = nextFile(&dir);
		if (error) return error;
	}

	closeDir(&dir);
	return BMD_ERROR_FILE_NOT_FOUND;
}

int loadFile(const char* filePath, file_t* file)
{
	if(!doesFileExist(filePath))
	{
		FILE* f;
		fopen_s(&f, filePath, "at");
		fclose(f);
	}
	int lastSlashIndex = lastIndexOf(filePath, '/');
	if (lastSlashIndex < 0)
		lastSlashIndex = lastIndexOf(filePath, '\\');
	if (lastSlashIndex < 0)
		return lastSlashIndex;
	char* dirName = substr(filePath, 0, lastSlashIndex);
	char* fileName = substr(filePath, lastSlashIndex + 1);

	return loadFile(dirName, fileName, file);
}

int readFile(const char* file, char** data)
{
	if (!doesFileExist(file)) return NULL;
	FILE* f;
	int error = fopen_s(&f, file, "rt");
	checkErrorMsg(error, "Could not open file %s\n", file);
	fseek(f, 0, SEEK_END);
	ulong len = ftell(f);
	char* buffer = (char*) malloc(len + 1);
	if (!buffer)
	{
		checkErrorMsg(BMD_ERROR_INVALID_MEMORY_ALLOCATION,
					  "Failed to allocate memory while reading file %s\n", file);
	}
	memset(buffer, 0, len + 1);
	fseek(f, 0, SEEK_SET);
	fread(buffer, 1, len, f);
	*data = buffer;
	error = fclose(f);
	checkErrorMsg(error, "Failed to close file %s\n", file);
	return BMD_NO_ERROR;
}

int loadFileAndReadContents(const char* dir, const char* fileName, file_t* file)
{
	int error = BMD_NO_ERROR;
	dir_t dirt;
	error = openDir(&dirt, dir);
	if (error) return error;
	file_t temp;
	while (dirt.hasNext)
	{
		error = loadFileAndReadContents(&dirt, &temp);
		if (error) return error;
		if (temp.isFile && strcmp(temp.name, fileName) == 0)
		{
			copyStr_s(file->path, temp.path, MAX_PATH_LENGTH);
			copyStr_s(file->name, temp.name, MAX_FILENAME_LENGTH);
			copyStr_s(file->ext, temp.ext, MAX_EXT_LENGTH);
			file->isDir = temp.isDir;
			file->isFile = temp.isFile;
			file->size = temp.size;
			file->contents = temp.contents;
			closeDir(&dirt);
			return error;
		}
		error = nextFile(&dirt);
		if (error) return error;
	}
	closeDir(&dirt);
	return BMD_ERROR_FILE_NOT_FOUND;
}

int loadFileAndReadContents(const char* filePath, file_t* file)
{
	int lastSlashIndex = lastIndexOf(filePath, '/');
	if (lastSlashIndex < 0)
		lastSlashIndex = lastIndexOf(filePath, '\\');
	if (lastSlashIndex < 0)
		return lastSlashIndex;
	char* dirName = substr(filePath, 0, lastSlashIndex);
	char* fileName = substr(filePath, lastSlashIndex + 1);

	return loadFileAndReadContents(dirName, fileName, file);
}

int readFileContents(file_t* file)
{
	if (!file) return BMD_ERROR_NULL_FILE;
	if (!doesFileExist(file->path)) return BMD_ERROR_FILE_NOT_FOUND;
	FILE* f;
	fopen_s(&f, file->path, "rt");
	//fseek(f, 0, SEEK_END);
	//ulong len = ftell(f);
	char* data = (char*) malloc(file->size);
	memset(data, 0, file->size);
	fread(data, 1, file->size - 1, f);
	fclose(f);
	file->contents = data;
	if (!file->contents) return BMD_ERROR_READ_FILE;
	return BMD_NO_ERROR;
}

int writeFile(const char* file, const char* data, const char* mode)
{
	FILE* f;
	fopen_s(&f, file, mode);
	fwrite(data, 1, strlen(data), f);
	fclose(f);
	return BMD_NO_ERROR;
}

int writeFile(file_t* file, const char* data, const char* mode)
{
	if (!file) return BMD_ERROR_NULL_FILE;
	if (!file->isFile) return BMD_ERROR_NOT_A_FILE;
	FILE* f;
	fopen_s(&f, file->path, mode);
	fwrite(data, 1, strlen(data), f);
	fseek(f, 0, SEEK_END);
	ulong len = ftell(f);
	fclose(f);
	file->size = len + 1;
	return BMD_NO_ERROR;
}

int traverse(const char* dirPath, fs_callback callback, void* userData)
{
	dir_t dir;
	int error = openDir(&dir, dirPath);
	checkError(error)

	while (dir.hasNext)
	{
		file_t file;
		error = loadFile(&dir, &file);
		checkError(error)

		if (file.isFile)
			callback(&file, userData);
		error = nextFile(&dir);
		checkError(error)
	}
	error = closeDir(&dir);
	checkError(error)
	return BMD_NO_ERROR;
}

int traverse_r(const char* dirPath, fs_callback callback, void* userData)
{
	dir_t dir;
	int error = openDir(&dir, dirPath);
	checkError(error)

	while (dir.hasNext)
	{
		file_t file;
		error = loadFile(&dir, &file);
		checkError(error)
		if (file.isDir && file.name[ 0 ] != '.')
		{
			char path[MAX_PATH_LENGTH];
			int size = copyStr_s(path, dirPath, MAX_PATH_LENGTH);
			if (size < 0)
			{
				logWarn("Failed to copy directory path string while traversing");
				return size; // will be BMD_ERROR_EXCEEDS_LENGTH
			}
			error = concatStr(path, "/");
			checkError(error)
			error = concatStr(path, file.name);
			checkError(error)
			error = traverse_r(path, callback, userData);
			checkError(error)
		}

		if (file.isFile)
			callback(&file, userData);
		error = nextFile(&dir);
		checkError(error)
	}
	error = closeDir(&dir);
	checkError(error)
	return BMD_NO_ERROR;
}

int getCreationTime(file_t* file, fs_time* time)
{
	if (!file) return BMD_ERROR_NULL_FILE;
	return getCreationTime(file->path, time);
}

int getLastModifiedTime(file_t* file, fs_time* time)
{
	if (!file) return BMD_ERROR_NULL_FILE;
	return getLastModifiedTime(file->path, time);
}

#ifdef OS_WINDOWS

int doesFileExist(const char* path)
{
	WIN32_FILE_ATTRIBUTE_DATA temp;
	return GetFileAttributesExA(path, GetFileExInfoStandard, &temp);
}

int loadFile(dir_t* dir, file_t* file)
{
			BMD_ASSERT(dir->handle != INVALID_HANDLE_VALUE);
	int n = 0;
	int error = BMD_NO_ERROR;
	char* dirPath = dir->path;
	char* filePath = file->path;
	n = copyStr_s(filePath, dirPath, MAX_PATH_LENGTH);
	if (n < 0) return n;
	error = concatStr(filePath, "/");
	if (error) return error;

	char* dirName = dir->fdata.cFileName;
	char* fileName = file->name;

	n = copyStr_s(fileName, dirName, MAX_FILENAME_LENGTH);
	if (n < 0) return n;

	error = concatStr(filePath, fileName);
	if (error) return error;

	file->size = ((size_t) dir->fdata.nFileSizeHigh * (MAXDWORD + 1)) + (size_t) dir->fdata.nFileSizeLow;
	getExt(file);
	file->isDir = (dir->fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
	file->isFile = (dir->fdata.dwFileAttributes & FILE_ATTRIBUTE_NORMAL) != 0 ||
				   !(dir->fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);

	return BMD_NO_ERROR;
}

int loadFileAndReadContents(dir_t* dir, file_t* file)
{
			BMD_ASSERT(dir->handle != INVALID_HANDLE_VALUE);
	int n = 0;
	int error = BMD_NO_ERROR;
	char* dirPath = dir->path;
	char* filePath = file->path;
	n = copyStr_s(filePath, dirPath, MAX_PATH_LENGTH);
	if (n < 0) return n;
	error = concatStr(filePath, "/");
	if (error) return error;

	char* dirName = dir->fdata.cFileName;
	char* fileName = file->name;

	n = copyStr_s(fileName, dirName, MAX_FILENAME_LENGTH);
	if (n < 0) return n;

	error = concatStr(filePath, fileName);
	if (error) return error;

	file->size = ((size_t) dir->fdata.nFileSizeHigh * (MAXDWORD + 1)) + (size_t) dir->fdata.nFileSizeLow;
	getExt(file);
	file->isDir = (dir->fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
	file->isFile = (dir->fdata.dwFileAttributes & FILE_ATTRIBUTE_NORMAL) != 0 ||
				   !(dir->fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
	if (file->isFile && !file->isDir)
		error = readFileContents(file);

	return error;
}

int openDir(dir_t* dir, const char* path)
{
	int n = 0;
	int error = BMD_NO_ERROR;
	n = copyStr_s(dir->path, path, MAX_PATH_LENGTH);
	if (n < 0) return n;
	error = concatStr(dir->path, "\\*");
	if (error) return error;

	dir->handle = FindFirstFileA(dir->path, &dir->fdata);
	dir->path[ n - 1 ] = 0;

	if (dir->handle == INVALID_HANDLE_VALUE)
	{
		if (BMD_DEBUGGING)
			fprintf(stderr, "Error: Could not open directory [%s] - %s", path, strerror(errno));
		// To be safe, lets mark the directory as closed
		closeDir(dir);
		//BMD_ASSERT(0);
		return BMD_ERROR_OPEN_DIR;
	}

	dir->hasNext = 1;
	return BMD_NO_ERROR;
}


int closeDir(dir_t* dir)
{
	dir->path[ 0 ] = 0;
	dir->hasNext = 0;
	if (dir->handle != INVALID_HANDLE_VALUE)
		FindClose(dir->handle);
	else return BMD_ERROR_CLOSE_DIR;
	return BMD_NO_ERROR;
}

int createDir(const char* path)
{
	int success = CreateDirectoryA(path, 0);
	if (success) return BMD_NO_ERROR;
	DWORD err = GetLastError();
	if (err == ERROR_PATH_NOT_FOUND)
		return BMD_ERROR_PATH_NOT_FOUND;
	else if (err != ERROR_ALREADY_EXISTS && !success)
		return BMD_ERROR_CREATE_DIR;
	return BMD_NO_ERROR;
}

int nextFile(dir_t* dir)
{
			BMD_ASSERT(dir->hasNext);

	if (!FindNextFileA(dir->handle, &dir->fdata))
	{
		dir->hasNext = 0;
		DWORD err = GetLastError();
		int retErr = err == ERROR_SUCCESS || err == ERROR_NO_MORE_FILES;
				BMD_ASSERT(retErr);
		return retErr ? BMD_NO_ERROR : BMD_ERROR_NEXT_FILE;
	}

	return BMD_NO_ERROR;
}

int getCreationTime(const char* path, fs_time* time)
{
	if (!doesFileExist(path)) return BMD_ERROR_FILE_NOT_FOUND;
	time->time = { 0 };
	WIN32_FILE_ATTRIBUTE_DATA info;
	if (GetFileAttributesExA(path, GetFileExInfoStandard, &info))
	{
		time->time = info.ftCreationTime;

		TIME_ZONE_INFORMATION tzi;
		int zone = GetTimeZoneInformation(&tzi);
		SYSTEMTIME utcTime;
		FileTimeToSystemTime(&(info.ftCreationTime), &utcTime);
		SYSTEMTIME local;
		SystemTimeToTzSpecificLocalTime(&tzi, &utcTime, &local);
		WCHAR* zoneName = nullptr;
		if (zone == TIME_ZONE_ID_STANDARD)
			zoneName = tzi.StandardName;
		else if (zone == TIME_ZONE_ID_DAYLIGHT)
			zoneName = tzi.DaylightName;
		// Going for format -> MM/dd/yyyy at hh:mm:ss
		// That's 22 characters, 23 if we include null terminating character
		//char* formatted = (char*) malloc(23 * sizeof(char));
		sprintf(time->time_str, "%02d/%02d/%04d at %02d:%02d:%02d %ls", local.wMonth, local.wDay, local.wYear,
				local.wHour, local.wMinute, local.wSecond, zoneName);
		//time->time_str = formatted;
		return BMD_NO_ERROR;
	}

	return BMD_ERROR_FILE_TIME;
}

int getLastModifiedTime(const char* path, fs_time* time)
{
	if (!doesFileExist(path)) return BMD_ERROR_FILE_NOT_FOUND;
	time->time = { 0 };
	WIN32_FILE_ATTRIBUTE_DATA info;
	if (GetFileAttributesExA(path, GetFileExInfoStandard, &info))
	{
		time->time = info.ftLastWriteTime;

		TIME_ZONE_INFORMATION tzi;
		int zone = GetTimeZoneInformation(&tzi);
		SYSTEMTIME utcTime;
		FileTimeToSystemTime(&(info.ftLastWriteTime), &utcTime);
		SYSTEMTIME local;
		SystemTimeToTzSpecificLocalTime(&tzi, &utcTime, &local);
		// Going for format -> MM/dd/yyyy at hh:mm:ss
		// That's 22 characters, 23 if we include null terminating character
		//char* formatted = (char*) malloc(30 * sizeof(char));
		WCHAR* zoneName = (WCHAR*) "";
		if (zone == TIME_ZONE_ID_STANDARD)
			zoneName = tzi.StandardName;
		else if (zone == TIME_ZONE_ID_DAYLIGHT)
			zoneName = tzi.DaylightName;

		sprintf(time->time_str, "%02d/%02d/%04d at %02d:%02d:%02d %ls", local.wMonth, local.wDay, local.wYear,
				local.wHour, local.wMinute, local.wSecond, zoneName);
		//time->time_str = formatted;
		return BMD_NO_ERROR;
	}

	return BMD_ERROR_FILE_TIME;
}

int compareTimes(fs_time* a, fs_time* b)
{
	return CompareFileTime(&a->time, &b->time);
}

#else

int doesFileExist(const char* path)
{
	return 0;
}

int loadFile(dir_t* dir, file_t* file)
{
	return BMD_ERROR_NOT_YET_IMPLEMENTED;
}

int openDir(dir_t* dir, const char* path)
{
	return BMD_ERROR_NOT_YET_IMPLEMENTED;
}

int closeDir(dir_t* dir)
{
	return BMD_ERROR_NOT_YET_IMPLEMENTED;
}

int createDir(const char* path)
{
	return BMD_ERROR_NOT_YET_IMPLEMENTED;
}

int nextFile(dir_t* dir)
{
	return BMD_ERROR_NOT_YET_IMPLEMENTED;
}

int getCreationTime(const char* path, fs_time* time)
{
	return BMD_ERROR_NOT_SUPPORTED_BY_PLATFORM;
}

int getLastModifiedTime(const char* path, fs_time* time)
{
	struct stat info;
	if(stat(path, &info)) return BMD_ERROR_FILE_TIME;
	time->time = info.st_mtime;
	//time->time_str = ctime(time->time);
}

int compareTimes(fs_time* a, fs_time* b)
{
	return BMD_ERROR_NOT_YET_IMPLEMENTED;
}

#endif // OS Check



