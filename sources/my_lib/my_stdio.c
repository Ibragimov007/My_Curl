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

#include "../../headers/my_lib/my_stdio.h"

void my_perror(char* string)
{
    int errno_save = errno;
    write(2, string, my_strlen(string));
    char* string_2 = ": errno equals ";
    write(2, string_2, my_strlen(string_2));
    char* error = my_itoa(errno_save);
    write(2, error, my_strlen(error));
    free(error);
}
