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
 * File Name: strutil.h
 * Date File Created: 7/30/2020 at 12:37 AM
 * Author: Matt
 */

#ifndef BMD_STRUTIL_H
#define BMD_STRUTIL_H

/**
* Overwrites the data in the destination string with the data from the src string
* <p>
* This is safe only in the sense that it will not copy past the given max, but due to dynamic allocation being used,
* when your code is done with the copied string (dest), be sure to call free(dest)!
* </p>
* @param dest The string to overwrite. Must be a fixed string, not dynamic.
* @param src The source string to copy to the destination
* @param max The maximum allowed length to copy for use cases where this can effect safety
* @return The size of the new destination string
*/
#define copyStr_s(dest, src, max) copyStr_safe_(dest, src, max, __FILE__, __LINE__)


/**
* Overwrites the data in the destination string with the data from the src string
* @param dest The string to overwrite
* @param src The source string to copy to the destination
* @param max The maximum allowed length to copy for use cases where this can effect safety
* @return The size of the new destination string or -13 if the src is longer than the given max
*/
#define copyStrDynamic_s(dest, src, max) _copyStrDynamic_safe_(dest, src, max, __FILE__, __LINE__)

/**
* Captures a sub string contained within str ranging from [start - (stop - 1)]
* @param str The string containing the desired sub string
* @param start The beginning index of the sub string, inclusive
* @param stop The ending index of the sub string, exclusive
* @return The substring, or NULL if either index were out of bounds
*/
#define substr(str, start, stop) substr_(str, start, stop, __FILE__, __LINE__)

/**
* Captures a sub string contained within str starting from the given start index. Use substr macro
* @param str The string containing the desired sub string
* @param start The beginning index of the sub string, inclusive
* @return The substring, or NULL if either index were out of bounds
*/
#define substrFrom(str, start) substr_(str, start, __FILE__, __LINE__)

/**
* Overwrites the data in the destination string with the data from the src string. The copyStr_s macro should be used.
* @param dest The string to overwrite. Must be a fixed string, not dynamic.
* @param src The source string to copy to the destination
* @param max The maximum allowed length to copy for use cases where this can effect safety
* @param file The file the function was executed in
* @param line The line number where the function was used
* @return The size of the new destination string or -13 if the src is longer than the given max
*/
extern int copyStr_safe_(char* dest, const char* src, int max, const char* file, int line);

/**
* Overwrites the data in the destination string with the data from the src string
* @param dest The string to overwrite. Must be a fixed string, not dynamic.
* @param src The source string to copy to the destination
* @return The size of the new destination string
*/
extern int copyStr(char* dest, const char* src);


/**
* Overwrites the data in the destination string with the data from the src string. The copyStrDynamic_s macro should be used.
* <p>
* This is safe only in the sense that it will not copy past the given max, but due to dynamic allocation being used,
* when your code is done with the copied string (dest), be sure to call free(dest)!
* </p>
* @param dest The string to overwrite
* @param src The source string to copy to the destination
* @param max The maximum allowed length to copy for use cases where this can effect safety
* @param file The file the function was executed in
* @param line The line number where the function was used
* @return The size of the new destination string or -13 if the src is longer than the given max
*/
extern int copyStrDynamic_safe_(char*& dest, const char* src, int max, const char* file, int line);


/**
* Overwrites the data in the destination string with the data from the src string
* <p>
* Due to dynamic allocation being used, when your code is done with the copied string (dest),
* be sure to call free(dest)!
* </p>
* @param dest The string to overwrite
* @param src The source string to copy to the destination
* @return The size of the new destination string
*/
extern int copyStrDynamic(char*& dest, const char* src);

/**
* Concatenates two C-Style strings with unknown lengths
* @param orig The original C-String
* @param add The C-String to append to orig
*/
extern int concatStr(char* orig, const char* add);

/**
* Concatenates two C-Style strings with unknown lengths
* @param orig The original C-String
* @param add The C-String to append to orig
* @param start The index to start concatenating at
* @param stop The index to stop concatenating at
*/
extern int concatStr(char* orig, const char* add, int start, int stop);

/**
* Concatenates two C-Style strings with unknown lengths
* @param orig The original C-String
* @param add The C-String to append to orig
* @param stop The index to stop concatenating at
*/
extern int concatStr(char* orig, const char* add, int stop);

/**
* Captures a sub string contained within str ranging from [start - (stop - 1)]. Use substr macro
* @param str The string containing the desired sub string
* @param start The beginning index of the sub string, inclusive
* @param stop The ending index of the sub string, exclusive
* @param file The file this function was called in
* @param line The line number of the file this function was called in
* @return The substring, or NULL if either index were out of bounds
*/
extern char* substr_(const char* str, int start, int stop, const char* file, int line);

/**
* Captures a sub string contained within str starting from the given start index. Use substr macro
* @param str The string containing the desired sub string
* @param start The beginning index of the sub string, inclusive
* @param file The file this function was called in
* @param line The line number of the file this function was called in
* @return The substring, or NULL if either index were out of bounds
*/
extern char* substr_(const char* str, int start, const char* file, int line);

/**
* Retrieves the first index where the given character exists
* @param str The string containing the character
* @param c The character to look for
* @return The first index of the character, or an error code (less than 0) if its not found
*/
extern int indexOf(const char* str, char c);

/**
* Retrieves the last index where the given character exists
* @param str The string containing the character
* @param c The character to look for
* @return The last index of the character, or an error code (less than 0) if its not found
*/
extern int lastIndexOf(const char* str, char c);

/**
* Retrieves every index where the given character exists and returns at as an int* (array)
* @param str The string containing the character
* @param c The character to look for
* @return An int* pointing to the array of indices, or NULL if the character is not found
*/
extern int* indicesOf(const char* str, char c);

/**
* Retrieves every index where the given character exists and stores them in an int* (array)
* @param str The string containing the character
* @param c The character to look for
* @param indices The int* to store the indices in
* @return The length of the indices array, or an error code (less than 0) if its not found
*/
extern int indicesOf(const char* str, char c, int*& indices);

#endif //BMD_STRUTIL_H
