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

#ifndef MY_ZSH_CONSTRUCTORS_H_
#define MY_ZSH_CONSTRUCTORS_H_

#include <stddef.h>

#include "structures.h"

// This library contains constructors for the structures of the project.

// Fills a string with '\0'.
void string_to_zero(char* string, int length);

// Fills an integer array with zeros.
void array_to_zero(int* array, int length);

void initialize_int_array(integer_array* array);

void initialize_string_array(string_array* array);

void initialize_blocks_node(blocks_node* node);

void initialize_listnode(listnode* node);

void initialize_node_and_int(node_and_int* node_and_int);

void initialize_string_and_length(string_and_length* string_and_length);

void initialize_node_and_string(node_and_string* node_and_string);

#endif  // MY_ZSH_CONSTRUCTORS_H_
