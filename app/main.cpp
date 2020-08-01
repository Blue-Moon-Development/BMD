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
#include <bmd/arrays.h>

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
	int len = indicesOf("this is a little monkey, let\'s give him lot\'s of love!", 'l', &ptr);
	printf("\nLs from the given length: ");
	for (int i = 0; i < len; i++)
	{
		printf("%i ", ptr[ i ]);
	}
	printf("\n");
}


void test_arr_length()
{
	float a[] = {1, 2, 3};
	int len = getLength(a);
	printf("Length is: %i\n", len);

	double b[] = {5, 2, 45, 5, 2};
	len = getLength(b);
	printf("Length is: %i\n", len);
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

	char* maybe = "hopefully";
	const char* add = " this works";
	int e = concatStrDynamic(&maybe, add);
	printf("Error is %i  maybe is: %s\n", e, maybe);
	if(!e && maybe)
		free(maybe);

	char* one = "one";
	int e2 = concatStrDynamic(&one, " two three four!", 4, 9);
	printf("one: %s\n", one);
	if(!e2 && one)
		free(one);

	char* abc  = "abc";
	int e3 = concatStrDynamic(&abc, " easy as 1 2 3!", 5);
	printf("abc: %s\n", abc);
	if(!e3 && abc)
		free(abc);
}

void test_copy()
{
	char staticStr[100] = { "this will get overwritten" };
	const char* newStaticStr = "new text!";
	copyStr_s(staticStr, newStaticStr, 100);
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

	// Dynamic copies must be freed or else we get memory leaks!
	// Would be cool to implement a C++ shared_ptr that works with raw C pointers, though I doubt that's possible
	if(dynStr)
		free(dynStr);
	if(rewriteThis)
		free(rewriteThis);
}

void test_arr_as_param(int* arr)
{
	//printf("Param arr length is: %i\n", getSize(arr));
}

// this works, and I believe would work in normal C as well (as C doesn't support passing by ref I believe)
// Needs testing, but could replace at least the copyStrDynamic functions and could just be copyStr(&dest, src)?
// Would be much safer than using the current dynamic system with malloc
// Especially since with the current dynamic malloc system, a string passed by reference is still required
void test_ptr_ref(char** dp, const char* p)
{
	if(!dp || !p) return;
	*dp = (char*)p;
}


int main(int argc, char** argv)
{


	//test_substr();
	//test_index_finder();
	//test_concat();
	//test_copy();
	test_arr_length();


	//int t[] = {
	//		1, 2, 3,
	//		4, 5, 6
	//};
	//test_arr_as_param(t);

}