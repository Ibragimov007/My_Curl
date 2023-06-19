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

#ifndef MY_CURL_HEADERS_MY_LIB_STRUCTURES_H_
#define MY_CURL_HEADERS_MY_LIB_STRUCTURES_H_

typedef struct struct_integer_array
{
    int length;
    int* array;
} integer_array;

typedef struct struct_string_and_length
{
    char* string;
    int length;
} string_and_length;

typedef struct struct_string_array
{
    char** array;
    int length;
} string_array;

typedef struct struct_blocks_node
{
    char* block_id;
    struct struct_blocks_node* previous;
    struct struct_blocks_node* next;
} blocks_node;

typedef struct struct_listnode
{
    int node_id;
    blocks_node* blocks;
    struct struct_listnode* previous;
    struct struct_listnode* next;
} listnode;

typedef struct struct_node_and_int
{
    listnode* node;
    int integer;
} node_and_int;

typedef struct struct_node_and_string
{
    listnode* node;
    char* string;
} node_and_string;

#endif  // MY_CURL_HEADERS_MY_LIB_STRUCTURES_H_
