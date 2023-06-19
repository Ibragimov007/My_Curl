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

#ifndef MY_CURL_HEADERS_MY_LIB_MY_READLINE_H_
#define MY_CURL_HEADERS_MY_LIB_MY_READLINE_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>

#include "../../headers/my_lib/my_string.h"
#include "../../headers/my_lib/constructors.h"

// Linked list structure for the lines read and their lengths.
typedef struct struct_list_node
{
    char* line;
    int line_length;
    struct struct_list_node* next;
} list_node;

// Initializes (or reinitializes) the global variable,
// in order to start reading another file.
void init_my_readline();

// Reads a line from the stream represented by fd and returns
// it into an allocated string.
char* my_readline(int fd);

// Fills the global variable "storage" from the file provided.
int fill_storage(int fd);

// Pushes the stack of a linked list.
int push_list(char* new_line);

// Copies a string from a read() buffer.
char* yank_from_buffer(int new_occurence, int last_occurence, char* buffer);

// Reverses a linked list.
int reverse_list(list_node** head_reference);

// Checks if the line in the global variable "storage" has
// a newline character at the end.
int check_termination(int fd);

// Makes a copy of a linked list node.
list_node* copy_node(list_node* origin_node);

// Concatenates the strings in the nodes given and sums their lengths.
int concatenate_nodes(list_node* origin_node, list_node* target_node);

// Makes all the memory taken up by a linked list free.
int deallocate_list(list_node** head);

#endif  // MY_CURL_HEADERS_MY_LIB_MY_READLINE_H_
