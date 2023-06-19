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

#include "../../headers/my_lib/constructors.h"

void string_to_zero(char* string, int length)
{
    for (int i = 0; i < length - 1; i++)
    {
        string[i] = '\0';
    }
}

void array_to_zero(int* array, int length)
{
    for (int i = 0; i < length - 1; i++)
    {
        array[i] = 0;
    }
}

void initialize_int_array(integer_array* array)
{
    array->length = 0;
    array->array = NULL;
}

void initialize_string_and_length(string_and_length* string_and_length)
{
    string_and_length->length = 0;
    string_and_length->string = NULL;
}

void initialize_string_array(string_array* array)
{
    array->length = 0;
    array->array = NULL;
}

void initialize_blocks_node(blocks_node* node)
{
    node->block_id = NULL;
    node->previous = NULL;
    node->next = NULL;
}

void initialize_listnode(listnode* node)
{
    node->node_id = 0;
    node->blocks = NULL;
    node->previous = NULL;
    node->next = NULL;
}

void initialize_node_and_int(node_and_int* node_and_int)
{
    node_and_int->integer = 0;
    node_and_int->node = NULL;
}

void initialize_node_and_string(node_and_string* node_and_string)
{
    node_and_string->string = NULL;
    node_and_string->node = NULL;
}
