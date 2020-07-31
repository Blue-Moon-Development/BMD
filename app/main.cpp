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
 * File Name: main.cpp
 * Date File Created: 7/30/2020 at 11:02 PM
 * Author: Matt
 */

#include <bmd/strutil.h>
#include <bmd/errors.h>
#include <bmd/types.h>
#include <stdio.h>
#include <limits>
#include <iostream>

void test_substr()
{
	// From start to end
	//TODO: Maybe scrap the idea of logging the file/line number, we have debugger for a reason
	char* sub = substr("This is an example string", 7);
	printf("Sub str is: %s\n", sub);
	sub = substr("How about this sample text", 4, 11);
	printf("Sub str is: %s\n", sub);
}

void test_index_finder()
{
	int first_L = indexOf("this is a little monkey, let\'s give him lot\'s of love!", 'l');
	printf("First L at: %i\n", first_L);
	int last_L = lastIndexOf("this is a little monkey, let\'s give him lot\'s of love!", 'l');
	printf("Last L at: %i\n", last_L);

	int* ptr;
	int len = indicesOf("this is a little monkey, let\'s give him lot\'s of love!", 'l', ptr);
	printf("\nLs from the given length: ");
	for (int i = 0; i < len; i++)
	{
		printf("%i ", ptr[ i ]);
	}
	printf("\n");
}

int getSize(int* arr)
{
	if (!arr) return 0;
	int n = 0;
	while (*arr != -858993460 && *arr != -33686019) //second check for new int[size], needs more testing
	{
		printf("Int at index %i is %i\n", n, *arr);
		arr++;
		n++;
	}

	return n;
}

int getSize(unsigned int* arr)
{
	if (!arr) return 0;
	int n = 0;
	while (*arr != -858993460)
	{
		printf("Int at index %i is %i\n", n, *arr);
		arr++;
		n++;
	}

	return n;
}

int getSize(float* arr)
{
	if (!arr) return 0;
	int n = 0;
	while (*arr != -107374176.0f)
	{
		printf("Float at index %i is %f\n", n, *arr);
		arr++;
		n++;
	}

	return n;
}

int getSize(double* arr)
{
	if (!arr) return 0;
	int n = 0;
	while (*arr != -92559631349317830736831783200707727132248687965119994463780864.0)
	{
		printf("Double at index %i is %f\n", n, *arr);
		arr++;
		n++;
	}

	return n;
}

int getSize(short* arr)
{
	if (!arr) return 0;
	int n = 0;
	while (*arr != -13108)
	{
		printf("Short at index %i is %i\n", n, *arr);
		arr++;
		n++;
	}

	return n;
}

int getSize(char* arr)
{
	if (!arr) return 0;
	int n = 0;
	while (*arr)
	{
		printf("Char at index %i is %i (%c)\n", n, *arr, *arr);
		arr++;
		n++;
	}

	return n;
}

int getSize(const char* arr)
{
	if (!arr) return 0;
	int n = 0;
	while (*arr)
	{
		printf("Char at index %i is %i (%c)\n", n, *arr, *arr);
		arr++;
		n++;
	}

	return n;
}

int getSize(long double* arr)
{

	if (!arr) return 0;
	int n = 0;
	while (*arr != -92559631349317830736831783200707727132248687965119994463780864.0)
	{
		printf("Char at index %i is %Lf\n", n, *arr);
		arr++;
		n++;
	}

	return n;
}

int getSize(long long* arr)
{
	if (!arr) return 0;
	int n = 0;
	while (*arr != -3689348814741910324)
	{
		printf("Char at index %i is %lli\n", n, *arr);
		arr++;
		n++;
	}

	return n;
}

int getSize(long* arr)
{
	if (!arr) return 0;
	int n = 0;
	while (*arr != -858993460)
	{
		printf("Char at index %i is %li\n", n, *arr);
		arr++;
		n++;
	}

	return n;
}

