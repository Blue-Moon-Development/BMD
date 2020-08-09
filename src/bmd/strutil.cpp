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
 * File Name: strutil.cpp
 * Date File Created: 7/30/2020 at 12:38 AM
 * Author: Matt
 */


#include "bmd/strutil.h"
#include "bmd/types.h"
#include "bmd/errors.h"
#include "bmd/common.h"

#include <string.h>
#include <stdlib.h>

//#include <setjmp.h>
//#include <signal.h>
//
//jmp_buf jump;
//
//void segv(int sig)
//{
//	longjmp(jump, 1);
//}
//
//int memcheck(void* x)
//{
//	volatile char c;
//	int illegal = 0;
//	signal(SIGSEGV, segv);
//	if(!setjmp(jump))
//		c = *(char*) (x);
//	else illegal = 1;
//	signal(SIGSEGV, SIG_DFL);
//	return illegal;
//}

int copyStr_s(char* dest, const char* src, int max)
{
	int size = 0;
	int character;
	const char* cpySrc = src;
	do
	{
		if (size >= max)
		{
			if (BMD_DEBUGGING)
				fprintf(stderr, "Error: String \"%s\" exceeds max length allowed (%i)\n",
						cpySrc, max);
					BMD_ASSERT(0);
			return BMD_ERROR_EXCEEDS_LENGTH;
		}
		character = *src++;
		//if(memcheck(dest))
		//{
		//	printf("Illegal pointer!\n");
		//	return -45435;
		//}
		dest[ size ] = character;
		size++;
	} while (character);

	return size;
}

int copyStr(char* dest, const char* src)
{
	int size = 0;
	int character;
	do
	{
		character = *src++;
		dest[ size ] = character;
		size++;
	} while (character);

	return size;
}

int copyStrDynamic_s(char*& dest, const char* src, int max)
{
	int bufferSize = sizeof(char) + strlen(src);
	char* buffer = (char*) malloc(bufferSize);
	if (!buffer) return BMD_ERROR_INVALID_MEMORY_ALLOCATION;
	int size = copyStr_s(buffer, src, max);
	dest = buffer;
	return size;
}

int copyStrDynamic(char*& dest, const char* src)
{
	int bufferSize = sizeof(char) + strlen(src);
	char* buffer = (char*) malloc(bufferSize);
	if (!buffer) return BMD_ERROR_INVALID_MEMORY_ALLOCATION;
	int size = copyStr(buffer, src);
	dest = buffer;
	return size;
}

int concatStr(char* orig, const char* add)
{
	if (!orig) return BMD_ERROR_NULL_STRING;
	if (!add) return BMD_ERROR_NULL_STRING;
	while (*orig)
		orig++;

	while (*add)
	{
		*orig = *add;
		add++;
		orig++;
	}

	*orig = NULL_TERM;
	return BMD_NO_ERROR;
}

int concatStr(char* orig, const char* add, int start, int stop)
{
	if (!orig) return BMD_ERROR_NULL_STRING;
	if (!add) return BMD_ERROR_NULL_STRING;
	while (*orig)
		orig++;
	int i = 0;
	while (*add)
	{
		if (i <= start)
		{
			add++;
			i++;
			continue;
		}
		*orig = *add;
		add++;
		orig++;
		i++;
		if (i > stop) break;
	}

	*orig = NULL_TERM;
	return BMD_NO_ERROR;
}

int concatStr(char* orig, const char* add, int stop)
{
	return concatStr(orig, add, -1, stop);
}

int concatStrDynamic(char** orig, const char* add)
{
	if (!orig) return BMD_ERROR_NULL_STRING;
	if (!add) return BMD_ERROR_NULL_STRING;
	int bufferSize = NULL_TERM_SIZE + strlen(*orig) + strlen(add);
	char* buffer = (char*) malloc(bufferSize);
	if (!buffer) return BMD_ERROR_INVALID_MEMORY_ALLOCATION;
	int error = BMD_NO_ERROR;
	if (strlen(*orig) > 0)
		copyStr(buffer, *orig);
	error = concatStr(buffer, add);
	if (!error) *orig = buffer;
	return error;
}


int concatStrDynamic(char** orig, const char* add, int start, int stop)
{
	if (!orig) return BMD_ERROR_NULL_STRING;
	if (!add) return BMD_ERROR_NULL_STRING;
	int bufferSize = NULL_TERM_SIZE + strlen(*orig) + strlen(add);
	char* buffer = (char*) malloc(bufferSize);
	if (!buffer) return BMD_ERROR_INVALID_MEMORY_ALLOCATION;
	int error = BMD_NO_ERROR;
	if (strlen(*orig) > 0)
		copyStr(buffer, *orig);
	error = concatStr(buffer, add, start, stop);
	if (!error) *orig = buffer;
	return error;
}


int concatStrDynamic(char** orig, const char* add, int stop)
{
	if (!orig) return BMD_ERROR_NULL_STRING;
	if (!add) return BMD_ERROR_NULL_STRING;
	int bufferSize = NULL_TERM_SIZE + strlen(*orig) + strlen(add);
	char* buffer = (char*) malloc(bufferSize);
	if (!buffer) return BMD_ERROR_INVALID_MEMORY_ALLOCATION;
	int error = BMD_NO_ERROR;
	if (strlen(*orig) > 0)
		copyStr(buffer, *orig);
	error = concatStr(buffer, add, stop);
	if (!error) *orig = buffer;
	return error;
}

char* substr(const char* str, int start, int stop)
{
	if (!str)
	{
		if (BMD_DEBUGGING)
			fprintf(stderr, "Error: Tried to get substring from a null string\n");
		return NULL;
	}
	int length = strlen(str);
	if (start < 0 || stop > length || start >= length || stop <= 0)
	{
		if (BMD_DEBUGGING)
			fprintf(stderr,
					"Error: Index out of bounds when trying to get a substring\n"
					"Ensure start >= 0 and stop < str length (%i). Given start: %i, stop: %i\n",
					length, start, stop);
		return NULL;
	}

	char* ptr = (char*) malloc(stop - start + sizeof(char)); // + char size to account for \0
	int c;
	for (c = 0; c < (stop - start); c++)
	{
		*(ptr + c) = *(str + start);
		str++;
	}
	*(ptr + c) = NULL_TERM;
	return ptr;
}

char* substr(const char* str, int start)
{
	if (!str)
	{
		if (BMD_DEBUGGING)
			fprintf(stderr, "Error: Attempted to capture a substring from a null string\n");
		return NULL;
	}

	return substr(str, start, strlen(str));
}

int indexOf(const char* str, char c)
{
	const char* ptr = strchr(str, c);
	int ret = (int) (ptr - str);
	if (ret == -1) return BMD_ERROR_CHAR_NOT_IN_STRING;
	return ret;
}

int lastIndexOf(const char* str, char c)
{
	const char* ptr = strrchr(str, c);
	int ret = (int) (ptr - str);
	if (ret == -1) return BMD_ERROR_CHAR_NOT_IN_STRING;
	return ret;
}


int indicesOf(const char* str, char c, int** indices)
{
	if (!str) return BMD_ERROR_NULL_STRING;
	int n = 0;
	int* ret = (int*) malloc(strlen(str) * sizeof(int));
	if (!ret) return BMD_ERROR_INVALID_MEMORY_ALLOCATION;
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[ i ] == c)
		{
			ret[ n ] = i;
			n++;
		}
	}
	*indices = ret;
	return n;
}



//#endif