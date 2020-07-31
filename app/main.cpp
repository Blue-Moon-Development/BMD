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
	int* ints = indicesOf("this is a little monkey, let\'s give him lot\'s of love!", 'l');
	printf("Ls from the pointer: ");
	for(int i = 0; i < sizeof(*ints) + 1; i++)
	{
		printf("%i ", ints[i]);
	}

	int* ptr;
	int len = indicesOf("this is a little monkey, let\'s give him lot\'s of love!", 'l', ptr);
	printf("\nLs from the given length: ");
	for(int i = 0; i < len; i++)
	{
		printf("%i ", ptr[i]);
	}
}

int main(int argc, char** argv)
{
	test_substr();
	test_index_finder();
}