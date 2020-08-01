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
#include "bmd/common.h"

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

template<typename T>
int getLength(const T* arr, length_callback<T> lcb)
{
	if (!arr) return -1;
	int n = 0;
	while (lcb(arr))
	{
		// for 'new double[]' and 'new long double[]' the "null terminating value" is 0,
		// obviously a very common value so we can't do that
		// we can include maths.h and do nan((char*)*arr) but not sure every compiler has that function for C++
		// At least according to my research, people were saying it wasn't implemented for C++ 11, though it seems to be
		// for vc++. Will have to test it later

		// If we reach an invalid number, the null terminating value probably wasn't found
		// and we've gone way beyond the length of the array, so return -1
		if(nan((char*)arr)) return -1;
		arr++;
		n++;
	}

	return n;
}

int getLength(const char* arr)
{
	if(!arr) return -1;
	return getLength<char>(arr, char_callback);
}

int getLength(const short* arr)
{
	if(!arr) return -1;
	return getLength<short>(arr, short_callback);
}

int getLength(const int* arr)
{
	if(!arr) return -1;

	return getLength<int>(arr, int_callback);
}

int getLength(const long* arr)
{

}
int getLength(const long long* arr)
{

}

int getLength(const uchar* arr)
{

}
int getLength(const ushort* arr)
{

}
int getLength(const uint* arr)
{

}
int getLength(const ulong* arr)
{

}
int getLength(const ulonglong* arr)
{

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

}

int ushort_callback(const ushort* arr)
{

}

int uint_callback(const uint* arr)
{

}

int ulong_callback(const ulong* arr)
{

}
int ulonglong_callback(const ulonglong* arr)
{

}