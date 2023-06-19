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

#include "../../headers/my_lib/my_readline.h"

// Number of characters read, glober per the assignment.
int READLINE_READ_SIZE = 512;

// Head of the linked list with the lines read, global to keep the state
// between the calls of the whole subroutine.
list_node* storage = NULL;

// Parks the head at NULL in the end.
int deallocate_list(list_node** head)
{
    list_node* current = *head;
    list_node* next;
    while (current != NULL)
    {
        next = current->next;
        free(current->line);
        free(current);
        current = next;
    }
    *head = NULL;
    return 0;
}

// Storage is filled in my_readline().
void init_my_readline()
{
    if (storage != NULL) deallocate_list(&storage);
    storage = NULL;  // Initialized to NULL.
    READLINE_READ_SIZE = 512;
}

// Makes use of two flag variables, performes various checks on the buffer
// and terminates the returned line with zero
// because malloc provides with more memory than it is asked from it.
char* yank_from_buffer(int new_occurence, int last_occurence, char* buffer)
{
    int line_length = new_occurence - last_occurence;
    int sole_newline = 0;  // It is a bit flag.
    if (line_length == 1)
    {
        sole_newline = 1;
        line_length++;
    }
    char* line = malloc(sizeof(char) * line_length + 1);
    string_to_zero(line, line_length + 1);
    int no_newline = 0;  // bit flag
    if (new_occurence >= READLINE_READ_SIZE) no_newline = 1;
    int read_length = line_length - sole_newline - no_newline;
    for (int i = 0; i < read_length; i++)
    {
        // last_occurence + 1 is at least zero.
        line[i] = buffer[last_occurence + i + 1];
    }
    line[line_length - sole_newline - no_newline] = '\0';
    return line;
}

// Creates a new node, then appends it to the storage.
int push_list(char* new_line)
{
    list_node* new_node = malloc(sizeof(list_node));
    new_node->line = new_line;
    new_node->line_length = my_strlen(new_node->line) + 1;
    new_node->next = storage;
    storage = new_node;
    return 0;
}

// In the beginning, checks if the list has only one node.
int reverse_list(list_node** head_reference)
{
    if ((*head_reference)->next == NULL) return 0;
    list_node* previous = NULL;
    list_node* current = *head_reference;
    list_node* next = NULL;
    while (current != NULL)
    {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    *head_reference = previous;
    return 0;
}

// Reads data from a file to a buffer and determines the boundaries of a line.
int fill_storage(int fd)
{
    char* buffer = malloc(sizeof(char) * READLINE_READ_SIZE);
    string_to_zero(buffer, READLINE_READ_SIZE);
    int read_result = read(fd, buffer, READLINE_READ_SIZE);
    if (read_result <= 0)
    {
        free(buffer);
        return 1;
    }
    // Last occurence of a newline character, has to be negative
    // for malloc, will be incremented by 1 before reading from the buffer.
    int last_occurence = -1;
    for (int i = 0; i < read_result; i++)
    {
        if (buffer[i] == '\n')
        {
            push_list(yank_from_buffer(i, last_occurence, buffer));
            last_occurence = i;
        }
    }
    if (buffer[read_result - 1] != '\n')
    {
        // Assumes there is a newline character later on.
        push_list(yank_from_buffer(read_result, last_occurence, buffer));
    }
    free(buffer);
    reverse_list(&storage);  // The list stack is created upside down.
    return 0;
}

// Chops the end character off the origin_node's line.
int concatenate_nodes(list_node* origin_node, list_node* target_node)
{
    int concatenated_length =
        origin_node->line_length + target_node->line_length - 1;
    char* concatenated_string = malloc(sizeof(char) * concatenated_length);
    for (int i = 0; i < origin_node->line_length - 1; i++)
    {
        concatenated_string[i] = origin_node->line[i];
    }
    for (int i = 0; i < target_node->line_length; i++)
    {
        concatenated_string[origin_node->line_length - 1 + i] =
            target_node->line[i];
    }
    target_node->line_length = concatenated_length;
    free(target_node->line);
    target_node->line = concatenated_string;
    return 0;
}

// Copies the line and its length.
list_node* copy_node(list_node* origin_node)
{
    list_node* target_node = malloc(sizeof(list_node));
    target_node->line_length = origin_node->line_length;
    char* string = malloc(sizeof(char) * origin_node->line_length);
    target_node->line = my_strcpy(string, origin_node->line);
    target_node->next = NULL;
    return target_node;
}

// Creates a reserve copy of a non-terminated line and pre-appends it to
// one with termination,
// end_of_file switch breaks the loop if nothing left to read from the file.
int check_termination(int fd)
{
    bool end_of_file = 0;
    while (!(storage->line[storage->line_length - 2] == '\n' || end_of_file))
    {
        list_node* leftover_node = copy_node(storage);
        free(storage->line);
        free(storage);
        storage = NULL;
        if (fill_storage(fd))
        {
            storage = copy_node(leftover_node);
            end_of_file = 1;
        }
        else
        {
            concatenate_nodes(leftover_node, storage);
        }
        free(leftover_node->line);
        free(leftover_node);
    }
    return 0;
}

// File descriptors are generally in the 0-1023 range
// returns NULL if fd or READLINE_READ_SIZE are wrong,
// no data read from file or no data left in storage
// copies storage node to a temporary node because
// the returned value will be freed in main.
char* my_readline(int fd)
{
    if (fd < 0 || fd > 1023 || READLINE_READ_SIZE <= 0) return NULL;
    if (storage == NULL && fill_storage(fd)) return NULL;
    if (storage == NULL) return NULL;
    check_termination(fd);
    char* string = malloc(sizeof(char) * storage->line_length);
    my_strcpy(string, storage->line);
    if (string[storage->line_length - 2] == '\n')
    {
        string[storage->line_length - 2] = '\0';
    }
    list_node* temporary = storage;
    storage = storage->next;
    free(temporary->line);
    free(temporary);
    return string;
}

/*
// The first argument is the file, the second is the buffer size
// the functions and syscalls used in main are for reviewer's testing
// convenience, and are not a part of the assignment.
int main(int ac, char **av)
{
    ac += 0;
    init_my_readline();
    if (av[1] && av[2]) READLINE_READ_SIZE = atoi(av[2]);
    char* string = NULL;
    int fd = 0;
    if (av[1]) fd = open(av[1], O_RDONLY);
    while ((string = my_readline(fd)) != NULL)
    {
        printf("%s\n", string);
        free(string);
    }
    if (fd) close(fd);
    return 0;
}
*/
