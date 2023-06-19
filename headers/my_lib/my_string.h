/*Copyright (C) 2023 Timur Timak

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public
License along with this program. If not, see
<https://www.gnu.org/licenses/>. */

#ifndef MY_CURL_HEADERS_MY_LIB_MY_STRING_H_
#define MY_CURL_HEADERS_MY_LIB_MY_STRING_H_

#include <stdlib.h>
#include <stddef.h>

#include "../../headers/my_lib/constructors.h"

// Returns the glued up string or NULL if any of the arguments is NULL.
char* my_strcat(char* first_string, char* second_string);

// Returns the length of a given null terminated string.
int my_strlen(char* string);

// Compares one string to another. Returns 0 if they are equal,
// 1 if ascii codes of the first one are bigger and 2 in the opposite case,
// -1 if one but not both of the arguments are NULL;
// my_strncmp compares only up to the length.
int my_strcmp(char* string1, char* string2);
int my_strncmp(char* string1, char* string2, int length);

// Copies one string to another.
// my_strncpy copies only up to the length.
char* my_strcpy(char* destination, char* source);
char* my_strncpy(char* destination, char* source, int length);

// Reverses the given string.
char* reverse_string(char* string);

// Adds a single character to string.
char* add_char_to_string(char* string, char character);

// Fills the string with the characters up to a length.
char* my_memset(char* string, char character, int length);

// Copies memory byte by byte from the source to the destination.
// Continues to do so for "length" bytes.
char* my_memcpy(char* destination, char* source, int length);

// Returns a NULL terminated array of tokens of the string.
// Non-standard behavior because we can't use static variables.
char** my_strtok(char* string, char* delimiter);

// Finds the first occurence of delimiter in the string.
int my_strspan(char* string, char* delimiter);

// Finds the first occurence of character in the string.
char* my_strchr(char* string, char character);

#endif  // MY_CURL_HEADERS_MY_LIB_MY_STRING_H_