void test_arr_length()
{
	int min = std::numeric_limits<int>::min();
	printf("Min value for an int is %i\n", min);
	// size 1 -> 19
	// size 2 -> 18
	// size 3, 4, 5, 6 -> 26
	// size 7, 8, 9, 10 -> 30
	// size 11, 12, 13, 14 -> 34
	int test[] = { 1, 2, 3, 4, 5, 6, 7, 0, 9 };
	int l = sizeof(test) / sizeof(int);

	int len = getSize(test);
	printf("Size of int is %zu\n", sizeof(int));
	printf("Length of test[] is %i\n", len);

	//int diff = len - l;
	//printf("Difference is %i\n", diff);

	float testf[] = { 1.2f, 0.1f, 2.3f };
	len = getSize(testf);
	printf("Length of testf[] is %i\n", len);


	double testd[] = { 1.2, 3, 4.5, 5.7 };
	len = getSize(testd);
	printf("Length of testd[] is %i\n", len);

	short tests[] = { 1, 2, 3 };
	len = getSize(tests);
	printf("Length of tests[] is %i\n", len);

	char testc[] = { "12abc 6789" };
	len = getSize(testc);
	printf("Length of testc[] is %i\n", len);
	printf("strlen returns %zu\n", strlen(testc));

	char* dyntest = "12345";
	len = getSize(dyntest);
	printf("Length of dyntest is %i\n", len);

	long testl[] = { 1, 2, 343545L };
	len = getSize(testl);
	printf("Length of testl[] is %i\n", len);

	long long testll[] = { 1, 2, 3, 4 };
	len = getSize(testll);
	printf("Length of testll[] is %i\n", len);

	long double testld[] = { 1.4, 4, 5, 4, 5, 7, 6.7 };
	len = getSize(testld);
	printf("Length of testld[] is %i\n", len);

	unsigned int testui[] { 1, 2, 3 };
	len = getSize(testui);
	printf("Length of testui[] is %i\n", len);

	int* dyntesti = new int[3];
	len = getSize(dyntesti);
	printf("Length of dyntesti is %i\n", len);

	dyntesti = new int[5];
	dyntesti[ 0 ] = 1;
	dyntesti[ 1 ] = 2;
	dyntesti[ 3 ] = 4;
	len = getSize(dyntesti);
	printf("Length of dyntesti is %i\n", len);

	delete[] dyntesti;

	const char* str = "123456";
	len = getSize(str);
	printf("Length of str is %i\n", len);
}

void test_concat()
{
	// TODO: Could have sworn these worked for dynamic strings earlier, oh well, will have to do that later
	//char* hello = (char*)"hello";
	char hello[20] = { "hello" };
	concatStr(hello, " world!");
	printf("hello became: %s\n", hello);

	char world[20] = { "world" };
	concatStr(world, " and hello! to you too!", 7);
	printf("world became: %s\n", world);

	char hi[20] = { "Really?" };
	concatStr(hi, " Yes really you monkey brain", 7, 10);
	printf("hi became: %s\n", hi);

	const char* maybe = "hopefully";
	//concatStr(maybe, " this works?");
}

void test_copy()
{
	char staticStr[100] = { "this will get overwritten" };
	copyStr_s(staticStr, "new text!", 100);
	printf("staticStr became: %s\n", staticStr);

	char* dynStr;
	copyStrDynamic_s(dynStr, "Set it to this text", 100);
	printf("dynStr became: %s\n", dynStr);

	char stStr[100] = { };
	copyStr(stStr, "Wow im cool!");
	printf("stStr became: %s\n", stStr);

	char* rewriteThis = (char*) "im gonna be replaced!"; // no cast works fine, but the warning was annoying me
	// (c++ 11 conversion from string literal to char* was removed, only still compiles for C compatibility)
	// Maybe I can disable that warning?
	copyStrDynamic(rewriteThis, "new dynamic text");
	printf("rewriteThis became: %s\n", rewriteThis);

}

void test_arr_as_param(int* arr)
{
	printf("Param arr length is: %i\n", getSize(arr));
}


int main(int argc, char** argv)
{
	test_substr();
	test_index_finder();
	test_concat();
	test_copy();
	test_arr_length();
	int t[] = {
			1, 2, 3,
			4, 5, 6
	};
	test_arr_as_param(t);

}