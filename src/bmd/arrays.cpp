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
 * File Name: arrays.cpp
 * Date File Created: 7/31/2020 at 11:39 PM
 * Author: Matt
 */

#include "bmd/arrays.h"

#include <math.h>

int char_callback(const char* arr);
int short_callback(const short* arr);
int int_callback(const int* arr);
int long_callback(const long* arr);
int longlong_callback(const long long* arr);

int uchar_callback(const uchar* arr);
int ushort_callback(const ushort* arr);
int uint_callback(const uint* arr);
int ulong_callback(const ulong* arr);
int ulonglong_callback(const ulonglong* arr);

int float_callback(const flt32* arr);
int double_callback(const flt64* arr);
int longdouble_callback(const flt96* arr);

template<typename T>
int getLength(const T* arr, length_callback<T> lcb)
{
	if (!arr) return -1;
	int n = 0;

	while (lcb(arr))
	{
		if(isnan((long double) *arr)) return -1;
		arr++;
		n++;
	}

	return n;
}

int getLength(const char* arr)
{
	if (!arr) return -1;
	return getLength<char>(arr, char_callback);
}

int getLength(const short* arr)
{
	if (!arr) return -1;
	return getLength<short>(arr, short_callback);
}

int getLength(const int* arr)
{
	//if (!arr) return -1;
	return getLength<int>(arr, int_callback);
}

int getLength(const long* arr)
{
	if (!arr) return -1;
	return getLength<long>(arr, long_callback);
}

int getLength(const long long* arr)
{
	if (!arr) return -1;
	return getLength<long long>(arr, longlong_callback);
}

int getLength(const uchar* arr)
{
	if (!arr) return -1;
	return getLength<uchar>(arr, uchar_callback);
}

int getLength(const ushort* arr)
{
	if (!arr) return -1;
	return getLength<ushort>(arr, ushort_callback);
}

int getLength(const uint* arr)
{
	//if (!arr) return -1;
	return getLength<uint>(arr, uint_callback);
}

int getLength(const ulong* arr)
{
	if (!arr) return -1;
	return getLength<ulong>(arr, ulong_callback);
}

int getLength(const ulonglong* arr)
{
	if (!arr) return -1;
	return getLength<ulonglong>(arr, ulonglong_callback);
}

int getLength(const flt32* arr)
{
	if (!arr) return -1;
	return getLength<flt32>(arr, float_callback);
}

int getLength(const flt64* arr)
{
	if (!arr) return -1;
	return getLength<flt64>(arr, double_callback);
}

int getLength(const flt96* arr)
{
	if (!arr) return -1;
	return getLength<flt96>(arr, longdouble_callback);
}


int char_callback(const char* arr)
{
	return !*arr;
}

int short_callback(const short* arr)
{
	return *arr != NULL_TERMINATING_SHORT && *arr != NULL_TERMINATING_SHORT_NEW;
}

int int_callback(const int* arr)
{
	return *arr != NULL_TERMINATING_INT && *arr != NULL_TERMINATING_INT_NEW;
}

int long_callback(const long* arr)
{
	return *arr != NULL_TERMINATING_LONG && *arr != NULL_TERMINATING_LONG_NEW;
}

int longlong_callback(const long long* arr)
{
	return *arr != NULL_TERMINATING_LONG_LONG && *arr != NULL_TERMINATING_LONG_LONG_NEW;
}

int uchar_callback(const uchar* arr)
{
	return !*arr;
}

int ushort_callback(const ushort* arr)
{
	return *arr != NULL_TERMINATING_SHORT && *arr != NULL_TERMINATING_SHORT_NEW;
}

int uint_callback(const uint* arr)
{
	return *arr != NULL_TERMINATING_INT && *arr != NULL_TERMINATING_INT_NEW;
}

int ulong_callback(const ulong* arr)
{
	return *arr != NULL_TERMINATING_LONG && *arr != NULL_TERMINATING_LONG_NEW;
}

int ulonglong_callback(const ulonglong* arr)
{
	return *arr != NULL_TERMINATING_LONG_LONG && *arr != NULL_TERMINATING_LONG_LONG_NEW;
}

int float_callback(const flt32* arr)
{
	return *arr != NULL_TERMINATING_FLOAT && *arr != NULL_TERMINATING_FLOAT_NEW;
}

int double_callback(const flt64* arr)
{
	return *arr != NULL_TERMINATING_DOUBLE;
}

int longdouble_callback(const flt96* arr)
{
	return *arr != NULL_TERMINATING_LONG_DOUBLE;
}