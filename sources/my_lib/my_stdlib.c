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

#include "../../headers/my_lib/my_stdlib.h"

int my_atoi(char* string)
{
    if (string == NULL) return 0;
    int i = 0, j = 0;
    int negative = 0;
    int return_value = 0;
    if (string[0] == '-') negative = 1;
    for (i = 0 + negative; string[i] != '\0'; i++)
    {
        if (string[i] < 48 || string[i] > 57)
        {
            return 0;
        }
    }
    j = i - 1;
    for (i = 0 + negative; string[i] != '\0'; i++)
    {
        return_value = return_value + (string[i] - 48) * my_pow(10, j - i);
    }
    if (negative) return -return_value;
    return return_value;
}

// Learns the amount of digits in the number, creates a string of the
// same length, fill it with the digits, and reverses it in the end.
char* my_itoa(int number)
{
    int negative = 0;
    if (number < 0)
    {
        negative = 1;
        number = -number;
    }
    int length = integer_length(number);
    char* string = malloc(sizeof(char) * (length + 1 + negative));
    int i = 0;
    do string[i++] = number % 10 + '0';
    while ((number /= 10) > 0);
    if (negative) string[i++] = '-';
    string[i] = '\0';
    char* temporary_string = string;
    string = reverse_string(string);
    free(temporary_string);
    return string;
}

// A lookup table solution of the problem.
int integer_length(int number)
{
    if (number < 0) number = -number;
    if (number < 10) return 1;
    if (number < 100) return 2;
    if (number < 1000) return 3;
    if (number < 10000) return 4;
    if (number < 100000) return 5;
    return 0;
}
