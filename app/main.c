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
#include <bmd/arrays.h>
#include <bmd/files.h>

void test_substr()
{
	// From start to end
	//TODO: Maybe scrap the idea of logging the file/line number, we have debugger for a reason
	char* sub = substrFrom("This is an example string", 7);
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
	float a[] = { 1, 2, 3 };
	int len = getLength_f(a);
	printf("Length is: %i\n", len);

	double b[] = { 5, 2, 45, 5, 2 };
	len = getLength_d(b);
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
	concatStr_to(world, " and hello! to you too!", 7);
	printf("world became: %s\n", world);

	char hi[20] = { "Really?" };
	concatStr_r(hi, " Yes really you monkey brain", 7, 10);
	printf("hi became: %s\n", hi);

	char* maybe = "hopefully";
	const char* add = " this works";
	int e = concatStrDynamic(&maybe, add);
	printf("Error is %i  maybe is: %s\n", e, maybe);
	if (!e && maybe)
		free(maybe);

	char* one = "one";
	int e2 = concatStrDynamic_r(&one, " two three four!", 4, 9);
	printf("one: %s\n", one);
	if (!e2 && one)
		free(one);

	char* abc = "abc";
	int e3 = concatStrDynamic_to(&abc, " easy as 1 2 3!", 5);
	printf("abc: %s\n", abc);
	if (!e3 && abc)
		free(abc);
}

void test_copy()
{
	char staticStr[100] = { "this will get overwritten" };
	const char* newStaticStr = "new text!";
	copyStr_s(staticStr, newStaticStr, 100);
	printf("staticStr became: %s\n", staticStr);

	char* dynStr;
	copyStrDynamic_s(&dynStr, "Set it to this text", 100);
	printf("dynStr became: %s\n", dynStr);

	char stStr[100];
	copyStr(stStr, "Wow im cool!");
	printf("stStr became: %s\n", stStr);

	char* rewriteThis = "im gonna be replaced!";
	// (c++ 11 conversion from string literal to char* was removed, only still compiles for C compatibility)
	// Maybe I can disable that warning?
	copyStrDynamic(&rewriteThis, "new dynamic text");
	printf("rewriteThis became: %s\n", rewriteThis);

	// Dynamic copies must be freed or else we get memory leaks!
	// Would be cool to implement a C++ shared_ptr that works with raw C pointers, though I doubt that's possible
	if (dynStr)
		free(dynStr);
	if (rewriteThis)
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
	if (!dp || !p) return;
	*dp = (char*) p;
}

void test_files()
{
	file_t file;
	int error = loadFile("./test/fname.txt", &file);
	if (!error)
		printf("File path: %s\nFile name: %s\nFile ext: %s\nFile size: %zu\n",
			   file.path, file.name, file.ext, file.size);
	else printf("Error: %i\n", error);

	error = readFileContents(&file);
	if (!error)
		printf("File contents:\n%s\n", file.contents);
	else printf("error: %i\n", error);

	fs_time time;
	error = getCreationTime(file.path, &time);
	if (!error)
		printf("File was created at: %s\n", time.time_str);

	error = getLastModifiedTime(file.path, &time);
	if (!error)
		printf("File was last modified at: %s\n", time.time_str);


	printf("Ext is %s\n", getExt(&file));
	printf("Ext is .txt? %i\n", doesFileHaveExt(&file, ".txt"));
	printf("Ext is .dat? %i\n", doesFileHaveExt(&file, ".dat"));

	char* fileContents;
	error = readFile("./test/fname.txt", &fileContents);
	if (!error)
		printf("Contents of fname.txt:\n%s\n", fileContents);

	if (fileContents) free(fileContents);
	if (file.contents) free(file.contents);

	file_t load_read;
	error = loadFileAndReadContents("./CmakeFiles/CMakeDirectoryInformation.cmake", &load_read);
	if (!error)
		printf("File contents:\n%s\n", load_read.contents);

	fs_time loadreadTime;
	error = getCreationTimeOfFile(&load_read, &loadreadTime);
	if (!error)
		printf("File created: %s\n", loadreadTime.time_str);

	int check = compareTimes(&loadreadTime, &time);
	if (check == -1)
		printf("%s comes before %s\n", loadreadTime.time_str, time.time_str);
	else if (check == 1)
		printf("%s comes after %s\n", loadreadTime.time_str, time.time_str);
	else if (check == 0)
		printf("%s is same time as %s\n", loadreadTime.time_str, time.time_str);

	file_t writeToHere;
	//error = writeFile("./test.log", "This is just to start things", "wt");
	//if(!error)
	loadFileAndReadContents("./test.log", &writeToHere);
	char* fileContentsW;
	readFile("./test.log", &fileContentsW);
	printf("File contents of variable: %s\nAnd when reading file: %s\n", writeToHere.contents, fileContentsW);
	error = writeToFile(&writeToHere, "\nThis is some more testing", "at");
	if (!error)
	{
		printf("File contents of variable: %s\nAnd when reading file: %s\n", writeToHere.contents,
			   fileContentsW);
		if (fileContentsW) free(fileContentsW);
	}

	if (writeToHere.contents) free(writeToHere.contents);
	if (load_read.contents) free(load_read.contents);
	//file_t file;
	//dir_t dir;
	//openDir(&dir, "./test");
	//loadFile(&dir, &file);
	//printf("File path: %s\nFile name: %s\nFile ext: %s\nFile size: %zu\n",
	//	   file.path, file.name, file.ext, file.size);
	//closeDir(&dir);
}


#include <bmd/timer.h>
#include <bmd/logger.h>
#define BMD_PROFILE 0
#include <bmd/profiler.h>

int main(int argc, char** argv)
{

	//int* p = nullptr;
	//formatStr_s("format", 32, 0.27453f, 43545L, 2.01, 'c', (int)'c', p);
	//char buf[100];
	//getCurrentTime(buf);
	//printf("Time is %s\n", buf);

	initLog("./info.log", LOG_MODE_ARCHIVE, 7);
	PROFILER_START("Log profile");
	logInfo("This is just a test");
	PROFILER_END;
	logInfo("This is just a test 1");
	logTrace("This is just a test 2");
	logTrace("This is just a test 3");
	logError("This is just a test 4");
	logDebug("This is just a test 5");
	logInfo("This is just a test 6");
	logWarn("This is just a test 7");
	logInfo("This is just a test 8");
	logDebug("This is just a test 9");
	logError("Another error!");
	logInfo("This is just a test 10");
	logInfo("This is just a test 11");
	logError(getErrorString(-16));

	//test_substr();
	//test_index_finder();
	//test_concat();
	//test_copy();
	//
	//test_arr_length();
	//test_files();
	//int t[] = {
	//		1, 2, 3,
	//		4, 5, 6
	//};
	//test_arr_as_param(t);


}