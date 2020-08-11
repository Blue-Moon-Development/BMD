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



int getLength_c(const char* arr)
{
	if (!arr) return -1;
	int n = 0;

	while (*arr)
	{
		arr++;
		n++;
	}

	return n;
}

int getLength_s(const short* arr)
{
	if (!arr) return -1;
	int n = 0;

	while (*arr != NULL_TERMINATING_SHORT && *arr != NULL_TERMINATING_SHORT_NEW)
	{
		arr++;
		n++;
	}

	return n;
}

int getLength_i(const int* arr)
{
	if (!arr) return -1;
	int n = 0;

	while (*arr != NULL_TERMINATING_INT && *arr != NULL_TERMINATING_INT_NEW)
	{
		arr++;
		n++;
	}

	return n;
}

int getLength_l(const long* arr)
{
	if (!arr) return -1;
	int n = 0;

	while (*arr != NULL_TERMINATING_LONG && *arr != NULL_TERMINATING_LONG_NEW)
	{
		arr++;
		n++;
	}

	return n;
}

int getLength_ll(const long long* arr)
{
	if (!arr) return -1;
	int n = 0;

	while (*arr != NULL_TERMINATING_LONG_LONG && *arr != NULL_TERMINATING_LONG_LONG_NEW)
	{
		arr++;
		n++;
	}

	return n;
}

int getLength_uc(const uchar* arr)
{
	if (!arr) return -1;
	int n = 0;

	while (*arr)
	{
		arr++;
		n++;
	}

	return n;
}

int getLength_us(const ushort* arr)
{
	if (!arr) return -1;
	int n = 0;

	while (*arr > 0)
	{
		arr++;
		n++;
	}

	return n;
}

int getLength_ui(const uint* arr)
{
	if (!arr) return -1;
	int n = 0;

	while (*arr > 0)
	{
		arr++;
		n++;
	}

	return n;
}

int getLength_ul(const ulong* arr)
{
	if (!arr) return -1;
	int n = 0;

	while (*arr > 0)
	{
		arr++;
		n++;
	}

	return n;
}

int getLength_ull(const ulonglong* arr)
{
	if (!arr) return -1;
	int n = 0;

	while (*arr > 0)
	{
		arr++;
		n++;
	}

	return n;
}

int getLength_f(const flt32* arr)
{
	if (!arr) return -1;
	int n = 0;

	while (*arr != NULL_TERMINATING_FLOAT && *arr != NULL_TERMINATING_FLOAT_NEW && !isnan(*arr))
	{
		arr++;
		n++;
	}

	return n;
}

int getLength_d(const flt64* arr)
{
	if (!arr) return -1;
	int n = 0;

	while (*arr != NULL_TERMINATING_DOUBLE && !isnan(*arr))
	{
		arr++;
		n++;
	}

	return n;
}

int getLength_ld(const flt96* arr)
{
	if (!arr) return -1;
	int n = 0;

	while (*arr != NULL_TERMINATING_LONG_DOUBLE && !isnan(*arr))
	{
		arr++;
		n++;
	}

	return n;
}