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

#include "../../headers/my_lib/my_string.h"

char* my_strcat(char* destination, char* source)
{
    if (!destination) return NULL;
    if (!source) return NULL;
    int length = my_strlen(destination);
    int i = 0;
    for (i = 0; source[i] != '\0'; i++)
    {
        destination[length + i] = source[i];
    }
    destination[length + i] = '\0';
    return destination;
}

int my_strlen(char* string)
{
    if (!string) return -1;
    int i = 0;
    for (i = 0; string[i] != '\0'; i++)
    {
        continue;
    }
    return i;
}

int my_strcmp(char* string1, char* string2)
{
    if (string1 == NULL && string2 == NULL) return 0;
    if (string1 == NULL || string2 == NULL) return -1;
    int i = 0;
    for (i = 0; string1[i] != '\0' || string2[i] != '\0'; i++)
    {
        if (string1[i] > string2[i]) return 1;
        if (string1[i] < string2[i]) return 2;
    }
    if (string1[i] == '\0' && string2[i] == '\0') return 0;
    if (string1[i] == '\0') return 2;
    if (string2[i] == '\0') return 1;
    return 0;
}

int my_strncmp(char* string1, char* string2, int length)
{
    if (string1 == NULL && string2 == NULL) return 0;
    if (string1 == NULL || string2 == NULL) return -1;
    int i = 0;
    while (i < length && (string1[i] != '\0' || string2[i] != '\0'))
    {
        if (string1[i] > string2[i]) return 1;
        if (string1[i] < string2[i]) return 2;
        i++;
    }
    return 0;
}

char* my_strcpy(char* destination, char* source)
{
    if (!source || !destination) return NULL;
    int length = my_strlen(source) + 1;
    for (int i = 0; i < length; i++)
    {
        destination[i] = source[i];
    }
    return destination;
}

char* my_strncpy(char* destination, char* source, int length)
{
    if (!source || !destination) return NULL;
    for (int i = 0; i < length; i++)
    {
        destination[i] = source[i];
    }
    return destination;
}

// Creates a new string and writes to it from the end to the beginning
// of the original string.
char* reverse_string(char* input_string)
{
    int length = my_strlen(input_string);
    char* output_string = malloc(sizeof(char) * (length + 1));
    int j = 0;
    for (int i = length - 1; i >= 0; i--)
    {
        output_string[j] = input_string[i];
        j++;
    }
    output_string[length] = '\0';
    return output_string;
}

char* add_char_to_string(char* string, char character)
{
    int old_length = my_strlen(string);
    char* new_string = malloc(sizeof(char) * (old_length + 2));
    for (int i = 0; i < old_length; i++)
    {
        new_string[i] = string[i];
    }
    new_string[old_length] = character;
    new_string[old_length + 1] = '\0';
    return new_string;
}

char* my_memset(char* string, char character, int length)
{
    for (int i = 0; i < length; i++)
    {
        string[i] = character;
    }
    return string;
}

char* my_memcpy(char* destination, char* source, int length)
{
    for (int i = 0; i < length; i++)
    {
        destination[i] = source[i];
    }
    return destination;
}

// Looks up the first position of the delimiter in the string,
// saves the position to an array.
// In the end creates a new compact array and writes the positions to it.
char** my_strtok(char* string, char* delimiter)
{
    if (!string || !delimiter) return NULL;
    int string_length = my_strlen(string);
    int delimiter_length = my_strlen(delimiter);
    int* addresses = malloc(sizeof(int) * string_length);
    array_to_zero(addresses, string_length);
    int address_count = 0;
    char* string_head = string;
    while (string)
    {
        int first_delimiter = my_strspan(string, delimiter);
        if (first_delimiter > 0) string[first_delimiter] = '\0';
        if (first_delimiter != 0 && string[0] != '\0')
        {
            addresses[address_count] = string - string_head;
            address_count++;
        }
        if (first_delimiter < 0) break;
        string += first_delimiter + delimiter_length;
    }
    char** string_array = malloc(sizeof(char*) * (address_count + 1));
    for (int i = 0; i < address_count; i++)
    {
        string_array[i] = &string_head[addresses[i]];
    }
    string_array[address_count] = NULL;
    free(addresses);
    return string_array;
}

// Finds the first character, then checks if the delimiter is fully present.
int my_strspan(char* string, char* delimiter)
{
    int string_length = my_strlen(string);
    int delimiter_length = my_strlen(delimiter);
    for (int i = 0; string[i] != '\0'; i++)
    {
        if (string[i] == delimiter[0])
        {
            int j = 1;
            for (j = 1; (i + j) < string_length && j < delimiter_length; j++)
            {
                if (string[i + j] != delimiter[j])
                {
                    break;
                }
            }
            if (j == delimiter_length)
            {
                return i;
            }
        }
    }
    return -1;
}

char* my_strchr(char* string, char character)
{
    if (!string) return NULL;
    int i = 0;
    for (i = 0; string[i] != '\0'; i++)
    {
        if (string[i] == character) break;
    }
    if (string[i] == '\0') return NULL;
    return string + i;
}
