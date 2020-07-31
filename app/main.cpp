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
#include <stdio.h>

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
	for(int i = 0; i < len; i++)
	{
		printf("%i ", ptr[i]);
	}
	printf("\n");
}


void test_concat()
{
	// TODO: Could have sworn these worked for dynamic strings earlier, oh well, will have to do that later
	//char* hello = (char*)"hello";
	char hello[20] = {"hello"};
	concatStr(hello, " world!");
	printf("hello became: %s\n", hello);

	char world[20] = {"world"};
	concatStr(world, " and hello! to you too!", 7);
	printf("world became: %s\n", world);

	char hi[20] = {"Really?"};
	concatStr(hi, " Yes really you monkey brain", 7, 10);
	printf("hi became: %s\n", hi);
}

void test_copy()
{
	char staticStr[100] = {"this will get overwritten"};
	copyStr_s(staticStr, "new text!", 100);
	printf("staticStr became: %s\n", staticStr);

	char* dynStr;
	copyStrDynamic_s(dynStr, "Set it to this text", 100);
	printf("dynStr became: %s\n", dynStr);

	char stStr[100] = {};
	copyStr(stStr, "Wow im cool!");
	printf("stStr became: %s\n", stStr);

	char* rewriteThis = (char*)"im gonna be replaced!"; // no cast works fine, but the warning was annoying me
	// (c++ 11 conversion from string literal to char* was removed, only still compiles for C compatibility)
	// Maybe I can disable that warning?
	copyStrDynamic(rewriteThis, "new dynamic text");
	printf("rewriteThis became: %s\n", rewriteThis);

}

int main(int argc, char** argv)
{
	test_substr();
	test_index_finder();
	test_concat();
	test_copy();
}