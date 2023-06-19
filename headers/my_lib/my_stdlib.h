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

#ifndef MY_CURL_HEADERS_MY_LIB_MY_STDLIB_H_
#define MY_CURL_HEADERS_MY_LIB_MY_STDLIB_H_

#include <stddef.h>
#include <stdlib.h>

#include "../../headers/my_lib/my_math.h"
#include "../../headers/my_lib/my_string.h"

// Converts a line of ASCII numeral characters to an integer.
// Return 0 on error.

int my_atoi(char* string);

// Returns a given ASCII string representation of an integer number.
char* my_itoa(int number);

// Returns the amount of digits in a number.
int integer_length(int number);

#endif  // MY_CURL_HEADERS_MY_LIB_MY_STDLIB_H_
